#include "piece.h"
#include "plateau.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


class instance
{
public:

	instance();
	instance(const char* path);
	void afficherEnsemblePiece();
	bool init(const char* path);
	void generatAndTest() ;
	
private:

	std::vector<piece> EnsemblePiece;
	int iCol;
	int iRow;
	std::vector<plateau> plateaux;
	
};