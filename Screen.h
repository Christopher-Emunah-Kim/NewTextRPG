#pragma once
#include "Common.h"
#include "Util/Singleton.h"


constexpr int32 SCREEN_WIDTH = 128;
constexpr int32 SCREEN_HEIGHT = 50;
constexpr int32 LAYOUT_RATIO = 4;
constexpr int32 PLAYERINFO_PANEL_WIDTH = 32; //SCREEN_WIDTH / LAYOUT_RATIO
constexpr int32 GAME_PANEL_START_X = PLAYERINFO_PANEL_WIDTH + 2; //MARGIN
constexpr int8 BUFFER_SIZE = 2;


class Screen : public Singleton<Screen>
{
public:
	Screen() = default;
	virtual ~Screen();
	Screen(const Screen&) = delete;
	Screen& operator = (const Screen&) = delete;

private:
	HANDLE m_consoleBuffers[BUFFER_SIZE] = { INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE };
	int32 m_backBufferIdx = 0;
	WCHAR* m_writeBuffer = nullptr;

private:
	void VisibleConsoleCursor(bool isVisible);
	bool IsValidCoordinate(const int32& x, const int32& y);
	bool IsWideCharacter(const wchar_t& c) const;

public:
	void Init();
	void Release();
	void Clear();
	void SwapBuffer();
	void Draw(const int32& x, const int32& y, const wchar_t& c);
	void Draw(const int32& x, const int32& y, const wstring& str);

};

