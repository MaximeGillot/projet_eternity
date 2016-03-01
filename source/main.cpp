#include <iostream>
#include "instance.h"

int main(int argc, char const *argv[])
{
	std::cout << " Programme de M.G " << std::endl;

	const char * path = argv[1] ;
	instance in = instance(path);
	in.afficherEnsemblePiece();
	in.hillClimbing() ;
	return 0;
}