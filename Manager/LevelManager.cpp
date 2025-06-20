#include "LevelManager.h"
#include "../Core/GameInstance.h"
#include "../Level/BaseLevel.h"
#include "../Level/TestLevel.h"
#include "../Level/TitleLevel.h"
#include "../Util/OutputSystem.h"
#include "../Object/Player.h"
#include "../Screen.h"


LevelManager::~LevelManager()
{
	Release();
}


void LevelManager::Init()
{
	m_levels["Test"] = new TestLevel("Test");
	m_levels["Title"] = new TitleLevel("Title");

	m_currentLevel = m_levels["Test"]; //TODO : 이후 Title로 변경

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

	for (unordered_map<string, BaseLevel*>::iterator it = m_levels.begin(); it != m_levels.end(); ++it)
	{
		delete it->second;
	}

	m_levels.clear();
}


bool LevelManager::IsSetNextLevel() const
{
	return m_nextLevel != nullptr;
}

void LevelManager::SetNextLevel(const string& name)
{
	if (m_nextLevel != nullptr)
	{
		OutputSystem::PrintErrorMsg("설정된 NextLevel 이 존재합니다. 새로운 Level 을 설정할 수 없습니다.");
		return;
	}

	unordered_map<string, BaseLevel*>::iterator it = m_levels.find(name);
	if (it == m_levels.end())
	{
		OutputSystem::PrintErrorMsg(name + "라는 이름의 Level 이 존재하지 않습니다.");
		return;
	}

	m_nextLevel = it->second;

}

void LevelManager::ChangeLevel()
{
	if (m_nextLevel)
	{
		Player& player = GameInstance::GetInstance()->GetPlayer();
		BaseGameObject* currentPlayerObject = m_currentLevel->FindObject("Player");


		if (currentPlayerObject && currentPlayerObject == &player)
		{
			m_currentLevel->DetachObject(currentPlayerObject);
		}


		m_currentLevel->Release();
		m_currentLevel = m_nextLevel;
		m_currentLevel->Init();

		player.UpdateLevel(m_currentLevel);

		m_nextLevel = nullptr;
	}
}
