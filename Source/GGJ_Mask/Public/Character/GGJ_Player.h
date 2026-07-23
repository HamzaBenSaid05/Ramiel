#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "GGJ_Player.generated.h"

UCLASS()
class GGJ_MASK_API AGGJ_Player : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	FGenericTeamId GetGenericTeamId() const override;
	void SetGenericTeamId(const FGenericTeamId & teamID) override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Team Id")
	uint8 TeamId = 0;
};
