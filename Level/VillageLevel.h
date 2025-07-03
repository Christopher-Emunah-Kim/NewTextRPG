#pragma once
#include "BaseLevel.h"


class GameInstance;
class Healer;
class Merchant;

class VillageLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~VillageLevel();

	virtual void Init() override;

private:
	void Welcome();
	void OnEnterItemShop();
	void OnBuyItem();
	void BuySelectedItem(int32 itemId);
	void OnSellIItem();
	void OnEnterHealerShop();
	void OnRecoverPlayer();
	void OnExitVillage();

private:
	Healer* m_healer;
	Merchant* m_merchant;
	GameInstance* gi;
	
};

