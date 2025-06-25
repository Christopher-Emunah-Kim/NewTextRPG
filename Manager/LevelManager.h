#pragma once
#include "../Common.h"
#include "../Util/Singleton.h"
#include "../Core/IBehavior.h"

class BaseLevel;

class LevelManager final : public Singleton<LevelManager>, public IBehavior
{
public:
	LevelManager() = default;
	virtual ~LevelManager();

private:
	BaseLevel* m_currentLevel = nullptr;
	BaseLevel* m_nextLevel = nullptr;
	unordered_map<wstring, BaseLevel*> m_levels;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	bool IsSetNextLevel() const;
	void SetNextLevel(const wstring& name);
	void ChangeLevel();

	inline BaseLevel* GetCurrentLevel() const { return m_currentLevel; }
	inline BaseLevel* GetNextLevel() const { return m_nextLevel; }
};

