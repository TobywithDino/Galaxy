#pragma once

struct velocity{
    velocity(float xv, float yv){
        this->xv = xv;
        this->yv = yv;
    };
    velocity(){};
    ~velocity(){};
    bool operator==(velocity b){
        if(xv != b.xv) return xv == b.xv;
        else return yv == b.yv;
    }
    velocity operator+(velocity b){
        return velocity(xv+b.xv, yv+b.yv);
    }
    velocity operator-(velocity b){
        return velocity(xv-b.xv, yv-b.yv);
    }

    float xv;
    float yv;
};