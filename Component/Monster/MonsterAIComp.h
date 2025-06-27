#pragma once
#include "../BaseComponent.h"

class MonsterAIComp final : public BaseComponent
{
public:
	MonsterAIComp(BaseGameObject* owner);
	virtual ~MonsterAIComp();
};

