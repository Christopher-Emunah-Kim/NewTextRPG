#pragma once
#include "BaseComponent.h"
#include "../Common.h"


class SystemRendererComp : public BaseComponent
{
public:
	SystemRendererComp(BaseGameObject* owner);
	virtual ~SystemRendererComp() = default;

private:
	queue<wstring> m_textQueue;
	int8 m_selectedOption = 0;
	vector<wstring> m_optionTexts;
	vector<wstring> m_optionEvents;
	bool m_IsAwaitingSlections = false;

public: 
	virtual void Render(Screen* screen) override;
	virtual void Update() override;

	void SetText(const wstring& text);
	void EnqueueText(const wstring& text);
	void ClearTexts();

	void AddOption(const wstring& option, const wstring& eventName);
	void ClearOption();
	void SelectNextOption();
	void SelectPreviousOption();
	void ConfirmSelection();

	inline bool HasOptions() const { return !m_optionTexts.empty(); }
	inline int8 GetSelectedOption() const noexcept { return m_selectedOption; }
	inline const vector<wstring>& GetOptionTexts() const { return m_optionTexts; }
};

