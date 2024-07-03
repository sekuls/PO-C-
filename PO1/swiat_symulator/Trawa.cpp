#include "Trawa.h"

Trawa::Trawa(int x, int y) : Roslina("Trawa", 'T', x, y, 0)
{
}

Organizm* Trawa::dziecko()
{
    return new Trawa(*this);
}

//Trawa::Trawa(const Trawa& other) : Roslina(other)
//{
//}'

