#pragma once
#include "../BaseComponent.h"
#include "../../Util/Type/PlayerInfo.h"
#include <queue>

constexpr __int32 MAX_LINES = 10;
constexpr __int32 DEFAULT_BASE_Y = SCREEN_HEIGHT - MAX_LINES - 1;
constexpr __int8 LEFT_MARGIN = 4;
constexpr __int16 PLAYER_UI_BASE_Y = 10;

class SystemUIComp : public BaseComponent
{
public:
	SystemUIComp(BaseGameObject* owner);
	virtual ~SystemUIComp() = default;

private:
	queue<wstring> m_textQueue;
	FPlayerInfo m_playerInfo;

public:
	virtual void Render(Screen* screen) override;

	void SetText(const wstring& text);
	void EnqueueText(const wstring& text);
	void ClearTexts();

	void UpdatePlayerInfo(const FPlayerInfo& playerInfo);

private:
	void RenderPlayerInfo(Screen* screen);
	void RenderSystemText(Screen* screen);

};

