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
	BaseGameObject(BaseLevel* level, const wstring& tag);
	virtual ~BaseGameObject();

private:
	int32 m_x;
	int32 m_y;
	BaseLevel* m_level = nullptr;
	wstring m_objectTag = L" ";
	vector<BaseComponent*> m_components;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	vector<BaseComponent*>& GetComponents();

	void SetLevel(BaseLevel* level);
	void SetTag(const wstring& tag) noexcept;
	void SetPosition(const int32& x, const int32& y) noexcept;

	bool IsComponentsEmpty() const;
	void UpdateLevel(BaseLevel* level);
	void AddComponent(BaseComponent* component);
	void RemoveComponent(BaseComponent* component);
	
	inline wstring		GetTag() const noexcept { return m_objectTag; }
	inline BaseLevel* GetLevel() const noexcept { return m_level; }
	inline int32		GetX() const noexcept { return m_x; }
	inline int32		GetY() const noexcept { return m_y; }

	template<typename T>
	bool HasComponentType() const
	{
		for (size_t i = 0; i < m_components.size(); ++i)
		{
			BaseComponent* comp = m_components[i];
			if (dynamic_cast<T*>(comp) != nullptr)
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	T* GetComponentsByType() const
	{
		for (size_t i = 0; i < m_components.size(); ++i)
		{
			T* typedComp = dynamic_cast<T*>(m_components[i]);
			if (typedComp != nullptr)
			{
				return typedComp;
			}
		}
		return nullptr;
	}
};

