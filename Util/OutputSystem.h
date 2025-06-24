#pragma once
#include "../Common.h"
#include "../Core/GameInstance.h"


class OutputSystem
{

public:

	static void PrintErrorMsg(const wstring& errorMessage) {
		wcerr << L"[Error] " << errorMessage << endl;
	}
	static void PrintInfoMsg(const wstring& infoMessage) {
		wcerr << L"[Info] " << infoMessage << endl;
	}
	static void PrintWarningMsg(const wstring& warningMessage) {
		GameInstance::GetInstance()->DisplaySystemText(L"[Warning] " + warningMessage);
	}
	static void PrintSystemMsg(const wstring& systemMessage) {
		GameInstance::GetInstance()->DisplaySystemText(L"[System] " + systemMessage);
	}
	static void PrintLine() {
		GameInstance::GetInstance()->DisplaySystemText(L"\n\n===========================================================\n\n");
	}
	static void ClearScreen()
	{
		system("cls");
	}

};