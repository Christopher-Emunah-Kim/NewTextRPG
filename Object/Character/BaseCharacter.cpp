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
