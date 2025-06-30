#pragma once
#include "BaseLevel.h"

class HUDUI;

class TitleLevel final : public BaseLevel
{
public:
	TitleLevel(const wstring& tag);
	virtual ~TitleLevel() = default;

private:
	vector<wstring> m_systemTexts;
	HUDUI* m_HUDUI = nullptr;

public:
	virtual void Init() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

private:
	void SetTitleLevel();
	void ProcessTitleMenu();

	void OnEnterVillage();
	void OnEnterDungeon();
	void OnQuitGame();

	void AddText(const wstring& text);
	void ClearText();

};

