#include <time.h>  
#include "Game.h"  

int main()  
{  
	std::locale::global(std::locale("ko_KR.UTF-8"));
	std::srand(static_cast<unsigned int>(time(nullptr)));

    Game game;  

	if (false == game.Init())
	{
		return 0;
	}

    game.Run();  

	return 0;
}
