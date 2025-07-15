#include "BaseLevel.h"
#include "../Character/BaseCharacter.h"

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
		IBehavior* obj = m_gameObjects[i];
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
		IBehavior* obj = m_gameObjects[i];
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
		IBehavior* obj = m_gameObjects[i];
		if (obj)
		{
			obj->Render(screen);
		}
	}
}

void BaseLevel::Release()
{
	if (bIsReleased)
	{
		return;
	}
	bIsReleased = true;


	for (vector<IBehavior*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); )
	{
		IBehavior* obj = *it;
		if (obj)
		{
			BaseCharacter* character = dynamic_cast<BaseCharacter*>(obj);
			if (character && character->GetTag() == L"Player")
			{
				it = m_gameObjects.erase(it);
				continue;
			}

			obj->Release();
			delete obj;
		}
		it = m_gameObjects.erase(it);
	}
}

void BaseLevel::AddObject(IBehavior* object)
{
	m_gameObjects.push_back(object);
}

void BaseLevel::DetachObject(IBehavior* object)
{
	for (vector<IBehavior*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();++it)
	{
		IBehavior* obj = *it;

		if (obj == object)
		{
			m_gameObjects.erase(it);
			return;
		}
	}
}

