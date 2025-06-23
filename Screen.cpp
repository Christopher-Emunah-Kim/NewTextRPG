#include "Screen.h"

Screen::Screen()
	: m_writeBuffer(nullptr), m_backBufferIdx(0)
{
	m_consoleBuffers[0] = INVALID_HANDLE_VALUE;
	m_consoleBuffers[1] = INVALID_HANDLE_VALUE;
}

Screen::~Screen()
{
	Release();
}

void Screen::VisibleConsoleCursor(bool isVisible)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	
	GetConsoleCursorInfo(m_consoleBuffers[0], &cursorInfo);
	cursorInfo.bVisible = isVisible;
	SetConsoleCursorInfo(m_consoleBuffers[0], &cursorInfo);

	GetConsoleCursorInfo(m_consoleBuffers[1], &cursorInfo);
	cursorInfo.bVisible = isVisible;
	SetConsoleCursorInfo(m_consoleBuffers[1], &cursorInfo);
}

void Screen::Init()
{
	SetConsoleOutputCP(CP_UTF8);

	for (int8 i = 0; i < 2; ++i)
	{
		m_consoleBuffers[i] = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE, //dwDesiredAccess
			0, nullptr, // dwShareMode,*lpSecurityAttributes
			CONSOLE_TEXTMODE_BUFFER, //dwFlags
			nullptr //lpScreenBufferData
		);

		SetConsoleScreenBufferSize(m_consoleBuffers[i], { SCREEN_WIDTH, SCREEN_HEIGHT });

		SMALL_RECT rect = { 
			0, //left
			0, //top
			SCREEN_WIDTH - 1, //right 
			SCREEN_HEIGHT - 1 //bottom
		};

		SetConsoleWindowInfo(m_consoleBuffers[i], TRUE, &rect);
	}

	m_writeBuffer = new WCHAR[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_backBufferIdx = 0;
	Clear();

	VisibleConsoleCursor(false);
}

void Screen::Release()
{
	if (m_writeBuffer)
	{
		delete[] m_writeBuffer;
		m_writeBuffer = nullptr;
	}

	if (m_consoleBuffers[0] != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_consoleBuffers[0]);
	}

	if (m_consoleBuffers[1] != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_consoleBuffers[1]);
	}
}

void Screen::Clear()
{
	for (int32 i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; ++i)
	{
		m_writeBuffer[i] = L' ';
	}
}

void Screen::Draw(const int32& x, const int32& y, const wstring& str)
{
	if (false == IsValidCoordinate(x, y))
	{
		return;
	}

	int32 currentX = x;

	for (size_t i = 0; i < str.length(); ++i)
	{
		//Draw(currentX + static_cast<int32>(i), y, str[i]);
		Draw(currentX, y, str[i]);

		if (IsWideCharacter(str[i]))
		{
			currentX += 2;
		}
		else
		{
			currentX += 1;
		}

	}
}

void Screen::Draw(const int32& x, const int32& y, const wchar_t& c)
{
	if (false == IsValidCoordinate(x, y))
	{
		return;
	}

	m_writeBuffer[y * SCREEN_WIDTH + x] = c;
}

bool Screen::IsValidCoordinate(const int32& x, const int32& y)
{
	if (0 <= x && x < SCREEN_WIDTH && 0 <= y && y < SCREEN_HEIGHT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Screen::IsWideCharacter(const wchar_t& c) const
{
	if (c >= 0xAC00 && c <= 0xD7A3)
	{
		return true;
	}

	return false;
}

void Screen::SwapBuffer()
{
	HANDLE hBackBuffer = m_consoleBuffers[m_backBufferIdx];
	DWORD bytesWritten = 0;

	const int32 screenSize = SCREEN_WIDTH * SCREEN_HEIGHT;
	CHAR_INFO* tempBuffer = new CHAR_INFO[screenSize];

	for (int32 i = 0; i < screenSize; ++i)
	{
		tempBuffer[i].Char.UnicodeChar = static_cast<WCHAR>(m_writeBuffer[i]);
		tempBuffer[i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; //text color(white)
	}


	COORD bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD bufferCoord = { 0, 0 };


	SMALL_RECT writeRegion = { 
		0, 
		0, 
		SCREEN_WIDTH - 1, 
		SCREEN_HEIGHT - 1 };

	WriteConsoleOutputW(hBackBuffer, tempBuffer, bufferSize, bufferCoord, &writeRegion);


	SetConsoleActiveScreenBuffer(hBackBuffer);

	m_backBufferIdx = (m_backBufferIdx) % 2;

	delete[] tempBuffer;
}
