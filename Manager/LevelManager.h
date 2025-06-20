#pragma once
#include "../Common.h"
#include "../Util/Singleton.h"
#include "../Core/IBehavior.h"

class BaseLevel;

class LevelManager : public Singleton<LevelManager>, public IBehavior
{
public:
	LevelManager() = default;
	virtual ~LevelManager();

private:
	BaseLevel* m_currentLevel = nullptr;
	BaseLevel* m_nextLevel = nullptr;
	unordered_map<string, BaseLevel*> m_levels;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	bool IsSetNextLevel() const;
	void SetNextLevel(const string& name);
	void ChangeLevel();
};

