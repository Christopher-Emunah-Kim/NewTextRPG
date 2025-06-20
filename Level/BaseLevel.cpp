#include "BaseLevel.h"
#include "../Object/BaseGameObject.h"

BaseLevel::BaseLevel(const string& tag)
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
		BaseGameObject* obj = m_gameObjects[i];
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
		BaseGameObject* obj = m_gameObjects[i];
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
		BaseGameObject* obj = m_gameObjects[i];
		if (obj)
		{
			obj->Render(screen);
		}
	}
}

void BaseLevel::Release()
{
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		BaseGameObject* obj = m_gameObjects[i];
		if (obj)
		{
			obj->Release();

			delete obj;
			obj = nullptr;
		}
	}

	m_gameObjects.clear();
}

void BaseLevel::AddObject(BaseGameObject* object)
{
	m_gameObjects.push_back(object);
}

void BaseLevel::DetachObject(BaseGameObject* object)
{
	for (vector<BaseGameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();++it)
	{
		BaseGameObject* obj = *it;

		if (obj == object)
		{
			m_gameObjects.erase(it);
			return;
		}
	}
}

void BaseLevel::RemoveObject(const string& tag)
{
	for (vector<BaseGameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)
	{
		BaseGameObject* obj = *it;

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

BaseGameObject* BaseLevel::FindObject(const string& tag)
{
	for (vector<BaseGameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		BaseGameObject* obj = *it;
		if (obj && obj->GetTag() == tag)
		{
			return obj;
		}
	}

	return nullptr;
}
