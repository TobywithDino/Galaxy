#include "headers/menu.h"
#include <iostream>

void menu::init(SDL_Renderer* renderer){
    this->renderer = renderer;
    titleWord = new word(new position(0,0), 60, "Galaxy", {200,200,200}, renderer, false);
    inspiredWord = new word(new position(0,0), 12, "Referenced from Nova Drift", {230,230,230}, renderer, false);
    creditWord = new word(new position(0,0), 12, "Made by Toby 2023", {230,230,230}, renderer, false);
    startButton = new button(140, 40, buttonTex::menuButton, "START", 25, renderer);
    settingButton = new button(140, 40, buttonTex::menuButton, "SETTING", 18, renderer);
    quitButton = new button(140, 40, buttonTex::menuButton, "QUIT", 25, renderer);
    fullScreenButton = new button(140, 40, buttonTex::menuButton, "FULLSCREEN", 12, renderer);
    resolutionButton = new button(140, 40, buttonTex::menuButton, "1600x900", 16, renderer);
    menuButton = new button(140, 40, buttonTex::menuButton, "MENU", 25, renderer);
    fullScreenButton->setActive(false);
    resolutionButton->setActive(false);
    menuButton->setActive(false);
    openingSetting = false;
    isFullScreen = true;
    currentDPI = gameScreen::screen_1600x900;
}

void menu::handleEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if(event.type == SDL_QUIT) game::changeGameState(gameState::quiting);
    if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT){
            if(startButton->checkClick(position(mouseX, mouseY))) {
                game::refreshObjects(renderer);
                game::changeGameState(gameState::gaming);
            }
            if(quitButton->checkClick(position(mouseX, mouseY))) game::changeGameState(gameState::quiting);
            if(fullScreenButton->checkClick(position(mouseX, mouseY))){
                if(!isFullScreen){
                    game::changeGameScreen(gameScreen::fullScreen);
                    isFullScreen = true;
                }
                else{
                    game::changeGameScreen(currentDPI);
                    isFullScreen = false;
                }
            }
            if(resolutionButton->checkClick(position(mouseX, mouseY))){
                switch (currentDPI)
                {
                case gameScreen::screen_1600x900:
                    currentDPI = gameScreen::screen_1440x810;
                    resolutionButton->wordOnButton->setText("1440x810");
                    break;
                case gameScreen::screen_1440x810:
                    currentDPI = gameScreen::screen_1366x768;
                    resolutionButton->wordOnButton->setText("1366x768");
                    break;
                case gameScreen::screen_1366x768:
                    currentDPI = gameScreen::screen_1280x720;
                    resolutionButton->wordOnButton->setText("1280x720");
                    break;
                case gameScreen::screen_1280x720:
                    currentDPI = gameScreen::screen_1600x900;
                    resolutionButton->wordOnButton->setText("1600x900");
                    break;
                default:
                    break;
                }
                if(!isFullScreen) game::changeGameScreen(currentDPI);
            }
            if(settingButton->checkClick(position(mouseX, mouseY))) openSetting(true);
            if(menuButton->checkClick(position(mouseX, mouseY))) openSetting(false);
        }
    }
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_ESCAPE){
            if(openingSetting) openSetting(false);
        }
    }
}

void menu::update(){
    titleWord->update(new position(game::GameWidth/2, 150*game::scale));
    inspiredWord->update(new position(game::GameWidth-165*game::scale, game::GameHeight-40*game::scale));
    creditWord->update(new position(game::GameWidth-130*game::scale, game::GameHeight-20*game::scale));
    startButton->update(position(game::GameWidth/2, game::GameHeight/2));
    settingButton->update(position(game::GameWidth/2, game::GameHeight/2+50*game::scale));
    quitButton->update(position(game::GameWidth/2, game::GameHeight/2+100*game::scale));
    fullScreenButton->update(position(game::GameWidth/2, game::GameHeight/2));
    resolutionButton->update(position(game::GameWidth/2, game::GameHeight/2+50*game::scale));
    menuButton->update(position(game::GameWidth/2, game::GameHeight/2+100*game::scale));
}

void menu::render(){
    SDL_SetRenderDrawColor(renderer, 70, 70, 145, 255);
    SDL_RenderClear(renderer);
    //start render menu
    titleWord->render();
    inspiredWord->render();
    creditWord->render();
    startButton->render();
    settingButton->render();
    quitButton->render();
    resolutionButton->render();
    fullScreenButton->render();
    menuButton->render();
    //end render menu

    SDL_RenderPresent(renderer);
}

void menu::openSetting(bool open){
    openingSetting = open;
    startButton->setActive(!open);
    settingButton->setActive(!open);
    quitButton->setActive(!open);
    resolutionButton->setActive(open);
    fullScreenButton->setActive(open);
    menuButton->setActive(open);
}