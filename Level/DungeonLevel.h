#pragma once
#include "BaseLevel.h"


class HUDUI;
class Monster;
struct Status;

class DungeonLevel : public BaseLevel
{

public:
	DungeonLevel(const wstring& tag);
	virtual ~DungeonLevel() = default;

private:
	vector<wstring> m_systemTexts;
	HUDUI* m_HUDUI = nullptr;
	Monster* m_monster;


public:
	virtual void Init() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	void AddText(const wstring& text);
private:
	void SetDungeonStage();
	void Welcome();
	void OnEnterStage();
	void OnBackToVillage();
	void OnStartBattle();
	void OnEscape();

	void ClearText();

};

