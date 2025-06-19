#include <time.h>  
#include "Game.h"  

int main()  
{  
    srand(static_cast<unsigned int>(time(NULL)));  
    Game game;  
    game.Run();  
}
