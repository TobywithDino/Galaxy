#pragma once
#include "headers/weapon.h"

class machinegun : public weapon{
public:
    machinegun(SDL_Renderer* renderer, entity* e, float shootPointOffset, collideType colType);
    machinegun(){};
    ~machinegun(){};

private:
};