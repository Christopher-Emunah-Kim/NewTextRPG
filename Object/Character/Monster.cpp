#include "Monster.h"

/*#include "../../Component/Monster/MonsterLootComp.h"
#include "../../Component/Monster/MonsterStatusComp.h"
#include "../../Component/Monster/MonsterAIComp.h"*/

Monster::Monster(BaseLevel* level, const wstring& tag)
	:BattleCharacter(level, tag), m_monsterInfo(DEFAULT_LEVEL)
{
	m_monsterInfo.name = tag;
	m_monsterInfo.description = L"야생의 " + tag;
	//TODO 몬스터테이블에서 불러오기
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

	/*if (!HasComponentType<MonsterLootComp>())
	{
		AddComponent(new MonsterLootComp(this));
	}

	if (!HasComponentType<MonsterStatusComp>())
	{
		AddComponent(new MonsterStatusComp(this));
	}

	if (!HasComponentType<MonsterAIComp>())
	{
		AddComponent(new MonsterAIComp(this));
	}*/

	//TODO 랜덤 드롭아이템 세팅

}

void Monster::DropRewards()
{
	/*MonsterLootComp* lootComp = GetComponentsByType<MonsterLootComp>();
	if (lootComp)
	{
		lootComp->DropLoot();
	}*/
}
