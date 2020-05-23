///////////////////////////////////////////////////////////////////////////////////
// \title       Tri
// \file        Exo4.cpp
// \author      Marc-André Gosselin (2020217)
// \author      Martin Careau (1978446)
// \date        24/05/2020
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>



int main() {
	const int tailleTableau = 10;

	std::cout << "Entrez dix nombres entiers : ";
	int tableau[tailleTableau];
	int temp;
	for (int i = 0; i < tailleTableau; i++) {
		std::cin >> tableau[i];
	}
	for (int i = 0; i < tailleTableau; i++) {
		for (int j = i + 1; j < tailleTableau; j++) {
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