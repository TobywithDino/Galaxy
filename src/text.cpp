#include "headers/text.h"
#include "headers/game.h"
#include <iostream>

/*
    text funtions:
*/
TTF_Font* text::font;
int text::wordID = 0;
constexpr SDL_Color text::menuTextColor;
constexpr SDL_Color text::gameUITextColor;
constexpr SDL_Color text::playerHurtTextColor;
constexpr SDL_Color text::enemyHurtTextColor;

void text::init(SDL_Renderer* renderer){
    this->renderer = renderer;
    font = TTF_OpenFont("res/GothicA1-Light.ttf", 12);     
    if(renderer == nullptr) std::cout << "text::init() : error, can't get renderer\n";
    if(font == nullptr) std::cout << "text::init() : can't open font : " << TTF_GetError() << std::endl;   
    playerHPBar = new bar(position(0,0), {210, 180, 180}, {255, 60, 0}, game::p, 2, 5, false, renderer);
    escButton = new button(60, 30, buttonTex::menuButton, "ESC", 20, renderer);
    resumeButton = new button(140, 40, buttonTex::menuButton, "RESUME", 20, renderer);
    menuButton = new button(140, 40, buttonTex::menuButton, "MENU", 25, renderer);
    menuButton->setActive(false);
    resumeButton->setActive(false);
    openingESC = false;
}

void text::handleEvent(SDL_Event e){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if(e.type == SDL_MOUSEBUTTONDOWN){
        if(e.button.button == SDL_BUTTON_LEFT){
            if(escButton->checkClick(position(mouseX, mouseY))) openESC(true);
        }
    }
    if(e.type == SDL_MOUSEBUTTONUP){
        if(e.button.button == SDL_BUTTON_LEFT){
            if(resumeButton->checkClick(position(mouseX, mouseY))) openESC(false);
            if(menuButton->checkClick(position(mouseX, mouseY))) backToMenu();
        }
    }
    if(e.type == SDL_KEYDOWN){
        if(e.key.keysym.sym == SDLK_ESCAPE){
            if(!openingESC) openESC(true);
            else openESC(false);
        }
    }
}

void text::openESC(bool open){
    openingESC = open;
    game::pauseGame(open);
    menuButton->setActive(open);
    resumeButton->setActive(open);
    escButton->setActive(!open);
}

void text::backToMenu(){
    openESC(false);
    game::changeGameState(gameState::menu);
}

void text::update(){
    playerHPBar->update(position(game::GameWidth/2, game::GameHeight-5*game::scale));
    escButton->update(position(game::GameWidth-50*game::scale, 30*game::scale));
    menuButton->update(position(game::GameWidth/2, game::GameHeight/2+50*game::scale));
    resumeButton->update(position(game::GameWidth/2, game::GameHeight/2));
}

void text::render(){
    playerHPBar->render();
    escButton->render();
    menuButton->render();
    resumeButton->render();
}

SDL_Texture* text::getTextTexture(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color color){
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(textTexture == nullptr) std::cout << "text::getTextTexture() : can't get texture (" << text << ")\n";
    return textTexture;
}

void text::creatDisappearWord(position* pos, float size, std::string text, SDL_Color color, SDL_Renderer* renderer){
    game::wordGroup[wordID] = new word(pos, size, text, color, renderer, true);
    wordID++;
    wordID %= game::maxWords;
}

/*
    word funtions:
*/
word::word(position* pos, float size, std::string text, SDL_Color color, SDL_Renderer* renderer, bool disappear){
    this->pos = pos;
    this->size = size;
    this->text = text;
    this->color = color;
    this->renderer = renderer;
    this->disappear = disappear;
    this->tex = text::getTextTexture(this->renderer, text::font, this->text, this->color);
    this->birthTime = SDL_GetTicks64();
    this->lifeSpan = 800;//milliseconds
    this->active = true;
}

void word::render(){
    if(!active) return;
    TTF_SetFontSize(text::font, size);
    SDL_Rect dst;
    dst.w = size * text.size() * game::scale;
    dst.h = size * game::scale;
    dst.x = pos->x - dst.w/2;
    dst.y = pos->y - dst.h/2;
    if(SDL_RenderCopy(renderer, tex, NULL, &dst) != 0) std::cout << "word::render() error occur: " << SDL_GetError() << std::endl;
}

void word::update(position* pos){
    this->pos = pos;
    if(!active || !disappear) return;
    if(SDL_GetTicks64() - birthTime >= lifeSpan) active = false;
}

void word::setText(std::string newText){
    this->text = newText;
    this->tex = text::getTextTexture(renderer, text::font, newText, color);
}