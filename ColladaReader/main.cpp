#include "ColladaToBin.h"

#include <iostream>

int main(void)
{
	ColladaToBin model("test/prueba.dae");

	std::cout << model.getStatus()  << std::endl;

	system("pause");

	return 0;
}