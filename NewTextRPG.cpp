#include <time.h>  
#include "Game.h"  

int main()  
{  
    srand(static_cast<unsigned int>(time(NULL)));  

    Game game;  

	if (false == game.Init())
	{
		return 0;
	}

    game.Run();  

	return 0;
}
