#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ResetInvestigate.generated.h"

UCLASS()
class GGJ_MASK_API UBTTask_ResetInvestigate : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_ResetInvestigate();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, Category = "Task")
	FBlackboardKeySelector InvestigateKey;
};
