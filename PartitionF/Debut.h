#ifndef DEF_DEBUT
#define DEF_DEBUT

#include "Element.h"
#include "enums.h"


class Debut : public Element
{
    public:
    Debut(int numerateur, int denominateur);
    virtual SDL_Surface* afficher(SDL_Surface* ecranBis, int* taille);
    virtual int getType();
    virtual void calculs();
    int getCasesMesure();
    virtual ~Debut();

    protected:
    int m_numerateur;
    int m_denominateur;

};

#endif // DEF_DEBUT
