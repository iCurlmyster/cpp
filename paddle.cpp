//
//  paddle.cpp
//  Pong2
//
//  Created by Joshua Matthews on 7/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "paddle.h"
paddle::paddle(SDL_Surface* img, int x, int y,int h, int w, int yvel)
{
    box.x=x;
    box.y=y;
    box.h=h;
    box.w=w;
    image=img;
    yVel=yvel;
    point = 0;
    
}
paddle::~paddle()
{
    SDL_FreeSurface(image);
    
}

void paddle::moveUp()
{
    
    if(box.y>0)
        box.y -= yVel;
    
}

void paddle::moveDown()
{
    if(box.y + box.h < SDL_GetVideoSurface()->clip_rect.h)    
        box.y += yVel;
    
}

void paddle::show()
{
    SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
    
}

SDL_Rect* paddle::getRect()
{
    return &box;
}
void paddle::incpoint()
{
    
    point++;
    
}

void paddle::setBack(int x, int y, int h, int w, int yvel)
{
    box.x=x;
    box.y=y;
    box.h=h;
    box.w=w;
    yVel=yvel;
}
int paddle::getPoints()
{
    return point;
}
