#pragma once
#include "BaseLevel.h"

constexpr __int32 HEALER_COST = 100;

class GameInstance;

class VillageLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~VillageLevel() = default;

	virtual void Init() override;

private:
	void Welcome();
	void OnEnterItemShop();
	void OnBuyItem();
	void BuySelectedItem(const wstring& itemName);
	void OnSellIItem();
	void OnEnterHealerShop();
	void OnRecoverPlayer();
	void OnExitVillage();

private:
	int32 healerCost;
	GameInstance* gi;
};

