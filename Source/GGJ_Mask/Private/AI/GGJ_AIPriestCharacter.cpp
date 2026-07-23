#include "AI/GGJ_AIPriestCharacter.h"
#include "AI/GGJ_AIPriestController.h"

AGGJ_AIPriestCharacter::AGGJ_AIPriestCharacter() { AIControllerClass = AGGJ_AIPriestController::StaticClass(); }

void AGGJ_AIPriestCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AGGJ_AIPriestController* AIController = Cast<AGGJ_AIPriestController>(GetController()))
	{
		UE_LOG(LogTemp, Log, TEXT(" AIPawnTest AIControllerTest is assigned correctly"));
	}
	else { UE_LOG(LogTemp, Error, TEXT("AIPawnTest AIControllerTest is NOT assigned")); }
	SetGenericTeamId(AITeamId);
}
