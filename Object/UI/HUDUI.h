#pragma once
#include "../BaseGameObject.h"

class Player;
class BaseLevel;
class SystemUIComp;

class HUDUI final : public BaseGameObject
{
public:
	HUDUI(BaseLevel* level);
	virtual ~HUDUI() = default;

private:
	SystemUIComp* m_UIRenderComp = nullptr;

public:

	virtual void Init() override;

	void UpdatePlayerInfoDialog(const Player& player);
	void RegisterInNewLevel(BaseLevel* newLevel);

	void SetSystemText(const wstring& text);
	void ClearSystemText();


};

