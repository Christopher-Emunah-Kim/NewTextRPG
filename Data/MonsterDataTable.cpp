#include "MonsterDataTable.h"
#include "../include/parser.hpp"
#include "../Core/GameInstance.h"
#include "../Object/Character/Monster.h"


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

bool MonsterDataTable::HasMonster(const wstring& monsterName) const
{
	return m_monsterDataTable.find(monsterName) != m_monsterDataTable.end();
}

wstring MonsterDataTable::StringToWString(const string& str) const
{
	if (str.empty())
	{
		return wstring();
	}

	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	wstring resultWstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &resultWstr[0], size_needed);

	return resultWstr;
}

Monster* MonsterDataTable::CreateMonster(BaseLevel* level, const wstring& monsterName) const
{
	MonsterInfoUMap::const_iterator it = m_monsterDataTable.find(monsterName);
	if (it != m_monsterDataTable.end())
	{
		return new Monster(level, monsterName, it->second);
	}
	GameInstance::GetInstance()->EnqueueText(L"존재하지 않는 몬스터입니다: " + monsterName);
	return nullptr;
}

void MonsterDataTable::ProcessCSVParsing()
{
	ifstream file("Data/MonsterCSVData.csv");
	if (!file.is_open())
	{
		GameInstance::GetInstance()->EnqueueText(L"CSV 파일을 열 수 없습니다: Data/MonsterCSVData.csv");
		return;
	}

	CsvParser parser(file);
	bool headerSkipped = false;

	int16 monsterId;
	string nameStr, descStr;
	int32 health, maxHealth;
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
			GameInstance::GetInstance()->EnqueueText(L"잘못된 열 수를 가진 CSV 행 발견, 건너뜁니다.");
			continue;
		}

		monsterId = (int16)stoi(row[0]);
		nameStr = row[1];
		characterLevel = (int16)stoi(row[2]);
		descStr = row[3];
		health = (int32)stoi(row[4]);
		maxHealth = (int32)stoi(row[5]);
		monsterAttack = (int16)stoi(row[6]);
		monsterDefense = (int16)stoi(row[7]);
		monsterAgility = (int16)stoi(row[8]);
		dropGold = (int16)stoi(row[9]);
		dropExperience = (int16)stoi(row[10]);

		wstring name = StringToWString(nameStr);
		wstring desc = StringToWString(descStr);

		
		FMonsterInfo monsterInfo(characterLevel);
		monsterInfo.name = name;
		monsterInfo.description = desc;
		monsterInfo.health = health;
		monsterInfo.maxHealth = maxHealth;
		monsterInfo.status = Status::NewStatus(monsterAttack, monsterDefense, monsterAgility);
		monsterInfo.dropGold = dropGold;
		monsterInfo.dropExperience = dropExperience;
		monsterInfo.monsterId = monsterId; 

		m_monsterDataTable[name] = monsterInfo;
	}
}

const MonsterInfoUMap& MonsterDataTable::GetMonsterDataTable() const noexcept
{
	return m_monsterDataTable;
}

const FMonsterInfo* MonsterDataTable::GetMonsterInfo(const wstring& monsterName) const
{
	MonsterInfoUMap::const_iterator it = m_monsterDataTable.find(monsterName);
	if (it != m_monsterDataTable.end())
	{
		return &(it->second);
	}
	GameInstance::GetInstance()->EnqueueText(L"존재하지 않는 몬스터입니다: " + monsterName);
	return nullptr;
}

const vector<wstring> MonsterDataTable::GetMonsterNames() const noexcept
{
	vector<wstring> monsterNames;

	for (MonsterInfoUMap::const_iterator it = m_monsterDataTable.begin(); it != m_monsterDataTable.end(); ++it)
	{
		monsterNames.push_back(it->first);
	}

	return monsterNames;
}
