#include <vector>
#include "piece.h"

class plateau
{
private:
	int iRow;
	int iCol;
public:

	std::vector<std::vector<piece> > puzzle;

	plateau();

	plateau( int row , int col );

	void afficherPuzzle() ;

	int nbErreur();

	void initVide();

	void randomRotateHillClimbing() ;

	void randomSwapHillClimbing();
};