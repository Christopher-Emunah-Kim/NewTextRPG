#pragma once
#include "BaseLevel.h"

class GameInstance;

class TitleLevel final : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~TitleLevel() = default;

	virtual void Init() override;

private:
	void SetTitleLevel();
	void ShowTitleMenu();

	void OnEnterVillage();
	void OnEnterDungeon();
	void OnQuitGame();

private:
	GameInstance* gi;
};

