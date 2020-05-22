///////////////////////////////////////////////////////////////////////////////////
// \title       Magasin
// \file        Exo5.cpp
// \author      Marc-André Gosselin (2020217)
// \author      Martin Careau (1978446)
// \date        24/05/2020
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

int main() {

    const int MAX_ALIMENTS = 10;
    const std::string nomInventaire = "inventaire.txt";

    struct Aliment {
        std::string nom;
        double prix;
        std::string type;
        int quantite;
    };
    struct Inventaire {
        Aliment aliment[MAX_ALIMENTS];
        int nb = 0;
    };

    std::ifstream fichier(nomInventaire, std::ios::in);
    if (fichier) {
        std::string ligne;
        Inventaire inventaire;
        while (getline(fichier, ligne)) {
            std::istringstream stream(ligne);
            getline(stream, inventaire.aliment[inventaire.nb].nom, '\t');
            getline(stream, inventaire.aliment[inventaire.nb].type, '\t');
            stream >> inventaire.aliment[inventaire.nb].quantite >> inventaire.aliment[inventaire.nb].prix;
            inventaire.nb += 1;
        }
        int i = 0;
        for (int j = 1; j < inventaire.nb; j++) {
            if (inventaire.aliment[i].prix < inventaire.aliment[j].prix) {
                i = j;
            }
        }
        std::cout << inventaire.aliment[i].quantite
            << " " << inventaire.aliment[i].nom
            << " (" << inventaire.aliment[i].type << ")"
            << " a " << std::setprecision(2) << std::fixed << inventaire.aliment[i].prix << "$ chacun";
    }
}