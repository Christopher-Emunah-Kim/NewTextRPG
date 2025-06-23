#pragma once
#include "../Util/Singleton.h"
#include "../Common.h"

//class Player;
//class PlayerInfoDialog;
class BaseLevel;
class BaseGameObject;
class SystemTextDialog;

class GameInstance : public Singleton<GameInstance>
{
	friend class Singleton<GameInstance>;
	
private:
	GameInstance() = default;

public:
	virtual ~GameInstance() = default;

private:
	//Player m_player;
	//PlayerInfoDialog* m_playerInfoDialog;
	//bool m_bIsPlayerInitialzed = false;
	unordered_map<wstring, wstring> m_globalStateCache;
	BaseGameObject* m_player = nullptr;
	SystemTextDialog* m_systemTextDialog = nullptr;
	wstring m_currentScenario = L" ";
	map<wstring, bool> m_gameFlags;
	bool m_initialized = false;

public:
	void Init();
	void Release();

	//bool IsPlayerInitialzed() const;
	//void SetPlayerInitialize(bool bIsInitialized);

	void SaveObjectState(const BaseGameObject* object);
	bool HasSavedState(const wstring& objectType, const wstring& objectTag);
	wstring GetSavedState(const wstring& objectType, const wstring& objectTag);
	void ClearSavedState(const wstring& objectType, const wstring& objectTag);
	void ClearAllStates();

	void SetPlayer(BaseGameObject* player);
	void SetSystemTextDialog(SystemTextDialog* systemDialogObj);

	void DisplaySystemText(const wstring& text);
	void AdvanceScenario(const wstring& scenarioKey);
	void SetGameFlag(const wstring& flag, bool value);
	bool GetGameFlag(const wstring& flag) const;

	bool LoadSerializedDataFromFile(BaseLevel* level, const wstring& filePath);


	void ChangeLevelAreaSettings(BaseLevel* newLevel);
	void SyncObejctsToNewLevel(BaseLevel* oldLevel, BaseLevel* newLevel);

	void ProcessObjectInteraction(const wstring& sourceTag, const wstring& targetTag);
	void ProcessGameEvent(const wstring& eventName);

	//void SetPlayerInfoDialog(PlayerInfoDialog* playerInfoObj);
	//void UpdatePlayerInfo();

	//inline Player& GetPlayer() noexcept { return m_player; }
	//inline PlayerInfoDialog* GetPlayerInfoDialog() const { return m_playerInfoDialog; }
	inline bool IsInitialized() const { return m_initialized; }
	inline BaseGameObject* GetPlayer() const { return m_player; }
	inline SystemTextDialog* GetSystemTextDialog() const { return m_systemTextDialog; }
};