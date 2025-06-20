#pragma once
#include "Common.h"
#include "Util/Singleton.h"


constexpr int32 SCREEN_WIDTH = 128;
constexpr int32 SCREEN_HEIGHT = 64;


class Screen : public Singleton<Screen>
{
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
	void Draw(const int32& x, const int32& y, const char& c);

public:
	void Init();
	void Release();
	void Clear();
	void Draw(const int32& x, const int32& y, const string& str);
	void SwapBuffer();


};

