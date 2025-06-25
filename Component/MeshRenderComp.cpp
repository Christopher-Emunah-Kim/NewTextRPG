#include "MeshRenderComp.h"
#include "../Object/BaseGameObject.h"
#include "../Screen.h"


MeshRenderComp::MeshRenderComp(BaseGameObject* owner, const wstring& renderShape)
	: BaseComponent(owner), m_renderShape(renderShape)
{
}

void MeshRenderComp::Render(Screen* screen)
{
	screen->Draw(m_owner->GetX(), m_owner->GetY(), m_renderShape);
}
