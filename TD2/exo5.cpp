//////////////////////////////////////////////////////////////////////////////
// \file   exo5.cpp
// \author Marc-André Gosselin (2020217)
// \author Martin Careau (1978446)
// \date   2020/05/20
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main3() {
    //Initialisation des constantes 
    const int MAX_PARTICIPANTS = 5;
    const int MAX_LONG = 9;
    const std::string nomStat = "statistiques.txt";
    const std::string nomGagnant = "gagnants.txt";

    //Ouverture des fichiers texte
    std::ifstream stat(nomStat, std::ios::in);
    std::ofstream gagnants(nomGagnant, std::ios::out);

    std::string nom;
    double cash;
    double dette = 0.0;
    int nb = 0;

    if (stat)
    {
        while (!ws(stat).eof())
        {
            stat >> nom;
            stat>> cash;
            if (cash) {
                nb += 1;
                dette += cash;
                gagnants << std::left << std::setw(MAX_LONG)
                    << nom << std::right << std::setw(MAX_LONG)
                    << cash << "$" << std::endl;
            }
        }
        gagnants << std::endl << std::left << std::setw(MAX_LONG)
            << "TOTAL :" << std::right << std::setw(MAX_LONG)
            << dette << "$" << std::endl
            << "NOMBRE DE GAGNANTS : " << nb;
    }
    else {
        std::cerr << "Le fichier " << nomStat
            << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    }
    return 0;
}