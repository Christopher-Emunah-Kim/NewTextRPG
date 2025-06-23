#include "GameInstance.h"
#include "../Data/PlayerDataTablePerLevel.h"
#include "../Util/OutputSystem.h"
#include "../Level/BaseLevel.h"
#include "../Manager/LevelManager.h"
#include "../Object/Player.h"
#include "../Object/UI/SystemTextDialog.h"
#include "../Object/UI/PlayerInfoDialog.h"


GameInstance::~GameInstance()
{
	Release();
}

void GameInstance::Init()
{
	//m_player = Player();
	//m_bIsPlayerInitialzed = false;
	//m_systemTextDialog = nullptr;
	//m_playerInfoDialog = nullptr;
	m_initialized = true;
}

void GameInstance::Release()
{
	ClearAllStates();
	m_initialized = false;
}

void GameInstance::SaveObjectState(const BaseGameObject* object)
{
	if (nullptr == object)
	{
		return;
	}

	wstring key = object->GetType() + L"_" + object->GetTag();
	m_globalStateCache[key] = object->SerializeStateToString();
}

bool GameInstance::HasSavedState(const wstring& objectType, const wstring& objectTag)
{
	wstring key = objectType + L"_" + objectTag;
	return m_globalStateCache.find(key) != m_globalStateCache.end();
}

wstring GameInstance::GetSavedState(const wstring& objectType, const wstring& objectTag)
{
	wstring key = objectType + L"_" + objectTag;
	unordered_map<wstring, wstring>::const_iterator it = m_globalStateCache.find(key);
	if (it != m_globalStateCache.end())
	{
		return it->second;
	}

	return L" ";
}

void GameInstance::ClearSavedState(const wstring& objectType, const wstring& objectTag)
{
	wstring key = objectType + L"_" + objectTag;
	m_globalStateCache.erase(key);
}

void GameInstance::ClearAllStates()
{
	m_globalStateCache.clear();
	m_gameFlags.clear();
}

//bool GameInstance::IsPlayerInitialzed() const
//{
//	return m_bIsPlayerInitialzed;
//}
//
//void GameInstance::SetPlayerInitialize(bool bIsInitialized)
//{
//	m_bIsPlayerInitialzed = bIsInitialized;
//}

void GameInstance::SetPlayer(BaseGameObject* player)
{
	m_player = player;
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

void GameInstance::AdvanceScenario(const wstring& scenarioKey)
{
}

void GameInstance::SetGameFlag(const wstring& flag, bool value)
{
	m_gameFlags[flag] = value;
}

bool GameInstance::GetGameFlag(const wstring& flag) const
{


	return false;
}

bool GameInstance::LoadSerializedDataFromFile(BaseLevel* level, const wstring& filePath)
{
	return false;
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


	/*if (m_playerInfoDialog == nullptr)
	{
		m_playerInfoDialog = new PlayerInfoDialog(newLevel);
		m_playerInfoDialog->Init();
	}
	else
	{
		m_playerInfoDialog->RegisterPlayerInfoDialogInNewLevel(newLevel);
	}

	UpdatePlayerInfo();*/
}

void GameInstance::SyncObejctsToNewLevel(BaseLevel* oldLevel, BaseLevel* newLevel)
{
}

void GameInstance::ProcessObjectInteraction(const wstring& sourceTag, const wstring& targetTag)
{
}

void GameInstance::ProcessGameEvent(const wstring& eventName)
{
}

//void GameInstance::SetPlayerInfoDialog(PlayerInfoDialog* playerInfoObj)
//{
//	m_playerInfoDialog = playerInfoObj;
//}
//
//void GameInstance::UpdatePlayerInfo()
//{
//	if (nullptr != m_playerInfoDialog)
//	{
//		m_playerInfoDialog->UpdatePlayerInfoDialog(m_player);
//	}
//}
