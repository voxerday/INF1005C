///////////////////////////////////////////////////////////////////////////////////
// \title       Tri
// \file        Exo4.cpp
// \author      Marc-André Gosselin (2020217)
// \author      Martin Careau (1978446)
// \date        24/05/2020
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>


int main() {
	const int TAILLE_TABLEAU = 10;

	std::cout << "Entrez dix nombres entiers : ";
	int tableau[TAILLE_TABLEAU];
	int temp;
	std::string line;
	getline(std::cin, line);
	std::stringstream stream(line);
	for (int i = 0; i < tailleTableau; i++) {
		stream >> tableau[i];
	}
	for (int i = 0; i < TAILLE_TABLEAU; i++) {
		for (int j = i + 1; j < TAILLE_TABLEAU; j++) {
			if (tableau[j] < tableau[i]) {
				temp = tableau[i];
				tableau[i] = tableau[j];
				tableau[j] = temp;
			}
		}
	}
	std::cout << "Voici le tableau trie :";
	for (int tab : tableau) {
		std::cout << " " << tab;
	}
}
