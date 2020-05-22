///////////////////////////////////////////////////////////////////////////////////
// \title       Devinette
// \file        Exo2.cpp
// \author      Marc-André Gosselin (2020217)
// \author      Martin Careau (1978446)
// \date        24/05/2020
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <time.h>
#include <random>



int lireValeur(std::string texte, int min, int max) {
	int essai;
	do {
		std::cout << texte;
		std::cin >> essai;
	} while (essai < min || essai > max);
	return essai;
}

int main() {
	srand(time(NULL));
	int devine = rand() % 1000;
	int essai;
	do {
		essai = lireValeur("Entrez un nombre entier : ", 0, 1000);
		if (essai < devine) {
			std::cout << "Trop bas." << std::endl;
		}
		else if (essai > devine) {
			std::cout << "Trop haut." << std::endl;
		}
	} while (essai != devine);
	std::cout << "Bravo! Vous avez reussi!";
}