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
	void hillClimbing() ;
	void plateau2file(const char* nomFichier) ;
	
private:

	std::vector<piece> EnsemblePiece;
	int iCol;
	int iRow;
	plateau p;
	
};