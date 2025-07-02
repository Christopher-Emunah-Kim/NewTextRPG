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

void GameInstance::UpdatePlayerHealth(int32 health, int32 maxHealth)
{
	m_Hud.UpdatePlayerHealth(health, maxHealth);
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

void GameInstance::UpdateInvetoryItems(const wstring& name)
{
	m_Hud.UpdateInvetoryItems(name);
}

void GameInstance::EnqueueText(const wstring& text)
{
	m_Hud.EnqueueText(text);
}

void GameInstance::ClearText()
{
	m_Hud.ClearText();
}

void GameInstance::RenderHud(Screen& screen) const
{
	m_Hud.Render(screen);
}



void GameInstance::SyncAllHudData(const wstring& levelName, const wstring& playerName, int16 level, int32 health, int32 maxHealth, const Status& status, const Experience& experience, const Gold& gold, const wstring& weaponName, EItemType weaponType, const wstring& armorName, EItemType armorType, const vector<wstring>& inventoryItems)
{
	m_Hud.UpdateLevelName(levelName);
	m_Hud.UpdatePlayerName(playerName);
	m_Hud.UpdatePlayerLevel(level);
	m_Hud.UpdatePlayerHealth(health, maxHealth);
	m_Hud.UpdatePlayerStatus(status);
	m_Hud.UpdatePlayerExperience(experience);
	m_Hud.UpdatePlayerGold(gold);
	m_Hud.UpdateEquippedItem(weaponName, weaponType);
	m_Hud.UpdateEquippedItem(armorName, armorType);
	for (size_t i = 0; i < inventoryItems.size(); ++i)
	{
		m_Hud.UpdateInvetoryItems(inventoryItems[i]);
	}
}



















////bool GameInstance::LoadSerializedDataFromFile(BaseLevel* level, const wstring& filePath)
////{
////	if (nullptr == level)
////	{
////		return false;
////	}
////
////	ifstream file(filePath);
////
////	if (false == file.is_open())
////	{
////		OutputSystem::PrintErrorMsg(L"레벨 파일을 열 수 없습니다." + filePath);
////		return false;
////	}
////
////	string line;
////	while (getline(file, line))
////	{
////		//parsing
////		istringstream iss(line);
////		string objectTypeStr, tagStr, msgStr;
////
////		if (!(iss >> objectTypeStr >> tagStr))
////		{
////			continue;
////		}
////
////		getline(iss >> ws, msgStr);
////
////		wstring objectType = wstring(objectTypeStr.begin(), objectTypeStr.end());
////		wstring tag = wstring(tagStr.begin(), tagStr.end());
////		wstring message = wstring(msgStr.begin(), msgStr.end());
////
////		size_t customFieldStart = message.find(L'[');
////		size_t customFieldEnd = message.find(L']', customFieldStart);
////
////		wstring customFieldsData = L"";
////		if (customFieldStart != wstring::npos && customFieldEnd != wstring::npos)
////		{
////			customFieldsData = message.substr(customFieldStart + 1, customFieldEnd - customFieldStart - 1);
////			message = message.substr(0, customFieldStart);
////		}
////
////		if (message.length() >= 2 && message.front() == L'"' && message.back() == L'"')
////		{
////			message = message.substr(1, message.length() - 2);
////		}
////
////		//existingObject
////		bool bIsPersistentObject = (objectType == L"Player" || objectType == L"SystemText");
////		BaseGameObject* existingObject = nullptr;
////
////		if (bIsPersistentObject)
////		{
////			if (objectType == L"Player" && m_player)
////			{
////				existingObject = m_player;
////			}
////			else if (objectType == L"SystemText" && m_systemTextDialog)
////			{
////				existingObject = m_systemTextDialog;
////			}
////		}
////
////		if (nullptr == existingObject)
////		{
////			existingObject = level->FindObject(tag);
////		}
////
////		if (existingObject)
////		{
////			existingObject->SetMessage(message);
////
////			if (false == customFieldsData.empty())
////			{
////				size_t pos = 0;
////				wstring token;
////				while ((pos = customFieldsData.find(L',')) != wstring::npos || !customFieldsData.empty())
////				{
////					if (pos != wstring::npos)
////					{
////						token = customFieldsData.substr(0, pos);
////					}
////					else
////					{
////						token = customFieldsData;
////					}
////
////					size_t equalsPos = token.find(L'=');
////
////					if (equalsPos != wstring::npos)
////					{
////						wstring key = token.substr(0, equalsPos);
////						wstring value = token.substr(equalsPos + 1);
////
////						existingObject->SetCustomField(key, value);
////					}
////
////					if (pos != wstring::npos)
////					{
////						customFieldsData.erase(0, pos + 1);
////					}
////					else
////					{
////						customFieldsData.clear();
////					}
////				}
////			}
////
////			if (bIsPersistentObject && existingObject->GetLevel() != level)
////			{
////				existingObject->RegisterNewLevelArea(level);
////			}
////
////			continue;
////		}
////
////		BaseGameObject* newObject = new BaseGameObject(level, tag, objectType);
////		newObject->SetMessage(message);
////
////		if (!customFieldsData.empty())
////		{
////			size_t pos = 0;
////			wstring token;
////			while ((pos = customFieldsData.find(L',')) != wstring::npos || !customFieldsData.empty())
////			{
////
////				if (pos != wstring::npos)
////				{
////					token = customFieldsData.substr(0, pos);
////				}
////				else
////				{
////					token = customFieldsData;
////				}
////
////				size_t equalsPos = token.find(L'=');
////				if (equalsPos != wstring::npos)
////				{
////					wstring key = token.substr(0, equalsPos);
////					wstring value = token.substr(equalsPos + 1);
////					newObject->SetCustomField(key, value);
////				}
////
////				if (pos != wstring::npos)
////				{
////					customFieldsData.erase(0, pos + 1);
////				}
////				else
////				{
////					customFieldsData.clear();
////				}
////			}
////		}
////
////		if (HasSavedState(objectType, tag))
////		{
////			wstring savedState = GetSavedState(objectType, tag);
////			newObject->LoadStateFromString(savedState);
////		}
////
////		if (objectType == L"Player")
////		{
////			m_player = newObject;
////			if (nullptr == newObject->GetComponentsByType<PlayerStatusComp>())
////			{
////				PlayerStatusComp* statusComp = new PlayerStatusComp(newObject);
////				newObject->AddComponent(statusComp);
////			}
////		}
////		else if (objectType == L"Enemy")
////		{
////			if (nullptr == newObject->GetComponentsByType<EnemyComp>())
////			{
////				EnemyComp* enemyComp = new EnemyComp(newObject);
////				newObject->AddComponent(enemyComp);
////			}
////		}
////		else if (objectType == L"Item")
////		{
////			if (nullptr == newObject->GetComponentsByType<ItemComp>())
////			{
////				ItemComp* itempComp = new ItemComp(newObject);
////				newObject->AddComponent(itempComp);
////			}
////		}
////		else if (objectType == L"InfoPanel")
////		{
////			if (nullptr == newObject->GetComponentsByType<PlayerInfoUpdateComp>())
////			{
////				PlayerInfoUpdateComp* infoComp = new PlayerInfoUpdateComp(newObject);
////				newObject->AddComponent(infoComp);
////			}
////		}
////		else if (objectType == L"SystemText")
////		{
////			m_systemTextDialog = newObject;
////			if (nullptr == newObject->GetComponentsByType<SystemTextComp>())
////			{
////				SystemTextComp* textComp = new SystemTextComp(newObject);
////				newObject->AddComponent(textComp);
////			}
////		}
////
////		level->AddObject(newObject);
////		newObject->Init();
////
////	}
////
////	BaseGameObject* infoPanel = level->FindObject(L"InfoPanel");
////	if (infoPanel && m_player)
////	{
////		InitPlayerInfoPanel(infoPanel, m_player);
////	}
////
////	file.close();
////	return true;
////}
//
//
////void GameInstance::SyncObejctsToNewLevel(BaseLevel* oldLevel, BaseLevel* newLevel)
////{
////	if (nullptr == oldLevel || nullptr == newLevel)
////	{
////		return;
////	}
////
////	const vector<BaseGameObject*>& tempObjects = oldLevel->GetObjects();
////	for (size_t i = 0; i < tempObjects.size(); ++i)
////	{
////		BaseGameObject* obj = tempObjects[i];
////		wstring type = obj->GetType();
////
////		if (type == L"Player" || type == L"SystemText")
////		{
////			SaveObjectState(obj);
////		}
////	}
////}
////
////void GameInstance::ProcessObjectInteraction(const wstring& sourceTag, const wstring& targetTag)
////{
////	BaseGameObject* source = nullptr;
////	BaseGameObject* target = nullptr;
////
////	if (m_player && m_player->GetTag() == sourceTag)
////	{
////		source = m_player;
////	}
////
////	if (source && m_player->GetLevel())
////	{
////		target = m_player->GetLevel()->FindObject(targetTag);
////	}
////
////	if (source && target)
////	{
////		source->Interact(target);
////
////		SaveObjectState(source);
////		SaveObjectState(target);
////
////		wstring interactionEvent = sourceTag + L"_interacts_" + targetTag;
////		ProcessGameEvent(interactionEvent);
////	}
////}
////
////void GameInstance::ProcessGameEvent(const wstring& eventName)
////{
////	if (m_player)
////	{
////		m_player->ProcessEvent(eventName);
////		SaveObjectState(m_player);
////	}
////
////	if (eventName.substr(0, 9) == L"scenario_")
////	{
////		wstring scenarioKey = eventName.substr(9);
////		DisplaySystemText(L"[시나리오] " + scenarioKey + L" 진행 중...");
////	}
////	else if (eventName == L"show_game_info")
////	{
////		DisplaySystemText(L"[게임 정보] 텍스트 RPG 게임 v1.0");
////
////		BaseGameObject* systemTextObj = GetSystemTextDialog();
////		if (systemTextObj)
////		{
////			SystemTextComp* textComp = systemTextObj->GetComponentsByType<SystemTextComp>();
////			if (textComp)
////			{
////				textComp->ClearOption();
////				textComp->AddOption(L"1. 게임 정보 보기", L"show_game_info");
////				textComp->AddOption(L"2. 던전 입장하기", L"enter_dungeon");
////				textComp->AddOption(L"3. 게임 종료하기", L"exit_game");
////			}
////		}
////	}
////	else if (eventName == L"enter_dungeon")
////	{
////		DisplaySystemText(L"던전으로 이동합니다...");
////		LevelManager::GetInstance()->SetNextLevel(L"Dungeon");
////	}
////	else if (eventName == L"exit_game")
////	{
////		DisplaySystemText(L"게임을 종료합니다...");
////		exit(0);
////	}
////
////
////}
//
//
////void GameInstance::SaveObjectState(const BaseGameObject* object)
////{
////	if (nullptr == object)
////	{
////		return;
////	}
////
////	wstring key = object->GetType() + L"_" + object->GetTag();
////	m_globalStateCache[key] = object->SerializeStateToString();
////}
////
////bool GameInstance::HasSavedState(const wstring& objectType, const wstring& objectTag)
////{
////	wstring key = objectType + L"_" + objectTag;
////	return m_globalStateCache.find(key) != m_globalStateCache.end();
////}
////
////wstring GameInstance::GetSavedState(const wstring& objectType, const wstring& objectTag)
////{
////	wstring key = objectType + L"_" + objectTag;
////	unordered_map<wstring, wstring>::const_iterator it = m_globalStateCache.find(key);
////	if (it != m_globalStateCache.end())
////	{
////		return it->second;
////	}
////
////	return L" ";
////}
////
////void GameInstance::ClearSavedState(const wstring& objectType, const wstring& objectTag)
////{
////	wstring key = objectType + L"_" + objectTag;
////	m_globalStateCache.erase(key);
////}
////
////void GameInstance::ClearAllStates()
////{
////	m_globalStateCache.clear();
////	m_gameFlags.clear();
////}
//
