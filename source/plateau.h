#include <vector>
#include "piece.h"

class plateau
{
private:
	std::vector<piece> EnsemblePiece;
	int iCol;
	int iRow;
	bool init(const char* path) ;
	std::vector<std::vector<piece> > puzzle;

public:
	/*
		initialise le plateau
		@param path chemin vers le fichier texte contenant l'instance du puzzle
	*/
	plateau(const char* path);

	/*
		afficher l'ensenble des pieces disponibles , EnsemblePiece
	*/
	void afficherEnsemblePiece();

	void afficherPuzzle() ;

	void backtracking() ;

	int nbErreur();
};