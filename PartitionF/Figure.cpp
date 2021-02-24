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
#include "Figure.h"

using namespace std;

Figure::Figure(int duree, int bpm) : Element(), m_duree(duree), m_point(0), m_vide(0), m_bpm(bpm)
{}

int Figure::getType()
{
    return 1;
}

SDL_Surface* Figure::afficher(SDL_Surface* ecran, int* taille)
{
    return ecran;
}

void Figure::calculs()
{

}

int Figure::getCases()
{
    return (m_duree*m_bpm)/15000;
}

Figure::~Figure()
{

}
