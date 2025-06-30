#include "Player.h"
#include "../../Screen.h"
#include "../../Core/GameInstance.h"
#include "../../Component/ControllerComp.h"
#include "../../Level/BaseLevel.h"
#include "../../Component/Player/EquipmentComp.h"
#include "../../Component/Player/PlayerStatusComp.h"
#include "../../Component/Player/InventoryComp.h"



Player::Player()
	:BattleCharacter(nullptr, L"Player"), m_playerInfo(DEFAULT_LEVEL)
{
}


void Player::Init()
{
	SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	if (false == HasComponentType<PlayerStatusComp>())
	{
		AddComponent(new PlayerStatusComp(this));
	}
	/*if (false == HasComponentType<EquipmentComp>())
	{
		AddComponent(new EquipmentComp(this));
	}
	if (false == HasComponentType<InventoryComp>())
	{
		AddComponent(new InventoryComp(this));
	}*/

	BattleCharacter::Init();
}

void Player::RegisterNewLevelArea(BaseLevel* level)
{
	if (level != nullptr)
	{
		if (GetLevel() == level)
		{
			return;
		}

		if (GetLevel() != nullptr)
		{
			GetLevel()->DetachObject(this);
		}

		SetLevelArea(level);

		if (IsComponentsEmpty())
		{
			Init();
		}

		if (level->FindObject(L"Player") == nullptr)
		{
			level->AddObject(this);
		}
	}
}

void Player::LevelUp()
{
	++m_playerInfo.characterLevel;
	PlayerStatusComp* statusComp = GetComponentsByType<PlayerStatusComp>();
	if (statusComp)
	{
		statusComp->LoadStatusByLevel();
		AddSystemText(L"레벨업! 현재 레벨: " + to_wstring(m_playerInfo.characterLevel));
	}
}



//bool Player::GainExperience(int32 exp)
//{
//	PlayerStatusComp* statusComp = GetComponentsByType<PlayerStatusComp>();
//	if (statusComp)
//	{
//		return statusComp->GainExperience(exp);
//	}
//
//	return false;
//}
//
//bool Player::GainGold(int16 amount)
//{
//	m_playerInfo.gold.GainGold(amount);
//	GameInstance::GetInstance()->DisplaySystemText(to_wstring(amount) + L"골드를 획득했습니다. 현재 보유 골드 : " + to_wstring(m_playerInfo.gold.GetAmount()));
//
//	return true;
//}
//
//bool Player::UseGold(int16 amount)
//{
//	return m_playerInfo.gold.UseGold(amount);
//}
//
//bool Player::EquipWeapon(const wstring& itemId)
//{
//	EquipmentComp* equipComp = GetComponentsByType<EquipmentComp>();
//	if (equipComp)
//	{
//		return equipComp->EquipItem(itemId, EItemType::Weapon);
//	}
//
//	return false;
//}
//
//bool Player::EquipArmor(const wstring& itemId)
//{
//	EquipmentComp* equipComp = GetComponentsByType<EquipmentComp>();
//	if (equipComp)
//	{
//		return equipComp->EquipItem(itemId, EItemType::Armor);
//	}
//
//	return false;
//}
//
//bool Player::AddItemToInventory(const wstring& itemId)
//{
//	InventoryComp* inventoryComp = GetComponentsByType<InventoryComp>();
//	if (inventoryComp)
//	{
//		return inventoryComp->AddItem(itemId);
//	}
//	return false;
//
//}