#include "Additive.h"
#include "Multiplicative.h"
#include "Exponential.h"
#include <iostream>

int main() {
	Additive add(4);
	std::string texto1=add.encrypt("hola caracola");
	std::cout<<add.decrypt(texto1)<<std::endl;

	Multiplicative mul(5);
	std::string texto2 = mul.encrypt("hello world");
	std::cout << mul.decrypt(texto2)<<std::endl;

	Exponential exp(7);
	std::string texto3 = exp.encrypt("hallo wie geht");
	std::cout << exp.decrypt(texto3);

	getchar();
}