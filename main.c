#include "enregistrement.h"

ChampSaisie champEmail = {{LARGEUR_ECRAN / 2 - 150, 200, 300, 40}, "Email", false};
ChampSaisie champNumero = {{LARGEUR_ECRAN / 2 - 150, 260, 300, 40}, "Numero", false};
ChampSaisie champNom = {{LARGEUR_ECRAN / 2 - 150, 140, 300, 40}, "Nom", false};
ChampSaisie champPrenoms = {{LARGEUR_ECRAN / 2 - 150, 80, 300, 40}, "Prénoms", false};

int main(int argc, char* argv[]) {
    initialiserSDL();

    SDL_bool enCours = SDL_TRUE;
    SDL_Event evenement;

    while (enCours) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                enCours = SDL_FALSE;
            }
            else if (evenement.type == SDL_TEXTINPUT || evenement.type == SDL_KEYDOWN) {
                gererSaisie(evenement, &champNom);
                gererSaisie(evenement, &champPrenoms);
                gererSaisie(evenement, &champEmail);
                gererSaisie(evenement, &champNumero);
            }
        }

        afficher();
    }

    fermerSDL();
    return 0;
}
