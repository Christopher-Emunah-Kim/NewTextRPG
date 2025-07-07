#include "BaseGameObject.h"
#include "../Level/BaseLevel.h"
#include "../Util/OutputSystem.h"

BaseGameObject::BaseGameObject(BaseLevel* level, const wstring& tag)
	: m_levelArea{level}, m_objectTag(tag)
{
	if (m_levelArea)
	{
		m_levelArea->AddObject(this);
	}
	else
	{
		OutputSystem::PrintErrorMsg(L"GameObject가 추가될 Level 이 존재하지 않습니다.");
	}
}

BaseGameObject::~BaseGameObject()
{
	Release();
}

void BaseGameObject::Init()
{
}

void BaseGameObject::Update()
{
}


void BaseGameObject::Render(Screen* screen)
{
}

void BaseGameObject::Release()
{
}


void BaseGameObject::AddComponent(BaseComponent* component)
{
	m_components.push_back(component);
}

void BaseGameObject::RemoveComponent(BaseComponent* component)
{
	vector<BaseComponent*>::iterator it = remove(m_components.begin(), m_components.end(), component);

	m_components.erase(it, m_components.end());
}

vector<BaseComponent*>& BaseGameObject::GetComponents()
{
	return m_components;
}

void BaseGameObject::SetTag(const wstring& tag) noexcept
{
	m_objectTag = tag;
}


void BaseGameObject::SetLevelArea(BaseLevel* level)
{
	m_levelArea = level;
}

void BaseGameObject::RegisterInLevelArea(BaseLevel* level)
{
	if (m_levelArea && m_levelArea != level)
	{
		m_levelArea->DetachObject(this);
	}

	m_levelArea = level;

	if (m_levelArea)
	{
		m_levelArea->AddObject(this);
	}
}

bool BaseGameObject::IsComponentsEmpty() const
{
	return m_components.empty();
}
