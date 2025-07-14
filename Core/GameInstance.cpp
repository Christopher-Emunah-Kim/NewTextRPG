#include "GameInstance.h"


void GameInstance::UpdateLevelName(const wstring& levelName)
{
	m_Hud.UpdateLevelName(levelName);
}

void GameInstance::UpdatePlayerName(const wstring& playerName)
{
	m_Hud.UpdatePlayerName(playerName);
}

void GameInstance::UpdatePlayerLevel(int16 level)
{
	m_Hud.UpdatePlayerLevel(level);
}

void GameInstance::UpdatePlayerHealth(const Health& health)
{
	m_Hud.UpdatePlayerHealth(health);
}

void GameInstance::UpdatePlayerStatus(const Status& status)
{
	m_Hud.UpdatePlayerStatus(status);
}

void GameInstance::UpdatePlayerExperience(const Experience& experience)
{
	m_Hud.UpdatePlayerExperience(experience);
}

void GameInstance::UpdatePlayerGold(const Gold& gold)
{
	m_Hud.UpdatePlayerGold(gold);
}

void GameInstance::UpdateEquippedItem(const wstring& name, EItemType type)
{
	m_Hud.UpdateEquippedItem(name, type);
}

void GameInstance::UpdateInvetoryItems(const vector<InventoryItem>& items)
{
	m_Hud.UpdateInvetoryItems(items);
}

void GameInstance::WriteLine(const wstring& text)
{
	m_Hud.WriteLine(text);
}

void GameInstance::ClearText()
{
	m_Hud.ClearText();
}

void GameInstance::RenderHud(Screen& screen) const
{
	m_Hud.Render(screen);
}

void GameInstance::RequestShutdown()
{
	m_ShouldQuit = true;
}

bool GameInstance::ShouldQuit() const
{
	return m_ShouldQuit;
}
