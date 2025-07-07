#include "Player.h"
#include "../../Screen.h"
#include "../../Core/GameInstance.h"
#include "../../Level/BaseLevel.h"


Player::Player()
	:BattleCharacter(nullptr, L"Player"), m_gold(DEFAULT_OWNED_GOLD),
	m_experience(0, FPlayerDataTablePerLevel::GetRequiredMaxExp(DEFAULT_LEVEL)),
	m_inventory(), m_equipment()
{ }

void Player::Init()
{
	UpdatePlayerHUD();

	BattleCharacter::Init();
}

void Player::UpdatePlayerHUD()
{
	GameInstance* gameInstance = GameInstance::GetInstance();

	gameInstance->UpdatePlayerName(GetTag());
	gameInstance->UpdatePlayerLevel(m_battleCharacterInfo.characterLevel);
	gameInstance->UpdatePlayerHealth(m_battleCharacterInfo.health);
	gameInstance->UpdatePlayerStatus(GetTotalStatus());
	gameInstance->UpdatePlayerExperience(m_experience);

	BaseItem* weapon = m_equipment.GetEquippedItem(EItemType::Weapon);
	BaseItem* armor = m_equipment.GetEquippedItem(EItemType::Armor);

	if (weapon)
	{
		gameInstance->UpdateEquippedItem(weapon->GetName(), EItemType::Weapon);
	}
	else
	{
		gameInstance->UpdateEquippedItem(L"없음", EItemType::Weapon);
	}

	if (armor)
	{
		gameInstance->UpdateEquippedItem(armor->GetName(), EItemType::Armor);
	}
	else
	{
		gameInstance->UpdateEquippedItem(L"없음", EItemType::Armor);
	}

	const vector<BaseItem*>& items = m_inventory.GetInventoryItems();
	for (size_t i = 0; i < items.size(); ++i)
	{
		BaseItem* item = items[i];
		gameInstance->UpdateInvetoryItems(m_inventory.GetInventoryItems());
	}
}

void Player::RegisterNewLevelArea(BaseLevel* level)
{
	if (level != nullptr)
	{
		if (GetLevel() == level)
		{
			return;
		}

		SetLevelArea(level);

		level->AddObject(this);
	}
	else
	{
		GameInstance::GetInstance()->WriteLine(L"[오류] 플레이어를 등록할 레벨이 존재하지 않습니다.");
		SetLevelArea(GetLevel());
	}
}

Health Player::GetHealth() const
{
	return m_battleCharacterInfo.health;
}

bool Player::CanAfford(int32 cost) const
{
	return m_gold.CanAfford(cost);
}

bool Player::IsFullHealth() const
{
	return m_battleCharacterInfo.health.IsFull();
}

void Player::Recover(int32 amount)
{
	m_battleCharacterInfo.health = m_battleCharacterInfo.health.Recover(amount);
}

bool Player::UseGold(int32 amount)
{
	m_gold = m_gold.Use(amount);

	if (m_gold.GetAmount() > 0)
	{
		return true;
	}

	return false;
}

void Player::GainGold(int32 amount)
{
	m_gold = m_gold.Gain(amount);
}

Gold Player::GetGold() const
{
	return m_gold;
}

int32 Player::GetGoldAmount() const
{
	return m_gold.GetAmount();
}

bool Player::GainExperience(int32 exp)
{
	int16 levelUpCount = m_experience.AddExperience(exp, m_battleCharacterInfo.characterLevel);

	GameInstance::GetInstance()->UpdatePlayerExperience(m_experience);

	if (levelUpCount > 0)
	{
		m_battleCharacterInfo.characterLevel += levelUpCount;

		LoadLevelPropertiesByLevel();

		GameInstance::GetInstance()->UpdatePlayerLevel(m_battleCharacterInfo.characterLevel);
		GameInstance::GetInstance()->UpdatePlayerHealth(m_battleCharacterInfo.health);
		GameInstance::GetInstance()->UpdatePlayerStatus(GetTotalStatus());

		return true;
	}

	return false;
}

void Player::LoadLevelPropertiesByLevel()
{
	FLevelProperties levelProps = FPlayerDataTablePerLevel::LoadPlayerLevelData(m_battleCharacterInfo.characterLevel);

	m_battleCharacterInfo.health = Health::New(levelProps.maxHealthPerLevel);
	m_experience.SetMaxExp(levelProps.maxExperiencePerLevel);

	m_battleCharacterInfo.status = Status(
		levelProps.attackPerLevel,
		levelProps.defensePerLevel,
		levelProps.agilityPerLevel
	);
}

Status Player::GetTotalStatus() const
{
	Status baseStatus = m_battleCharacterInfo.status;
	Status equipStatus = m_equipment.GetTotalEquipmentStatus();
	baseStatus = Status::AddStatus(baseStatus, equipStatus);

	return baseStatus;
}

Experience Player::GetExperience() const
{
	return m_experience;
}

Inventory& Player::GetInventory() 
{
	return m_inventory;
}

Equipment& Player::GetEquipment()
{
	return m_equipment;
}

