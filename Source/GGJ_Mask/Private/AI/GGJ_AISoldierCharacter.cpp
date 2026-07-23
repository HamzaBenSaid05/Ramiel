#include "AI/GGJ_AISoldierCharacter.h"
#include "AI/GGJ_AISoldierController.h"

AGGJ_AISoldierCharacter::AGGJ_AISoldierCharacter() { AIControllerClass = AGGJ_AISoldierController::StaticClass(); }

void AGGJ_AISoldierCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AGGJ_AISoldierController* AIController = Cast<AGGJ_AISoldierController>(GetController()))
	{
		UE_LOG(LogTemp, Log, TEXT(" AIPawnTest AIControllerTest is assigned correctly"));
	}
	else { UE_LOG(LogTemp, Error, TEXT("AIPawnTest AIControllerTest is NOT assigned")); }
	SetGenericTeamId(AITeamId);
}
