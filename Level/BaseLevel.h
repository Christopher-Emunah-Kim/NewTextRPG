#pragma once
#include "../Common.h"
#include "../Core/IBehavior.h"

//class BaseGameObject;
class BaseCharacter;

class BaseLevel abstract : public IBehavior
{
public:
	BaseLevel(const wstring& tag);
	virtual ~BaseLevel();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Screen* screen) override;
	virtual void Release() override;

	void AddObject(BaseCharacter* object);
	void DetachObject(BaseCharacter* object);
	void RemoveObject(const wstring& tag);
	BaseCharacter* FindObject(const wstring& tag);

	inline const wstring& GetTag() const noexcept { return m_levelTag; }

protected:
	wstring m_levelTag = L" ";
	vector<BaseCharacter*> m_gameObjects;

};

