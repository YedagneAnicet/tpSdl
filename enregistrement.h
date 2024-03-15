#ifndef ENREGISTREMENT_H
#define ENREGISTREMENT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>

#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600
#define TAILLE_POLICE 24

typedef struct {
    SDL_Rect rect;
    char* texte;
    bool actif;
} ChampSaisie;

extern ChampSaisie champNom;
extern ChampSaisie champPrenoms;
extern ChampSaisie champEmail;
extern ChampSaisie champNumero;


void initialiserSDL();
void fermerSDL();

void afficherTexte(int x, int y, const char* texte, SDL_Color couleur);
void afficherChampSaisie(ChampSaisie* champ);
void afficher();


void gererSaisie(SDL_Event evenement, ChampSaisie* champ);

#endif /* ENREGISTREMENT_H */
