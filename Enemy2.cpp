#include "Enemy2.h"

Enemy2::Enemy2(int x, int y,SDL_Renderer* renderer,
            list<Personaje*>* personajes)
{
    mode = 3;
    this->rectangulo.x = x;
    this->rectangulo.y = y;
    this->personajes=personajes;
    SDL_Texture *textura = IMG_LoadTexture(renderer, "assets/npcs/npc3/right1.png");
    SDL_QueryTexture(textura, NULL, NULL, &this->rectangulo.w, &this->rectangulo.h);

    texturas_right.push_back(textura);
    texturas_right.push_back(IMG_LoadTexture(renderer, "assets/npcs/npc3/right2.png"));

    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/npcs/npc3/left1.png"));
    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/npcs/npc3/left2.png"));

    textura_actual=texturas_right.begin();

    orientacion="right";
}

void Enemy2::logic(Uint8* teclas_presionadas)
{
//    SDL_Rect temp = this->rectangulo;

    if(mode == 1)
    {
    rectangulo.x++;
    if(orientacion!="right")
            textura_actual=texturas_right.begin();
    orientacion="right";
        if(rectangulo.x > 500 - rectangulo.w)
            mode = 3;
    }
    if(mode == 3)
    {
    rectangulo.x--;
    if(orientacion!="left")
            textura_actual=texturas_left.begin();
    orientacion="left";
        if(rectangulo.x < 100)
            mode = 1;
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
