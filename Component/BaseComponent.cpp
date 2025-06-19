#include "BaseComponent.h"
#include "../Object/BaseGameObject.h"

BaseComponent::BaseComponent(BaseGameObject* owner, int32 order)
	: m_owner{ owner }, m_componentOrder{ order }
{
	m_owner->AddComponent(this);
}

BaseComponent::~BaseComponent()
{
	m_owner->RemoveComponent(this);
	m_owner = nullptr;
}

void BaseComponent::Init()
{

}


void BaseComponent::Update()
{

}

void BaseComponent::Render()
{

}

void BaseComponent::Release()
{

}

int32 BaseComponent::GetOrder() const
{
	return m_componentOrder;
}
