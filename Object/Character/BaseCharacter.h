#pragma once
#include "../BaseGameObject.h"
#include "../../Util/Type/CharacterInfo.h"

class BaseCharacter abstract : public BaseGameObject
{
public:
	BaseCharacter(BaseLevel*, const wstring& tag);
	virtual ~BaseCharacter();

	virtual void Init() override;

	inline wstring GetName() const noexcept { return m_characterInfo.name; }

protected:
	FCharacterInfo m_characterInfo;
};

