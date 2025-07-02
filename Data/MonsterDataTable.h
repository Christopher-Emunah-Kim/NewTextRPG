#pragma once
#include "../Common.h"
#include "../Util/Singleton.h"

struct FMonsterInfo;
class BaseLevel;
class Monster;

constexpr __int16 MONSTER_CSV_COLUMN_NUM = 11;

using MonsterInfoUMap = unordered_map<wstring, FMonsterInfo>;

class MonsterDataTable final : public Singleton<MonsterDataTable>
{
public:
	MonsterDataTable() = default;
	virtual ~MonsterDataTable();

private:
	MonsterInfoUMap m_monsterDataTable;

public:
	void Init();
	void Release();

	bool HasMonster(const wstring& monsterName) const;
	wstring StringToWString(const string& str) const;
	Monster* CreateMonster(BaseLevel* level, const wstring& monsterName) const;
	void ProcessCSVParsing();

	const MonsterInfoUMap& GetMonsterDataTable() const noexcept;
	const FMonsterInfo* GetMonsterInfo(const wstring& monsterName) const;
	const vector<wstring> GetMonsterNames() const noexcept;
};

