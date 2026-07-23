#include "BehaviourTrees/Tasks/BTTask_SetNextWaypoint.h"
#include "AI/GGJ_AISoldierController.h"

UBTTask_SetNextWaypoint::UBTTask_SetNextWaypoint() { NodeName = "Set Next Waypoint"; }

EBTNodeResult::Type UBTTask_SetNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AGGJ_AIBaseController* aiController = Cast<AGGJ_AIBaseController>(OwnerComp.GetAIOwner()))
	{
		aiController->SetBlackBoardNextWaypoint();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
