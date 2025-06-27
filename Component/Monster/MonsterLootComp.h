#pragma once
#include "../BaseComponent.h"

class MonsterLootComp : public BaseComponent
{
public:
	MonsterLootComp(BaseGameObject* owner);
	virtual ~MonsterLootComp();


	void DropLoot();
};

