#include "PlayerDataTablePerLevel.h"
#include "include/parser.hpp"


using namespace aria::csv;

PlayerLevelPropertiesTable::~PlayerLevelPropertiesTable()
{
	Release();
}

void PlayerLevelPropertiesTable::Init()
{
	ProcessCSVParsing();
}

void PlayerLevelPropertiesTable::Release()
{
	m_levelPropertiesTable.clear();
}


void PlayerLevelPropertiesTable::ProcessCSVParsing()
{
	ifstream file("Data/PlayerLevelPropertiesCSVData.csv");
	if (!file.is_open())
	{
		throw runtime_error("CSV 파일을 열 수 없습니다: Data/PlayerLevelPropertiesCSVData.csv");
	}

	CsvParser parser(file);

	bool headerSkipped = false;
	int16 level;
	FLevelProperties props;

	for (CsvParser::iterator it = parser.begin(); it != parser.end(); ++it)
	{
		const vector<string>& row = *it;
		if (headerSkipped == false)
		{
			headerSkipped = true;
			continue;
		}
		if (row.size() < 6)
		{
			throw runtime_error("잘못된 열 수를 가진 CSV 행 발견, 건너뜁니다.");
		}

		level = (int16)stoi(row[0]);
		props.maxExperiencePerLevel = (int32)stoi(row[1]);
		props.maxHealthPerLevel = (int32)stoi(row[2]);
		props.attackPerLevel = (int16)stoi(row[3]);
		props.defensePerLevel = (int16)stoi(row[4]);
		props.agilityPerLevel = (int16)stoi(row[5]);

		m_levelPropertiesTable[level] = props;
	}

}

FLevelProperties PlayerLevelPropertiesTable::LoadPlayerLevelData(int16 level) const 
{
	unordered_map<int16, FLevelProperties>::const_iterator it = m_levelPropertiesTable.find(level);
	if (it != m_levelPropertiesTable.end())
	{
		return it->second;
	}

	FLevelProperties defaultProps;
	defaultProps.maxExperiencePerLevel = DEFAULT_PLAYER_MAX_EXPERIENCE;
	defaultProps.maxHealthPerLevel = DEFAULT_CHARACTER_MAX_HEALTH;
	defaultProps.attackPerLevel = DEFAULT_ATTACK;
	defaultProps.defensePerLevel = DEFAULT_DEFENSE;
	defaultProps.agilityPerLevel = DEFAULT_AGILITY;
	return defaultProps;
}

int16 PlayerLevelPropertiesTable::GetRequiredMaxExp(int16 level) const
{
	unordered_map<int16, FLevelProperties>::const_iterator it = m_levelPropertiesTable.find(level);
	if (it != m_levelPropertiesTable.end())
	{
		return it->second.maxExperiencePerLevel;
	}

	return DEFAULT_PLAYER_MAX_EXPERIENCE + (level - 1) * ADDITIONAL_EXPERIENCE_PER_LEVEL;
}

