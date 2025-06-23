#pragma once
#include "Common.h"
#include "Util/Singleton.h"


constexpr int32 SCREEN_WIDTH = 128;
constexpr int32 SCREEN_HEIGHT = 64;
constexpr int32 LAYOUT_RATIO = 4;
constexpr int32 PLAYERINFO_PANEL_WIDTH = SCREEN_WIDTH / LAYOUT_RATIO;;
constexpr int32 GAME_PANEL_START_X = PLAYERINFO_PANEL_WIDTH + 1;


class Screen : public Singleton<Screen>
{
	friend class Singleton<Screen>;

private:
	Screen();
	~Screen();
	Screen(const Screen&) = delete;
	Screen& operator = (const Screen&) = delete;

private:
	HANDLE m_consoleBuffers[2];
	int32 m_backBufferIdx;
	WCHAR* m_writeBuffer;

private:
	void VisibleConsoleCursor(bool isVisible);
	bool IsValidCoordinate(const int32& x, const int32& y);
	void Draw(const int32& x, const int32& y, const wchar_t& c);

public:
	void Init();
	void Release();
	void Clear();
	void Draw(const int32& x, const int32& y, const wstring& str);
	void SwapBuffer();

};

