#pragma once
#include "BaseLevel.h"


class GameInstance;
class Healer;
class Merchant;
class InventoryItem;
enum class EPlayerHandleItemResult;

class VillageLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~VillageLevel();

	virtual void Init() override;

private:
	void ShowGreetingMenu();
	void BuySelectedItem(int32 itemId);
	void SellSelectedItem(int32 itemId);

	void OnEnterItemShop();
	void OnBuyItem();
	void OnSellItem();
	void OnEnterHealerShop();
	void OnRecoverPlayer();
	void OnExitVillage();

	wstring GetMsgForItemHandleResult(EPlayerHandleItemResult result, InventoryItem item);

private:
	Healer* m_healer;
	Merchant* m_merchant;
	GameInstance* gi;
};

