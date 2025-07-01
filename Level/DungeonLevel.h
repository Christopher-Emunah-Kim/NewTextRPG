#pragma once
#include "BaseLevel.h"


class HUD;
class Monster;
struct Status;

class DungeonLevel : public BaseLevel
{

public:
	using BaseLevel::BaseLevel;
	//DungeonLevel(const wstring& tag);
	virtual ~DungeonLevel() = default;

private:
	/*vector<wstring> m_systemTexts;
	HUD* m_HUDUI = nullptr;*/
	Monster* m_monster = nullptr;


public:
	virtual void Init() override;
	//virtual void Render(Screen* screen) override;
	virtual void Release() override;

private:
	void SetDungeonStage();
	void Welcome();
	void OnEnterStage();
	void OnBackToVillage();
	void OnStartBattle();
	void OnEscape();

	//void AddText(const wstring& text);
	//void ClearText();

};

