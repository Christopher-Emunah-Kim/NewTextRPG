//#include "BaseGameObject.h"
//#include "../Level/BaseLevel.h"
//#include "../Util/OutputSystem.h"
//
//BaseGameObject::BaseGameObject(BaseLevel* level, const wstring& tag)
//	: m_levelArea{level}, m_objectTag(tag)
//{
//	if (m_levelArea)
//	{
//		m_levelArea->AddObject(this);
//	}
//	else
//	{
//		OutputSystem::PrintErrorMsg(L"GameObject가 추가될 Level 이 존재하지 않습니다.");
//	}
//}
//
//BaseGameObject::~BaseGameObject()
//{
//	Release();
//}
//
//void BaseGameObject::Init()
//{
//}
//
//void BaseGameObject::Update()
//{
//}
//
//void BaseGameObject::Render(Screen* screen)
//{
//}
//
//void BaseGameObject::Release()
//{
//}
//
//void BaseGameObject::SetLevelArea(BaseLevel* level)
//{
//	m_levelArea = level;
//}
