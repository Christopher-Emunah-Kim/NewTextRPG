#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(BaseLevel*, const wstring& tag)
	: BaseGameObject(nullptr, tag), m_characterInfo(DEFAULT_LEVEL)
{
	m_characterInfo.name = tag;
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::Init()
{
	BaseGameObject::Init();
}

void BaseCharacter::SetName(const wstring& name)
{
	m_characterInfo.name = name;
}

void BaseCharacter::SetDescription(const wstring& description)
{
	m_characterInfo.description = description;
}

void BaseCharacter::SetCharacterLevel(int16 level)
{
	m_characterInfo.characterLevel = level;
}
