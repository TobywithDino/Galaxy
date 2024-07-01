#include "headers/level.h"
#include <iostream>

int level::enemyAmount;

void level::init(SDL_Renderer* renderer){
    this->renderer = renderer;
    this->newStageStarted = false;
    this->currentStage = 0;
    this->stageSpan = 2000;
    this->newStageStartTime = SDL_GetTicks64();
    this->lastSpawnTime = 0;
    this->spawnWave = 1;
    this->enemyAmount = 0;
}

void level::update(){
    if(SDL_GetTicks64() - newStageStartTime >= stageSpan){
        currentStage++;
        newStageStartTime = SDL_GetTicks64();
    }
    enterStage(currentStage);
}

void level::enterStage(int stage){
    if(spawnWave == 0) return;
    if(SDL_GetTicks64() - lastSpawnTime < stageSpan/spawnWave) return;
    lastSpawnTime = SDL_GetTicks64();
    switch (stage)
    {
    case 1:
        stageSpan = 30000;
        spawnWave = 3;
        enemy::createEnemy(enemyType::sparkle, renderer, 4, 1);
        break;
    case 2:
        stageSpan = 30000;
        spawnWave = 5;
        enemy::createEnemy(enemyType::sparkle, renderer, 2, 1);
        enemy::createEnemy(enemyType::fort, renderer, 1, 1);
        break;
    case 3:
        stageSpan = 15000;
        spawnWave = 15;
        enemy::createEnemy(enemyType::sparkle, renderer, 1, 1);
        break;
    case 4:
        stageSpan = 15000;
        spawnWave = 7;
        enemy::createEnemy(enemyType::fort, renderer, 1, 1);
    default:
        break;
    }
}