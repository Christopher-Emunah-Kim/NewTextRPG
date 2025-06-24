//#pragma once
//#include "../BaseGameObject.h"
//
//class SystemTextDialog final : public BaseGameObject
//{
//public:
//	SystemTextDialog(BaseLevel* level);
//	virtual ~SystemTextDialog() = default;
//
//private:
//	int8 m_selectedOption= 0;
//	vector<wstring> m_optionTexts;
//	vector<wstring> m_optionEvents;
//	bool m_awaitingSelection = false;
//
//public:
//	virtual void Init() override;
//	virtual void Update() override;
//
//	void SetSystemText(const wstring& text);
//
//	void AddOption(const wstring& option, const wstring& eventName);
//
//	void ClearSystemText();
//
//	void ClearOptions();
//
//	int8 GetSelectedOption() const { return m_selectedOption; }
//
//	void SelectNextOption();
//
//	void SelectPreviousOption();
//
//	void ConfirmSelection();
//
//	bool HasOptions() const { return !m_optionTexts.empty(); }
//
//	const vector<wstring>& GetOptionTexts() const { return m_optionTexts; }
//
//	void RegisterSystemTextInNewLevel(BaseLevel* newLevel);
//};
//
