#pragma once
#include "game.h"
#include "headers/entity.h"
#include "headers/bullet.h"
#include "headers/weapon.h"
#include "headers/pistol.h"
#include "headers/machinegun.h"

class player : public entity{
public:
    player(position pos, SDL_Renderer* renderer);
    player(){active = false;};
    ~player() {};
    void respawn(position pos) override;
    virtual void handleEvent(SDL_Event e) override;
    virtual void update(float fframeTime) override;
private:
    position moveDir;
    bool accelerating;
    weapon* playerWeapon;
    void shoot();
    bool playerHoldingRightButton;
    bool playerHoldingLeftButton;
    bool playerHoldingKey;
    bool playerHoldingRightKey;
    bool playerHoldingLeftKey;
    bool playerHoldingUpKey;
    bool playerHoldingDownKey;
};