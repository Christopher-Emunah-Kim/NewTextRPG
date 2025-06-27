#pragma once
#include "../BaseComponent.h"

class MonsterStatusComp : public BaseComponent
{
public:
	MonsterStatusComp(BaseGameObject* owner);
	virtual ~MonsterStatusComp();
};

