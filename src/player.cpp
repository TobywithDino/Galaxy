#include "headers/player.h"
#include <iostream>
#include <math.h>

player::player(position pos, SDL_Renderer* renderer){
    entity();
    this->renderer = renderer;
    this->tex = getTexture(entityTex::playerTex);
    this->colType = collideType::playerCollider;
    setPos(pos);
    setVel(0,0);
    setAcce(0,0);
    this->speed = 30;
    this->fullHp = 100;
    this->hp = fullHp;
    this->hpRegen = 0.3;
    this->damage = 0;
    this->accelerationSpeedRatio = 0.3;
    this->frictionSpeedRatio = 0.03;
    this->texSize = 32;
    this->moveDir = position(0,0);
    this->accelerating = false;
    this->playerWeapon = new pistol(renderer, this, texSize/2*game::scale-5*game::scale, collideType::playerBulletCollider);
    this->playerHoldingLeftButton = false;
    this->playerHoldingRightButton = false;
    this->playerHoldingKey = false;
    this->travelMap = true;
    this->active = true;
}

void player::respawn(position pos){
    entity();
    this->tex = getTexture(entityTex::playerTex);
    this->colType = collideType::playerCollider;
    setPos(pos);
    setVel(0,0);
    setAcce(0,0);
    this->speed = 30;
    this->fullHp = 20;
    this->hp = fullHp;
    this->damage = 0;
    this->accelerationSpeedRatio = 0.3;
    this->frictionSpeedRatio = 0.03;
    this->texSize = 32;
    this->moveDir = position(0,0);
    this->accelerating = false;
    this->playerWeapon = new pistol(renderer, this, texSize/2*game::scale-5*game::scale, collideType::playerBulletCollider);
    this->playerHoldingLeftButton = false;
    this->playerHoldingRightButton = false;
    this->playerHoldingKey = false;
    this->travelMap = true;
    this->active = true;
}

void player::handleEvent(SDL_Event e){
    if(!active) return;
    if(game::isPausing()) return;
    if(e.type == SDL_MOUSEBUTTONDOWN){
        if(e.button.button == SDL_BUTTON_LEFT) playerHoldingLeftButton = true;
        if(e.button.button == SDL_BUTTON_RIGHT) playerHoldingRightButton = true;
    }

    if(e.type == SDL_MOUSEBUTTONUP){
        if(e.button.button == SDL_BUTTON_LEFT) playerHoldingLeftButton = false;
        if(e.button.button == SDL_BUTTON_RIGHT) playerHoldingRightButton = false;
    }

    if(e.type == SDL_KEYDOWN){
        playerHoldingKey = true;
        if(e.key.keysym.sym == SDLK_w) playerHoldingUpKey = true;
        if(e.key.keysym.sym == SDLK_s) playerHoldingDownKey = true;
        if(e.key.keysym.sym == SDLK_a) playerHoldingLeftKey = true;
        if(e.key.keysym.sym == SDLK_d) playerHoldingRightKey = true;
    }

    if(e.type == SDL_KEYUP){
        playerHoldingKey = false;
        if(e.key.keysym.sym == SDLK_w) playerHoldingUpKey = false;
        if(e.key.keysym.sym == SDLK_s) playerHoldingDownKey = false;
        if(e.key.keysym.sym == SDLK_a) playerHoldingLeftKey = false;
        if(e.key.keysym.sym == SDLK_d) playerHoldingRightKey = false;
    }
    
    if(playerHoldingRightButton){
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        moveDir = position(mouseX - pos.x, mouseY - pos.y);
        float x = moveDir.x;
        float y = moveDir.y;
        float dis = sqrt(x*x + y*y);
        if(dis >= texSize*game::scale/2) accelerating = true;
        else accelerating = false;
    }else if(playerHoldingKey){
        int x=0, y=0;
        if(playerHoldingUpKey) y-=1;
        if(playerHoldingDownKey) y+=1;
        if(playerHoldingRightKey) x+=1;
        if(playerHoldingLeftKey) x-=1;
        moveDir = position(x, y);
        accelerating = true;
    }else accelerating = false;

    if(playerHoldingLeftButton){
        shoot();
    }
}

void player::update(float fframeTime){
    if(accelerating) entity::accelerate(moveDir, fframeTime);
    entity::update(fframeTime);
}

void player::shoot(){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    float x = abs(mouseX - pos.x);
    float y = abs(mouseY - pos.y);
    float dis = sqrt(x*x + y*y);
    if(dis < texSize*game::scale/2) return;

    playerWeapon->shoot(position(mouseX, mouseY));
}