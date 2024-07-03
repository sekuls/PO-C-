#include "Zwierze.h"
#include "Swiat.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string>

Zwierze::Zwierze(string nazwa, char znak ,int x, int y, int sila, int inicjatywa) : Organizm(nazwa,znak, x, y, sila,inicjatywa)
{

}

void Zwierze::akcja()
{
	postarz();
	int move = rand() % 4;
	while (!setPozycja({ getX() + ruchy[move][0], getY() + ruchy[move][1] }, false)) {
		move++;
		move %= 4;
	}
}


void Zwierze::kolizja(Organizm* inny)
{
	if(!czyBylaKolizja())
	{
		if (this == inny)
			return;
		//porównywanie po znakach bo jak takie same to ten sam gatunek 
		if (this->getZnak() == inny->getZnak()) {
			if (getWiek() < 2 || inny->getWiek() < 2)
				return;
			swiat->dodajKomentarz(this, "rozmnazanie");

			Organizm* dziecko = this->dziecko();
			int move = rand() % 4;
			while (!dziecko->setPozycja({ getX() + ruchy[move % 4][0], getY() + ruchy[move % 4][1] }, true)) {
				move++;
				if (move > 8) {
					swiat->dodajKomentarz(this, "stop rozmnazaniu - za ma³o miejsca!");
					dziecko->zabij();
					return;
				}
			}
			inny->skolizjonowany();
			swiat->dodajKomentarz(this, "*wygenerowanie dziecka na polu (" + to_string(getX() + ruchy[move % 4][0]) + ", " + to_string(getY() + ruchy[move % 4][1]) + ")");
		}
		else if (czyUcieczka() || inny->czyUcieczka())
		{
			inny->skolizjonowany();
			return;
		}
		else if (getSila() > inny->getSila())
		{
			swiat->dodajKomentarz(this, "Wygral walke z  " + string(1, inny->getZnak()));
			swiat->unicestwOrganizm(inny);
		}
		else if (getSila() < inny->getSila())
		{
			swiat->dodajKomentarz(this, "Przegral walke z " + string( 1, inny->getZnak()) );
			swiat->unicestwOrganizm(this);
		}
		else
		{
			swiat->dodajKomentarz(this, "Rowne sily -> wygrywa atakujacy z " + string(1, inny->getZnak()));
			swiat->unicestwOrganizm(this);
		}
	}
	this->setKolizja();
}


Organizm* Zwierze::dziecko()
{
	return new Zwierze(*this);
}