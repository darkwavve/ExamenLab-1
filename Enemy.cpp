#include "Enemy.h"

Enemy::Enemy(int x, int y,SDL_Renderer* renderer,
            list<Personaje*>* personajes)
{
    mode = 0;
    this->rectangulo.x = x;
    this->rectangulo.y = y;
    this->personajes=personajes;
    SDL_Texture *textura = IMG_LoadTexture(renderer, "assets/npcs/npc2/up1.png");
    SDL_QueryTexture(textura, NULL, NULL, &this->rectangulo.w, &this->rectangulo.h);
    texturas_right.push_back(textura);
    texturas_up.push_back(IMG_LoadTexture(renderer, "assets/npcs/npc2/up2.png"));

    texturas_down.push_back(IMG_LoadTexture(renderer, "assets/npcs/npc2/down1.png"));
    texturas_down.push_back(IMG_LoadTexture(renderer, "assets/npcs/npc2/down2.png"));

    textura_actual=texturas_down.begin();

    orientacion="down";
}

void Enemy::logic(Uint8* teclas_presionadas)
{


   if(mode == 2)
    {
    rectangulo.y--;
    if(orientacion!="up")
            textura_actual=texturas_up.begin();
    orientacion="up";
        if(rectangulo.y < 1)
            mode = 0;
    }
    if(mode == 0)
    {
    rectangulo.y++;
    if(orientacion!="down")
            textura_actual=texturas_down.begin();
    orientacion="down";
        if((rectangulo.y > 250 - rectangulo.h))
            mode = 2;
    }

//    for(list<Personaje*>::iterator i = personajes->begin();
//            i!=personajes->end();
//            i++)
//    {
//        if(this==(*i))
//            continue;
//        if(colision(this->rectangulo, (*i)->rectangulo))
//            rectangulo=temp;
//    }
}
