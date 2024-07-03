#include "Wilk.h"

Wilk::Wilk(int x, int y) : Zwierze("Wilk", 'W', x, y, 9, 5)
{
}

Wilk* Wilk::dziecko()
{
	return new Wilk(*this);
}
