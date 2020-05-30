

#include <iostream>
#include <fstream>
#include "cppitertools/range.hpp"

static const int DIM_MATRICE_MAX = 32;

using namespace std;

struct Matrice
{
    int nLignes;
    int nColonnes;
    int matrice[DIM_MATRICE_MAX][DIM_MATRICE_MAX];
};



//! Methode qui charge une matrice � partir d'un fichier.
//! \param nomFichier           Le nom du fichier � lire.
//! \param matrice              Une struct Matrice.
//! \return                     Un bool repr�sentant si le chargement a �t� un succ�s.
bool chargerMatriceDepuisFichier(const std::string& nomFichier,
    Matrice& matrice)
{
    std::ifstream fichier(nomFichier);
    if (fichier) {
        fichier >> matrice.nLignes >> matrice.nColonnes;
        for (int i : iter::range(matrice.nLignes)) {
            for (int j : iter::range(matrice.nColonnes)) {
                fichier >> matrice.matrice[i][j];
            }
        }
    }
    else {
        std::cerr << "Le chargement du fichier a echoue." << std::endl;
        return false;
    }
    return true;
}

//! Methode qui ecrit une matrice dans un fichier.
//! \param nomFichier           Le nom du fichier de sortie pour la matrice r�sultante.
//! \param matrice              La matrice � �crire.
void ecrireMatriceDansFichier(const std::string& nomFichier, 
    const Matrice& matrice) 
{
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

bool additionMatrices(Matrice& matrice1, Matrice& matrice2) 
{
    if (matrice1.nColonnes == matrice2.nColonnes && matrice1.nLignes == matrice2.nLignes) {
        for (int i : iter::range(matrice1.nLignes)) {
            for (int j : iter::range(matrice1.nColonnes)) {
                matrice1.matrice[i][j] += matrice2.matrice[i][j];
            }
        }
    }
    else {
        std::cerr << "Les matrices doivent etre de meme taille pour l'addition." << std::endl;
        return false;
    }
    return true;
}

bool soustractionMatrices(Matrice& matrice1, Matrice& matrice2)
{
    if (matrice1.nColonnes == matrice2.nColonnes && matrice1.nLignes == matrice2.nLignes) {
        for (int i : iter::range(matrice1.nLignes)) {
            for (int j : iter::range(matrice1.nColonnes)) {
                matrice1.matrice[i][j] -= matrice2.matrice[i][j];
            }
        }
    }
    else {
        std::cerr << "Les matrices doivent etre de meme taille pour la soustraction." << std::endl;
        return false;
    }
    return true;
}

void multiplicationParScalaire(Matrice& matrice1, int& scalaire)
{
    for (int i : iter::range(matrice1.nLignes)) {
        for (int j : iter::range(matrice1.nColonnes)) {
            matrice1.matrice[i][j] = matrice1.matrice[i][j] * scalaire;
        }
    }
    
}

int produitMatrice(const Matrice& matrice1, const Matrice& matrice2, int posX, int posY)
{
    int produit = 0;
    for (int i : iter::range(matrice1.nColonnes)) {
        produit += matrice1.matrice[posX][i] * matrice2.matrice[i][posY];
    }
    return produit;
}

bool multiplicationMatrices(Matrice& matrice1, Matrice& matrice2)
{
    Matrice matrice{};
    if (matrice1.nColonnes == matrice2.nLignes) {
        matrice.nLignes = matrice1.nLignes;
        matrice.nColonnes = matrice2.nColonnes;
        for (int i : iter::range(matrice.nLignes)) {
            for (int j : iter::range(matrice.nColonnes)) {
                matrice.matrice[i][j] = produitMatrice(matrice1, matrice2, i, j);
            }
        }
    }
    else {
        std::cerr << "Le nombre de colonnes de la matrice 1 doit �tre �gal au nombre de lignes de la matrice 2." << std::endl;
        return false;
    }
    matrice1 = matrice;
    return true;
}

int main()
{
    int option, scalaire;
    Matrice matrice1{}, matrice2{};
    std::string nomFichierMatrice;
    do {

        std::cout << "1 - Addition de matrices" << std::endl
            << "2 - Soustraction de matrices" << std::endl
            << "3 - Multiplkication par scalaire" << std::endl
            << "4 - Multiplication matricielle" << std::endl
            << "Entrez une option : ";
        std::cin >> option;
        
        if (option >= 1 && option <= 4) {
            std::cout << "Entrez un nom de fichier pour la premiere matrice : ";
            std::cin >> nomFichierMatrice;
            if (chargerMatriceDepuisFichier(nomFichierMatrice, matrice1) == false) continue;
            if (option == 3) {
                std::cout << "Entrez un scalaire : ";
                std::cin >> scalaire;
                multiplicationParScalaire(matrice1, scalaire);
            }
            else {
                std::cout << "Entrez un nom de fichier pour la premiere matrice : ";
                std::cin >> nomFichierMatrice;
                if (chargerMatriceDepuisFichier(nomFichierMatrice, matrice2) == false) continue;
                if (option == 1) {
                    if (additionMatrices(matrice1, matrice2) == false) continue;
                }
                if (option == 2) {
                    if (soustractionMatrices(matrice1, matrice2) == false) continue;
                }
                if (option == 4) {
                    if (multiplicationMatrices(matrice1, matrice2) == false) continue;
                }
            }
            std::cout << "Entrez un nom de fichier pour le resultat : ";
            std::cin >> nomFichierMatrice;
            ecrireMatriceDansFichier(nomFichierMatrice, matrice1);
        }

    } while (option != -1);
}
