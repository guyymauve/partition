#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <cctype>
#include <ctime>
#include <errno.h>
#include <SDL/SDL.h>
#include "Debut.h"

using namespace std;

Debut::Debut(int numerateur, int denominateur) : m_numerateur(numerateur), m_denominateur(denominateur)
{

}

SDL_Surface* Debut::afficher(SDL_Surface* ecranBis, int* taille)
{

    SDL_Surface* cle(NULL);
    SDL_Rect positionCle;

    positionCle.x = *taille;
    positionCle.y = 81;

    cle = SDL_LoadBMP("./images/cleSol.bmp");
    SDL_SetColorKey(cle, SDL_SRCCOLORKEY, SDL_MapRGB(cle->format, 0, 255, 0));
    SDL_BlitSurface(cle, NULL, ecranBis, &positionCle);

    SDL_Surface* numerateurS(NULL);
    SDL_Surface* denominateurS(NULL);
    positionCle.x += cle->w - 15;
    positionCle.y += 15;

    switch (m_numerateur)
    {
    case 1:
        numerateurS = SDL_LoadBMP("./images/1.bmp");
        break;
    case 2:
        numerateurS = SDL_LoadBMP("./images/2.bmp");
        break;
    case 3:
        numerateurS = SDL_LoadBMP("./images/3.bmp");
        break;
    case 4:
        numerateurS = SDL_LoadBMP("./images/4.bmp");
        break;
    case 5:
        numerateurS = SDL_LoadBMP("./images/5.bmp");
        break;
    case 6:
        numerateurS = SDL_LoadBMP("./images/6.bmp");
        break;
    case 8:
        numerateurS = SDL_LoadBMP("./images/8.bmp");
        break;
    }

    switch (m_denominateur)
    {
    case 1:
        denominateurS = SDL_LoadBMP("./images/.bmp");
        break;
    case 2:
        denominateurS = SDL_LoadBMP("./images/2.bmp");
        break;
    case 3:
        denominateurS = SDL_LoadBMP("./images/3.bmp");
        break;
    case 4:
        denominateurS = SDL_LoadBMP("./images/4.bmp");
        break;
    case 5:
        denominateurS = SDL_LoadBMP("./images/5.bmp");
        break;
    case 6:
        denominateurS = SDL_LoadBMP("./images/6.bmp");
        break;
    case 8:
        denominateurS = SDL_LoadBMP("./images/8.bmp");
        break;
    }

    SDL_SetColorKey(numerateurS, SDL_SRCCOLORKEY, SDL_MapRGB(numerateurS->format, 0, 255, 0));
    SDL_SetColorKey(denominateurS, SDL_SRCCOLORKEY, SDL_MapRGB(denominateurS->format, 0, 255, 0));
    SDL_BlitSurface(numerateurS, NULL, ecranBis, &positionCle);
    positionCle.y += numerateurS->h - 4;
    SDL_BlitSurface(denominateurS, NULL, ecranBis, &positionCle);

    *taille += cle->w + numerateurS->w - 15;

    SDL_FreeSurface(numerateurS);
    SDL_FreeSurface(denominateurS);
    SDL_FreeSurface(cle);

    return ecranBis;
}

int Debut::getType()
{
    return 0;
}

void Debut::calculs()
{

}

int Debut::getCasesMesure()
{
    return m_numerateur*16/m_denominateur;
}

Debut::~Debut()
{

}
