///////////////////////////////////////////////////////////////////////////////////
// \title       Tri
// \file        Exo4.cpp
// \author      Marc-André Gosselin (2020217)
// \author      Martin Careau (1978446)
// \date        24/05/2020
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>



int main() {
	std::cout << "Entrez dix nombres entiers : ";
	int tableau[10];
	int temp;
	for (int i = 0; i < 10; i++) {
		std::cin >> tableau[i];
	}
	for (int i = 0; i < 10; i++) {
		for (int j = i + 1; j < 10; j++) {
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