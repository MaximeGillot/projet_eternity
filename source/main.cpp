#include <iostream>
#include "instance.h"

int main(int argc, char const *argv[])
{
	const char * path = argv[1] ;
	std::cout << " Programme de M.G " << std::endl;
	srand (time(0));
	instance in = instance(path);
	in.afficherEnsemblePiece();
	in.hillClimbing() ;
	in.plateau2file(path);
	return 0;
}