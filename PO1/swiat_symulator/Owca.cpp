#include "Owca.h"

Owca::Owca(int x, int y) : Zwierze("Owca" , 'O', x, y, 4, 4 )
{
}

Owca* Owca::dziecko()
{
    return new Owca(*this);
}
