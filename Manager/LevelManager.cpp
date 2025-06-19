#include "LevelManager.h"
#include "../Level/BaseLevel.h"
#include "../Level/TestLevel.h"
#include "../Util/OutputSystem.h"


LevelManager::~LevelManager()
{
	Release();
}


void LevelManager::Init()
{
	m_levels["Temp"] = new TestLevel("Temp");

	m_currentLevel = m_levels["Temp"]; //TODO : 이후 Title로 변경
	m_currentLevel->Init();
}

void LevelManager::Update()
{
	m_currentLevel->Update();
}

void LevelManager::Render()
{
	m_currentLevel->Render();
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
	if (m_nextLevel == nullptr)
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

}
