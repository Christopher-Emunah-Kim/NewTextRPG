#include "LevelManager.h"
#include "../Core/GameInstance.h"
#include "../Util/OutputSystem.h"
#include "../Level/BaseLevel.h"
#include "../Level/TitleLevel.h"
#include "../Level/DungeonLevel.h"
#include "../Screen.h"



LevelManager::~LevelManager()
{
	Release();
}


void LevelManager::Init()
{
	m_levels[L"Title"] = new TitleLevel(L"Title");
	m_levels[L"Dungeon"] = new DungeonLevel(L"Dungeon");

	m_currentLevel = m_levels[L"Title"];


	m_currentLevel->Init();
}

void LevelManager::Update()
{
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
		//BaseGameObject* currentPlayerObject = m_currentLevel->FindObject(L"Player");
		//m_currentLevel->DetachObject(currentPlayerObject);

		m_currentLevel->Release();
		m_currentLevel = m_nextLevel;
		GameInstance::GetInstance()->UpdateLevelName(m_currentLevel->GetTag());
		m_currentLevel->Init();

		m_nextLevel = nullptr;
	}
}
