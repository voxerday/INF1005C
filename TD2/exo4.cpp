//////////////////////////////////////////////////////////////////////////////
// \file   exo4.cpp
// \author Marc-André Gosselin (2020217)
// \author Martin Careau (1978446)
// \date   2020/05/20
//////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <random>
#include <time.h>

int multiplication(int a, int b) {
	int result = 0;
	for (int i = b; b != 0; b--) {
		result += a;
	}
	return result;
}



int main() {
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


//int main() {
//	int a[3] = { 23, 10, 18 };
//	int b[3] = { 45, 12, 17 };
//	for (int i = 0; i < 3; i++) {
//		int result = a[i] * b[i];
//		bool match = result == multiplication(a[i], b[i]);
//		std::cout << a[i] << " X " << b[i] << " = " << result << "\t"
//		<< std::boolalpha
//		<< match
//		<< std::endl;
//	}
//	
//
//}