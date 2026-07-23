#include "AI/GGJ_AIBaseController.h"
#include "AI/GGJ_AIBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Interface/GetPossessedState.h"

AGGJ_AIBaseController::AGGJ_AIBaseController()
{
	PrimaryActorTick.bCanEverTick = true;
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SightCfg = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight CFG"));

	SightCfg->SightRadius = 5000.f;
	SightCfg->LoseSightRadius = 5200.f;
	SightCfg->PeripheralVisionAngleDegrees = 90.0f;
	SightCfg->AutoSuccessRangeFromLastSeenLocation = 300.0f;
	SightCfg->DetectionByAffiliation.bDetectEnemies = true;
	SightCfg->DetectionByAffiliation.bDetectFriendlies = false;
	SightCfg->DetectionByAffiliation.bDetectNeutrals = true;
	SightCfg->SetMaxAge(SigthMaxAge);
	SightCfg->AutoSuccessRangeFromLastSeenLocation = 0.f;
	Perception->SetDominantSense(UAISense_Sight::StaticClass());
	Perception->ConfigureSense(*SightCfg);
}

void AGGJ_AIBaseController::BeginPlay()
{
	Super::BeginPlay();
	Perception->OnPerceptionUpdated.AddDynamic(this, &AGGJ_AIBaseController::OnTargetPerceptionUpdated);
}

void AGGJ_AIBaseController::OnTargetPerceptionUpdated(const TArray<AActor*>& updatedActors) {}

void AGGJ_AIBaseController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossessedPawn = Cast<AGGJ_AIBaseCharacter>(InPawn);
	if (PossessedPawn == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("AAIControllerTest AiPawn is nullptr."));
		return;
	}
	if (PossessedPawn->BTAsset)
	{
		BTAsset = PossessedPawn->BTAsset;
		RunBehaviorTree(BTAsset);
	}
	else
		UE_LOG(LogTemp, Log, TEXT("AAIControllerTest BT is null"));
	Blackboard = GetBlackboardComponent();
	if (Blackboard == nullptr) { UE_LOG(LogTemp, Log, TEXT("AAIControllerTest Blackboard is null")); }
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (player == nullptr) { UE_LOG(LogTemp, Log, TEXT("player is null")); }
	Blackboard->SetValueAsObject("Player", player);
	SetBlackBoardNextWaypoint();
}

void AGGJ_AIBaseController::SetBlackBoardNextWaypoint()
{
	CurrentTarget = PossessedPawn->SplinePoints[CurrentTargetIndex];
	Blackboard->SetValueAsVector(TEXT("WaypointLocation"), CurrentTarget);
	//DrawDebugSphere(GetWorld(), CurrentTarget, 100.0f, 12, FColor::Yellow, true);
	CurrentTargetIndex = (CurrentTargetIndex + 1) % (PossessedPawn->SplinePoints.Num());
}
