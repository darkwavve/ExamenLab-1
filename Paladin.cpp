#include "Paladin.h"

Paladin::Paladin(int x, int y,SDL_Renderer* renderer,
                        list<Personaje*>*personajes)
{
    this->rectangulo.x = x;
    this->rectangulo.y = y;
    this->personajes=personajes;

    SDL_Texture *textura = IMG_LoadTexture(renderer, "assets/personaje/paladin/down1.png");
    SDL_QueryTexture(textura, NULL, NULL, &this->rectangulo.w, &this->rectangulo.h);
    texturas_down.push_back(textura);
    texturas_down.push_back(IMG_LoadTexture(renderer, "assets/personaje/paladin/down2.png"));

    ataque.push_back(IMG_LoadTexture(renderer, "assets/personaje/paladin/ataque.png"));

    texturas_up.push_back(IMG_LoadTexture(renderer, "assets/personaje/paladin/up1.png"));
    texturas_up.push_back(IMG_LoadTexture(renderer, "assets/personaje/paladin/up2.png"));

    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/personaje/paladin/left1.png"));
    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/personaje/paladin/left2.png"));

    texturas_right.push_back(IMG_LoadTexture(renderer, "assets/personaje/paladin/right1.png"));
    texturas_right.push_back(IMG_LoadTexture(renderer, "assets/personaje/paladin/right2.png"));

    orientacion="down";

    textura_actual=texturas_down.begin();
}

Paladin::~Paladin()
{
    //dtor
}

void Paladin::logic(Uint8* teclas_presionadas)
{
    SDL_Rect temp = this->rectangulo;

    if( teclas_presionadas[ SDL_SCANCODE_UP ] )
    {
        rectangulo.y-=1;
        if(orientacion!="up")
            textura_actual=texturas_up.begin();
        orientacion="up";
    }
    if( teclas_presionadas[ SDL_SCANCODE_DOWN ] )
    {
        rectangulo.y+=1;
        if(orientacion!="down")
            textura_actual=texturas_down.begin();
        orientacion="down";
    }
    if( teclas_presionadas[ SDL_SCANCODE_RIGHT ] )
    {
        rectangulo.x+=1;
        if(orientacion!="right")
            textura_actual=texturas_right.begin();
        orientacion="right";
    }
    if( teclas_presionadas[ SDL_SCANCODE_LEFT ] )
    {
        rectangulo.x-=1;
        if(orientacion!="left")
            textura_actual=texturas_left.begin();
        orientacion="left";
    }
    if( teclas_presionadas[SDL_SCANCODE_SPACE])
    {
        textura_actual = ataque.begin();
        orientacion = "ataque";
    }

    for(list<Personaje*>::iterator i = personajes->begin();
            i!=personajes->end();
            i++)
    {
        if(this==(*i))
            continue;
        if(colision(this->rectangulo, (*i)->rectangulo) && teclas_presionadas[SDL_SCANCODE_SPACE])
        {
            personajes->erase(i);
            break;
        }
        if(colision(this->rectangulo, (*i)->rectangulo))
        {
            rectangulo.x = 0;
            rectangulo.y = 0;
            cont++;
            cout<<"Vidas: "<<(5-cont)<<endl;
            break;
        }

    }
}
