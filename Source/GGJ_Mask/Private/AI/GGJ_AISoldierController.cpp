#include "AI/GGJ_AISoldierController.h"
#include "AI/GGJ_AISoldierCharacter.h"
#include "Interface/GetPossessedState.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

void AGGJ_AISoldierController::BeginPlay()
{
	Super::BeginPlay();
	if (SightCfg) { CachedSightRadius = SightCfg->SightRadius; }
}

AGGJ_AISoldierController::AGGJ_AISoldierController()
{
	HearingCfg = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing CFG"));
	HearingCfg->HearingRange = 2000.f;
	HearingCfg->SetMaxAge(2.f);
	HearingCfg->DetectionByAffiliation.bDetectEnemies = true;
	HearingCfg->DetectionByAffiliation.bDetectFriendlies = true;
	HearingCfg->DetectionByAffiliation.bDetectNeutrals = true;

	Perception->ConfigureSense(*HearingCfg);
}

void AGGJ_AISoldierController::OnTargetPerceptionUpdated(const TArray<AActor*>& updatedActors)
{
	FActorPerceptionBlueprintInfo info;
	for (AActor* updatedActor : updatedActors)
	{
		if (PossessedPawn->GetTeamAttitudeTowards(*updatedActor) == ETeamAttitude::Friendly) continue;

		Perception->GetActorsPerception(updatedActor, info);

		for (const FAIStimulus& stimulus : info.LastSensedStimuli)
		{
			if (stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
			{
				if (stimulus.WasSuccessfullySensed())
				{
					// Target is in the FOV
					CurrentTargetActor = updatedActor;
					bIsInFOV = true;

					// Init transform state when entering the FOV 
					if (updatedActor->Implements<UGetPossessedState>()) { bWasTransformedLastFrame = IGetPossessedState::Execute_IsPossessed(updatedActor); }
				}
				else
				{
					// Target has exit the FOV or is behind a wall
					bIsInFOV = false;
					bSeeingPlayer = false;
					bSawPlayerTransform = false;
					if (updatedActor->Implements<UGetPossessedState>()) { bWasTransformedLastFrame = IGetPossessedState::Execute_IsPossessed(updatedActor); }

					Blackboard->SetValueAsBool("bIsInvestigatePlayer", false);
					Blackboard->SetValueAsBool("bIsInvestigate", true);
					Blackboard->SetValueAsBool("bPlayerSeen", false);
					LastSeenLocation = stimulus.StimulusLocation;
					Blackboard->SetValueAsVector("TargetPosition", LastSeenLocation);
					PossessedPawn->OnEnemySeePlayer.Broadcast(0.f);
					bHasAlertedAllies = false;
				}
			}
			if (stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
			{
				if (stimulus.WasSuccessfullySensed())
				{
					if (!Blackboard->GetValueAsBool("bPlayerSeen"))
					{
						Blackboard->SetValueAsBool("bIsInvestigate", true);
						Blackboard->SetValueAsVector(
							"TargetPosition",
							stimulus.StimulusLocation
						);
					}
				}
			}
		}
	}
}

void AGGJ_AISoldierController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CurrentTargetActor && bIsInFOV)
	{
		bool bShouldDetect = true;
		bool bIsFullyDetected = Blackboard->GetValueAsBool("bPlayerSeen");

		if (CurrentTargetActor->Implements<UGetPossessedState>())
		{
			bool bIsCurrentlyTransformed = IGetPossessedState::Execute_IsPossessed(CurrentTargetActor);
			bool bIsMoving = IGetPossessedState::Execute_IsMoving(CurrentTargetActor);

			// If transformed when is in the FOV, enemy see it 
			if (!bWasTransformedLastFrame && bIsCurrentlyTransformed) { bSawPlayerTransform = true; }

			if (!bIsFullyDetected)
			{
				// If transformed and still, is considered invisible
				if (bIsCurrentlyTransformed && !bIsMoving && !bSawPlayerTransform) { bShouldDetect = false; }
			}

			bWasTransformedLastFrame = bIsCurrentlyTransformed;
		}

		bSeeingPlayer = bShouldDetect;

		if (bSeeingPlayer)
		{
			Blackboard->SetValueAsBool("bIsInvestigatePlayer", true);
			LastSeenLocation = CurrentTargetActor->GetActorLocation();
			Blackboard->SetValueAsVector("TargetPosition", LastSeenLocation);
			Blackboard->SetValueAsObject("Player", CurrentTargetActor);
			Blackboard->SetValueAsBool("bIsInvestigate", false);
		}
	}
	else
	{
		// If is not in FOV, not saw
		bSeeingPlayer = false;
		bHasAlertedAllies = false;
	}

	// Timer logic with multiplier for distance
	if (bSeeingPlayer && CurrentTargetActor)
	{
		// Calculate distance between ai and target
		float Distance = FVector::Dist(PossessedPawn->GetActorLocation(), CurrentTargetActor->GetActorLocation());

		float MaxRange = (CachedSightRadius > 0.f) ? CachedSightRadius : 5000.f;

		float ProximityMultiplier = FMath::GetMappedRangeValueClamped(
		                                                              FVector2D(0.f, MaxRange),
		                                                              FVector2D(MaxDetectionMultiplier, MinDetectionMultiplier),
		                                                              Distance
		                                                             );

		SightAccumulatedTime += DeltaSeconds * ProximityMultiplier;
	}
	else
	{
		// If not saw, the timer will decrease base on the normal lose sight
		SightAccumulatedTime -= DeltaSeconds * LoseDetectionSpeed;
	}

	SightAccumulatedTime = FMath::Clamp(SightAccumulatedTime, 0.f, TimeToDetect);

	const float StealthValue = SightAccumulatedTime / TimeToDetect;
	PossessedPawn->OnEnemySeePlayer.Broadcast(StealthValue);

	if (SightAccumulatedTime >= TimeToDetect)
	{
		Blackboard->SetValueAsBool("bPlayerSeen", true);
		Blackboard->SetValueAsBool("bIsInvestigate", false);
		Blackboard->SetValueAsBool("bIsInvestigatePlayer", false);

		bSawPlayerTransform = false;
		if (!bHasAlertedAllies)
		{
			bHasAlertedAllies = true;

			UAISense_Hearing::ReportNoiseEvent(
			                                   GetWorld(),
			                                   PossessedPawn->GetActorLocation(),
			                                   1.0f,
			                                   PossessedPawn,
			                                   AlertRadius
			                                  );
			DrawDebugSphere(
			                GetWorld(),
			                PossessedPawn->GetActorLocation(),
			                AlertRadius,
			                24,
			                FColor::Red,
			                false,
			                2.0f
			               );
		}
	}
	else if (SightAccumulatedTime <= 0.f)
	{
		Blackboard->SetValueAsBool("bPlayerSeen", false);
		bHasAlertedAllies = false;
	}
}
