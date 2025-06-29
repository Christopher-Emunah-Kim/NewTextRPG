#pragma once

#include "../Common.h"
#include "BaseLevel.h"

class CsmLevel final : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;

	virtual ~CsmLevel() = default;

	void Init() override;
	void Render(Screen* screen) override;

private:
	void Welcome();
	void EnterVillage();
	void EnterDungeon();
	void GoToHell();

	void AddText(wstring text);
	void ClearText();
private:
	std::vector<std::wstring> _texts{ };
};