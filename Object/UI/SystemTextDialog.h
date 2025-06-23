#pragma once
#include "../BaseGameObject.h"

class SystemTextDialog final : public BaseGameObject
{
public:
	SystemTextDialog(BaseLevel* level);
	virtual ~SystemTextDialog() = default;

	virtual void Init() override;

	void SetSystemText(const wstring& text);

	void ClearSystemText();

	void RegisterSystemTextInNewLevel(BaseLevel* newLevel);
};

