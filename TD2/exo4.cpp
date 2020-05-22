///////////////////////////////////////////////////////////////////////////////////
// \title		Programme qui calcule l'énergie cinétique (joules)
// \file		exo1.cpp
// \author		Marc-André Gosselin et Martin Careau
// \matricule	2020217 et 1978446
// \date		20 mai 2020
///////////////////////////////////////////////////////////////////////////////////




#include <iostream>
#include <time.h>

int multiplication(int a, int b) {
	int result = 0;
	for (int i = b; b != 0; b--) {
		result += a;
	}
	return result;
}


int main3() {
	//Initialisation du seed
	srand(time(NULL));
	for (int i = 0; i < 3; i++) {
		int a = rand() % 100;
		int b = rand() % 100;
		int result = a * b;
		bool match = result == multiplication(a, b);
		std::cout << a << " X " << b << " = " << result << "\t"
			<< std::boolalpha
			<< match
			<< std::endl;
	}
	return 0;
}