#include "enregistrement.h"
#include <SDL_ttf.h>
#include <stdio.h>
#include <string.h>

SDL_Window* fenetre = NULL;
SDL_Renderer* rendu = NULL;
TTF_Font* police = NULL;

char saisie[100] = "";

ChampSaisie champEmail = {{LARGEUR_ECRAN / 2 - 150, 200, 300, 40}, "Adresse e-mail ", "", true, false};
ChampSaisie champMotDePasse = {{LARGEUR_ECRAN / 2 - 150, 260, 300, 40}, "Mot de passe", "", true, false};
Bouton boutonConnexion = {{LARGEUR_ECRAN / 2 - 150, 320, 300, 40}, "Se Connecter", false, false};

ChampSaisie* champSaisieActif = NULL;

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

void afficherChampSaisie(ChampSaisie champ) {
    SDL_SetRenderDrawColor(rendu, 205, 25, 225, 20);
    SDL_RenderDrawRect(rendu, &(champ.rect)); // Modification ici
    afficherTexte(champ.rect.x + 10, champ.rect.y + 10, champ.texte, (SDL_Color){0, 0, 0, 255}); // Texte en noir

    if (champSaisieActif == &champ) {
        afficherTexte(champ.rect.x + 10 + strlen(champ.texte) * TAILLE_POLICE, champ.rect.y + 10, "|", (SDL_Color){0, 0, 0, 255}); // Affiche un caractère vide à côté du texte du champ de saisie
    }
}


void afficherBouton(Bouton bouton) {
    static bool clicked = false; // Variable statique pour suivre l'état du clic

    SDL_Color couleur;
    if (bouton.actif) { // Correction ici
        couleur = (SDL_Color){0, 128, 5, 215}; // Couleur bleue si le bouton est actif
        if (!clicked) { // Vérifie si le bouton est activé pour la première fois
            printf("Vous m'avez cliqué\n");
            clicked = true; // Marque le bouton comme cliqué
        }

    } else {
        couleur = (SDL_Color){0, 152, 59, 8}; // Couleur bleue normale, les valeurs ont été ajustées pour éviter le dépassement
        clicked = false; // Réinitialise la variable clicked lorsque le bouton est désactivé
    }

    SDL_SetRenderDrawColor(rendu, couleur.r, couleur.g, couleur.b, couleur.a);
    SDL_RenderFillRect(rendu, &(bouton.rect));
    afficherTexte(bouton.rect.x + 50, bouton.rect.y + 10, bouton.texte, (SDL_Color){255, 255, 255, 255}); // Texte en blanc
}

void afficher() {
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255); // Couleur de fond blanc
    SDL_RenderClear(rendu);

    afficherChampSaisie(champEmail);
    afficherChampSaisie(champMotDePasse);
    afficherBouton(boutonConnexion);

    SDL_RenderPresent(rendu);
}

bool isMouseInsideRect(SDL_Rect rect, int mouseX, int mouseY) {
    return mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h;
}

void gererClicChampSaisie(ChampSaisie* champ, int mouseX, int mouseY) {
    if (isMouseInsideRect(champ->rect, mouseX, mouseY)) {
        champ->actif = true;
        champSaisieActif = champ; // Met à jour le champ de saisie actif
        strcpy(saisie, champ->inputText);
        champ->texte = "Saisir";
        printf("Vous avez cliqué sur le champ de saisie\n"); // Affichage du message lorsque le champ de saisie est cliqué
    } else {
        champ->actif = false;
    }
}

void handleDelete(SDL_Event event) {
    if (champSaisieActif != NULL && event.type == SDL_KEYDOWN &&
        (event.key.keysym.sym == SDLK_DELETE || event.key.keysym.sym == SDLK_BACKSPACE)) {
        if (strlen(champSaisieActif->inputText) > 0) { // Vérifie si le champ de saisie n'est pas vide
            if (strlen(champSaisieActif->inputText) > 1) {
                champSaisieActif->inputText[strlen(champSaisieActif->inputText) - 1] = '\0'; // Supprime le dernier caractère
                printf("Vous avez supprimé le dernier caractère\n");
            } else {
                champSaisieActif->inputText[0] = ' '; // Réinitialiser l'entrée à une chaîne vide
                printf("Le champ de saisie est maintenant vide\n");
            }
        } else {
            printf("Erreur : Le champ de saisie est déjà vide\n");
        }
    }
}

void gererSaisieTexte(SDL_Event event) {
    if (champSaisieActif != NULL && event.type == SDL_TEXTINPUT) {
        strcat(champSaisieActif->inputText, event.text.text); // Concatène le texte entré à la fin du texte existant
        printf("Input Text: %s\n", champSaisieActif->inputText); // Affiche le texte entré dans le champ de saisie
        champSaisieActif->texte = champSaisieActif->inputText;
    } else {
        handleDelete(event); // Gérer la touche "Supprimer"
    }
}

void gererClicBouton(Bouton* bouton, int mouseX, int mouseY) {
    if (isMouseInsideRect(bouton->rect, mouseX, mouseY)) {
        // Mettez ici le code pour l'action à effectuer lors du clic sur le bouton
        bouton->actif = !bouton->actif; // Correction ici
    }
}
