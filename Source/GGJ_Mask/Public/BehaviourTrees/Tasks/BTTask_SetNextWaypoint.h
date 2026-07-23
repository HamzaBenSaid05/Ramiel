#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetNextWaypoint.generated.h"

UCLASS()
class GGJ_MASK_API UBTTask_SetNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_SetNextWaypoint();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
