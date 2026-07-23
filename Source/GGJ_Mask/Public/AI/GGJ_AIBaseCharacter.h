#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "GGJ_AIBaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySeePlayer, float, Percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeath, AActor*, Enemy);

UCLASS()
class GGJ_MASK_API AGGJ_AIBaseCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AGGJ_AIBaseCharacter();
	virtual void OnConstruction(const FTransform& Transform) override;
	FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	void SetGenericTeamId(const FGenericTeamId& teamID) override;
	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BTAsset;
	UPROPERTY(EditAnywhere, Category="AI")
	uint8 AITeamId = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	bool bIsPossessd = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	bool bIsDied = false;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "AI")
	FOnEnemyDeath OnEnemyDeath;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "AI")
	FOnEnemySeePlayer OnEnemySeePlayer;
	UPROPERTY(EditDefaultsOnly, Category = "Spline")
	TObjectPtr<class USplineComponent> SplineComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Spline")
	TArray<FVector> SplinePoints;
};
