#include "GameInstance.h"
#include "../Data/PlayerDataTablePerLevel.h"
#include "../Util/OutputSystem.h"
#include "../Level/BaseLevel.h"
#include "../Manager/LevelManager.h"


void GameInstance::Init()
{
	m_player = Player();
	m_bIsPlayerInitialzed = false;
	//m_systemTextDialog = nullptr;
	m_HUDUI = nullptr;

}

bool GameInstance::IsPlayerInitialzed() const
{
	return m_bIsPlayerInitialzed;
}

void GameInstance::SetPlayerInitialize(bool bIsInitialized)
{
	m_bIsPlayerInitialzed = bIsInitialized;
}

//void GameInstance::SetSystemTextDialog(SystemTextDialog* systemDialogObj)
//{
//	if (systemDialogObj != nullptr)
//	{
//		m_systemTextDialog = systemDialogObj;
//	}
//}

void GameInstance::SetHUDUI(HUDUI* hudUI)
{
	if (hudUI != nullptr)
	{
		m_HUDUI = hudUI;

	}
}

void GameInstance::DisplaySystemText(const wstring& text)
{
	if (m_HUDUI != nullptr)
	{
		BaseLevel* currentLevel = LevelManager::GetInstance()->GetCurrentLevel();
		if (currentLevel)
		{
			m_HUDUI->RegisterInNewLevel(currentLevel);
		}

		m_HUDUI->SetSystemText(text);
	}
}

void GameInstance::ChangeLevelAreaSettings(BaseLevel* newLevel)
{
	if (m_HUDUI != nullptr)
	{
		m_HUDUI->RegisterInNewLevel(newLevel);

		DisplaySystemText(L"새로운 레벨(" + newLevel->GetTag() + L")에 진입했습니다.");

		UpdatePlayerInfo();
	}
}



void GameInstance::UpdatePlayerInfo()
{
	if (m_HUDUI != nullptr)
	{
		m_HUDUI->UpdatePlayerInfoDialog(m_player);
	}
}
