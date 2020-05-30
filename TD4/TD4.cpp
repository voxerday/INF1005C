

#include <iostream>
#include <fstream>
#include "cppitertools/range.hpp"

const int DIM_MATRICE_MAX = 32;

using namespace std;

struct Matrice
{
    int nLignes;
    int nColonnes;
    int matrice[DIM_MATRICE_MAX][DIM_MATRICE_MAX];
};



//! Methode qui charge une matrice à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param isLecture            Un bool représentant si le chargement a été un succès.
//! \return                     Une struct Matrice.
Matrice chargerMatriceDepuisFichier(const std::string& nomFichier,
    bool& isLecture)
{
    std::ifstream fichier(nomFichier);
    Matrice matrice{};
    if (fichier) {
        fichier >> matrice.nLignes >> matrice.nColonnes;
        for (int i : iter::range(matrice.nLignes)) {
            for (int j : iter::range(matrice.nColonnes)) {
                fichier >> matrice.matrice[i][j];
            }
        }
        isLecture = true;
    }
    else {
        std::cerr << "Le chargement du fichier a echoue." << std::endl;
        isLecture = false;
    }
    return matrice;
}

//! Methode qui ecrit une matrice dans un fichier.
//! \param matrice              La matrice à écrire.
void ecrireMatriceDansFichier(Matrice& matrice) {
    std::cout << "Entrez un nom de fichier pour le resultat : ";
    std::string nomFichier;
    std::cin >> nomFichier;
    std::ofstream fichier(nomFichier);
    fichier << matrice.nLignes << " " << matrice.nColonnes << std::endl;
    for (int i : iter::range(matrice.nLignes)) {
        fichier << std::endl;
        for (int j : iter::range(matrice.nColonnes)) {
            fichier << matrice.matrice[i][j];
            if (j < matrice.nColonnes - 1)
                fichier << " ";
        }
    }
}

Matrice additionMatrices(bool& isValide) {
    //bool isLecture = false;
    Matrice matrice1{}, matrice2{};
    std::string nomFichierMatrice;
    std::cout << "Entrez un nom de fichier pour la premiere matrice : ";
    std::cin >> nomFichierMatrice;
    matrice1 = chargerMatriceDepuisFichier(nomFichierMatrice, isValide);
    if (isValide == true) {
        isValide = false;
        std::cout << "Entrez un nom de fichier pour la deuxieme matrice : ";
        std::cin >> nomFichierMatrice;
        matrice2 = chargerMatriceDepuisFichier(nomFichierMatrice, isValide);
        if (isValide == true) {
            if (matrice1.nColonnes == matrice2.nColonnes && matrice1.nLignes == matrice2.nLignes) {
                for (int i : iter::range(matrice1.nLignes)) {
                    for (int j : iter::range(matrice1.nColonnes)) {
                        matrice1.matrice[i][j] += matrice2.matrice[i][j];
                    }
                }
            }
            else
                std::cerr << "Les matrices doivent etre de meme taille." << std::endl;
        }
    }
    return matrice1;
}


int main()
{
    bool isValide = false;
    Matrice matrice = chargerMatriceDepuisFichier("matrice.txt", isValide);
    ecrireMatriceDansFichier(matrice);
}
