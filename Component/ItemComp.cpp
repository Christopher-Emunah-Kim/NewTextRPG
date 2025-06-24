#include "ItemComp.h"  
#include "../Object/BaseGameObject.h" 
#include "Player/PlayerStatusComp.h"
#include "../Core/GameInstance.h"

ItemComp::ItemComp(BaseGameObject* owner)  
	:BaseComponent(owner, 5)  
{  
}  

void ItemComp::Init()  
{  
	m_owner = GetOwner();  

	if (m_owner->HasCustomField(L"healAmount"))
	{  
		m_healAmount = stoi(m_owner->GetCustomField(L"healAmount"));
	}  

	if (m_owner->HasCustomField(L"buyValue"))
	{
		m_buyValue = stoi(m_owner->GetCustomField(L"buyValue"));
	}

	if (m_owner->HasCustomField(L"sellValue"))
	{
		m_sellValue = stoi(m_owner->GetCustomField(L"sellValue"));
	}

	if (m_owner->HasCustomField(L"attack") && m_owner->HasCustomField(L"defense") && m_owner->HasCustomField(L"agility"))
	{
		int16 atk = stoi(m_owner->GetCustomField(L"attack"));
		int16 def = stoi(m_owner->GetCustomField(L"defense"));
		int16 agi = stoi(m_owner->GetCustomField(L"agility"));
		m_itemStatus = Status(atk, def, agi);
	}

	if (m_owner->HasCustomField(L"itemType"))
	{
		m_itemType = stoi(m_owner->GetCustomField(L"itemType"));
	}
	else
	{
		m_itemType = m_owner->GetTag();
	}
}  

void ItemComp::UseHealItem(BaseGameObject* target)
{  
	if (nullptr == target)
	{
		return;
	}

	PlayerStatusComp* statusComp = target->GetComponentsByType<PlayerStatusComp>();

	if (nullptr == statusComp)
	{
		return;
	}

	if (m_healAmount > 0)
	{
		int32 currentHealth = statusComp->GetPlayerHealth();
		int32 maxHealth = statusComp->GetPlayerMaxHealth();

		statusComp->SetPlayerHealth(min(currentHealth + m_healAmount, maxHealth));

		GameInstance::GetInstance()->DisplaySystemText(L"체력이 " + to_wstring(m_healAmount) + L" 회복되었습니다!");
	}
}

void ItemComp::UseEquipableItem(BaseGameObject* target)
{
	if (nullptr == target)
	{
		return;
	}

	PlayerStatusComp* statusComp = target->GetComponentsByType<PlayerStatusComp>();

	if (nullptr == statusComp)
	{
		return;
	}

	if (m_itemStatus.GetAttack() > 0 || m_itemStatus.GetDefense() > 0 || m_itemStatus.GetAgility())
	{
		Status curStatus = statusComp->GetStatus();
		Status newStatus = curStatus.AddStatus(curStatus, m_itemStatus);
		statusComp->SetStatus(newStatus);

		GameInstance::GetInstance()->DisplaySystemText(m_itemType + L" 을 장착하였습니다!");

	}
}

void ItemComp::SetItemStatus(const int32& atk, const int32& def, const int32& agi)  
{  
	m_itemStatus = Status(atk, def, agi);  
}
