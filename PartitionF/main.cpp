#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

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


int main ( int argc, char** argv )
{
    std::string const fichier("Notes.txt");

    int continuer(1);
    int i;
    SDL_Surface *ecran(NULL);
    SDL_Surface *page(NULL);
    SDL_Surface *portees(NULL);
    SDL_Surface *barre(NULL);
    SDL_Surface *bois(NULL);
    SDL_Surface *icone(NULL);
    SDL_Event event;
    SDL_Rect positionPart;
    SDL_Rect positionPortee;

    positionPart.x = 50;
    positionPart.y = 65;
    positionPortee.x = 75;
    positionPortee.y = 110;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }

    atexit(SDL_Quit);

    icone = SDL_LoadBMP("./images/icone.bmp");
    SDL_WM_SetIcon(icone, NULL);

    ecran = SDL_SetVideoMode(1300, 825, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo");
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("My Part'", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 136, 66, 29));

    bois = SDL_LoadBMP("./images/bois.bmp");
    SDL_BlitSurface(bois, NULL, ecran, 0);

    page = SDL_LoadBMP("./images/papier.bmp");
    SDL_BlitSurface(page, NULL, ecran, &positionPart);

    barre = SDL_LoadBMP("./images/barre.bmp");
    SDL_BlitSurface(barre, NULL, ecran, 0);

    portees = SDL_LoadBMP("./images/portee.bmp");
    SDL_SetColorKey(portees, SDL_SRCCOLORKEY, SDL_MapRGB(portees->format, 0, 255, 0));
    SDL_BlitSurface(portees, NULL, ecran, &positionPortee);
    for (i = 0 ; i < 5 ; i++)
    {
        positionPortee.y += 35 + 75;
        SDL_BlitSurface(portees, NULL, ecran, &positionPortee);
    }
    positionPortee.y = 110;

    Partition partition1;
    partition1.lireFichier(fichier);
    ecran = partition1.afficher(ecran);

    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN: //Appui sur une touche
            switch(event.key.keysym.sym)
            {
            case SDLK_RETURN:
            case SDLK_ESCAPE: //Echap
                continuer = 0;
                break;
            default:
                break;
            }
            break;
        default:
               break;
        }
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(page);
    SDL_FreeSurface(barre);
    SDL_FreeSurface(bois);

    SDL_Quit();

    return 0;
}
