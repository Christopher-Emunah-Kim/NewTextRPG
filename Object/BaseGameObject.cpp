#include "BaseGameObject.h"
#include "../Level/BaseLevel.h"
#include "../Component/BaseComponent.h"
#include "../Util/OutputSystem.h"

BaseGameObject::BaseGameObject(BaseLevel* level, const wstring& tag, const wstring& type)
	: m_level{level}, m_objectTag(tag), m_objectType(type)
{
	/*if (m_level)
	{
		m_level->AddObject(this);
	}
	else
	{
		OutputSystem::PrintErrorMsg(L"GameObject가 추가될 Level 이 존재하지 않습니다.");
	}*/
}

BaseGameObject::~BaseGameObject()
{
	Release();
}

void BaseGameObject::Init()
{
	for (size_t i = 0; i < m_components.size(); ++i)
	{
		BaseComponent* comp = m_components[i];
		if (comp)
		{
			comp->Init();
		}
	}
}

void BaseGameObject::Update()
{
	for (size_t i = 0; i < m_components.size(); ++i)
	{
		BaseComponent* comp = m_components[i];
		if (comp)
		{
			comp->Update();
		}
	}
}


void BaseGameObject::Render(Screen* screen)
{
	for (size_t i = 0; i < m_components.size(); ++i)
	{
		BaseComponent* comp = m_components[i];
		if (comp)
		{
			comp->Render(screen);
		}
	}
}

void BaseGameObject::Release()
{
	for (size_t i = 0; i < m_components.size(); ++i)
	{
		BaseComponent* comp = m_components[i];
		if (comp)
		{
			comp->Release();
			delete comp;
			comp = nullptr;
		}
	}
	m_components.clear();
}

void BaseGameObject::Interact(BaseGameObject* other)
{
	if (other && !m_message.empty())
	{
		GameInstance::GetInstance()->DisplaySystemText(m_message);
	}
}

void BaseGameObject::ProcessEvent(const wstring& eventName)
{
	wstring evenKey = L"event_" + eventName;
	if (HasCustomField(evenKey))
	{
		wstring eventResponse = GetCustomField(evenKey);
		GameInstance::GetInstance()->DisplaySystemText(eventResponse);
	}
}


void BaseGameObject::AddComponent(BaseComponent* component)
{
	if (component)
	{
		m_components.push_back(component);

		sort(m_components.begin(), m_components.end(),
			[](const BaseComponent* left, const BaseComponent* right) {
				return left->GetOrder() < right->GetOrder();
			});
	}
}

void BaseGameObject::RemoveComponent(BaseComponent* component)
{
	if (component)
	{
		vector<BaseComponent*>::iterator it = remove(m_components.begin(), m_components.end(), component);
		if (it != m_components.end())
		{
			m_components.erase(it);
			delete component; //TODO 여기서 메모리 해제를 해도되나?
		}
	}
}

vector<BaseComponent*>& BaseGameObject::GetComponents()
{
	return m_components;
}

void BaseGameObject::SetTag(const wstring& tag) noexcept
{
	m_objectTag = tag;
}

void BaseGameObject::SetType(const wstring& type) noexcept
{
	m_objectType = type;
}

void BaseGameObject::SetMessage(const wstring& message) noexcept
{
	m_message = message;
}

//void BaseGameObject::SetPosition(const int32& x, const int32& y) noexcept
//{
//	m_x = x;
//	m_y = y;
//}

void BaseGameObject::SetLevel(BaseLevel* level)
{
	m_level = level;
}

//void BaseGameObject::UpdateLevel(BaseLevel* level)
//{
//	if (m_level && m_level != level)
//	{
//		m_level->DetachObject(this);
//	}
//
//	m_level = level;
//
//	if (m_level)
//	{
//		m_level->AddObject(this);
//	}
//}

bool BaseGameObject::IsComponentsEmpty() const
{
	return m_components.empty();
}

void BaseGameObject::SetCustomField(const wstring& key, const wstring& value)
{
	m_customFields[key] = value;
}

wstring BaseGameObject::GetCustomField(const wstring& key) const
{
	map<wstring, wstring>::const_iterator it = m_customFields.find(key);
	if (it != m_customFields.end())
	{
		return it->second;
	}
	return L" ";
}

bool BaseGameObject::HasCustomField(const wstring& key) const
{
	return m_customFields.find(key) != m_customFields.end();
}

wstring BaseGameObject::SerializeStateToString() const
{
	wstring serializedText = m_objectType + L"|" + m_objectTag + L"|" + m_message + L"|";

	serializedText += L"FIELDS";

	for (map<wstring, wstring>::const_iterator it = m_customFields.begin(); it != m_customFields.end(); ++it)
	{
		pair<wstring, wstring> field = *it;
		serializedText += field.first + L"=" + field.second + L";";
	}

	return serializedText;
}

void BaseGameObject::LoadStateFromString(const wstring& serializedState)
{
	vector<wstring> parts;
	size_t start = 0;
	size_t end = serializedState.find(L"|");

	while (end != wstring::npos)
	{
		parts.push_back(serializedState.substr(start, end - start));
		start = end + 1;
		end = serializedState.find(L"|", start);
	}

	parts.push_back(serializedState.substr(start));

	if (parts.size() >= 3)
	{
		m_objectType = parts[0];
		m_objectTag = parts[1];
		m_message = parts[2];

		if (parts.size() >= 4 && parts[3].substr(0, 7) == L"FIELDS")
		{
			wstring customFieldText = parts[3].substr(7);
			m_customFields.clear();

			size_t fieldStart = 0;
			size_t fieldEnd = customFieldText.find(L";");

			while (fieldEnd != wstring::npos)
			{
				wstring fieldPair = customFieldText.substr(fieldStart, fieldEnd - fieldStart);
				size_t equalSign = fieldPair.find(L"=");

				if (equalSign != wstring::npos)
				{
					wstring key = fieldPair.substr(0, equalSign);
					wstring value = fieldPair.substr(equalSign + 1);
					m_customFields[key] = value;
				}

				fieldStart = fieldEnd + 1;
				fieldEnd = customFieldText.find(L";", fieldStart);
			}
		}
	}
}

void BaseGameObject::RegisterNewLevelArea(BaseLevel* newLevel)
{
	if (GetLevel() != newLevel)
	{
		if (GetLevel())
		{
			GetLevel()->DetachObject(this);
		}

		SetLevel(newLevel);
		
		if (newLevel)
		{
			newLevel->AddObject(this);
		}
	}
}