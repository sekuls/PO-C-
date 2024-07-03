#include "Guarana.h"
#include "Swiat.h"

Guarana::Guarana(int x, int y) : Roslina("Guarana" ,'G', 0, x, y)
{
}

void Guarana::kolizja(Organizm* inny)
{
	//string nazwa = Organizm::getNazwa();
	
	inny->wzmocnij(3);
	swiat->dodajKomentarz(this, " Wzmocnila " + string(1, inny->getZnak()) + "  , sila  -> " + to_string(inny->getSila()));
	zabij();
}

Organizm* Guarana::dziecko()
{
	return new Guarana(*this);
}
