//
//  main.cpp
//  Pong2
//
//  Created by Joshua Matthews on 7/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include "SDLMain.h"
#include <SDL/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <SDL_mixer/SDL_mixer.h>
#include "ball.h"
#include "paddle.h"


SDL_Surface* load_Image(const char* c)
{
    
    SDL_Surface* tmp=SDL_LoadBMP(c);
    Uint32 colorkey = SDL_MapRGB(tmp->format, 255, 255, 255);
    SDL_SetColorKey(tmp, SDL_SRCCOLORKEY, colorkey);
    
    return tmp;
    
}

int main (int argc,char** argv)
{
    const int FPS = 30;
    const int height = 480;
    const int width = 640;
    SDL_Surface* screen;
    screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("Pong of Death!", NULL);
    TTF_Font* font;
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Music* music;
    Mix_Chunk* effect;
    music = Mix_LoadMUS("My_Song_2.wav");
    effect = Mix_LoadWAV("bassBeat.wav");
    Mix_PlayMusic(music, -1);
    font = TTF_OpenFont("leadcoat.ttf", 20);
    SDL_Color color = {0,0,0};
    SDL_Event event;
    Uint32 start;
    bool running=true;
    bool arr[4]={0,0,0,0};
    paddle player1(load_Image("paddle.bmp"),0,225,96,13,5);
    paddle player2(load_Image("paddle.bmp"),width - 10,225,96,13,5);    
    ball ball1(load_Image("ball.bmp"), 320,240,37,46,5,5);
    while (running) {
        start = SDL_GetTicks();
        //handle events
        while(SDL_PollEvent(&event)){
            
            switch (event.type) {
                case SDL_QUIT:
                    running=false;
                    break;
                    
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            arr[0]=1;
                            break;
                        case SDLK_DOWN:
                            arr[1]=1;
                            break;
                            
                        case SDLK_w:
                            arr[2]=1;
                            break;
                        case SDLK_s:
                            arr[3]=1;
                            break;                            
                        default:
                            break;
                    }
                    break;
                    
                    
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            arr[0]=0;
                            break;
                        case SDLK_DOWN:
                            arr[1]=0;
                            break;
                            
                        case SDLK_w:
                            arr[2]=0;
                            break;
                        case SDLK_s:
                            arr[3]=0;
                            break;                            
                        default:
                            break;
                    }
                    break;
                    
                    
                default:
                    break;
            }
        }
        //logic
        if (arr[0]){
            player2.moveUp();
        }
        else if (arr[1]){
            player2.moveDown();
        }
        if(arr[2]){
            player1.moveUp();
        }
        else if (arr[3]){
            player1.moveDown();
        }
        ball1.move(player1.getRect(), player2.getRect(), effect);
        
        switch (ball1.isOut()) {
            case 1:
                player2.incpoint();
                player1.setBack(0, 225, 96, 13, 5);
                player2.setBack(width - 10, 225, 96, 13, 5);
                ball1.setBack(320, 240, 37, 46, 5, 5);
                break;
                
            case 2:
                player1.incpoint();
                player1.setBack(0, 225, 96, 13, 5);
                player2.setBack(width - 10, 225, 96, 13, 5);
                ball1.setBack(320, 240, 37, 46, 5, 5);
                break;
                
            default:
                break;
        }
        
        //render
        SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 255, 255));
        player1.show();
        player2.show();
        ball1.show();
        SDL_Surface* text;
        //another way to initialize a const char* (in comments)
        //std::stringstream chil, tili;
         char chil[5];
         SDL_Rect temp ={10,0};
         sprintf(chil, "%d", player1.getPoints());
       // chil << player1.getPoints(); same as tili
         text = TTF_RenderText_Solid(font, chil, color);  //chil.str().c_str() inplace of chil
        SDL_BlitSurface(text, NULL,screen, &temp);
        //tili<<player2.getPoints(); puts player2.getPoints() to tili
         temp.x = width-40;
         sprintf(chil, "%d", player2.getPoints());
         text = TTF_RenderText_Solid(font,chil , color);  //tili.str().c_str() inplace of tili
        SDL_BlitSurface(text, NULL, screen, &temp);
         SDL_FreeSurface(text);
        SDL_Flip(screen);
                
        //regulate FPS
        if (1000/FPS>(SDL_GetTicks()-start)) {
            SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
        }
        
    }
    Mix_FreeMusic(music);
    Mix_FreeChunk(effect);
    Mix_CloseAudio();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}


