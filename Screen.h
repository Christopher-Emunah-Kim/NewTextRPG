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

	void VisibleConsoleCursor(bool isVisible);

private:
	HANDLE m_consoleBuffers[2];
	int32 m_backBufferIdx;
	char* m_writeBuffer;


public:
	void Init();
	void Release();
	void Clear();
	void Draw(const int32& x, const int32& y, const string& str);
	void Draw(const int32& x, const int32& y, const char& c);
	void SwapBuffer();


};

