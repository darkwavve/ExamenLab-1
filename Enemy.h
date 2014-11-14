#ifndef ENEMY_H
#define ENEMY_H
#include "Personaje.h"

class Enemy : public Personaje
{
    public:
        Enemy(int x, int y,SDL_Renderer* renderer,
            list<Personaje*>*personajes);
        void logic(Uint8* teclas_presionadas);
    protected:
    private:
};

#endif // ENEMY_H
