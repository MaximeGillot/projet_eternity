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