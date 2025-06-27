#pragma once  
#include "BattleCharacter.h"  
#include "../../Util/Type/CharacterInfo.h"

class Player final : public BattleCharacter  
{  
public:  

	Player();
	virtual ~Player() = default;

private:
	FPlayerInfo m_playerInfo;

public:
	virtual void Init() override;  

	void RegisterNewLevelArea(BaseLevel* level);

	void LevelUp();
	bool GainExperience(int32 exp);
	bool GainGold(int16 amount);
	bool UseGold(int16 amount);

	bool EquipWeapon(const wstring& itemId);
	bool EquipArmor(const wstring& itemId);
	bool AddItemToInventory(const wstring& itemId);

	const FPlayerInfo& GetPlayerInfo() const { return m_playerInfo; }
};
