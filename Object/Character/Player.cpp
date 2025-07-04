#include "Player.h"
#include "../../Screen.h"
#include "../../Core/GameInstance.h"
#include "../../Level/BaseLevel.h"
#include "../../Component/Player/EquipmentComp.h"
#include "../../Component/Player/InventoryComp.h"


Player::Player()
	:BattleCharacter(nullptr, L"Player"), m_gold(DEFAULT_OWNED_GOLD),
	m_experience(0, FPlayerDataTablePerLevel::GetRequiredMaxExp(DEFAULT_LEVEL))
{ }

void Player::Init()
{
	InitializeComponents();

	BattleCharacter::Init();
}

void Player::InitializeComponents()
{
	if (false == HasComponentType<InventoryComp>())
	{
		AddComponent(new InventoryComp(this));
	}

	if (false == HasComponentType<EquipmentComp>())
	{
		AddComponent(new EquipmentComp(this));
	}

	GameInstance* gameInstance = GameInstance::GetInstance();

	gameInstance->UpdatePlayerName(GetTag());
	gameInstance->UpdatePlayerLevel(m_battleCharacterInfo.characterLevel);
	gameInstance->UpdatePlayerHealth(m_battleCharacterInfo.health);
	gameInstance->UpdatePlayerStatus(GetTotalStatus());
	gameInstance->UpdatePlayerExperience(m_experience);

	EquipmentComp* equipComp = GetComponentByType<EquipmentComp>();
	if (equipComp)
	{
		BaseItem* weapon = equipComp->GetEquippedItem(EItemType::Weapon);
		BaseItem* armor = equipComp->GetEquippedItem(EItemType::Armor);

		gameInstance->UpdateEquippedItem(weapon ? weapon->GetName() : L"없음", EItemType::Weapon);
		gameInstance->UpdateEquippedItem(armor ? armor->GetName() : L"없음", EItemType::Armor);
	}

	InventoryComp* invComp = GetComponentByType<InventoryComp>();
	if (invComp)
	{
		const vector<BaseItem*>& items = invComp->GetInventoryItems();
		for (size_t i = 0; i < items.size(); ++i)
		{
			BaseItem* item = items[i];
			gameInstance->UpdateInvetoryItems(item->GetName());
		}
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

		if (level->FindObject(L"Player") == nullptr)
		{
			level->AddObject(this);
		}

		if (IsComponentsEmpty())
		{
			Init();
		}
		else
		{
			InitializeComponents();
		}
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

	EquipmentComp* equipComp = GetComponentByType<EquipmentComp>();
	if (equipComp)
	{
		Status equipStatus = equipComp->GetTotalEquipmentStatus();
		baseStatus = Status::AddStatus(baseStatus, equipStatus);
	}

	return baseStatus;
}

Experience Player::GetExperience() const
{
	return m_experience;
}

