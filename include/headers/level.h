#pragma once
#include <stdlib.h>
#include "headers/game.h"
#include "headers/enemy.h"

class level{
public:
    level(){}
    ~level(){}
    void init(SDL_Renderer* renderer);
    void update();
    void enterStage(int stage);
    static int enemyAmount;
private:
    Uint64 newStageStartTime;
    int stageSpan;

    int spawnWave;
    Uint64 lastSpawnTime;
    
    int currentStage;
    bool newStageStarted;
    SDL_Renderer* renderer;
};