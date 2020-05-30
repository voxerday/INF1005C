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

    const int maxAliment = 5;
    const std::string nomInventaire = "inventaire.txt";

    struct Aliment {
        std::string nom;
        double prix;
        std::string type;
        int quantite;
    };
    struct Inventaire {
        Aliment aliments[maxAliment];
        int nAliments = 0;
    };

    std::ifstream fichier(nomInventaire, std::ios::in);
    if (fichier) {
        std::string ligne;
        Inventaire inventaire;
        while (!ws(fichier).eof()) {
            getline(fichier, inventaire.aliments[inventaire.nAliments].nom, '\t');
            getline(fichier, inventaire.aliments[inventaire.nAliments].type, '\t');
            fichier >> inventaire.aliments[inventaire.nAliments].quantite 
                >> inventaire.aliments[inventaire.nAliments].prix;
            inventaire.nAliments += 1;
        }
        int i = 0;
        for (int j = 1; j < inventaire.nAliments; j++) {
            if (inventaire.aliments[i].prix < inventaire.aliments[j].prix) {
                i = j;
            }
        }
        std::cout << inventaire.aliments[i].quantite
            << " " << inventaire.aliments[i].nom
            << " (" << inventaire.aliments[i].type << ")"
            << " a " << std::setprecision(2) << std::fixed << inventaire.aliments[i].prix << "$ chacun";
    }
}