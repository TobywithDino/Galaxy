#include <iostream>
#include <random> /* for random method */
#include <time.h> 
#include "headers/game.h"

int main(int argc, char* argv[]){
    srand(time(NULL));

    game game;
    game.init("Galaxy");
    game.run();
    game.quit();
    return 0;
}