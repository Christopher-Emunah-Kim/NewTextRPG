#pragma once
#include "BaseGameObject.h"

class Player : public BaseGameObject
{
public:
	using BaseGameObject::BaseGameObject;

	virtual void Init() override;
};

