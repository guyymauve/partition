#ifndef DEF_SILENCE
#define DEF_SILENCE

#include "enums.h"
#include "Figure.h"

class Silence : public Figure
{
    public:
    Silence(int duree, int bpm);
    virtual SDL_Surface* afficher(SDL_Surface* ecran, int* taille);
    virtual void calculs();
    virtual ~Silence();

    protected:
    Silences m_typeS;

};

#endif // DEF_SILENCE
