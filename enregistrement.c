#include "enregistrement.h"
#include <stdio.h>
#include <string.h>

SDL_Window* fenetre = NULL;
SDL_Renderer* rendu = NULL;
TTF_Font* police = NULL;

// DEBUT test
SDL_Texture* textureTexte;
SDL_Rect rectTexte;
char texteSaisi[256] = "";

// FIN test

void initialiserSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    fenetre = SDL_CreateWindow("Connexion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_ECRAN, HAUTEUR_ECRAN, SDL_WINDOW_SHOWN);
    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    police = TTF_OpenFont("arial.ttf", TAILLE_POLICE);
}

void fermerSDL() {
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();
}

void afficherTexte(int x, int y, const char* texte, SDL_Color couleur) {
    SDL_Surface* surface = TTF_RenderText_Blended(police, texte, couleur);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);

    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(rendu, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void afficherChampSaisie(ChampSaisie* champ) {
    SDL_SetRenderDrawColor(rendu, 255, 205, 225, 245);
    SDL_RenderDrawRect(rendu, &(champ->rect));
    afficherTexte(champ->rect.x + 10, champ->rect.y + 10, champ->texte, (SDL_Color){0, 0, 0, 255});
}

void afficher() {
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
    SDL_RenderClear(rendu);

    // Afficher le titre "ENREGISTREMENT"
    afficherTexte(LARGEUR_ECRAN / 2 - 70, 20, "ENREGISTREMENT", (SDL_Color){0, 0, 0, 255});

    // Afficher les champs de saisie
    afficherChampSaisie(&champNom);
    afficherChampSaisie(&champPrenoms);
    afficherChampSaisie(&champEmail);
    afficherChampSaisie(&champNumero);

    // Afficher le bouton d'enregistrement
    SDL_Rect rectBouton = {LARGEUR_ECRAN / 2 - 150, 320, 300, 40};
    SDL_SetRenderDrawColor(rendu, 0, 128, 255, 255);
    SDL_RenderFillRect(rendu, &rectBouton);
    afficherTexte(LARGEUR_ECRAN / 2 - 50, 330, "Enregistrer", (SDL_Color){255, 255, 255, 255});

    SDL_RenderPresent(rendu);
}



// AJout pour test

void gererSaisie(SDL_Event evenement, ChampSaisie* champ) {
    if (evenement.type == SDL_TEXTINPUT) {
        // Concaténer le texte saisi à la fin du champ actif
        strcat(champ->texte, evenement.text.text);
    }
    else if (evenement.type == SDL_KEYDOWN) {
        if (evenement.key.keysym.sym == SDLK_BACKSPACE && strlen(champ->texte) > 0) {
            // Supprimer le dernier caractère du champ actif
            champ->texte[strlen(champ->texte) - 1] = '\0';
        }
    }
}

//FIN
