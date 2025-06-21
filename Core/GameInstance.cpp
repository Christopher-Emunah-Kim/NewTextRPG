#include "GameInstance.h"
#include "../Data/PlayerDataTablePerLevel.h"
#include "../Util/OutputSystem.h"


void GameInstance::Init()
{
	m_player = Player();
	m_bIsPlayerInitialzed = false;
	m_systemTextDialog = nullptr;
}

bool GameInstance::IsPlayerInitialzed() const
{
	return m_bIsPlayerInitialzed;
}

void GameInstance::SetPlayerInitialize(bool bIsInitialized)
{
	m_bIsPlayerInitialzed = bIsInitialized;
}

void GameInstance::SetSystemTextDialog(SystemTextDialog* dialogObj)
{
	m_systemTextDialog = dialogObj;
}

void GameInstance::DisplaySystemText(const string& text)
{
	if (m_systemTextDialog)
	{
		m_systemTextDialog->SetSystemText(text);
	}
	else
	{
		OutputSystem::PrintErrorMsg("SystemTextDialog is not set.");
	}
}
