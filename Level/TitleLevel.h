#pragma once
#include "BaseLevel.h"

class InputSystem;
class Player;
class HUDUI;

class TitleLevel final : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~TitleLevel() = default;

private:
	//Player* m_player = nullptr;
	vector<wstring> m_systemTexts;
	HUDUI* m_HUDUI = nullptr;

public:
	virtual void Init() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	//void ProcessTitleMenuInput();

	void Welcome();
	void EnterVillage();
	void EnterDungeon();
	void GoToHell();

	void AddText(const wstring& text);
	void ClearText();
};

