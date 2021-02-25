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
#include "Note.h"

using namespace std;

Note::Note(int duree, int frequence, int bpm) : Figure(duree, bpm), m_frequence(frequence), m_hauteur(RIEN), m_type(NUL), m_octave(0), m_diese(0), m_bemol(0)
{}

SDL_Surface* Note::afficher(SDL_Surface* ecran, int* taille)
{
    SDL_Surface* note(NULL);
    SDL_Surface* diese(NULL);
    SDL_Surface* point(NULL);
    SDL_Rect positionNote;
    SDL_Rect positionDiese;
    SDL_Rect positionPoint;

    positionNote.x = *taille;
    positionNote.y = 0;

    positionDiese.x = 0;
    positionDiese.y = 24;

    positionPoint.x = 0;
    positionPoint.y = 0;

    switch (m_type)
    {
    case DCROCHE :
        note = SDL_LoadBMP("./images/dcroche.bmp");
        if ((m_octave == 4) && (m_hauteur != DO))
        {
            note = SDL_LoadBMP("./images/dcroche2.bmp");
            positionDiese.y = -5;
        }
        break;
    case CROCHE :
        note = SDL_LoadBMP("./images/croche.bmp");
        if ((m_octave == 4) && (m_hauteur != DO))
        {
            note = SDL_LoadBMP("./images/croche2.bmp");
            positionDiese.y = -5;
            positionPoint.x = 4;
        }
        break;
    case NOIRE :
        note = SDL_LoadBMP("./images/noire.bmp");
        if ((m_octave == 4) && (m_hauteur != DO))
        {
            note = SDL_LoadBMP("./images/noire2.bmp");
            positionDiese.y = -5;
        }
        break;
    case BLANCHE :
        note = SDL_LoadBMP("./images/blanche.bmp");
        if ((m_octave == 4) && (m_hauteur != DO))
        {
            note = SDL_LoadBMP("./images/blanche2.bmp");
            positionDiese.y = -5;
        }
        break;
    case RONDE :
        note = SDL_LoadBMP("./images/ronde.bmp");
        break;
    }

    if ((m_octave == 1) && (m_hauteur == DO))
        positionNote.y = 243;
    if ((m_octave == 1) && (m_hauteur == RE))
        positionNote.y = 236;
    if ((m_octave == 1) && (m_hauteur == MI))
        positionNote.y = 229;
    if ((m_octave == 1) && (m_hauteur == FA))
        positionNote.y = 222;
    if ((m_octave == 1) && (m_hauteur == SOL))
        positionNote.y = 215;
    if ((m_octave == 1) && (m_hauteur == LA))
        positionNote.y = 207;
    if ((m_octave == 1) && (m_hauteur == SI))
        positionNote.y = 198;

    if ((m_octave == 2) && (m_hauteur == DO))
        positionNote.y = 190;
    if ((m_octave == 2) && (m_hauteur == RE))
        positionNote.y = 182;
    if ((m_octave == 2) && (m_hauteur == MI))
        positionNote.y = 174;
    if ((m_octave == 2) && (m_hauteur == FA))
        positionNote.y = 167;
    if ((m_octave == 2) && (m_hauteur == SOL))
        positionNote.y = 159;
    if ((m_octave == 2) && (m_hauteur == LA))
        positionNote.y = 150;
    if ((m_octave == 2) && (m_hauteur == SI))
        positionNote.y = 142;

    if ((m_octave == 3) && (m_hauteur == DO))
        positionNote.y = 134;
    if ((m_octave == 3) && (m_hauteur == RE))
        positionNote.y = 51 + 75;
    if ((m_octave == 3) && (m_hauteur == MI))
        positionNote.y = 44 + 75;
    if ((m_octave == 3) && (m_hauteur == FA))
        positionNote.y = 36 + 75;
    if ((m_octave == 3) && (m_hauteur == SOL))
        positionNote.y = 28 + 75;
    if ((m_octave == 3) && (m_hauteur == LA))
        positionNote.y = 19 + 75;
    if ((m_octave == 3) && (m_hauteur == SI))
        positionNote.y = 12 + 75;

    if ((m_octave == 4) && (m_hauteur == DO))
        positionNote.y = 79;
    if ((m_octave == 4) && (m_hauteur == RE))
        positionNote.y = 100;
    if ((m_octave == 4) && (m_hauteur == MI))
        positionNote.y = 92;
    if ((m_octave == 4) && (m_hauteur == FA))
        positionNote.y = 84;
    if ((m_octave == 4) && (m_hauteur == SOL))
        positionNote.y = 76;
    if ((m_octave == 4) && (m_hauteur == LA))
        positionNote.y = 68;
    if ((m_octave == 4) && (m_hauteur == SI))
        positionNote.y = 60;
    positionNote.y += 8;

  /*  switch (typeCle)
    {
    case UT1 :
        positionNote.y -= 16;
        break;
    case UT2 :
        positionNote.y -= 32;
        break;
    case UT3 :
        positionNote.y -= 48;
        break;
    case UT4 :
        positionNote.y -= 64;
        break;
    case FA3 :
        positionNote.y -= 80;
        break;
    case FA4 :
        positionNote.y -= 96;
        break;
    }

    */

    if ((m_type == RONDE) && (m_octave == 4) && (m_hauteur != DO))
        positionNote.y -= 29;

    positionDiese.x += positionNote.x;
    positionDiese.y += positionNote.y;

    if (m_type == RONDE)
        positionNote.y += 5;

    if (m_diese)
        diese = SDL_LoadBMP("./images/diese.bmp");

    if (diese != NULL)
    {
        SDL_SetColorKey(diese, SDL_SRCCOLORKEY, SDL_MapRGB(diese->format, 0, 255, 0));
        SDL_BlitSurface(diese, NULL, ecran, &positionDiese);
    }

    positionPoint.x += positionDiese.x + note->w - 12;
    positionPoint.y = positionDiese.y + 6;

    if (m_point)
    {
        point = SDL_LoadBMP("./images/point.bmp");
        SDL_SetColorKey(point, SDL_SRCCOLORKEY, SDL_MapRGB(point->format, 0, 255, 0));
        SDL_BlitSurface(point, NULL, ecran, &positionPoint);
        *taille += 8;
    }

    SDL_SetColorKey(note, SDL_SRCCOLORKEY, SDL_MapRGB(note->format, 0, 255, 0));
    SDL_BlitSurface(note, NULL, ecran, &positionNote);

    *taille += note->w;

    SDL_FreeSurface(point);
    SDL_FreeSurface(diese);
    SDL_FreeSurface(note);

    return ecran;
}

void Note::calculs()
{
    int fmin(0);
    int fmax(0);
    int i;

    for (i = 1 ; i < 6 ; i++)
    {
        if (i == 1)
        {
            fmin = 63;
            fmax = ((pow(2,i-1))*FSI + pow(2,i)*FDO)/2;
        }
        else if (i == 5)
        {
            fmax = 2034;
            fmin = ((pow(2,i-2))*FSI + (pow(2,i-1))*FDO)/2;
        }
        else
        {
            fmin = ((pow(2,i-2))*FSI + (pow(2,i-1))*FDO)/2;
            fmax = ((pow(2,i-1))*FSI + pow(2,i)*FDO)/2;
        }

        if (m_frequence >= fmin && m_frequence < (pow(2,i-1))*(FDO + FDOD)/2)
        {
            m_hauteur = DO;
        }
        if (m_frequence >= (pow(2,i-1))*(FDO + FDOD)/2 && m_frequence < (pow(2,i-1))*(FDOD + FRE)/2)
        {
            m_hauteur = DO;
            m_diese = 1;
        }

        if (m_frequence >= (pow(2,i-1))*(FDOD + FRE)/2 && m_frequence < (pow(2,i-1))*(FRE + FRED)/2)
        {
            m_hauteur = RE;
        }
        if (m_frequence >= (pow(2,i-1))*(FRE + FRED)/2 && m_frequence < (pow(2,i-1))*(FRED + FMI)/2)
        {
            m_hauteur = RE;
            m_diese = 1;
        }

        if (m_frequence >= (pow(2,i-1))*(FRED + FMI)/2 && m_frequence < (pow(2,i-1))*(FMI + FFA)/2)
        {
            m_hauteur = MI;
        }
        if (m_frequence >= (pow(2,i-1))*(FMI + FFA)/2 && m_frequence < (pow(2,i-1))*(FFA + FFAD)/2)
        {
            m_hauteur = FA;
        }

        if (m_frequence >= (pow(2,i-1))*(FFA + FFAD)/2 && m_frequence < (pow(2,i-1))*(FFAD + FSOL)/2)
        {
            m_hauteur = FA;
            m_diese = 1;
        }
        if (m_frequence >= (pow(2,i-1))*(FFAD + FSOL)/2 && m_frequence < (pow(2,i-1))*(FSOL + FSOLD)/2)
        {
            m_hauteur = SOL;
        }

        if (m_frequence >= (pow(2,i-1))*(FSOL + FSOLD)/2 && m_frequence < (pow(2,i-1))*(FSOLD + FLA)/2)
        {
            m_hauteur = SOL;
            m_diese = 1;
        }
        if (m_frequence >= (pow(2,i-1))*(FSOLD + FLA)/2 && m_frequence < (pow(2,i-1))*(FLA + FLAD)/2)
        {
            m_hauteur = LA;
        }

        if (m_frequence >= (pow(2,i-1))*(FLA + FLAD)/2 && m_frequence < (pow(2,i-1))*(FLAD + FSI)/2)
        {
            m_hauteur = LA;
            m_diese = 1;
        }
        if (m_frequence >= (pow(2,i-1))*(FLAD + FSI)/2 && m_frequence < fmax)
        {
            m_hauteur = SI;
        }

        if (m_hauteur != RIEN)
        {
            m_octave = i;
            break;
        }

    }

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
        m_type = RONDE;
        break;
    case 13:
    case 12:
    case 11:
    case 10:
        m_point = 1;
    case 9:
    case 8:
    case 7:
        m_type = BLANCHE;
        break;
    case 6:
    case 5:
        m_point = 1;
    case 4:
        m_type = NOIRE;
        break;
    case 3:
        m_point = 1;
    case 2:
        m_type = CROCHE;
        break;
    case 1:
        m_type = DCROCHE;
        break;
    default:
        m_type = RONDE;
        m_point = 1;
        break;
    }


}

Note::~Note()
{

}
