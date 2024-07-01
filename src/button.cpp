#include "headers/button.h"

button::button(int w, int h, buttonTex texName, std::string texts, int textSize, SDL_Renderer* renderer){
    this->pos = position(0,0);
    this->width = w;
    this->height = h;
    this->wordOnButton = new word(&this->pos, textSize, texts, getColor(texName), renderer, false);
    this->renderer = renderer;
    this->tex = getTexture(texName);
    this->active = true;
}

void button::render(){
    if(!active) return;
    SDL_Rect dst;
    dst.w = width * game::scale;
    dst.h = height * game::scale;
    dst.x = pos.x - dst.w/2;
    dst.y = pos.y - dst.h/2;
    if(SDL_RenderCopy(renderer, tex, NULL, &dst) != 0) std::cout << "word::render() error occur: " << SDL_GetError() << std::endl;
    wordOnButton->render();
}

void button::update(position pos){
    if(!active) return;
    this->pos = pos;
}

bool button::checkClick(position mouse){
    if(!active) return false;
    if( pos.x - width*game::scale/2 < mouse.x  &&
        pos.x + width*game::scale/2 > mouse.x  &&
        pos.y - height*game::scale/2 < mouse.y &&
        pos.y + height*game::scale/2 > mouse.y )
    {
        return true;
    }
    else
    {
        return false;
    }
}

SDL_Texture* button::getTexture(buttonTex texName){
    SDL_Texture* tex = nullptr;
    if(texName == buttonTex::menuButton) tex = IMG_LoadTexture(renderer, "res/menuButton.png");

    if(tex == nullptr)  std::cout << "button::getTexture : could not load texture.\n";

    return tex;
}

SDL_Color button::getColor(buttonTex texName){
    SDL_Color c;
    switch (texName)
    {
    case buttonTex::menuButton:
        c = text::menuTextColor;
        break;
    
    default:
        break;
    }
    return c;
}