#pragma once
#include "BaseLevel.h"

class TestLevel final : public BaseLevel
{
public:
	TestLevel(const string& tag) : BaseLevel(tag) { }
	virtual ~TestLevel() = default;

	virtual void Init() override;
	virtual void Update() override;
};

