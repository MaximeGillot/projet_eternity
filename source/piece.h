#ifndef PIECE_H
#define PIECE_H


class piece
{
private:
	int iNord;
	int iSud;
	int iOuest;
	int iEst;
	int iRotation;

public:
	piece();
	piece(int nord , int sud , int ouest , int est );
	int get_Nord();
	int get_Sud();
	int get_Ouest();
	int get_Est();
	void set_Nord(int Nord);
	void set_Sud(int Sud);
	void set_Ouest(int Ouest);	
	void set_Est(int Est);
};


#endif