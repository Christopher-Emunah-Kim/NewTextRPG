#pragma once
#include "BaseComponent.h"
#include "../Object/Character/BattleCharacter.h"


class BattleComponent final : public BaseComponent
{
public:
	BattleComponent(BaseGameObject* owner, int32 order = 0);
	virtual ~BattleComponent();

private:
	BattleCharacter* m_owner;
	BattleCharacter* m_currentTarget;
	bool m_bIsBattleActive;
	bool m_bIsPlayerTurn;

public:
	void InitiateBattle(BattleCharacter* target);
	void EndBattle();
	void ProcessBattleTurn();

	bool DetermineFirstAttacker();
	void ExecuteAttack();
	bool CheckBattleEnd();
	void HandleBattleRewards();

	bool IsBattleActive() const noexcept { return m_bIsBattleActive; }
	bool IsPlayerTurn() const noexcept { return m_bIsPlayerTurn; }
	BattleCharacter* GetCurrentTarget() const { return m_currentTarget; }
};

