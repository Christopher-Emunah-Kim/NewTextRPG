#include "MeshUIComp.h"
#include "../../Screen.h"
#include "../../Object/BaseGameObject.h"

MeshUIComp::MeshUIComp(BaseGameObject* owner, const wstring& renderShape)
	: BaseComponent(owner), m_renderShape(renderShape)
{
}

void MeshUIComp::Render(Screen* screen)
{
	screen->Draw(m_owner->GetX(), m_owner->GetY(), m_renderShape);
}
