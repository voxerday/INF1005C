///////////////////////////////////////////////////////////////////////////////////
// \title       Nombres premiers
// \file        Exo1.cpp
// \author      Marc-André Gosselin (2020217)
// \author      Martin Careau (1978446)
// \date        24/05/2020
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>

int primeCheck(int n) {
    while (true)
    {
        bool isPrime = true;
        for (int i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                isPrime = false;
                n++;
                break;
            }
        }
        if (isPrime) {
            return n;
        }
    }
}

int main() {
	int n = 0;
    while (n != -1) {
        std::cout << "Entrez un nombre entier : ";
        std::cin >> n;
        if (n != -1) {
            std::cout << "Le prochain nombre premier est " << primeCheck(n) << "." << std::endl;
        }
    }
}
