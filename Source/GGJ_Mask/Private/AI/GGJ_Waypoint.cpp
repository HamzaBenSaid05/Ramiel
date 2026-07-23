#include "AI/GGJ_Waypoint.h"
#include "Components/SplineComponent.h"
#include "DrawDebugHelpers.h"

AGGJ_Waypoint::AGGJ_Waypoint() { SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline")); }

void AGGJ_Waypoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SplinePoints.Empty();
	int numPoints = SplineComponent->GetNumberOfSplinePoints();
	for (int i = 0; i < numPoints; i++)
	{
		FVector splinePointLocation = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		SplinePoints.Add(splinePointLocation);
	}
}
