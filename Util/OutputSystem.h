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
		//wcerr << L"[Warning] " << warningMessage << endl;
		GameInstance::GetInstance()->DisplaySystemText(L"[Warning] " + warningMessage);
	}
	static void PrintSystemMsg(const wstring& systemMessage) {
		//wcout << L"[System] " << systemMessage << endl;
		GameInstance::GetInstance()->DisplaySystemText(L"[System] " + systemMessage);
	}
	static void PrintLine() {
		//wcout << L"\n\n===========================================================\n\n" << endl;
		GameInstance::GetInstance()->DisplaySystemText(L"\n\n===========================================================\n\n");
	}
	static void ClearScreen()
	{
		system("cls");
	}

};