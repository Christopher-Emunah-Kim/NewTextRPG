#include "TestLevel.h"
#include "../Object/BaseGameObject.h"
#include "../Object/Player.h"
#include "../Util/InputSystem.h"


void TestLevel::Init()
{
	m_gameObjects.push_back(new Player(this, "Player"));
	

	BaseLevel::Init();
}

void TestLevel::Update()
{
	BaseLevel::Update();

	
}