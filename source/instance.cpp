#include "instance.h"
#include "piece.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

instance::instance()
{

}

instance::instance(const char* path)
{
	init(path);
}

bool instance::init(const char* path)
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
							p.set_Id(iNbLigne);
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

void instance::afficherEnsemblePiece()
{
	cout << " EnsemblePiece des Pieces Disponible : " << endl << endl ;
	for (int i = 0; i < EnsemblePiece.size(); ++i)
	{
		cout << " piece id " << EnsemblePiece.at(i).get_Id() << " : " << EnsemblePiece.at(i).get_Sud() << " " << EnsemblePiece.at(i).get_Ouest() << " " << EnsemblePiece.at(i).get_Nord() << " " << EnsemblePiece.at(i).get_Est() << endl ;
	}

	cout << endl ;
}

void instance::generatAndTest() // changer titre fonction en hill climbing
{
	bool PasTrouver = true ;

	plateau p = plateau(iRow,iCol);
	int i = 0;
	int j = 0;

	for (int k = 0; k < EnsemblePiece.size() ; ++k)
	{
		p.puzzle[i][j] = EnsemblePiece[k];
		j++;
		if (j == iCol)
		{
			i++;
			j=0;
		}
	}

	
	while(PasTrouver)
	{

		int action = rand() % 2 ;
		int oldErreur = p.nbErreur();

		if(action == 0)
		{
			p.randomSwapHillClimbing();
		}
		else
		{
			p.randomRotateHillClimbing();
		}

	

		if(p.nbErreur() < oldErreur)
		{
			cout << " meilleur solution trouver : " << endl << endl ;
			p.afficherPuzzle();
		}

		if (p.nbErreur() == 0)
		{
			cout << "Solution Final trouvé " << endl ;
			p.afficherPuzzle();
			PasTrouver = false ;
		}

	}

}