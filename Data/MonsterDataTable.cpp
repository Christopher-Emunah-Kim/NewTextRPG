#include "MonsterDataTable.h"
#include "include/parser.hpp"
#include "../Core/GameInstance.h"
#include "../Character/Monster.h"


using namespace aria::csv;

MonsterDataTable::~MonsterDataTable()
{
	Release();
}

void MonsterDataTable::Init()
{
	ProcessCSVParsing();
}

void MonsterDataTable::Release()
{
	m_monsterDataTable.clear();
}

bool MonsterDataTable::HasMonster(int32 monsterId) const
{
	return m_monsterDataTable.find(monsterId) != m_monsterDataTable.end();
}

wstring MonsterDataTable::ToWideStr(const string& str) const
{
	if (str.empty())
	{
		return wstring();
	}

	int size_needed = MultiByteToWideChar(CP_ACP, 0, &str[0], (int)str.size(), NULL, 0);

	wstring resultWstr(size_needed, 0);
	MultiByteToWideChar(CP_ACP, 0, &str[0], (int)str.size(), &resultWstr[0], size_needed);

	return resultWstr;
}

Monster* MonsterDataTable::CreateMonster(BaseLevel* level, int32 monsterId) const
{
	unordered_map<int32, FMonsterInfo>::const_iterator it = m_monsterDataTable.find(monsterId);
	if (it != m_monsterDataTable.end())
	{
		const FMonsterInfo& monsterInfo = it->second;
		return new Monster(level, monsterInfo.name, monsterInfo);
	}
	GameInstance::GetInstance()->WriteLine(L"존재하지 않는 몬스터입니다: " + to_wstring(monsterId));
	return nullptr;
}

void MonsterDataTable::ProcessCSVParsing()
{
	ifstream file("Data/MonsterCSVData.csv");
	if (!file.is_open())
	{
		throw::runtime_error("CSV 파일을 열 수 없습니다: Data/MonsterCSVData.csv");
	}

	CsvParser parser(file);
	bool headerSkipped = false;

	int32 monsterId;
	string nameStr, descStr;
	int32 maxHealth;
	int16 characterLevel, monsterAttack, monsterDefense, monsterAgility;
	int16 dropGold, dropExperience;

	for (CsvParser::iterator it = parser.begin(); it != parser.end(); ++it)
	{
		const vector<string>& row = *it;
		if (headerSkipped == false)
		{
			headerSkipped = true;
			continue;
		}
		if (row.size() < MONSTER_CSV_COLUMN_NUM)
		{
			GameInstance::GetInstance()->WriteLine(L"잘못된 열 수를 가진 CSV 행 발견, 건너뜁니다.");
			continue;
		}

		monsterId = (int32)stoi(row[0]);
		nameStr = row[1];
		characterLevel = (int16)stoi(row[2]);
		descStr = row[3];
		maxHealth = (int32)stoi(row[4]);
		monsterAttack = (int16)stoi(row[5]);
		monsterDefense = (int16)stoi(row[6]);
		monsterAgility = (int16)stoi(row[7]);
		dropGold = (int16)stoi(row[8]);
		dropExperience = (int16)stoi(row[9]);

		wstring name = ToWideStr(nameStr);
		wstring desc = ToWideStr(descStr);

		
		FMonsterInfo monsterInfo(characterLevel);
		monsterInfo.name = name;
		monsterInfo.description = desc;
		monsterInfo.health = Health::New(maxHealth);
		monsterInfo.status = Status::NewStatus(monsterAttack, monsterDefense, monsterAgility);
		monsterInfo.dropGold = dropGold;
		monsterInfo.dropExperience = dropExperience;
		monsterInfo.monsterId = monsterId; 

		m_monsterDataTable[monsterId] = monsterInfo;

	}
}


const FMonsterInfo* MonsterDataTable::GetMonsterInfo(int32 monsterId) const
{
	unordered_map<int32, FMonsterInfo>::const_iterator it = m_monsterDataTable.find(monsterId);
	if (it != m_monsterDataTable.end())
	{
		return &(it->second);
	}
	GameInstance::GetInstance()->WriteLine(L"존재하지 않는 몬스터입니다: " + to_wstring(monsterId));
	return nullptr;
}

const vector<wstring> MonsterDataTable::GetMonsterNames() const noexcept
{
	vector<wstring> monsterNames;

	for (unordered_map<int32, FMonsterInfo>::const_iterator it = m_monsterDataTable.begin(); it != m_monsterDataTable.end(); ++it)
	{
		monsterNames.push_back(it->second.name);
	}

	return monsterNames;
}

const vector<int32> MonsterDataTable::GetMonsterIds() const noexcept
{
	vector<int32> monsterIds;
	for (unordered_map<int32, FMonsterInfo>::const_iterator it = m_monsterDataTable.begin(); it != m_monsterDataTable.end(); ++it)
	{
		monsterIds.push_back(it->first);
	}

	return monsterIds;
}
