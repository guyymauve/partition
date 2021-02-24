#ifndef DEF_NOTE
#define DEF_NOTE

#include "enums.h"
#include "Figure.h"
#include <SDL/SDL.h>

class Note : public Figure
{
    public:
    Note(int duree, int frequence, int bpm);
    virtual SDL_Surface* afficher(SDL_Surface* ecran, int* taille);
    virtual void calculs();
    virtual ~Note();

    protected:
    int m_frequence; //
    Hauteurs m_hauteur; //
    TypeN m_type; //
    int m_octave; //
    bool m_diese; //
    bool m_bemol; //

};

#endif // DEF_NOTE
