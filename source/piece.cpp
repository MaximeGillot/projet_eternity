#include "piece.h"

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