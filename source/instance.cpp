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
							p.set_Id(iNbLigne-1);
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

		p = plateau(iRow,iCol);
		p.puzzle[0][0] = EnsemblePiece[0] ;
		p.puzzle[0][iCol-1] = EnsemblePiece[1] ;
		p.puzzle[iRow-1][0] = EnsemblePiece[2];
		p.puzzle[iRow-1][iCol-1] = EnsemblePiece[3];

		int k = 4 ;
		for (int i = 0; i < iRow; ++i)
		{
			for (int j = 0; j < iCol; ++j)
			{
				if( (i == 0 || i == iRow-1 || j == 0 || j == iCol-1 ) && p.puzzle[i][j].get_Id() == -1 )
				{
					p.puzzle[i][j] = EnsemblePiece[k];
					k++;
				}
			}
		}

		for (int i = 0; i < iRow; ++i)
		{
			for (int j = 0; j < iCol; ++j)
			{
				if(  p.puzzle[i][j].get_Id() == -1 )
				{
					p.puzzle[i][j] = EnsemblePiece[k];
					k++;
				}
			}
		}

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

void instance::hillClimbing()
{
	bool PasTrouver = true ;
	int i = 0;
	int j = 0;
	int iterationMax = 0 ;
	int action ;
	int currentErreur ;
	clock_t t1, t2;
    t1 = clock();
    bestSolution = p.nbErreur();
    currentErreur = p.nbErreur() ;
    int oldErreur ;
	

	cout << " puzzle initial : " << endl ;
	p.afficherPuzzle();

	while(PasTrouver )
	{
		action = rand() % 3 ;
		iterationMax++;
		oldErreur = p.nbErreur();
		if(action == 0)
		{
			if(p.randomSwapHillClimbingStochastique (false,currentErreur))
			{
				
				currentErreur = p.nbErreur() ;
			}
		}
		else if(action == 1)
		{
			if(p.randomRotateHillClimbingStochastique (false,currentErreur))
			{
				
				currentErreur = p.nbErreur() ;
			}
		}
		else
		{
			if(p.randomSwapAndRotateHillClimbingStochastique(false,currentErreur))
			{
				
				currentErreur = p.nbErreur() ;
			}
		}

		if (currentErreur < oldErreur)
		{
			iterationMax = 0;
		}
	
		if(currentErreur < bestSolution )
		{
			cout << " meilleur solution trouver avec : " << currentErreur << " erreurs " << endl << endl ;
			t2 = clock();              
			plateau2file((float)(t2-t1)/CLOCKS_PER_SEC , currentErreur );
			p.afficherPuzzle();
			bestSolution = currentErreur;

			if (currentErreur == 0)
			{
				cout << "Solution Final trouvé " << endl ;
				p.afficherPuzzle();
				PasTrouver = false ;
				iterationMax = 0 ;
			}
		}	
		
		if (iterationMax == 100000) // nombre d'itération a faire avant d'effectuer une perturbation
		{
			p.perturbation(iCol+iRow);
			iterationMax = 0 ;
			currentErreur = p.nbErreur() ;
		}

	}

}



void instance::plateau2file(double tempsExecution , int erreur )
{
	ofstream fichier;
	string FileNamePath = "../resultat/piece_" + to_string(iCol) + "x" + to_string(iRow) + "_.txt" ;
	cout << " fichier : "  << FileNamePath << " crée " << endl  ;
	fichier.open(FileNamePath) ;
	if(!fichier) 
	{   
		cerr << " erreur d'ouverture du fichier pour l'ecriture de la solution" << endl ;
	}
	fichier << erreur << " erreur " << "\n" ;
	fichier << "temps execution : piece_" + to_string(iCol) + "x" + to_string(iRow) + "_.txt :" + to_string(tempsExecution) + "seconde\n" ;

	for (int i = 0; i < iRow; ++i)
	{
		for (int j = 0; j < iCol ; ++j)
		{
			fichier << p.puzzle[i][j].get_Id() << " " << p.puzzle[i][j].get_Rotation() << "\n" ;
		}
	}
	fichier.close();

	/*fichier.open("../resultat/temps execution.txt" , std::ofstream::out | std::ofstream::app );
	if(!fichier) 
	{   
		cerr << " erreur d'ouverture du fichier temps execution.txt" << endl ;
	}

	fichier << "temps execution : piece_" + to_string(iCol) + "x" + to_string(iRow) + "_.txt :" + to_string(tempsExecution) + "seconde\n" ;
	fichier.close();*/
}

