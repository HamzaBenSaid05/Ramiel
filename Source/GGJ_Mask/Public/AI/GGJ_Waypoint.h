#pragma once

#include "CoreMinimal.h"
#include "GGJ_Waypoint.generated.h"

UCLASS()
class GGJ_MASK_API AGGJ_Waypoint : public AActor
{
	GENERATED_BODY()
public:
	AGGJ_Waypoint();
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USplineComponent> SplineComponent;
	void OnConstruction(const FTransform& Transform) override;
	UPROPERTY(EditDefaultsOnly, Category = "Spline")
	TArray<FVector> SplinePoints;
};