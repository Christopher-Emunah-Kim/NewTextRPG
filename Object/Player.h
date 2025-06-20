#pragma once  
#include "BaseGameObject.h"  

class Player : public BaseGameObject  
{  
public:  
	using BaseGameObject::BaseGameObject;  

	Player() : BaseGameObject(nullptr, "Player") { }  


	virtual void Init() override;  

	void UpdateLevel(BaseLevel* level);

};
