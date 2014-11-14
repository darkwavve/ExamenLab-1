#ifndef ENEMY2_H
#define ENEMY2_H
#include "Personaje.h"

class Enemy2 : public Personaje
{
    public:
        Enemy2(int x, int y,SDL_Renderer* renderer,
            list<Personaje*>*personajes);
        void logic(Uint8* teclas_presionadas);
    protected:
    private:
};

#endif // ENEMY2_H
