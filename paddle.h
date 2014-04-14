//
//  paddle.h
//  Pong2
//
//  Created by Joshua Matthews on 7/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//
#include "SDLMain.h"
#include <SDL/SDL.h>

#ifndef PADDLE_H
#define PADDLE_H

class paddle{
    SDL_Rect box;
    SDL_Surface* image;
    int yVel;
    int point;
public:
    paddle(SDL_Surface* img, int x, int y, int h, int w, int yvel);
    ~paddle();
    SDL_Rect* getRect();
    void moveUp();
    void moveDown();
    void show();
    void incpoint();
    void setBack(int x, int y, int h, int w, int yvel);
    int getPoints();
    
};


#endif
