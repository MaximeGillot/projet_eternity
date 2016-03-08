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
					if (j == iCol-1 )
					{
						cout << "   " << puzzle[i][j].get_Ouest() << "|" << puzzle[i][j].get_Est() ; 
					}
					else
					{
						cout << "  " << puzzle[i][j].get_Ouest() << "|" << puzzle[i][j].get_Est() ; 
					}
					
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

int plateau::nbErreur() 
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
bool plateau::randomSwapHillClimbing(bool force) //revoir pour le rendre intéligent revoir le swap intéligent
{
	int randomRow1 = rand() % iRow;
	int randomCol1 = rand() % iCol;
	int randomRow2 ;
	int randomCol2 ;

	if (puzzle[randomRow1][randomCol1].get_Id() < 4) // si la piece choisie au hasard est un coin
	{
		int aleatoire = rand() % 4 + 1 ;
		if (aleatoire == 1)
		{
			randomRow2 = 0 ;
			randomCol2 = 0 ;
		}
		else if(aleatoire == 2)
		{
			randomRow2 = 0;
			randomCol2 = iCol-1 ;
		}
		else if(aleatoire == 3)
		{
			randomRow2 = iRow-1 ;
			randomCol2 = 0;
		}
		else if(aleatoire == 4)
		{
			randomRow2 = iRow-1 ;
			randomCol2 = iCol-1 ;			
		}
	}
	else if ( randomRow1 == 0 || randomRow1 == iRow-1 || randomCol1 == 0 || randomCol1 == iCol-1 ) // si c'est un bord
	{
		randomRow2 = rand() % iRow;
		if(randomRow2 == 0 || randomRow2 == iRow-1)
		{
			randomCol2 = rand() % (iCol-2) + 1 ;
			//cout << iCol-2 << " randomCol2 : " << randomCol2 << endl ;
		}
		else
		{
			int aleatoire = rand() % 2 + 1 ;
			if (aleatoire == 1)
			{
				randomCol2 = 0;
			}
			else
			{
				randomCol2 = iCol-1 ;
			}
		}
	}
	else	// si c'est une piece du millieux 
	{

		randomRow2 = rand() % ((iRow-1)-1) + 1 ;
		randomCol2 = rand() % ((iCol-1)-1) + 1 ;
	}
	int oldErreur = nbErreur();
	piece tmp = puzzle[randomRow2][randomCol2] ;
	puzzle[randomRow2][randomCol2] = puzzle[randomRow1][randomCol1] ;
	puzzle[randomRow1][randomCol1] = tmp ;

	if(force == false)
	{	
		if(nbErreur() >= oldErreur )
		{
			puzzle[randomRow1][randomCol1] = puzzle[randomRow2][randomCol2];
			puzzle[randomRow2][randomCol2] = tmp ;
			return false ;
		}
	}

	return true ;
}

bool plateau::randomRotateHillClimbing(bool force)
{
	//cout << " rotate aléatoire " << endl ;
	int randomRow1 = rand() % iRow;
	int randomCol1 = rand() % iCol;
	int rotateNumber = rand() % 3 + 1 ;
	int oldErreur = nbErreur();

	//cout << "Rotation alléatoire de la case " << randomRow1 << "," << randomCol1 << " de force " << rotateNumber ;
	for (int i = 0; i < rotateNumber ; ++i)
	{
		puzzle[randomRow1][randomCol1].rotate();
	}

	if(force == false )
	{
		if(nbErreur() >= oldErreur )
		{
			for (int i = 0; i < rotateNumber ; ++i)
			{
				puzzle[randomRow1][randomCol1].unRotate();
			}
		return false;
		}
	}

	return true ;
}

bool plateau::randomSwapHillClimbingStochastique (bool force , int oldErreur) 
{
	int randomRow1 = rand() % iRow;
	int randomCol1 = rand() % iCol;
	int randomRow2 ;
	int randomCol2 ;

	if (puzzle[randomRow1][randomCol1].get_Id() < 4) // si la piece choisie au hasard est un coin
	{
		int aleatoire = rand() % 4 + 1 ;
		if (aleatoire == 1)
		{
			randomRow2 = 0 ;
			randomCol2 = 0 ;
		}
		else if(aleatoire == 2)
		{
			randomRow2 = 0;
			randomCol2 = iCol-1 ;
		}
		else if(aleatoire == 3)
		{
			randomRow2 = iRow-1 ;
			randomCol2 = 0;
		}
		else if(aleatoire == 4)
		{
			randomRow2 = iRow-1 ;
			randomCol2 = iCol-1 ;			
		}
	}
	else if ( randomRow1 == 0 || randomRow1 == iRow-1 || randomCol1 == 0 || randomCol1 == iCol-1 ) // si c'est un bord
	{
		randomRow2 = rand() % iRow;
		if(randomRow2 == 0 || randomRow2 == iRow-1)
		{
			randomCol2 = rand() % (iCol-2) + 1 ;
			//cout << iCol-2 << " randomCol2 : " << randomCol2 << endl ;
		}
		else
		{
			int aleatoire = rand() % 2 + 1 ;
			if (aleatoire == 1)
			{
				randomCol2 = 0;
			}
			else
			{
				randomCol2 = iCol-1 ;
			}
		}
	}
	else	// si c'est une piece du millieux 
	{

		randomRow2 = rand() % ((iRow-1)-1) + 1 ;
		randomCol2 = rand() % ((iCol-1)-1) + 1 ;
	}

	piece tmp = puzzle[randomRow2][randomCol2] ;
	puzzle[randomRow2][randomCol2] = puzzle[randomRow1][randomCol1] ;
	puzzle[randomRow1][randomCol1] = tmp ;

	if(force == false)
	{	
		if(nbErreur() > oldErreur )
		{
			puzzle[randomRow1][randomCol1] = puzzle[randomRow2][randomCol2];
			puzzle[randomRow2][randomCol2] = tmp ;
			return false ;
		}
	}

	return true ;
}

bool plateau::randomRotateHillClimbingStochastique (bool force , int oldErreur)
{
	//cout << " rotate aléatoire " << endl ;
	int randomRow1 = rand() % iRow;
	int randomCol1 = rand() % iCol;
	int rotateNumber = rand() % 3 + 1 ;

	//cout << "Rotation alléatoire de la case " << randomRow1 << "," << randomCol1 << " de force " << rotateNumber ;
	for (int i = 0; i < rotateNumber ; ++i)
	{
		puzzle[randomRow1][randomCol1].rotate();
	}

	if(force == false )
	{
		if(nbErreur() > oldErreur )
		{
			for (int i = 0; i < rotateNumber ; ++i)
			{
				puzzle[randomRow1][randomCol1].unRotate();
			}
		return false;
		}
	}

	return true ;
}

bool plateau::randomSwapAndRotateHillClimbingStochastique(bool force,  int oldErreur) 
{
	int randomRow1 = rand() % iRow;
	int randomCol1 = rand() % iCol;
	int randomRow2 ;
	int randomCol2 ;
	int rotateNumber1 = rand() % 3 + 1 ;
	int rotateNumber2 = rand() % 3 + 1 ;

	if (puzzle[randomRow1][randomCol1].get_Id() < 4) // si la piece choisie au hasard est un coin
	{
		int aleatoire = rand() % 4 + 1 ;
		if (aleatoire == 1)
		{
			randomRow2 = 0 ;
			randomCol2 = 0 ;
		}
		else if(aleatoire == 2)
		{
			randomRow2 = 0;
			randomCol2 = iCol-1 ;
		}
		else if(aleatoire == 3)
		{
			randomRow2 = iRow-1 ;
			randomCol2 = 0;
		}
		else if(aleatoire == 4)
		{
			randomRow2 = iRow-1 ;
			randomCol2 = iCol-1 ;			
		}
	}
	else if ( randomRow1 == 0 || randomRow1 == iRow-1 || randomCol1 == 0 || randomCol1 == iCol-1 ) // si c'est un bord
	{
		randomRow2 = rand() % iRow;
		if(randomRow2 == 0 || randomRow2 == iRow-1)
		{
			randomCol2 = rand() % (iCol-2) + 1 ;
			//cout << iCol-2 << " randomCol2 : " << randomCol2 << endl ;
		}
		else
		{
			int aleatoire = rand() % 2 + 1 ;
			if (aleatoire == 1)
			{
				randomCol2 = 0;
			}
			else
			{
				randomCol2 = iCol-1 ;
			}
		}
	}
	else	// si c'est une piece du millieux 
	{

		randomRow2 = rand() % ((iRow-1)-1) + 1 ;
		randomCol2 = rand() % ((iCol-1)-1) + 1 ;
	}

	piece tmp = puzzle[randomRow2][randomCol2] ;
	puzzle[randomRow2][randomCol2] = puzzle[randomRow1][randomCol1] ;
	puzzle[randomRow1][randomCol1] = tmp ;

	for (int i = 0; i < rotateNumber1 ; ++i)
	{
		puzzle[randomRow1][randomCol1].rotate();
	}
	for (int i = 0; i < rotateNumber2 ; ++i)
	{
		puzzle[randomRow2][randomCol2].rotate();
	}

	if(force == false)
	{	
		if(nbErreur() > oldErreur )
		{

			for (int i = 0; i < rotateNumber1 ; ++i)
			{
				puzzle[randomRow1][randomCol1].unRotate();
			}

			for (int i = 0; i < rotateNumber2 ; ++i)
			{
				puzzle[randomRow2][randomCol2].unRotate();
			}
			puzzle[randomRow1][randomCol1] = puzzle[randomRow2][randomCol2];
			puzzle[randomRow2][randomCol2] = tmp ;
			return false ;
		}
	}

	return true ;
}

// le nb d'erreur dans le random et swap n'est pas important car pas évaluer étant donnée que les actions sont forcé
void plateau::perturbation(int nbPerturbation) 
{	
	int action ;
	for (int i = 0; i < nbPerturbation ; ++i)
	{
		action = rand() % 3 ;
		if(action == 0)
		{
			randomSwapHillClimbingStochastique(true , 0);
		}
		else if(action == 1)
		{
			randomRotateHillClimbingStochastique(true , 0);
		}
		else
		{
			randomSwapAndRotateHillClimbingStochastique(true , 0);
		}
	}
}