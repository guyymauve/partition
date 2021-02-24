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
#include "Silence.h"

using namespace std;

Silence::Silence(int duree, int bpm) : Figure(duree, bpm), m_typeS(ZERO)
{}

SDL_Surface* Silence::afficher(SDL_Surface* ecran, int* taille)
{
    SDL_Surface* silence(NULL);
    SDL_Rect positionSilence;

    positionSilence.x = *taille;

    switch (m_typeS)
    {
    case QUARTSOUPIR :
        silence = SDL_LoadBMP("qsoupir.bmp");
        positionSilence.y = 34 + 75;
        break;
    case DEMISOUPIR :
        silence = SDL_LoadBMP("dsoupir.bmp");
        positionSilence.y = 31 + 75;
        break;
    case SOUPIR :
        silence = SDL_LoadBMP("soupir.bmp");
        positionSilence.y = 18 + 75;
        break;
    case DEMIPAUSE :
        silence = SDL_LoadBMP("dpause.bmp");
        positionSilence.y = 34 + 75;
        break;
    case PAUSE :
        silence = SDL_LoadBMP("pause.bmp");
        positionSilence.y = 28 + 75;
        break;
    }
    positionSilence.y += 8;

    if (m_point)
    {
        SDL_Surface* point = SDL_LoadBMP("point.bmp");
        SDL_Rect positionPoint;
        positionPoint.x = positionSilence.x + silence->w;
        positionPoint.y = 116;
        SDL_SetColorKey(point, SDL_SRCCOLORKEY, SDL_MapRGB(point->format, 0, 255, 0));
        SDL_BlitSurface(point, NULL, ecran, &positionPoint);
        SDL_FreeSurface(point);
        *taille += 8;
    }

    SDL_SetColorKey(silence, SDL_SRCCOLORKEY, SDL_MapRGB(silence->format, 0, 255, 0));
    SDL_BlitSurface(silence, NULL, ecran, &positionSilence);

    *taille += silence->w + 8;

    SDL_FreeSurface(silence);

    return ecran;
}

void Silence::calculs()
{

    int cases((m_duree*m_bpm)/15000);

    switch (cases)
    {
    case 27:
    case 26:
    case 25:
    case 24:
    case 23:
    case 22:
    case 21:
    case 20:
        m_point = 1;
    case 19:
    case 18:
    case 17:
    case 16:
    case 15:
    case 14:
        m_typeS = PAUSE;
        break;
    case 13:
    case 12:
    case 11:
    case 10:
        m_point = 1;
    case 9:
    case 8:
    case 7:
        m_typeS = DEMIPAUSE;
        break;
    case 6:
    case 5:
        m_point = 1;
    case 4:
        m_typeS = SOUPIR;
        break;
    case 3:
        m_point = 1;
    case 2:
        m_typeS = DEMISOUPIR;
        break;
    case 1:
        m_typeS = QUARTSOUPIR;
        break;
    default:
        m_typeS = ZERO;
        break;
    }
}

Silence::~Silence()
{

}
