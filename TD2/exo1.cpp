//////////////////////////////////////////////////////////////////////////////
// \file   exo1.cpp
// \author Marc-André Gosselin (2020217)
// \author Martin Careau (1978446)
// \date   2020/05/20
//////////////////////////////////////////////////////////////////////////////


#include <iostream>


int main() {
	double m, v;
	std::cout << "Veuillez entrer la masse" << std::endl;
	std::cin >> m;
	std::cout << "Veuillez entrer la vitesse" << std::endl;
	std::cin >> v;
	std::cout << "L'energie cinetique de l'objet est " << (m * v * v / 2) << " joules." << std::endl;
}