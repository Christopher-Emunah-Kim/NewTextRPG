#include "GameInstance.h"
#include "../Data/PlayerDataTablePerLevel.h"
#include "../Util/OutputSystem.h"
#include "../Level/BaseLevel.h"


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

void GameInstance::DisplaySystemText(const wstring& text)
{
	if (m_systemTextDialog)
	{
		m_systemTextDialog->SetSystemText(text);
	}
	else
	{
		OutputSystem::PrintErrorMsg(L"SystemTextDialog is not set.");
	}
}

void GameInstance::ChangeLevelAreaSettings(BaseLevel* newLevel)
{
	if (m_systemTextDialog == nullptr)
	{
		m_systemTextDialog = new SystemTextDialog(nullptr);
		m_systemTextDialog->Init();
	}

	if (m_systemTextDialog && newLevel)
	{
		m_systemTextDialog->RegisterSystemTextInNewLevel(newLevel);

		DisplaySystemText(L"새로운 레벨(" + newLevel->GetTag() + L")에 진입했습니다.");
	}
}
