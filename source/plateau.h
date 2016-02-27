#include <vector>
#include "piece.h"

class plateau
{
private:
	std::vector<piece> EnsemblePiece;
	int iCol;
	int iRow;
	bool init(const char* path) ;

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
};