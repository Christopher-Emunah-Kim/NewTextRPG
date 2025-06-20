#include "RendererComp.h"
#include "../Object/BaseGameObject.h"
#include "../Screen.h"


RendererComp::RendererComp(BaseGameObject* owner, const string& renderShape)
	: BaseComponent(owner), m_renderShape(renderShape)
{
}

void RendererComp::Render(Screen* screen)
{
	screen->Draw(m_owner->GetX(), m_owner->GetY(), m_renderShape);
}
