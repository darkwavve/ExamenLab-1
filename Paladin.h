#ifndef PALADIN_H
#define PALADIN_H
#include "Personaje.h"

class Paladin : public Personaje
{
    public:
        Paladin(int x, int y,
        SDL_Renderer* renderer,
        list<Personaje*>*personajes);
        void logic(Uint8* teclas_presionadas);
        virtual ~Paladin();
    protected:
    private:
};

#endif // PALADIN_H
