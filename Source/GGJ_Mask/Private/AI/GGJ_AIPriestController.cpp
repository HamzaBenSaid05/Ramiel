#include "AI/GGJ_AIPriestController.h"
#include "AI/GGJ_AIPriestCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

AGGJ_AIPriestController::AGGJ_AIPriestController() {}

void AGGJ_AIPriestController::OnTargetPerceptionUpdated(const TArray<AActor*>& updatedActors)
{
	FActorPerceptionBlueprintInfo info;
	for (AActor* updatedActor : updatedActors)
	{
		if (PossessedPawn->GetTeamAttitudeTowards(*updatedActor) == ETeamAttitude::Friendly)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is Friendly"), *updatedActor->GetName());
			continue;
		}
		Perception->GetActorsPerception(updatedActor, info);

		for (const FAIStimulus& stimulus : info.LastSensedStimuli)
		{
			if (stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
			{
				if (stimulus.WasSuccessfullySensed()) 
				{ 
					Blackboard->SetValueAsBool("bPlayerSeen", true); 
				}
				else 
				{
					Blackboard->SetValueAsBool("bPlayerSeen", false);
				}
			}
			
			if (stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
			{
				if (stimulus.WasSuccessfullySensed())
				{
					Blackboard->SetValueAsBool("bPlayerSeen", true);
					Blackboard->SetValueAsObject("Player", updatedActor);
					
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
				else
				{
					Blackboard->SetValueAsBool("bPlayerSeen", false);
					bHasAlertedAllies = false;
				}
			}
		}
	}
}
