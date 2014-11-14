#ifndef NINJA_H
#define NINJA_H
#include "Personaje.h"

class Ninja: public Personaje
{
    public:
        Ninja(int x, int y,
        SDL_Renderer* renderer,
        list<Personaje*>*personajes);
        void logic(Uint8* teclas_presionadas);
        virtual ~Ninja();
    protected:
    private:
};

#endif // NINJA_H
