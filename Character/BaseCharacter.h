#pragma once
#include "../Core/IBehavior.h"
#include "../Util/Type/CharacterInfo.h"

class BaseLevel;

class BaseCharacter abstract : public IBehavior
{
public:
	BaseCharacter(BaseLevel* level, const wstring& tag);
	virtual ~BaseCharacter();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	void SetLevelArea(BaseLevel* level);
	inline wstring GetTag() const noexcept { return m_characterTag; }
	inline wstring GetName() const noexcept { return m_characterInfo.name; }
	inline BaseLevel* GetLevel() const noexcept { return m_levelArea; }

protected:
	FCharacterInfo m_characterInfo;
	BaseLevel* m_levelArea = nullptr;
	wstring m_characterTag = L"";

};

