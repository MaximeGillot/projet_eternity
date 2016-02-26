#include <iostream>
#include "plateau.h"

int main(int argc, char const *argv[])
{
	const char * path = argv[1] ;
	plateau bord = plateau(path);
	std::cout << " Programme de M.G " << std::endl;
	return 0;
}