#include "BaseGameObject.h"
#include "../Level/BaseLevel.h"
#include "../Component/BaseComponent.h"
#include "../Util/OutputSystem.h"

BaseGameObject::BaseGameObject(BaseLevel* level, const wstring& tag)
	: m_levelArea{level}, m_objectTag(tag), m_x(0), m_y(0)
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


void BaseGameObject::Render(Screen* screen)
{
	for (size_t i = 0; i < m_components.size(); ++i)
	{
		BaseComponent* comp = m_components[i];
		if (comp)
		{
			comp->Render(screen);
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

void BaseGameObject::SetPosition(const int32& x, const int32& y) noexcept
{
	m_x = x;
	m_y = y;
}

void BaseGameObject::SetLevel(BaseLevel* level)
{
	m_levelArea = level;
}

void BaseGameObject::UpdateLevel(BaseLevel* level)
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
