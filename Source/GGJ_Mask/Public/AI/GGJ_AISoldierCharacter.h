#pragma once

#include "GGJ_AIBaseCharacter.h"
#include "GGJ_AISoldierCharacter.generated.h"

UCLASS()
class GGJ_MASK_API AGGJ_AISoldierCharacter : public AGGJ_AIBaseCharacter
{
	GENERATED_BODY()

public:
	AGGJ_AISoldierCharacter();
	void BeginPlay() override;
};
