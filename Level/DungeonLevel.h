#pragma once
#include "BaseLevel.h"


class HUDUI;
struct Status;

class DungeonLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~DungeonLevel() = default;

private:
	vector<wstring> m_systemTexts;
	HUDUI* m_HUDUI = nullptr;


	wstring currentMonsterName;
	Status currentMonsterStatus;

public:
	virtual void Init() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

private:
	void SetHUDUI();
	void SetDungeonStage();
	void Welcome();
	void EnterStage();
	void BackToVillage();
	void StartBattle();
	void RunToEnterance();
	bool DeicdeFirstAttacker();

	void AddText(const wstring& text);
	void ClearText();

};

