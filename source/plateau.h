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

	bool randomRotateHillClimbing(bool force, int oldErreur) ;

	bool randomSwapHillClimbing(bool force, int oldErreur );

	bool randomRotateHillClimbingStochastique (bool force , int oldErreur) ;

	bool randomSwapHillClimbingStochastique (bool force, int oldErreur);

	bool randomSwapAndRotateHillClimbingStochastique(bool force,  int oldErreur) ;

	void perturbation(int nbPerturbation) ;


};