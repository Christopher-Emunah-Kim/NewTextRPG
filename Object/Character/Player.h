#pragma once  
#include "../BaseGameObject.h"  

class Player final : public BaseGameObject  
{  
public:  
	using BaseGameObject::BaseGameObject;  

	Player() : BaseGameObject(nullptr, L"Player") { }


	virtual void Init() override;  

	void RegisterNewLevelArea(BaseLevel* level);

};
