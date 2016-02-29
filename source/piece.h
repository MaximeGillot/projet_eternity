#ifndef PIECE_H
#define PIECE_H


class piece
{
private:

	int iId;
	int iNord;
	int iSud;
	int iOuest;
	int iEst;
	int iRotation;

public:
	piece();
	piece(int nord , int sud , int ouest , int est );

	int get_Id();
	int get_Nord();
	int get_Sud();
	int get_Ouest();
	int get_Est();
	int get_Rotation();

	void set_Id(int id);
	void set_Nord(int Nord);
	void set_Sud(int Sud);
	void set_Ouest(int Ouest);	
	void set_Est(int Est);
	void set_Rotation(int Rotation);

	void rotate(); // rotation de la piece dans le sens des aiguilles d'une montre
	void unRotate(); // sans inverse d'une montre
};


#endif