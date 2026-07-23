#pragma once

#include "CoreMinimal.h"
#include "GGJ_AIBaseController.h"
#include "GGJ_AISoldierController.generated.h"

UCLASS()
class GGJ_MASK_API AGGJ_AISoldierController : public AGGJ_AIBaseController
{
	GENERATED_BODY()

public:
	AGGJ_AISoldierController();

private:
	UPROPERTY(EditDefaultsOnly, Category="AI Perception")
	float LoseDetectionSpeed = 1.0f;
	virtual void OnTargetPerceptionUpdated(const TArray<AActor*>& updatedActors) override;
	UPROPERTY()
	FVector LastSeenLocation;
	UPROPERTY()
	float LastSeenTime = -1;
	UPROPERTY()
	FVector LastHeardLocation;
	UPROPERTY()
	float LastHeardTime = -1;
	float SightAccumulatedTime = 0.f;
	float CachedSightRadius;
	UPROPERTY()
	AActor* CurrentTargetActor = nullptr;
	bool bIsInFOV = false;
	bool bSawPlayerTransform = false;
	bool bWasTransformedLastFrame = false;
	UPROPERTY(EditDefaultsOnly, Category="AI|TimerDetect")
	float TimeToDetect = 1.0f;
	UPROPERTY(EditAnywhere, Category = "AI|TimerDetect")
	float MaxDetectionMultiplier = 4.0f;
	UPROPERTY(EditAnywhere, Category = "AI|TimerDetect")
	float MinDetectionMultiplier = 1.0f;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
