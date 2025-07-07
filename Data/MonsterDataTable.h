#pragma once
#include "../Common.h"
#include "../Util/Singleton.h"

constexpr __int16 MONSTER_CSV_COLUMN_NUM = 11;

struct FMonsterInfo;
class BaseLevel;
class Monster;


class MonsterDataTable final : public Singleton<MonsterDataTable>
{
public:
	MonsterDataTable() = default;
	~MonsterDataTable();

	void Init();
	void Release();

	bool HasMonster(const wstring& monsterName) const;
	wstring ToWideStr(const string& str) const;
	Monster* CreateMonster(BaseLevel* level, const wstring& monsterName) const;
	void ProcessCSVParsing();

	const FMonsterInfo* GetMonsterInfo(const wstring& monsterName) const;
	const vector<wstring> GetMonsterNames() const noexcept;

private:
	unordered_map<wstring, FMonsterInfo> m_monsterDataTable;
};

