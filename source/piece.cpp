#include "piece.h"

piece::piece() {}

piece::piece(int nord , int sud , int ouest , int est ) :
iNord(nord) , iSud(sud) , iOuest(ouest) , iEst(est) 
{
	iRotation = 0;
}

int piece::get_Id()
{
	return iId ;
}

int piece::get_Nord()
{
	switch(iRotation)
	{
		case 0 :
		return iNord ;
		break;

		case 1 :
		return iOuest;
		break;

		case 2 :
		return iSud;
		break;

		case 3 :
		return iEst;
		break;
	}	
}

int piece::get_Sud()
{
	switch(iRotation)
	{
		case 0 :
		return iSud;
		break;

		case 1 :
		return iEst;
		break;

		case 2 :
		return iNord;
		break;

		case 3 :
		return iOuest;
		break;
	}	
}

int piece::get_Est()
{
	switch(iRotation)
	{
		case 0 :
		return iEst;
		break;

		case 1 :
		return iNord;
		break;

		case 2 :
		return iOuest;
		break;

		case 3 :
		return iSud;
		break;
	}	
}

int piece::get_Ouest()
{
	switch(iRotation)
	{
		case 0 :
		return iOuest;
		break;

		case 1 :
		return iSud;
		break;

		case 2 :
		return iEst;
		break;

		case 3 :
		return iNord;
		break;
	}	
}

int piece::get_Rotation()
{
	return iRotation;
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

void piece::set_Rotation(int Rotation)
{
	iRotation = Rotation ;
}

void piece::set_Id(int id)
{
	iId = id ;
}

void piece::rotate()
{
	if( iRotation == 3)
	{
		iRotation = 0 ;
	}
	else
	{
		iRotation++;
	}
}

void piece::unRotate()
{
	if(iRotation == 0)
	{
		iRotation = 3 ;
	}
	else
	{
		iRotation--;
	}
}