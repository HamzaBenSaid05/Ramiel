#pragma once

#include "CoreMinimal.h"
#include "GGJ_AIBaseCharacter.h"
#include "GGJ_AIPriestCharacter.generated.h"

UCLASS()
class GGJ_MASK_API AGGJ_AIPriestCharacter : public AGGJ_AIBaseCharacter
{
	GENERATED_BODY()

public:
	AGGJ_AIPriestCharacter();
	void BeginPlay() override;
};
