#pragma once
#include "BaseLevel.h"

class HUD;

class TitleLevel final : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	//TitleLevel(const wstring& tag);
	virtual ~TitleLevel() = default;

private:
	/*vector<wstring> m_systemTexts;
	HUD* m_HUDUI = nullptr;*/

public:
	virtual void Init() override;
	//virtual void Render(Screen* screen) override;
	virtual void Release() override;

private:
	void SetTitleLevel();
	void ProcessTitleMenu();

	void OnEnterVillage();
	void OnEnterDungeon();
	void OnQuitGame();

	/*void AddText(const wstring& text);
	void ClearText();*/

};

