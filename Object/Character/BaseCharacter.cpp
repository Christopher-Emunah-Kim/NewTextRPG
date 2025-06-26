#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(BaseLevel*, const wstring& tag)
	: BaseGameObject(nullptr, tag), m_name(L"Default Character"), m_description(L"description.."), m_characterLevel(1)
{
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::Init()
{

}

void BaseCharacter::SetName(const wstring& name)
{
}

void BaseCharacter::SetDescription(const wstring& desc)
{
}

void BaseCharacter::SetLevel(int16 level)
{
}
