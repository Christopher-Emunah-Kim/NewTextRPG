#pragma once
#include "../BaseGameObject.h"
#include "../../Util/Type/CharacterInfo.h"
#include <queue>

constexpr __int32 MAX_LINES = 10;
constexpr __int32 DEFAULT_BASE_Y = SCREEN_HEIGHT - MAX_LINES - 4;
constexpr __int8 LEFT_MARGIN = 3;
constexpr __int8 RIGHT_MARGIN = 4;
constexpr __int8 COMMAND_BLOCK_HEIGHT = 3;
constexpr __int16 PLAYER_UI_BASE_Y = 1;

class Player;
class BaseLevel;
class SystemUIComp;

class HUDUI final : public BaseGameObject
{
public:
	HUDUI(BaseLevel* level);
	virtual ~HUDUI() = default;

private:
	//SystemUIComp* m_UIRenderComp = nullptr;
	queue<wstring> m_textQueue;
	FPlayerInfo m_playerInfo;

private:
	void RenderPlayerInfo(Screen* screen);
	void RenderSystemText(Screen* screen);

public:

	virtual void Init() override;
	virtual void Render(Screen* screen) override;

	void UpdatePlayerInfoDialog(const Player& player);
	void RegisterInNewLevel(BaseLevel* newLevel);

	void SetSystemText(const wstring& text);
	void EnqueueText(const wstring& text);
	void ClearSystemText();
	void UpdatePlayerInfo(const FPlayerInfo& playerInfo);


};

