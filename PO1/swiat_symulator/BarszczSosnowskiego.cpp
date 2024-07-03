#include "BarszczSosnowskiego.h"
#include "Swiat.h"
#include "Zwierze.h"

BarszczSosnowskiego::BarszczSosnowskiego(int x, int y) : Roslina("BarszczSosnowskiego", 'B', 10, x, y)
{
}

void BarszczSosnowskiego::akcja()
{
	bool zasieje = rand() % 40 == 1;

	//sianie
	if (zasieje) {
		Organizm* dziecko = this->dziecko();
		int move = rand() % 4;
		while (!dziecko->setPozycja({ getX() + ruchy[move % 4][0], getY() + ruchy[move % 4][1] }, true)) {

			move++;
			if (move > 8) {
				swiat->dodajKomentarz(this, "Nie ma miejsca na rozsianie");
				dziecko->zabij();
				return;
			}
		}
		swiat->dodajKomentarz(this, "*Rozsiala sie na (" + to_string(getX() + ruchy[move % 4][0]) + "," + to_string(getY() + ruchy[move % 4][1]) + ")");
		swiat->dodajOrganizm(dziecko);
	}

	//trucie
	for (int i = 0; i < 4; i++) {
		auto sasiad = swiat->getOrganizm({ getX() + ruchy[i][0], getY() + ruchy[i][1] });
		if (sasiad != nullptr) {
			if( sasiad -> getInicjatywa() > 0) //tylko zwierzeta maja inicjatywe wieksza od 0
			{
				swiat->dodajKomentarz(this, "Zatrul sasiada: " + string( 1,sasiad -> getZnak() ));
				sasiad->zabij();
			}
		}
	}
}

void BarszczSosnowskiego::kolizja(Organizm* inny)
{

	swiat->dodajKomentarz(this, "Zatrul " + string(1, inny->getZnak()));
	inny->zabij();
	zabij();
}

Organizm* BarszczSosnowskiego::dziecko()
{
	return new BarszczSosnowskiego(*this);
}
