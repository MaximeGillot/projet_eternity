#include "plateau.h"
#include "piece.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;



plateau::plateau(const char* path)
{
	init(path);
}

bool plateau::init(const char* path)
{

	ifstream fichier( path , ios::in); 
	if(fichier) 
	{   
		string ligne;  	
		int iNbLigne = 0;

		while(getline(fichier, ligne)) 
		{
				string currentSentence = ligne ;
				currentSentence += " ";
				std::string delimiter = " ";					
				size_t pos = 0;
				std::string token;
				int i = 0 ;
				piece p = piece();

				while ((pos = currentSentence.find(delimiter)) != std::string::npos) 
				{
					token = currentSentence.substr(0, pos);

					if( iNbLigne == 0 ) // si on trouve un sommet
					{
						if (i == 0)
						{
							iCol = stoi(token);
						}
						else
						{
							iRow = stoi(token);
						}
					}
					else
					{
						switch(i)
						{
							case 0 :
							p.set_Sud(stoi(token));
							break;

							case 1 :
							p.set_Ouest(stoi(token));
							break;
							
							case 2 :
							p.set_Nord(stoi(token));
							break;
							
							case 3 :
							p.set_Est(stoi(token));
							p.set_Rotation(0);
							EnsemblePiece.push_back(p);
							break;
						}

					}
					

					i++;
					currentSentence.erase(0, pos + delimiter.length());
				}

			iNbLigne++;
		}
		cout << " row" << iRow << " col " << iCol << endl ;
		return true ;
	}
	else
	{
		cout << " Fichier non trouvé " << endl ;
		exit (EXIT_FAILURE);
		return false ;
	}
}

void plateau::afficherEnsemblePiece()
{
	for (int i = 0; i < EnsemblePiece.size(); ++i)
	{
		cout << " piece numéro " << i << " : " << EnsemblePiece.at(i).get_Sud() << " " << EnsemblePiece.at(i).get_Ouest() << " " << EnsemblePiece.at(i).get_Nord() << " " << EnsemblePiece.at(i).get_Est() << endl ;
	}
}

void plateau::afficherPuzzle() // revoir affichage
{
	for (int i = 0; i < puzzle.size(); ++i)
	{
		for (int k = 0; k < 3 ; ++k)
		{
			for (int j = 0; j < puzzle[i].size() ; ++j)
			{
		
				switch(k)
				{
					case 0 :
					cout << "  "  << puzzle[i][j].get_Nord() ;
					break ;

					case 1 :
					cout << puzzle[i][j].get_Ouest() << "  " << puzzle[i][j].get_Est() ; ;
					break ;

					case 2 :
					cout << puzzle[i][j].get_Sud() << "    " ;
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
	for (int i = 0; i < puzzle.size() ; ++i)
	{
		for (int j = 0; j < puzzle[i].size() ; ++j)
		{
			if( i == 0 )
			{
				if( puzzle[i][j].get_Ouest() != 0 )
				{
					nbErreur++;
				}
			}

			if( j == 0 )
			{
				if (puzzle[i][j].get_Nord() != 0 )
				{
					nbErreur++;
				}
			}

			if ( j == puzzle[i].size()-1)
			{
				if (puzzle[i][j].get_Sud() != 0 )
				{
					nbErreur++;
				}
			}

			if (i == puzzle[i].size()-1)
			{
				if(puzzle[i][j].get_Est() != 0)
				{
					nbErreur++;
				}
			}

			if (i != puzzle.size()-1 && puzzle[i][j].get_Est() != puzzle[i+1][j].get_Ouest())
			{
				nbErreur++;
			}

			if (j != puzzle[i].size() && puzzle[i][j].get_Sud() != puzzle[i][j+1].get_Nord())
			{
				nbErreur++;
			}

		}
	}

	return nbErreur ;
}



void plateau::backtracking() // a faire
{
	for (int i = 0; i < 3; ++i)
	{
		std::vector<piece> v;
		for (int j = 0; j < 3 ; ++j)
		{
			v.push_back(EnsemblePiece[j]);
		}
		puzzle.push_back(v);
	}
}