#include "BehaviourTrees/Tasks/BTTask_FindPlayerLocation.h"
#include "AI/GGJ_AISoldierController.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation() { NodeName = "Find Player Location"; }

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGGJ_AISoldierController* aiController = Cast<AGGJ_AISoldierController>(OwnerComp.GetAIOwner());
	if (!aiController)
		return EBTNodeResult::Failed;
	UBlackboardComponent* blackboardComp = aiController->GetBlackboardComponent();
	AActor* playerActor = Cast<AActor>(blackboardComp->GetValueAsObject(PlayerKey.SelectedKeyName));
	blackboardComp->SetValueAsVector(TargetLocationKey.SelectedKeyName, playerActor->GetActorLocation());
	return EBTNodeResult::Succeeded;
}
