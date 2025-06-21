#pragma once
#include "BaseGameObject.h"

class SystemTextDialog : public BaseGameObject
{
public:
	SystemTextDialog(BaseLevel* level);
	virtual ~SystemTextDialog() = default;

	virtual void Init() override;

	void SetSystemText(const string& text) noexcept;
};

