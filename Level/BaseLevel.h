#pragma once
#include "../Common.h"
#include "../Core/IBehavior.h"

class BaseGameObject;

class BaseLevel abstract : public IBehavior
{
public:
	BaseLevel(const string& tag);
	virtual ~BaseLevel();

private:
	string m_levelTag = " ";
	vector<BaseGameObject*> m_gameObjects;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void AddObject(BaseGameObject* object);
	void RemoveObject(const string& tag);
	BaseGameObject* FindObject(const string& tag);

	inline string GetTag() const noexcept { return m_levelTag; }
};

