#include "headers/sparkle.h"
#include "headers/game.h"
#include <math.h>
#include <iostream>

sparkle::sparkle(SDL_Renderer* renderer, position pos){
    enemy();
    this->renderer = renderer;
    this->tex = getTexture(entityTex::sparkleTex);
    this->texSize = 24;
    this->colType = collideType::enemyCollider;
    setPos(pos);
    setVel(0,0);
    setAcce(0,0);
    this->speed = 45;
    this->fullHp = 2;
    this->hp = fullHp;
    this->damage = 2;
    this->accelerationSpeedRatio = 1;
    this->frictionSpeedRatio = 0.1;
    this->chaseTime = getRandomInt(600, 750);//milliseconds
    this->lastChaseTime = SDL_GetTicks64();
    this->chasing = true;
    this->moveDir = position(0,0);
    this->active = true;
}

void sparkle::update(float fframeTime){
    if(!active) return;
    chasePlayer(fframeTime);
    enemy::update(fframeTime);
}

void sparkle::chasePlayer(float fframeTime){
    if(!chasing && vel == velocity(0,0)){
        chasing = true;
        moveDir = position(game::p->getPos().x - pos.x,
                            game::p->getPos().y - pos.y)
                + getRandomSquarePos(-10*game::scale, 10*game::scale);
        lastChaseTime = SDL_GetTicks64();
    }
    if(chasing) accelerate(moveDir, fframeTime);
    if(chasing && SDL_GetTicks64() - lastChaseTime > chaseTime) chasing = false;
}

//include a and b
int sparkle::getRandomInt(int a, int b){
    if(a == b) return a;
    if(a > b) std::swap(a,b);
    return rand()%(b-a) + a;
}