#pragma once
#include "../Common.h"
#include "../Util/Type/StatusType.h"
#include "../Util/Type/Experience.h"
#include "../Core/IBehavior.h"


class BaseComponent;
class BaseLevel;

class BaseGameObject abstract : public IBehavior
{
public:
	explicit BaseGameObject(BaseLevel* level, const wstring& tag);
	virtual ~BaseGameObject();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	void SetLevelArea(BaseLevel* level);

	inline wstring		GetTag() const noexcept { return m_objectTag; }
	inline BaseLevel* GetLevel() const noexcept { return m_levelArea; }

protected:
	BaseLevel* m_levelArea = nullptr;
	wstring m_objectTag = L"";
	vector<BaseComponent*> m_components;
};

