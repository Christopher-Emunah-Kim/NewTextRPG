#include "GameInstance.h"
#include "../Data/PlayerDataTablePerLevel.h"


void GameInstance::Init()
{
	m_player = Player();
	m_bIsPlayerInitialzed = false;
}

bool GameInstance::IsPlayerInitialzed() const
{
	return m_bIsPlayerInitialzed;
}

void GameInstance::SetPlayerInitialize(bool bIsInitialized)
{
	m_bIsPlayerInitialzed = bIsInitialized;
}
