///////////////////////////////////////////////////////////////////////////////////
// \title       Collision
// \file        Exo3.cpp
// \author      Marc-André Gosselin (2020217)
// \author      Martin Careau (1978446)
// \date        24/05/2020
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>



int lireValeur(std::string texte, int min, int max) {
	int essai;
	do {
		std::cout << texte;
		std::cin >> essai;
	} while (essai < min || essai > max);
	return essai;
}

int main() {
	int temps = lireValeur("Entrez le temps total : ", 0, INT_MAX);
	int pos1 = lireValeur("Entrez la position initiale du premier train : ", INT_MIN, INT_MAX);
	int v1 = lireValeur("Entrez la vitesse du premier train : ", INT_MIN, INT_MAX);
	int pos2 = lireValeur("Entrez la position initiale du second train : ", INT_MIN, INT_MAX);
	int v2 = lireValeur("Entrez la vitesse du second train : ", INT_MIN, INT_MAX);
	int colision;
	if ((v2 - v1) != 0) {
		colision = ((pos1 - pos2) / (v2 - v1)) + ((pos1 - pos2) % (v2 - v1) != 0);
	}
	for (int i = 1; (i <= colision && i <= temps); i++) {
		std::cout << "Apres " << i << " seconde(s)" << std::endl;
		std::cout << "Train 1 : " << (pos1 + v1 * i) << std::endl;
		std::cout << "Train 2 : " << (pos2 + v2 * i) << std::endl;
	}
	if (colision <= temps) {
		std::cout << "Il y a eu une collision pendant la " << colision << "e seconde !";
	}
	else {
		std::cout << "Il n'y a pas eu de collision !";
	}
}
