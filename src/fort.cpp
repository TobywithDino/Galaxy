#include "headers/fort.h"
#include "headers/game.h"
#include "headers/machinegun.h"
#include <math.h>

fort::fort(SDL_Renderer* renderer, position pos){
    enemy();
    this->renderer = renderer;
    this->tex = getTexture(entityTex::fortTex);
    this->texSize = 44;
    this->colType = collideType::enemyCollider;
    setPos(pos);
    setVel(0,0);
    setAcce(0,0);
    this->speed = 25;
    this->fullHp = 14;
    this->hp = fullHp;
    this->damage = 3;
    this->accelerationSpeedRatio = 0.15;
    this->frictionSpeedRatio = 0.3;
    this->enemyWeapon = new machinegun(renderer, this, 0, collideType::enemyBulletCollider);
    this->lastMoveTime = 0;
    this->moveGapTime = 3000;//milliseconds
    this->moving = true;
    this->sitePos = getSitePos();
    this->willLeave = true;
    this->stayTime = 20000;//milliseconds
    this->active = true;
}

void fort::update(float fframeTime){
    if(!active) return;
    if(!leaving){
        moveToSite(fframeTime);
        if(!moving) enemyWeapon->shoot(game::p->getPos());
    }
    enemy::update(fframeTime);
}

position fort::getSitePos(){
    position sitePos;
    sitePos = game::p->getPos() + getRandomSquarePos(-texSize*5, texSize*5);
    if(sitePos.x < 0) sitePos.x = 0;
    else if(sitePos.x > game::GameWidth) sitePos.x = game::GameWidth;
    if(sitePos.y < 0) sitePos.y = 0;
    else if(sitePos.y > game::GameHeight) sitePos.y = game::GameHeight;
    return sitePos;
}

void fort::moveToSite(float fframeTime){
    if(!moving && SDL_GetTicks64() - lastMoveTime >= moveGapTime) {
        moving = true;
        sitePos = getSitePos();
    }
    if(!moving) return;
    position moveDir = sitePos - pos;
    accelerate(moveDir, fframeTime);
    if(checkOnSite()){
        moving = false;
        lastMoveTime = SDL_GetTicks64();
    }
}

bool fort::checkOnSite(){
    float dis;
    float x = abs(pos.x - sitePos.x);
    float y = abs(pos.y - sitePos.y);
    dis = sqrt(x*x + y*y);
    if(dis < texSize/2) return true;
    return false;
}