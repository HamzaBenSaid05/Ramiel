#pragma once

#include "CoreMinimal.h"
#include "GGJ_AIBaseController.h"
#include "GGJ_AIPriestController.generated.h"

UCLASS()
class GGJ_MASK_API AGGJ_AIPriestController : public AGGJ_AIBaseController
{
	GENERATED_BODY()

public:
	AGGJ_AIPriestController();

private:
	virtual void OnTargetPerceptionUpdated(const TArray<AActor*>& updatedActors) override;
};
