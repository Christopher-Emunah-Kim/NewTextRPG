#include "Monster.h"

Monster::Monster(BaseLevel* level, const wstring& tag)
	:BattleCharacter(level, tag), m_monsterInfo(DEFAULT_LEVEL)
{
	m_monsterInfo.name = tag;
	m_monsterInfo.description = L"야생의 " + tag;
}

Monster::Monster(BaseLevel* level, const wstring& tag, const FMonsterInfo& info)
	:BattleCharacter(level, tag), m_monsterInfo(info)
{
	m_monsterInfo.name = tag;
	m_monsterInfo.description = L"야생의 " + tag;
	m_battleCharacterInfo = info;
}

Monster::~Monster()
{
}

void Monster::Init()
{
	BattleCharacter::Init();


}

