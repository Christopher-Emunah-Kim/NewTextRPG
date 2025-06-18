#include "LevelManager.h"


LevelManager::~LevelManager()
{
	Release();
}


void LevelManager::Init()
{
	
}

void LevelManager::Update()
{
	//m_currentLevel->Update();
}

void LevelManager::Render()
{

}

void LevelManager::Release()
{
	m_currentLevel = nullptr;
	m_nextLevel = nullptr;


	for (unordered_map<string, BaseLevel*>::iterator it = m_levels.begin(); it != m_levels.end(); ++it)
	{
		delete it->second;
	}

}


bool LevelManager::IsSetNextLevel() const
{
	return false;
}

void LevelManager::SetNextLevel(const string& name)
{
}

void LevelManager::ChangeLevel()
{
}
