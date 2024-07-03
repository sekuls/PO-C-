#include "WilczeJagody.h"
#include "Swiat.h"

WilczeJagody::WilczeJagody(int x, int y) : Roslina("WilczeJagody" ,'J', x, y, 99)
{
}

void WilczeJagody::kolizja(Organizm* inny)
{
	//string nazwa = Organizm::getNazwa();
	swiat->dodajKomentarz(this, " zatruto " + string(1,inny->getZnak()));
	inny->zabij();
	zabij();
}

Organizm* WilczeJagody::dziecko()
{
	return new WilczeJagody(*this);
}
