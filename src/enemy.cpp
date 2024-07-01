#include "headers/enemy.h"
#include "headers/bullet.h"
#include "headers/game.h"
#include "headers/sparkle.h"
#include "headers/fort.h"
#include <stdlib.h>

int enemy::enemyID = 0;
enemy::enemy(){
    entity();
    enemyWeapon = new weapon();
    leaving = false;
    willLeave = false;
    stayTime = 0;
    spawnTime = SDL_GetTicks64();
    leaveDir = position(rand()%201-100, rand()%201-100);
}

void enemy::update(float fframeTime){
    if(willLeave){
        if(SDL_GetTicks64() - spawnTime >= stayTime){
            travelMap = false;
            leaving = true;
            accelerate(leaveDir, fframeTime);
            if( pos.x + texSize/2 < 0 ||
                pos.x - texSize/2 > game::GameWidth ||
                pos.y + texSize/2 < 0 ||
                pos.y - texSize/2 > game::GameHeight
            ){
                active = false;
            }
        }
    }
    if(!travelMap){
        if( pos.x > 0 &&
            pos.x < game::GameWidth &&
            pos.y > 0 &&
            pos.y < game::GameHeight)
        {
            travelMap = true;
        }
    }
    entity::update(fframeTime);
}

void enemy::createEnemy(enemyType eType, SDL_Renderer* renderer, position pos, int tier){
    switch (eType)
    {
    case enemyType::sparkle:
        game::enemyGroup[enemy::enemyID] = new sparkle(renderer, pos);
        break;
    case enemyType::fort:
        game::enemyGroup[enemy::enemyID] = new fort(renderer, pos);
        break;
    default:
        std::cout << "enemy::createEnemy : Not including this enemyType\n";
        break;
    }
    game::enemyGroup[enemy::enemyID]->upgrade(tier);
    enemy::enemyID++;
    enemy::enemyID %= game::maxEnemies;
    level::enemyAmount++;
}
void enemy::createEnemy(enemyType eType, SDL_Renderer* renderer, int amount, int tier){
    for(int i=0;i<amount;i++){
        createEnemy(eType, renderer, getRandomSpawnPos(), tier);
    }
}

position enemy::getRandomSpawnPos(){
    float x, y;
    int r = rand()%4;//0=left 1=up 2=right 3=down
    if(r == 0){
        x = -50 * game::scale;
        y = rand() % game::GameHeight;
    }else if(r == 1){
        x = rand() % game::GameWidth;
        y = -50 * game::scale;
    }else if(r == 2){
        x = 50*game::scale + game::GameWidth;
        y = rand() % game::GameHeight;
    }else if(r == 3){
        x = rand() % game::GameWidth;
        y = 50*game::scale + game::GameHeight;
    }
    return position(x,y);
}

void enemy::shoot(position to){
    if(!enemyWeapon->isActive()) return;
    enemyWeapon->shoot(to);
}

//include from and to, also return positon with float values.
position enemy::getRandomSquarePos(int from, int to){
    float x = rand()%(100*(to-from)) + 100*from;
    float y = rand()%(100*(to-from)) + 100*from;
    x/=100;
    y/=100;
    return position(x,y);
}