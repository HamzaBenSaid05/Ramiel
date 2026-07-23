#include "AI/GGJ_AIBaseCharacter.h"
#include "AI/GGJ_AIPriestController.h"
#include "Components/SplineComponent.h"

AGGJ_AIBaseCharacter::AGGJ_AIBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplineComponent->SetUsingAbsoluteLocation(true);
	SplineComponent->SetUsingAbsoluteRotation(true);
	SplineComponent->SetUsingAbsoluteScale(true);}

void AGGJ_AIBaseCharacter::OnConstruction(const FTransform& Transform)
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

void AGGJ_AIBaseCharacter::SetGenericTeamId(const FGenericTeamId& teamID) { AITeamId = teamID; }

ETeamAttitude::Type AGGJ_AIBaseCharacter::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* otherTeamAgent = Cast<IGenericTeamAgentInterface>(&Other);
	if (!otherTeamAgent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Is Neutral"));
		return ETeamAttitude::Neutral;
	}

	uint8 otherTeam = otherTeamAgent->GetGenericTeamId().GetId();

	if (AITeamId == otherTeam)
	{
		UE_LOG(LogTemp, Warning, TEXT("Is Friendly"));
		return ETeamAttitude::Friendly;
	}

	UE_LOG(LogTemp, Warning, TEXT("Is Hostile"));
	return ETeamAttitude::Hostile;
}

FGenericTeamId AGGJ_AIBaseCharacter::GetGenericTeamId() const { return AITeamId; }
