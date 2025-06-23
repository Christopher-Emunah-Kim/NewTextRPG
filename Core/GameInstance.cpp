#include "GameInstance.h"
#include "../Data/PlayerDataTablePerLevel.h"
#include "../Util/OutputSystem.h"
#include "../Level/BaseLevel.h"
#include "../Manager/LevelManager.h"


void GameInstance::Init()
{
	m_player = Player();
	m_bIsPlayerInitialzed = false;
	m_systemTextDialog = nullptr;
	m_playerInfoDialog = nullptr;
}

bool GameInstance::IsPlayerInitialzed() const
{
	return m_bIsPlayerInitialzed;
}

void GameInstance::SetPlayerInitialize(bool bIsInitialized)
{
	m_bIsPlayerInitialzed = bIsInitialized;
}

void GameInstance::SetSystemTextDialog(SystemTextDialog* systemDialogObj)
{
	m_systemTextDialog = systemDialogObj;
}

void GameInstance::DisplaySystemText(const wstring& text)
{
	if (m_systemTextDialog == nullptr)
	{
		m_systemTextDialog = new SystemTextDialog(nullptr);
		m_systemTextDialog->Init();

		BaseLevel* currentLevel = LevelManager::GetInstance()->GetCurrentLevel();
		if (currentLevel)
		{
			m_systemTextDialog->RegisterSystemTextInNewLevel(currentLevel);
		}
	}

	m_systemTextDialog->SetSystemText(text);

}

void GameInstance::ChangeLevelAreaSettings(BaseLevel* newLevel)
{
	if (m_systemTextDialog == nullptr)
	{
		m_systemTextDialog = new SystemTextDialog(nullptr);
		m_systemTextDialog->Init();
	}
	else
	{
		m_systemTextDialog->RegisterSystemTextInNewLevel(newLevel);
	}
	DisplaySystemText(L"새로운 레벨(" + newLevel->GetTag() + L")에 진입했습니다.");


	if (m_playerInfoDialog == nullptr)
	{
		m_playerInfoDialog = new PlayerInfoDialog(newLevel);
		m_playerInfoDialog->Init();
	}
	else
	{
		m_playerInfoDialog->RegisterPlayerInfoDialogInNewLevel(newLevel);
	}

	UpdatePlayerInfo();
}

void GameInstance::SetPlayerInfoDialog(PlayerInfoDialog* playerInfoObj)
{
	m_playerInfoDialog = playerInfoObj;
}

void GameInstance::UpdatePlayerInfo()
{
	if (nullptr != m_playerInfoDialog)
	{
		m_playerInfoDialog->UpdatePlayerInfoDialog(m_player);
	}
}
