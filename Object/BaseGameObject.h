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
	BaseGameObject(BaseLevel* level, const wstring& tag);
	virtual ~BaseGameObject();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	vector<BaseComponent*>& GetComponents();

	void SetLevelArea(BaseLevel* level);
	void SetTag(const wstring& tag) noexcept;

	bool IsComponentsEmpty() const;
	void RegisterInLevelArea(BaseLevel* level);
	void AddComponent(BaseComponent* component);
	void RemoveComponent(BaseComponent* component);

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
	T* GetComponentByType() const
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
	
	inline wstring		GetTag() const noexcept { return m_objectTag; }
	inline BaseLevel*	GetLevel() const noexcept { return m_levelArea; }

protected:
	BaseLevel* m_levelArea = nullptr;
	wstring m_objectTag = L"";
	vector<BaseComponent*> m_components;
};

