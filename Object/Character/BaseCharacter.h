#pragma once
#include "../BaseGameObject.h"
#include "../../Util/Type/CharacterInfo.h"

class BaseCharacter abstract : public BaseGameObject
{
public:
	BaseCharacter(BaseLevel*, const wstring& tag);
	virtual ~BaseCharacter();

protected:
	FCharacterInfo m_characterInfo;

public:
	virtual void Init() override;

	virtual void Interact(BaseCharacter* other) {};


	void SetName(const wstring& name);
	void SetDescription(const wstring& desc);
	void SetLevel(int16 level);

	inline wstring GetName() const noexcept { return m_characterInfo.name; }
	inline wstring GetDescription() const noexcept { return m_characterInfo.description; }
	inline int16 GetCharacterLevel() const noexcept { return m_characterInfo.characterLevel; }
	inline const FCharacterInfo& GetCharacterInfo() const noexcept { return m_characterInfo; }
};

