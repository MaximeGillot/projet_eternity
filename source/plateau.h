#include <vector>
#include "piece.h"

class plateau
{
private:
	std::vector<piece> vPlateau;
	int iCol;
	int iRow;
	bool init(const char* path) ;

public:
	plateau(const char* path);
};