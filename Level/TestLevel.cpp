#include "TestLevel.h"
#include "../Object/Player.h"
#include "../Util/InputSystem.h"


void TestLevel::Init()
{
	Player* player = new Player(this, "Player");
	

	BaseLevel::Init();
}

void TestLevel::Update()
{
	BaseLevel::Update();

	
}