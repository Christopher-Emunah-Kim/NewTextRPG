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
	BaseLevel* m_level = nullptr;
	string m_objectTag = " ";
	vector<BaseComponent*> m_components;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void AddComponent(BaseComponent* component);
	void RemoveComponent(BaseComponent* component);
	vector<BaseComponent*>& GetComponents();

	inline void SetTag(const string& tag) { m_objectTag = tag; }
	inline string GetTag() { return m_objectTag; }
	inline BaseLevel* GetLevel() { return m_level; }
};

