#include "BehaviourTrees/Tasks/BTTask_ResetInvestigate.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ResetInvestigate::UBTTask_ResetInvestigate() { NodeName = "Reset Investigate"; }

EBTNodeResult::Type UBTTask_ResetInvestigate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* aiController = OwnerComp.GetAIOwner();
	UBlackboardComponent* blackboardComp = aiController->GetBlackboardComponent();
	blackboardComp->SetValueAsBool(InvestigateKey.SelectedKeyName, false);
	return EBTNodeResult::Succeeded;
}
