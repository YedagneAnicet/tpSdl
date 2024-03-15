#include "enregistrement.h"
#include <SDL.h>

int main(int argc, char* argv[]) {
    initialiserSDL();

    bool quitter = false;
    SDL_Event evenement;

    while (!quitter) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                quitter = true;
            } else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                gererClicChampSaisie(&champEmail, mouseX, mouseY);
                gererClicChampSaisie(&champMotDePasse, mouseX, mouseY);
                gererClicBouton(&boutonConnexion, mouseX, mouseY);

            } else if (evenement.type == SDL_TEXTINPUT) {
                gererSaisieTexte(evenement);
            }else if (evenement.type == SDL_KEYDOWN && evenement.key.keysym.sym == SDLK_DELETE || evenement.key.keysym.sym == SDLK_BACKSPACE ){
                printf("Vous avez cliqué sur delete  " );
                handleDelete(evenement);
            }
        }

        afficher();
    }

    fermerSDL();
    return 0;
}
