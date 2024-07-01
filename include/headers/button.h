#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "headers/position.h"
#include "headers/text.h"

enum class buttonTex{
    menuButton
};

class word;
class button{
public:
    button(int w, int h, buttonTex texName, std::string texts, int textSize, SDL_Renderer* renderer);
    button(){active = false;};
    ~button(){};

    position getPos() {return pos;};
    void setPos(position pos) {this->pos = pos;};
    void setActive(bool set){ active = set;};
    void render();
    void update(position pos);
    bool checkClick(position mouse);
    word* wordOnButton;
private:
    position pos;//center of the button
    int width;
    int height;
    bool active;
    SDL_Texture* tex;
    SDL_Renderer* renderer;
    
    SDL_Texture* getTexture(buttonTex texName);
    SDL_Color getColor(buttonTex texName);
};