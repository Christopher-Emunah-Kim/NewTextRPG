#include "BaseCharacter.h"
#include "../../Level/BaseLevel.h"

BaseCharacter::BaseCharacter(BaseLevel* level, const wstring& tag)
	: m_levelArea(level), m_characterTag(tag), m_characterInfo(DEFAULT_LEVEL)
{
	m_characterInfo.name = tag;

	if (m_levelArea)
	{
		m_levelArea->AddObject(this);
	}
	else
	{
		throw runtime_error("BaseCharacter가 추가될 Level 이 존재하지 않습니다.");
	}
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::Init()
{
}

void BaseCharacter::Update()
{
}

void BaseCharacter::Render(Screen* screen)
{
}

void BaseCharacter::Release()
{
}

void BaseCharacter::SetLevelArea(BaseLevel* level)
{
	m_levelArea = level;
}
