#pragma once
#include "../Common.h"
#include "../Util/Singleton.h"

constexpr __int16 MONSTER_CSV_COLUMN_NUM = 10;

struct FMonsterInfo;
class BaseLevel;
class Monster;


class MonsterDataTable final : public Singleton<MonsterDataTable>
{
public:
	MonsterDataTable() = default;
	virtual ~MonsterDataTable();

private:
	wstring ToWideStr(const string& str) const;
	void ProcessCSVParsing();

public:
	void Init();
	void Release();

	bool HasMonster(int32 monsterId) const;
	Monster* CreateMonster(BaseLevel* level, int32 monsterId) const;

	const FMonsterInfo* GetMonsterInfo(int32 monsterId) const;
	const vector<wstring> GetMonsterNames() const noexcept;
	const vector<int32> GetMonsterIds() const noexcept;

private:
	unordered_map<int32, FMonsterInfo> m_monsterDataTable;
};

