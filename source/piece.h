
class piece
{
private:
	int iNord;
	int iSud;
	int iOuest;
	int iEst;
	int iRotation;

public:
	piece(int nord , int sud , int ouest , int est );
	int get_Nord();
	int get_Sud();
	int get_Ouest();
	int get_Est();
	
};