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
#include "Partition.h"
#include "Note.h"
#include "Silence.h"
#include "Debut.h"

using namespace std;

void Partition::lireFichier(string const fichier)
{
    string ligne;

    ifstream fichierNotes(fichier.c_str());
    while (! fichierNotes.eof())
    {
        getline(fichierNotes, ligne);
        m_listeLignes.push(ligne);
    }

    conversion();
}

void Partition::conversion()
{
    char caractere;
    string chaine;
    int frequence, duree, puissance, numerateur, denominateur, bpm;
    char *pEnd;
    int const nombreChaines(m_listeLignes.size());

    for (int i(0) ; i < nombreChaines ; i++)
    {
        chaine = m_listeLignes.front();
        m_listeLignes.pop();
        caractere = chaine[0];
        chaine[0] = ' ';

        if (caractere == 'M')
        {
            char* chaineC = new char[chaine.size() + 1];
            copy(chaine.begin(), chaine.end(), chaineC);
            chaineC[chaine.size()] = '\0';
            frequence = strtol(chaineC, &pEnd, 10);
            duree = strtol(pEnd, &pEnd, 10);
            puissance = strtol(pEnd, NULL, 10);
            delete[] chaineC;
            chaineC = 0;

            if (frequence != 0)
                m_listeElements.push(new Note(duree, frequence, bpm));
            else
                m_listeElements.push(new Silence(duree, bpm));

        }
        else if (caractere == 'D')
        {
            char* chaineC = new char[chaine.size() + 1];
            copy(chaine.begin(), chaine.end(), chaineC);
            chaineC[chaine.size()] = '\0';
            numerateur = strtol(chaineC, &pEnd, 10);
            denominateur = strtol(pEnd, &pEnd, 10);
            bpm = strtol(pEnd, NULL, 10);
            delete[] chaineC;
            chaineC = 0;

            m_listeElements.push(new Debut(numerateur, denominateur));
        }
    }

    for (int i(0) ; i < nombreChaines ; i++)
    {
        if (m_listeElements.front()->getType())
            m_listeElements.front()->calculs();

        m_listeElements2.push(m_listeElements.front());
        m_listeElements.pop();
    }
}

SDL_Surface* Partition::afficher(SDL_Surface* ecran)
{
    int const nombreElements(m_listeElements2.size());
    int numeroPortee(0);
    int* taille(0);
    taille = new int;
    int tailleCases(0);
    bool pititePastille(0);

    SDL_Surface* portee(NULL);
    SDL_Rect positionPortee;

    positionPortee.x = 55;
    positionPortee.y = 20;

    SDL_Surface* barreMesure(SDL_LoadBMP("barreM.bmp"));
    SDL_Rect positionBarre;

    positionBarre.y = 96;

    SDL_Surface* barreMesure2(SDL_LoadBMP("barreD.bmp"));
    SDL_Rect positionBarre2;

    positionBarre2.y = 96;

    portee = SDL_CreateRGBSurface(SDL_HWSURFACE, 1200, 275, 32, 0, 0, 0, 0);
    SDL_FillRect(portee, 0, SDL_MapRGB(portee->format, 0, 255, 0));

    *taille = 0;

    Debut debutPrec(1, 1);
    Figure figureEnCours(1, 1);

    for (int i(0) ; i < nombreElements ; i++)
    {
        if (!m_listeElements2.front()->getType())
        {
            Element& r_element = *m_listeElements2.front();
            Debut& r_debutPrec = dynamic_cast<Debut&>(r_element);
            debutPrec = r_debutPrec;
        }
        else
        {
            Element& r_element = *m_listeElements2.front();
            Figure& r_figureEnCours = dynamic_cast<Figure&>(r_element);
            figureEnCours = r_figureEnCours;
        }

        if (!m_listeElements2.front()->getType() && (i != 0) && (!pititePastille))
        {
            positionBarre2.x = *taille;
            SDL_BlitSurface(barreMesure2, NULL, portee, &positionBarre2);
            tailleCases = 0;
        }
        pititePastille = 0;

        m_listeElements2.front()->afficher(portee, taille);
        if (m_listeElements2.front()->getType())
            tailleCases += figureEnCours.getCases();

        m_listeElements.push(m_listeElements2.front());
        m_listeElements2.pop();

        if (i != nombreElements - 1)
        {
            if ((tailleCases >= debutPrec.getCasesMesure()) && (m_listeElements2.front()->getType())) //Marche ? (étrange)
            {
                positionBarre.x = *taille;
                *taille += 7;
                SDL_BlitSurface(barreMesure, NULL, portee, &positionBarre);
                tailleCases %= debutPrec.getCasesMesure();
            }
        }

        if (*taille >= 1150)
        {
            numeroPortee++;
            SDL_SetColorKey(portee, SDL_SRCCOLORKEY, SDL_MapRGB(portee->format, 0, 255, 0));
            SDL_BlitSurface(portee, NULL, ecran, &positionPortee);

            //Afficher barre de mesure

            *taille = 0;
            SDL_FillRect(portee, 0, SDL_MapRGB(portee->format, 0, 255, 0));
            positionPortee.y = (110 * numeroPortee) + 20;
            pititePastille = 1;
            if (i != nombreElements - 1)
            {
                if (m_listeElements2.front()->getType())
                    debutPrec.afficher(portee, taille);
            }
        }
    }
    SDL_Surface* barreMesure3(SDL_LoadBMP("barreF.bmp"));
    positionBarre.x = *taille;
    SDL_BlitSurface(barreMesure3, NULL, portee, &positionBarre);

    SDL_SetColorKey(portee, SDL_SRCCOLORKEY, SDL_MapRGB(portee->format, 0, 255, 0));
    SDL_BlitSurface(portee, NULL, ecran, &positionPortee);

    SDL_FreeSurface(barreMesure3);
    SDL_FreeSurface(barreMesure2);
    SDL_FreeSurface(barreMesure);
    SDL_FreeSurface(portee);
    delete taille;
    taille = 0;

    return ecran;
}

Partition::~Partition()
{
    int const nombreElements(m_listeElements.size());

    for (int i(0) ; i < nombreElements ; i++)
    {
        delete m_listeElements.front();
        m_listeElements.pop();
    }
}
