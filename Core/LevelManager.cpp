#include "LevelManager.h"
#include "../Core/GameInstance.h"
#include "../Util/OutputSystem.h"
#include "../Level/BaseLevel.h"
#include "../Level/TitleLevel.h"
#include "../Level/DungeonLevel.h"
#include "../Level/VillageLevel.h"
#include "../Object/Character/Player.h"
#include "../Screen.h"



LevelManager::~LevelManager()
{
	Release();
}


void LevelManager::Init()
{
	m_levels[L"Title"] = new TitleLevel(L"Title");
	m_levels[L"Dungeon"] = new DungeonLevel(L"Dungeon");
	m_levels[L"Village"] = new VillageLevel(L"Village");

	m_currentLevel = m_levels[L"Title"];
	GameInstance::GetInstance()->UpdateLevelName(m_currentLevel->GetTag());

	InitializePlayer();

	m_currentLevel->Init();
}

void LevelManager::Update()
{
	if (IsSetNextLevel())
	{
		ChangeLevel();
	}
	m_currentLevel->Update();
}

void LevelManager::Render(Screen* screen)
{
	m_currentLevel->Render(screen);
}

void LevelManager::Release()
{
	if (m_currentLevel)
	{
		m_currentLevel->Release();

		m_currentLevel = nullptr;
	}

	m_nextLevel = nullptr;

	for (unordered_map<wstring, BaseLevel*>::iterator it = m_levels.begin(); it != m_levels.end(); ++it)
	{
		delete it->second;
	}

	m_levels.clear();
}


void LevelManager::InitializePlayer()
{
	Player& player = GameInstance::GetInstance()->GetPlayer();
	player.SetLevelArea(m_currentLevel);

	if (m_currentLevel->FindObject(L"Player") == nullptr)
	{
		m_currentLevel->AddObject(&player);
	}

	if (player.IsComponentsEmpty())
	{
		player.Init();
	}

	GameInstance* gi = GameInstance::GetInstance();
	gi->UpdateLevelName(m_currentLevel->GetTag());
	gi->UpdatePlayerName(player.GetPlayerInfo().name);
	gi->UpdatePlayerLevel(player.GetCharacterLevel());
	gi->UpdatePlayerHealth(player.GetHealth());
	gi->UpdatePlayerStatus(player.GetPlayerInfo().status);
	gi->UpdatePlayerGold(player.GetGold());
	gi->UpdateEquippedItem(L"없음", EItemType::Weapon);
	gi->UpdateEquippedItem(L"없음", EItemType::Armor);
	gi->UpdateInvetoryItems({ L"없음" });

}


bool LevelManager::IsSetNextLevel() const
{
	return m_nextLevel != nullptr;
}

void LevelManager::SetNextLevel(const wstring& name)
{
	if (m_nextLevel != nullptr)
	{
		OutputSystem::PrintErrorMsg(L"설정된 NextLevel 이 존재합니다. 새로운 Level 을 설정할 수 없습니다.");
		return;
	}

	unordered_map<wstring, BaseLevel*>::iterator it = m_levels.find(name);
	if (it == m_levels.end())
	{
		OutputSystem::PrintErrorMsg(name + L"라는 이름의 Level 이 존재하지 않습니다.");
		return;
	}

	m_nextLevel = it->second;

}

void LevelManager::ChangeLevel()
{
	if (m_nextLevel)
	{
		Player& player = GameInstance::GetInstance()->GetPlayer();
		m_currentLevel->DetachObject(&player);  

		m_currentLevel->Release();
		m_currentLevel = m_nextLevel;
		GameInstance::GetInstance()->UpdateLevelName(m_currentLevel->GetTag());

		player.RegisterNewLevelArea(m_currentLevel);

		m_currentLevel->Init();
		m_nextLevel = nullptr;
	}
}
