#include <vector>
#include "piece.h"

class plateau
{
private:
	std::vector<piece> plateau;

public:
	plateau();
	bool init() ;
};