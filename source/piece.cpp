#include "piece.h"

piece::piece() {}

piece::piece(int nord , int sud , int ouest , int est ) :
iNord(nord) , iSud(sud) , iOuest(ouest) , iEst(est) {}

int piece::get_Nord()
{
	return iNord;
}

int piece::get_Sud()
{
	return iSud;
}

int piece::get_Est()
{
	return iEst;
}

int piece::get_Ouest()
{
	return iOuest;
}

void piece::set_Nord(int Nord)
{
	iNord = Nord ;
}

void piece::set_Sud(int Sud)
{
	iSud = Sud ;
}

void piece::set_Ouest(int Ouest)
{
	iOuest = Ouest ;
}	

void piece::set_Est(int Est)
{
	iEst = Est ;
}
