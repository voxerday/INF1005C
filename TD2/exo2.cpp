//////////////////////////////////////////////////////////////////////////////
// \file   exo1.cpp
// \author Marc-André Gosselin (2020217)
// \author Martin Careau (1978446)
// \date   2020/05/20
//////////////////////////////////////////////////////////////////////////////


#include <iostream>


int main() {
	int tempsDebut, tempsFin;
	std::cout << "Veuillez entrer le temps de debut en secondes" << std::endl;
	std::cin >> tempsDebut;
	std::cout << "Veuillez entrer le temps de fin en secondes" << std::endl;
	std::cin >> tempsFin;
	int duree = tempsFin - tempsDebut;
	bool dureeValide = duree > 0;
	std::cout << "La duree est valide? : " << std::boolalpha << dureeValide << std::endl
		<< "Cette duree correspond a environ: " << std::endl
		<< duree / 31449600 << " annees" << std::endl
		<< (duree % 31449600) / 604800 << " semaines" << std::endl
		<< (duree % 604800) / 86400 << " jours" << std::endl
		<< (duree % 86400) / 3600 << " heures" << std::endl
		<< (duree % 3600) / 60 << " minutes" << std::endl
		<< duree % 60 << " secondes" << std::endl;
}