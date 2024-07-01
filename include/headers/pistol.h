#pragma once
#include "headers/weapon.h"

class pistol : public weapon{
public:
    pistol(SDL_Renderer* renderer, entity* e, float shootPointOffset, collideType colType);
    pistol(){};
    ~pistol(){};

    virtual void shoot(position to) override;
private:

};