#include "Screen.h"

Screen::Screen()
	: m_writeBuffer(nullptr), m_backBufferIdx(0)
{
	m_consoleBuffers[0] = nullptr;
	m_consoleBuffers[1] = nullptr;
}

Screen::~Screen()
{ }

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

	m_writeBuffer = new char[SCREEN_WIDTH * SCREEN_HEIGHT];
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

	if (m_consoleBuffers[0])
	{
		CloseHandle(m_consoleBuffers[0]);
	}

	if (m_consoleBuffers[1])
	{
		CloseHandle(m_consoleBuffers[1]);
	}
}

void Screen::Clear()
{
	for (int32 i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; ++i)
	{
		m_writeBuffer[i] = ' ';
	}
}

void Screen::Draw(const int32& x, const int32& y, const string& str)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}

	for (size_t i = 0; i < str.length(); ++i)
	{
		int32 screenX = x + i;
		if (screenX >= SCREEN_WIDTH)
		{
			break;
		}

		m_writeBuffer[y * SCREEN_WIDTH + x] = str[i];
	}
}

void Screen::Draw(const int32& x, const int32& y, const char& c)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}

	m_writeBuffer[y * SCREEN_WIDTH + x] = c;
}

void Screen::SwapBuffer()
{
	HANDLE hBackBuffer = m_consoleBuffers[m_backBufferIdx];
	DWORD bytesWritten = 0;

	CHAR_INFO* tempBuffer = new CHAR_INFO[SCREEN_WIDTH * SCREEN_HEIGHT];

	for (int32 i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i)
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

	delete[] tempBuffer;

	SetConsoleActiveScreenBuffer(hBackBuffer);

	m_backBufferIdx = 1 - m_backBufferIdx;

}
