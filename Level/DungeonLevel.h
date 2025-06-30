#pragma once
#include "BaseLevel.h"


class HUDUI;

class DungeonLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~DungeonLevel() = default;

private:
	vector<wstring> m_systemTexts;
	HUDUI* m_HUDUI = nullptr;

public:
	virtual void Init() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

private:
	void SetHUDUI();
	void Welcome();
	void EnterStage();
	void BackToVillage();

	void AddText(const wstring& text);
	void ClearText();

};

