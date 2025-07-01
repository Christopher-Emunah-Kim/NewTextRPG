#pragma once
#include "../Common.h"
#include "../Core/GameInstance.h"


class OutputSystem
{

public:

	static void PrintErrorMsg(const wstring& errorMessage) 
	{
		wcout << L"[Error] " << errorMessage << endl;
	}
	static void PrintInfoMsg(const wstring& infoMessage) 
	{
		wcout << L"[Info] " << infoMessage << endl;
	}
	static void PrintWarningMsg(const wstring& warningMessage) 
	{
		wcout << L"[Warning] " << warningMessage << endl;
	}
	static void PrintSystemMsg(const wstring& systemMessage) 
	{
		wcout << L"[System] " << systemMessage << endl;
	}
	static void ClearScreen()
	{
		system("cls");
	}

};