#include "plateau.h"
#include "piece.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;



plateau::plateau()
{
	initVide();
}

plateau::plateau(int row , int col) :
iRow(row) , iCol(col) 
{
	initVide();
}

void plateau::afficherPuzzle() // revoir affichage
{
	for (int i = 0; i < iRow; ++i)
	{
		for (int k = 0; k < 3 ; ++k)
		{
			for (int j = 0; j < iCol ; ++j)
			{
		
				switch(k)
				{
					case 0 :
					cout << "    "  << puzzle[i][j].get_Nord() ;
					break ;

					case 1 :
					cout << "  " << puzzle[i][j].get_Ouest() << "|" << puzzle[i][j].get_Est() ; 
					break ;

					case 2 :
					cout << "    "  << puzzle[i][j].get_Sud() ;
					break ;
					
				}
			}
			cout << endl ;
		}
	}
}

int plateau::nbErreur() //a tester
{
	int nbErreur = 0 ;
	for (int i = 0; i < iRow; ++i)
	{
		for (int j = 0; j < iCol ; ++j)
		{
			if( i == 0 )
			{
				if( puzzle[i][j].get_Nord() != 0 )
				{
					nbErreur++;


				}
			}

			if( j == 0 )
			{
				if (puzzle[i][j].get_Ouest() != 0 )
				{
					nbErreur++;

				}
			}

			if ( j == iCol-1)
			{
				if (puzzle[i][j].get_Est() != 0 )
				{
					nbErreur++;

				}
			}

			if (i == iRow-1)
			{
				if(puzzle[i][j].get_Sud() != 0)
				{
					nbErreur++;

				}
			}

			if (i != iRow-1 &&  ( puzzle[i][j].get_Sud() != puzzle[i+1][j].get_Nord()  ) ) // vérification du nord et sur des pieces
			{
				nbErreur++;
								
			}

			if ( j != iCol-1 && puzzle[i][j].get_Est() != puzzle[i][j+1].get_Ouest()  ) // vérification de l'ouest et l'est
			{
				nbErreur++;
			}



		}
	}

	return nbErreur ;
}

void plateau::initVide()
{
	for (int i = 0; i < iRow; ++i)
	{
		std::vector<piece> v;
		for (int j = 0; j < iCol; ++j)
		{
			piece p = piece();
			v.push_back(p);
		}
		puzzle.push_back(v);
	}
}

/*
si force = true alors l'action est executé et il n'y a pas de retour arriere
*/
bool plateau::randomSwapHillClimbing(bool force) //revoir pour le rendre intéligent
{
	//cout << " Swap aléatoire " << endl ;
	srand (time(NULL));
	int randomRow1 = rand() % iRow;
	int randomCol1 = rand() % iCol;
	int randomRow2 = rand() % iRow;
	int randomCol2 = rand() % iCol;
	int oldErreur = nbErreur();
	piece tmp = puzzle[randomRow2][randomCol2] ;
	puzzle[randomRow2][randomCol2] = puzzle[randomRow1][randomCol1] ;
	puzzle[randomRow1][randomCol1] = tmp ;

	if(nbErreur() > oldErreur || force)
	{
		puzzle[randomRow1][randomCol1] = puzzle[randomRow2][randomCol2];
		puzzle[randomRow2][randomCol2] = tmp ;
		return false ;
	}

	return true ;
}

bool plateau::randomRotateHillClimbing(bool force)
{
	//cout << " rotate aléatoire " << endl ;
	srand (time(NULL));
	int randomRow1 = rand() % iRow;
	int randomCol1 = rand() % iCol;
	int rotateNumber = rand() % 3 + 1 ;
	int oldErreur = nbErreur();

	//cout << "Rotation alléatoire de la case " << randomRow1 << "," << randomCol1 << " de force " << rotateNumber ;
	for (int i = 0; i < rotateNumber ; ++i)
	{
		puzzle[randomRow1][randomCol1].rotate();
	}

	if(nbErreur() > oldErreur || force)
	{
		for (int i = 0; i < rotateNumber ; ++i)
		{
			puzzle[randomRow1][randomCol1].unRotate();
		}
		return false;
	}

	return true ;
}