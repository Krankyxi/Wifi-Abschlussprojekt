#include "Spieler.h"

std::ostream& operator<<(std::ostream& out, const CSpieler& spieler)
{
	out << spieler.name;
	return out;
}
