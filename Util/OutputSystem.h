#pragma once
#include "../Common.h"


class OutputSystem
{

public:

	static void PrintErrorMsg(const string& errorMessage) {
		cerr << "[Error] " << errorMessage << endl;
	}
	static void PrintInfoMsg(const string& infoMessage) {
		cout << "[Info] " << infoMessage << endl;
	}
	static void PrintWarningMsg(const string& warningMessage) {
		cerr << "[Warning] " << warningMessage << endl;
	}
	static void PrintSystemMsg(const string& systemMessage) {
		cout << "[System] " << systemMessage << endl;
	}
	static void PrintLine() {
		cout << "\n\n===========================================================\n\n" << endl;
	}
	static void ClearScreen()
	{
		system("cls");
	}

	/*static string ToLower(const string& str) {
		string lowerStr = str;
		transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
		return lowerStr;
	}
	static string ToUpper(const string& str) {
		string upperStr = str;
		transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
		return upperStr;
	}*/
};