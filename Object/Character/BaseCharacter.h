#pragma once
#include "../BaseGameObject.h"

class BaseCharacter abstract : public BaseGameObject
{
public:
	BaseCharacter(BaseLevel*, const wstring& tag);
	virtual ~BaseCharacter();

protected:
	wstring m_name;
	wstring m_description;
	int16 m_characterLevel;

public:
	virtual void Init() override;

	virtual void Interact(BaseCharacter* other) = 0;


	void SetName(const wstring& name);
	void SetDescription(const wstring& desc);
	void SetLevel(int16 level);

	inline wstring GetName() const noexcept { return m_name; }
	inline wstring GetDescription() const noexcept { return m_description; }
	inline int16 GetCharacterLevel() const noexcept { return m_characterLevel; }
};

