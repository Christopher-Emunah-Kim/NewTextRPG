#include "BaseLevel.h"
//#include "../Object/BaseGameObject.h"
#include "../Object/Character/BaseCharacter.h"

BaseLevel::BaseLevel(const wstring& tag)
	: m_levelTag(tag)
{

}

BaseLevel::~BaseLevel()
{
	Release();
}

void BaseLevel::Init()
{
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		BaseCharacter* obj = m_gameObjects[i];
		if (obj)
		{
			obj->Init();
		}
	}
}

void BaseLevel::Update()
{
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		BaseCharacter* obj = m_gameObjects[i];
		if (obj)
		{
			obj->Update();
		}
	}
}

void BaseLevel::Render(Screen* screen)
{
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		BaseCharacter* obj = m_gameObjects[i];
		if (obj)
		{
			obj->Render(screen);
		}
	}
}

void BaseLevel::Release()
{
	static bool alreadyReleased = false;
	if (alreadyReleased) return;
	alreadyReleased = true;

	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		BaseCharacter* obj = m_gameObjects[i];
		if (obj)
		{
			if (obj->GetTag() == L"Player")
			{
				continue;
			}

			obj->Release();

			delete obj;
			obj = nullptr;
		}
	}

	m_gameObjects.clear();
}

void BaseLevel::AddObject(BaseCharacter* object)
{
	m_gameObjects.push_back(object);
}

void BaseLevel::DetachObject(BaseCharacter* object)
{
	for (vector<BaseCharacter*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();++it)
	{
		BaseCharacter* obj = *it;

		if (obj == object)
		{
			m_gameObjects.erase(it);
			return;
		}
	}
}

void BaseLevel::RemoveObject(const wstring& tag)
{
	for (vector<BaseCharacter*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)
	{
		BaseCharacter* obj = *it;

		if (obj && obj->GetTag() == tag) 
		{
			obj->Release();
			delete obj;
			obj = nullptr;

			it = m_gameObjects.erase(it);
		}
		else
		{
			++it;
		}
	}
}

BaseCharacter* BaseLevel::FindObject(const wstring& tag)
{
	for (vector<BaseCharacter*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		BaseCharacter* obj = *it;
		if (obj && obj->GetTag() == tag)
		{
			return obj;
		}
	}

	return nullptr;
}
