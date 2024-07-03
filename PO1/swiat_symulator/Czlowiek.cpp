#include "Czlowiek.h"
#include "Swiat.h"
#include "Zwierze.h"
#include <iostream>
#include "conio2.h"

Czlowiek::Czlowiek(int x, int y) : Zwierze( "Czlowiek" ,'H', x, y, 5, 4)
{
	umiejetnosc = -5;
	kierunek = { 0,0 };
}

int Czlowiek::setKierunek(pair<int, int> kierunek)
{
	if ((getX() + kierunek.first) < 0 || (getX() + kierunek.first) >= swiat->getSzerokosc() || (getY() + kierunek.second) < 0 || (getY() + kierunek.second) >= swiat->getWysokosc())
		return false;
	this->kierunek = kierunek;
	return true;
}

Czlowiek* Czlowiek::dziecko()
{
	return nullptr;
}


void Czlowiek::akcja()
{
	if (umiejetnosc > -5)
	{
		umiejetnosc--;
		if( umiejetnosc > 0 )
		{
			swiat->dodajKomentarz(this, "Zostalo " + to_string(umiejetnosc) + " tur umiejetnosci");
		}
	}
	if (umiejetnosc == 0)
	{
		swiat->dodajKomentarz(this, "Umiejetnosc zostala wylaczona");
		//Zwierze::akcja();
	}
	postarz();
	setPozycja({ getX() + kierunek.first ,getY() + kierunek.second }, false);
	kierunek = { 0,0 };
}

void Czlowiek::aktywujUmiejetnosc()
{
	if (umiejetnosc == -5)
	{
		umiejetnosc = 6;
		swiat->dodajKomentarz(this, "Aktywowano umiejetnosc");
	}
}

//int Czlowiek::getUmiejetnosc()
//{
//	return umiejetnosc;
//}



void Czlowiek::kolizja(Organizm* inny)
{
	if (!czyBylaKolizja())
	{
		if (this == inny)
			return;
		else if (umiejetnosc > 0)
		{
			if (inny->getInicjatywa() != 0)
			{
				int znak = inny->getZnak();

				swiat->dodajKomentarz(this, "Uzycie tarczy Alzura na: " + string(1, znak));
				int move = rand() % 4;
				while (!setPozycja({ inny->getX() + ruchy[move][0], inny->getY() + ruchy[move][1] }, false)) {
					move++;
					move %= 4;
				}
				inny->skolizjonowany();

			}

		}
		else if (czyUcieczka() || inny->czyUcieczka())
		{
			inny->skolizjonowany();
			return;
		}
		else if (getSila() > inny->getSila())
		{
			swiat->dodajKomentarz(this, "Wygral walke");
			inny->zabij();
		}
		else if (getSila() < inny->getSila())
		{
			swiat->dodajKomentarz(this, "Przegral walke");
			zabij();
		}
		else
		{
			swiat->dodajKomentarz(this, "Rowne sily - atakowal czlowiek");
			inny->zabij();
		}
	}
	this->setKolizja();
}
