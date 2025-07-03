#pragma once
#include "../Common.h"
#include "../Util/Type/StatusType.h"
#include "../Util/Type/Experience.h"
#include "../Core/IBehavior.h"


class BaseGameObject;

class BaseComponent abstract : public IBehavior
{
public:
	BaseComponent(BaseGameObject* owner, int32 order = 100);
	virtual ~BaseComponent();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	int32 GetOrder() const;
	
private:
	int32 m_componentOrder = 100;

protected:
	BaseGameObject* m_owner = nullptr;
};

