#include "Zolw.h"
#include "Swiat.h"

Zolw::Zolw(int x, int y) : Zwierze("Zolw" ,'Z', x, y, 2, 1)
{
}

void Zolw::akcja()
{
    bool robiRuch = (rand() % 100) >= 75;
    if (robiRuch)
        Zwierze::akcja();
    else
        postarz();
}

void Zolw::kolizja(Organizm* inny)
{
    char nazwa_inny = inny->getZnak();
    if (inny->getSila() < 5 && this->getZnak() != nazwa_inny) {
        swiat->dodajKomentarz(this, "Odparl atak" + string(1, inny->getZnak() ));
        inny->cofnijRuch();
    }
    else
        Zwierze::kolizja(inny);
}

Zolw* Zolw::dziecko()
{
    return new Zolw(*this);
}
