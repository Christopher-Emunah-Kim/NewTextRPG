#pragma once
#include "BaseLevel.h"


class GameInstance;
class Healer;
class Merchant;
//class BaseItem;
class InventoryItem;
enum class EPlayerHandleItemResult;

class VillageLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~VillageLevel();

	virtual void Init() override;

private:
	void Welcome();
	void BuySelectedItem(int32 itemId);
	void SellSelectedItem(int32 itemId);
	wstring GetMsgForItemHandleResult(EPlayerHandleItemResult result, InventoryItem item);

	void OnEnterItemShop();
	void OnBuyItem();
	void OnSellItem();
	void OnEnterHealerShop();
	void OnRecoverPlayer();
	void OnExitVillage();

private:
	Healer* m_healer;
	Merchant* m_merchant;
	GameInstance* gi;
};

