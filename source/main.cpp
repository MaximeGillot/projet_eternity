#include <iostream>
#include "plateau.h"

int main(int argc, char const *argv[])
{
	std::cout << " Programme de M.G " << std::endl;

	const char * path = argv[1] ;
	plateau bord = plateau(path);
	//bord.afficherEnsemblePiece() ;
	bord.backtracking();
	bord.afficherPuzzle();
	return 0;
}