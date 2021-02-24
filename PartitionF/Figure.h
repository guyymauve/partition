#ifndef DEF_FIGURE
#define DEF_FIGURE

#include "Element.h"

class Figure : public Element
{
    public:
    Figure(int duree, int bpm);
    virtual SDL_Surface* afficher(SDL_Surface* ecran, int* taille);
    virtual void calculs();
    virtual int getType();
    int getCases();
    virtual ~Figure();

    protected:
    int m_duree;
    bool m_point;
    bool m_vide;
    int m_bpm;

};

#endif // DEF_FIGURE
