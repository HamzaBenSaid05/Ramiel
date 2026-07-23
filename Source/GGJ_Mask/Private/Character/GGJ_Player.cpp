#include "Character/GGJ_Player.h"

FGenericTeamId AGGJ_Player::GetGenericTeamId() const { return TeamId; }
void AGGJ_Player::SetGenericTeamId(const FGenericTeamId& teamID) { TeamId = teamID; }
