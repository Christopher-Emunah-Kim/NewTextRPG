﻿#include "BaseCharacter.h"
#include "../Level/BaseLevel.h"
#include "../Core/GameInstance.h"

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
		GameInstance::GetInstance()->WriteLine(L"[오류] BaseCharacter가 추가될 Level이 존재하지 않습니다.");
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
