#pragma once
#include "../Common.h"
#include "../Core/IBehavior.h"

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

	void AddObject(IBehavior* object);
	void DetachObject(IBehavior* object);

	inline const wstring& GetTag() const noexcept { return m_levelTag; }

protected:
	wstring m_levelTag = L" ";
	vector<IBehavior*> m_gameObjects;

};

