#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<list>
#include "PersonajeJugador.h"
#include "NPC.h"
#include "Ninja.h"
#include "Paladin.h"
#include "Enemy.h"
#include "Enemy2.h"
#include <stdlib.h>     /* srand, rand */

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character, *menu,*game_over,*win,*charselection;
SDL_Rect rect_background,rect_character;

void loopMenu();

void gameWinner()
{
while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
             if(Event.key.keysym.sym == SDLK_ESCAPE)
            {
                loopMenu();
            }
        }
        SDL_RenderCopy(renderer, win, NULL, &rect_background);
        SDL_RenderPresent(renderer);
    }
}

void gameOver()
{
while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
             if(Event.key.keysym.sym == SDLK_ESCAPE)
            {
                loopMenu();
            }
        }
        SDL_RenderCopy(renderer, game_over, NULL, &rect_background);
        SDL_RenderPresent(renderer);
    }
}

void comenzarJuego(int mode)
{
    list<Personaje*>personajes;
    int s = personajes.size();
    if(mode == 0)
        personajes.push_back(new Ninja (0,0,renderer,&personajes));
    if(mode == 1)
        personajes.push_back(new PersonajeJugador (0,0,renderer,&personajes));
    if(mode == 2)
        personajes.push_back(new Paladin (0,0,renderer,&personajes));
    personajes.push_back(new NPC (100,0,renderer,&personajes));
    personajes.push_back(new Enemy (250,0,renderer,&personajes));
    personajes.push_back(new Enemy2 (250,125,renderer,&personajes));

    //Main Loop
    int frame=0;int cont=0;

    while(true)
    {
     frame++;
        if(frame%250==0)
        {
            personajes.push_back(new NPC (100,0,renderer,&personajes));
            personajes.push_back(new Enemy ((rand() % 350)+100,0,renderer,&personajes));
            personajes.push_back(new Enemy2 (250,(rand() % 150)+50,renderer,&personajes));
        }
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
             if(Event.key.keysym.sym == SDLK_ESCAPE)
            {
                loopMenu();
            }
        }

        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
            (*i)->logic((Uint8*)SDL_GetKeyboardState( NULL ));

        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
            {
            (*i)->render(renderer);
            if((*i)->cont > 4)
                    gameOver();
            }
        if(personajes.size() <= 1)
            gameWinner();

        SDL_RenderPresent(renderer);

        SDL_Delay(16.66);
    }
}

void charSelection()
{
    int mode = 0;
    list<Personaje*>chars;
    chars.push_back(new Ninja (65,150,renderer,&chars));
    chars.push_back(new PersonajeJugador (210,150,renderer,&chars));
    chars.push_back(new Paladin (360,150,renderer,&chars));
     while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {
                 if(Event.key.keysym.sym == SDLK_a)
                    mode = 0;
                if(Event.key.keysym.sym == SDLK_s)
                    mode = 1;
                if(Event.key.keysym.sym == SDLK_d)
                    mode = 2;
                if(Event.key.keysym.sym == SDLK_RETURN)
                    comenzarJuego(mode);
            }
        }
        SDL_RenderCopy(renderer, charselection, NULL, &rect_background);
        for(list<Personaje*>::iterator i = chars.begin();
                i!=chars.end();
                i++)
        (*i)->render(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16.66);
    }
}

void loopMenu()
{
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_RETURN)
                {
//                    comenzarJuego();
                    charSelection();
                }
            }
        }
        SDL_RenderCopy(renderer, menu, NULL, &rect_background);
        SDL_RenderPresent(renderer);
    }
}

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    character = IMG_LoadTexture(renderer, "assets/personaje/down.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;rect_character.y = 100;rect_character.w = w;rect_character.h = h;

    menu = IMG_LoadTexture(renderer, "menu.png");
    game_over = IMG_LoadTexture(renderer, "gameover.png");
    win = IMG_LoadTexture(renderer, "uwin.png");
    charselection = IMG_LoadTexture(renderer, "charselection.png");

    loopMenu();

    return 0;
}
