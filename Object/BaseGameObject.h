#pragma once
#include "../Common.h"
#include "../Util/Type/StatusType.h"
#include "../Util/Type/LootType.h"
#include "../Core/IBehavior.h"

class BaseComponent;
class BaseLevel;

class BaseGameObject abstract : public IBehavior
{
public:
	BaseGameObject(BaseLevel* level, const string& tag);
	virtual ~BaseGameObject();

private:
	int32 m_x;
	int32 m_y;
	BaseLevel* m_level = nullptr;
	string m_objectTag = " ";
	vector<BaseComponent*> m_components;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	inline string		GetTag() const noexcept { return m_objectTag; }
	inline BaseLevel* GetLevel() const noexcept { return m_level; }
	inline int32		GetX() const noexcept { return m_x; }
	inline int32		GetY() const noexcept { return m_y; }

	void SetTag(const string& tag) noexcept;
	void SetPosition(const int32& x, const int32& y) noexcept;
	void SetLevel(BaseLevel* level);

	void AddComponent(BaseComponent* component);
	void RemoveComponent(BaseComponent* component);
	void UpdateLevel(BaseLevel* level);
	bool IsComponentsEmpty() const;
	vector<BaseComponent*>& GetComponents();
};

