#include <iostream>
#include "instance.h"
#include <time.h>

int main(int argc, char const *argv[])
{
    clock_t t1, t2;
    t1 = clock();

	const char * path = argv[1] ;
	std::cout << " Programme de M.G " << std::endl;
	srand (time(0));
	instance in = instance(path);
	in.afficherEnsemblePiece();
	in.hillClimbing() ;

    t2 = clock();              
	in.plateau2file((float)(t2-t1)/CLOCKS_PER_SEC);
	return 0;
}


 

 
 
