#ifndef DEF_ELEMENT
#define DEF_ELEMENT

class Element
{
    public:
    virtual SDL_Surface* afficher(SDL_Surface* ecran, int* taille) = 0;
    virtual ~Element();
    virtual void calculs() = 0;
    virtual int getType() = 0;

    protected:

};

#endif // DEF_ELEMENT
