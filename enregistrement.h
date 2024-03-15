#ifndef ENREGISTREMENT_H
#define ENREGISTREMENT_H

#include <SDL.h>
#include <stdbool.h>

#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600
#define TAILLE_POLICE 24

typedef struct {
    SDL_Rect rect;
    char* texte;
    char inputText[100]; // Ajoutez ce membre pour stocker le texte saisi
    bool actif;
    bool survol;
} ChampSaisie;


typedef struct {
    SDL_Rect rect;
    char* texte;
    bool actif;
    bool survol;
} Bouton;

extern ChampSaisie champEmail;
extern ChampSaisie champMotDePasse;

extern Bouton boutonConnexion;

void initialiserSDL();
void fermerSDL();

void afficher();
void gererClicChampSaisie(ChampSaisie* champ, int mouseX, int mouseY);
void gererClicBouton(Bouton* bouton, int mouseX, int mouseY);
void gererSaisieTexte(SDL_Event event);

void handleDelete(SDL_Event event);

#endif /* ENREGISTREMENT_H */
