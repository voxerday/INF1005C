//////////////////////////////////////////////////////////////////////////////
// \file   exo3.cpp
// \author Marc-André Gosselin (2020217)
// \author Martin Careau (1978446)
// \date   2020/05/20
//////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <random>
#include <time.h>

int main() {
	const int boulierSize = 10;
	const int billetSize = 5;

	//Initialisation du seed
	srand(time(NULL));
	int boulier[boulierSize], billet[billetSize];

	std::cout << "Entrez les 10 nombres du boulier" << std::endl;
	for (int i = 0; i < boulierSize; i++)
		std::cin >> boulier[i];

	//Mélange les nombres du boulier
	for (int i = 0; i < boulierSize; ++i)
	{
		int random = rand() % boulierSize;
		int temp = boulier[i];
		boulier[i] = boulier[random];
		boulier[random] = temp;
	}

	//Assigne les nouveaux premier nombres du boulier au billet
	std::cout << "Voici votre billet :";
	for (int i = 0; i < billetSize; i++) {
		billet[i] = boulier[i];
		std::cout << " " << billet[i];
	}
	std::cout << std::endl;

	bool win = false;
	int winNum = rand() % boulierSize;
	std::cout << "Le numéro gagnant est: " << boulier[winNum] << std::endl;
	for (int num : billet) {
		if (num == boulier[winNum]){
			win = true;
		}
	}

	if (win) {
		std::cout << "Félicitation, vous avez gagné!";
	}
	else {
		std::cout << "Vous avez perdu!";
	}
	return 0;
}