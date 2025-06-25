#pragma once
#include "../Common.h"
#include "../Core/GameInstance.h"


class OutputSystem
{

public:

	static void PrintErrorMsg(const wstring& errorMessage) 
	{
		wcerr << L"[Error] " << errorMessage << endl;
	}
	static void PrintInfoMsg(const wstring& infoMessage) 
	{
		wcerr << L"[Info] " << infoMessage << endl;
	}
	static void PrintWarningMsg(const wstring& warningMessage) 
	{
		wcerr << L"[Warning] " << warningMessage << endl;
	}
	static void PrintSystemMsg(const wstring& systemMessage) 
	{
		wcerr << L"[System] " << systemMessage << endl;
	}
	static void PrintLine() 
	{
		wcerr << L"\n\n===========================================================\n\n" << endl;
	}
	static void ClearScreen()
	{
		system("cls");
	}

};