#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GetPossessedState.generated.h"

UINTERFACE()
class UGetPossessedState : public UInterface
{
	GENERATED_BODY()
};

class GGJ_MASK_API IGetPossessedState
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Possession")
	bool IsPossessed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Possession")
	bool IsMoving();
};
