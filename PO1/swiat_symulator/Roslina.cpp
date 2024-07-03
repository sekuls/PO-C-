#include "Roslina.h"
#include "Swiat.h"
Roslina::Roslina(string nazwa, char znak, int x, int y, int sila) : Organizm(nazwa,znak, x, y, sila,0)
{

}
void Roslina::akcja()
{
	bool zasieje = rand() % 20 == 1;

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
		swiat->dodajKomentarz(this,  "*Rozsiala sie na ("  + to_string(getX() + ruchy[move % 4][0]) +  "," + to_string(getY() + ruchy[move % 4][1]) + ")" );
		swiat->dodajOrganizm(dziecko);
	}
}

void Roslina::kolizja(Organizm* inny)
{
	if (this == inny)
		return;
	if (getSila() > inny->getSila())
	{
		swiat->dodajKomentarz(this, "Zatrula napastnika");
		swiat->unicestwOrganizm(inny);
	}
	else if (getSila() < inny->getSila())
	{
		swiat->dodajKomentarz(this, "Zostala zdeptana");
		swiat->unicestwOrganizm(this);
	}

}

Organizm* Roslina::dziecko() 
{
	return new Roslina(*this);
}