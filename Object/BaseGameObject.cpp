#include "BaseGameObject.h"
#include "../Level/BaseLevel.h"
#include "../Component/BaseComponent.h"

BaseGameObject::BaseGameObject(BaseLevel* level, const string& tag)
	: m_level{level}, m_objectTag(tag)
{
	m_level->AddObject(this);
}

BaseGameObject::~BaseGameObject()
{
	Release();
}

void BaseGameObject::Init()
{
	for (size_t i = 0; i < m_components.size(); ++i)
	{
		BaseComponent* comp = m_components[i];
		if (comp)
		{
			comp->Init();
		}
	}
}

void BaseGameObject::Update()
{
	for (size_t i = 0; i < m_components.size(); ++i)
	{
		BaseComponent* comp = m_components[i];
		if (comp)
		{
			comp->Update();
		}
	}
}


void BaseGameObject::Render()
{
	for (size_t i = 0; i < m_components.size(); ++i)
	{
		BaseComponent* comp = m_components[i];
		if (comp)
		{
			comp->Render();
		}
	}
}

void BaseGameObject::Release()
{
	for (size_t i = 0; i < m_components.size(); ++i)
	{
		BaseComponent* comp = m_components[i];
		if (comp)
		{
			comp->Release();

			delete comp;
			comp = nullptr;
		}
	}
}


void BaseGameObject::AddComponent(BaseComponent* component)
{
	m_components.push_back(component);

	sort(m_components.begin(), m_components.end(),
		[](const BaseComponent* left, const BaseComponent* right) {
			return left->GetOrder() < right->GetOrder();
		});
}

void BaseGameObject::RemoveComponent(BaseComponent* component)
{
	remove(m_components.begin(), m_components.end(), component);
}

vector<BaseComponent*>& BaseGameObject::GetComponents()
{
	return m_components;
}
