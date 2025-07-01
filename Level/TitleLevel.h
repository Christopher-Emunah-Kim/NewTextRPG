#pragma once
#include "BaseLevel.h"

class HUD;

class TitleLevel final : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~TitleLevel() = default;

public:
	virtual void Init() override;

private:
	void SetTitleLevel();
	void ProcessTitleMenu();

	void OnEnterVillage();
	void OnEnterDungeon();
	void OnQuitGame();

};

