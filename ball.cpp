//
//  ball.cpp
//  Pong2
//
//  Created by Joshua Matthews on 7/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ball.h"
#include "SDLMain.h"
#include <SDL/SDL.h>


ball::ball(SDL_Surface* img, int x, int y, int h, int w, int xvel, int yvel){
    image=img;
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    xVel=xvel;
    yVel=yvel;
}

ball::~ball()
{
    SDL_FreeSurface(image);
}

void ball::show()
{
    SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(), &box);
    
}
void ball::move(SDL_Rect* player1, SDL_Rect* player2, Mix_Chunk* effect)
{
    
    box.x += xVel;
    box.y += yVel;
    if (box.y<=0){
        yVel = -yVel;
        
    }
    if(box.y + box.h >= SDL_GetVideoSurface()->clip_rect.h){
        yVel = -yVel;
        
    }
    if(collision(&box, player1)){
        Mix_PlayChannel(-1, effect, 0);
        if(box.x+3 < player1->x+player1->w){
            yVel = -yVel;
        }else{
            xVel = -xVel;
        }
    }
    if(collision(player2, &box)){
        Mix_PlayChannel(-1, effect, 0);
        if(box.x + box.w -3 > player2->x)
        {   
            yVel= -yVel;
        }
        else
        {   
            xVel = -xVel;
        }
    }
}

bool ball::collision(SDL_Rect* rec1, SDL_Rect* rec2)
{
    
    if (rec1->y >= rec2->y + rec2->h){
        return 0;
    }
    if (rec1->x >= rec2->x + rec2->w){
        return 0;
    }
    if (rec1->y + rec1->h <= rec2->y){
        return 0;
    }
    if(rec1->x + rec1->w <= rec2->x){
        return 0;
    }
    return 1;
}

int ball::isOut()
{
    
    if(box.x<=0){
        return 1;
    }
    if(box.x >= SDL_GetVideoSurface()->clip_rect.w){
        return 2;
    }
    return 0;
    
}

void ball::setBack(int x, int y, int h, int w, int xvel, int yvel)
{
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    xVel=xvel;
    yVel=yvel;
}