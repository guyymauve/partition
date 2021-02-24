#ifndef DEF_PARTITION
#define DEF_PARTITION

#include <string>
#include <queue>
#include "Element.h"

class Partition
{
    public:
    void lireFichier(std::string const fichier);
    void conversion();
    SDL_Surface* afficher(SDL_Surface* ecran);
    ~Partition();

    protected:
    std::queue<std::string> m_listeLignes;
    std::queue<Element*> m_listeElements;
    std::queue<Element*> m_listeElements2;

};

#endif // DEF_PARTITION
