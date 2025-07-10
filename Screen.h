#pragma once
#include "Common.h"
#include "Util/Singleton.h"

constexpr int32 SCREEN_WIDTH = 128;
constexpr int32 SCREEN_HEIGHT = 42;
constexpr int32 RESOLUTION = SCREEN_HEIGHT * SCREEN_WIDTH;
constexpr int32 LAYOUT_RATIO = 4;
constexpr int32 PLAYERINFO_PANEL_WIDTH = 32; //SCREEN_WIDTH / LAYOUT_RATIO
constexpr int32 GAME_PANEL_START_X = PLAYERINFO_PANEL_WIDTH + 2; //MARGIN
constexpr int8 BUFFER_SIZE = 2;

class Screen final
{
public:
	virtual ~Screen();

private:
	void VisibleConsoleCursor(bool isVisible);
	bool IsValidCoordinate(int32 x, int32 y);
	bool IsHangulSyllable(const wchar_t& c) const;

public:
	void Init();
	void Release();
	void Clear();
	void SwapBuffer();
	void Draw(int32 x, int32 y, const wchar_t& c);
	void Draw(int32 x, int32 y, const wstring& str);

private:
	HANDLE m_consoleBuffers[BUFFER_SIZE] = { INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE };
	int32 m_backBufferIdx = 0;
	WCHAR m_writeBuffer[SCREEN_HEIGHT][SCREEN_WIDTH] = { };

};

