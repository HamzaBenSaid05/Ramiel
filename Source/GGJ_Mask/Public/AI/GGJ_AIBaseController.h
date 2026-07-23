#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "GGJ_AIBaseController.generated.h"

UCLASS()
class GGJ_MASK_API AGGJ_AIBaseController : public AAIController
{
	GENERATED_BODY()

public:
	AGGJ_AIBaseController();
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAIPerceptionComponent> Perception;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAISenseConfig_Sight> SightCfg;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAISenseConfig_Hearing> HearingCfg;
	void BeginPlay() override;
	UPROPERTY()
	FVector CurrentTarget;
	UPROPERTY()
	int CurrentTargetIndex = 0;
	UPROPERTY()
	TObjectPtr<class AGGJ_AIBaseCharacter> PossessedPawn;
	UFUNCTION(BlueprintCallable)
	virtual void SetBlackBoardNextWaypoint();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI Perception")
	float SigthMaxAge = 1.f;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI|Alert")
	float AlertRadius = 1800.f;
	UPROPERTY()
	TObjectPtr<UBehaviorTree> BTAsset;
	TObjectPtr<UBlackboardComponent> Blackboard;
	UFUNCTION()
	virtual void OnTargetPerceptionUpdated(const TArray<AActor*>& updatedActors);
	void OnPossess(APawn* InPawn) override;
	bool bSeeingPlayer = false;
	TWeakObjectPtr<AActor> Player;
	bool bHasAlertedAllies;
};
