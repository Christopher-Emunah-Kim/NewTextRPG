#include <time.h>  
#include "Game.h"  

int main()  
{  
	// 로케일 설정-한글출력지원
	setlocale(LC_ALL, "ko_KR.UTF-8");
	std::locale::global(std::locale("ko_KR.UTF-8"));
	std::wcout.imbue(std::locale("ko_KR.UTF-8"));
	std::wcin.imbue(std::locale("ko_KR.UTF-8"));
	// 콘솔 코드 페이지 설정
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);


    srand(static_cast<unsigned int>(time(NULL)));  

    Game game;  

	if (false == game.Init())
	{
		return 0;
	}

    game.Run();  

	return 0;
}
