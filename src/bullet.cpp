#include "headers/bullet.h"
#include "headers/game.h"
#include <stdlib.h>
#include <math.h>

int bullet::bulletID = 0;
bullet::bullet(position from, position to, SDL_Renderer* renderer, collideType colType, entityTex texName, int damage, float speed, int hp, int size){
    entity();
    this->renderer = renderer;
    this->tex = getTexture(texName);
    this->colType = colType;
    this->speed = speed;
    this->hp = hp;
    this->damage = damage;
    this->texSize = size;
    this->delayHurtTime = 10000;
    setPos(from.x, from.y);
    setVel(getNormalizedVelocity(speed, from, to));
    birthTime = SDL_GetTicks64();
    active = true;
}

void bullet::update(float fframeTime){
    if(!active) return;
    if(SDL_GetTicks64() - birthTime >= lifeSpan) destroy();
    pos.x += vel.xv * fframeTime;
    pos.y += vel.yv * fframeTime;
    if(hp <= 0) destroy();
    if( pos.x + texSize/2*game::scale < -50*game::scale ||
        pos.x - texSize/2*game::scale > game::GameWidth+50*game::scale ||
        pos.y + texSize/2*game::scale < 0-50*game::scale ||
        pos.y - texSize/2*game::scale > game::GameHeight+50*game::scale
    ){
        destroy();
    }
}

void bullet::createBullet(position from, position to, SDL_Renderer* renderer, collideType colType, entityTex texName, int damage, float speed, int hp, int size){
    game::bulletGroup[bullet::bulletID] = new bullet(from, to, renderer, colType, texName, damage, speed, hp, size);
    bullet::bulletID++;
    bullet::bulletID %= game::maxBullets;
}

void bullet::createBullet(position from, position to, SDL_Renderer* renderer, collideType colType, entityTex texName, int damage, float speed, int hp, int size, float accuracyRate){
    int t = accuracyRate * 100;
    if((rand()%100+1) > t) to = from + getRandomAngleDir(to - from);
    game::bulletGroup[bullet::bulletID] = new bullet(from, to, renderer, colType, texName, damage, speed, hp, size);
    bullet::bulletID++;
    bullet::bulletID %= game::maxBullets;
}

position bullet::getRandomAngleDir(position dir){
    float angle = atan2(dir.y, dir.x) * ((float)180/3.14);
    int bias = rand()%10+1;
    if(rand()%2 == 1) angle += bias;
    else angle -= bias;
    angle *= (3.14/(float)180);
    return position(cos(angle), sin(angle));
}