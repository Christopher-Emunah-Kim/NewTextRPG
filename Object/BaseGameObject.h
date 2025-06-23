#pragma once
#include "../Common.h"
#include "../Util/Type/StatusType.h"
#include "../Util/Type/LootType.h"
#include "../Core/IBehavior.h"

class BaseComponent;
class BaseLevel;
class Screen;

class BaseGameObject abstract : public IBehavior
{
public:
	BaseGameObject(BaseLevel* level, const wstring& tag, const wstring& type);
	virtual ~BaseGameObject();

private:
	//int32 m_x;
	//int32 m_y;
	BaseLevel* m_level = nullptr;
	wstring m_objectTag = L" ";
	wstring m_objectType = L" ";
	wstring m_message = L" ";
	vector<BaseComponent*> m_components;
	map<wstring, wstring> m_customFields;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	virtual void Interact(BaseGameObject* other);
	virtual void ProcessEvent(const wstring& eventName);

	//inline int32		GetX() const noexcept { return m_x; }
	//inline int32		GetY() const noexcept { return m_y; }

	void SetTag(const wstring& tag) noexcept;
	void SetType(const wstring& type) noexcept;
	void SetMessage(const wstring& message) noexcept;
	void SetLevel(BaseLevel* level);
	//void SetPosition(const int32& x, const int32& y) noexcept;

	vector<BaseComponent*>& GetComponents();
	void AddComponent(BaseComponent* component);
	void RemoveComponent(BaseComponent* component);
	bool IsComponentsEmpty() const;
	
	void SetCustomField(const wstring& key, const wstring& value);
	wstring GetCustomField(const wstring& key) const;
	bool HasCustomField(const wstring& key) const;

	wstring SerializeStateToString() const;
	void LoadStateFromString(const wstring& serializedState);

	void RegisterNewLevelArea(BaseLevel* newLevel);
	//void UpdateLevel(BaseLevel* level);


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


	inline wstring		GetTag() const noexcept { return m_objectTag; }
	inline wstring		GetType() const noexcept { return m_objectType; }
	inline wstring		GetMessage() const noexcept { return m_message; }
	inline BaseLevel*	GetLevel() const noexcept { return m_level; }
	inline const map<wstring, wstring>& GetAllCustomFields() const noexcept { return m_customFields; }
};

