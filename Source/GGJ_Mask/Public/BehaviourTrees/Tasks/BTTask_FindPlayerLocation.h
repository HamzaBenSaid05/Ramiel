#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPlayerLocation.generated.h"

UCLASS()
class GGJ_MASK_API UBTTask_FindPlayerLocation : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_FindPlayerLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, Category = "Task")
	FBlackboardKeySelector TargetLocationKey;
	UPROPERTY(EditAnywhere, Category = "Task")
	FBlackboardKeySelector PlayerKey;
};
