//
//  ball.h
//  Pong2
//
//  Created by Joshua Matthews on 7/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//
#include "SDLMain.h"
#include <SDL/SDL.h>
#include <SDL_mixer/SDL_mixer.h>
#ifndef BALL_H
#define BALL_H
class ball{
    
    int xVel,yVel;
    SDL_Surface* image;
    SDL_Rect box;
    bool collision(SDL_Rect* rec1,SDL_Rect* rec2);
public:
    ball(SDL_Surface* img, int x, int y, int h, int w, int xvel, int yvel);
    ~ball();
    void show();
    void move(SDL_Rect* player1, SDL_Rect* player2,Mix_Chunk*);
    int isOut();
    void setBack(int x, int y, int h, int w, int xvel, int yvel);
    
    
    
};

#endif