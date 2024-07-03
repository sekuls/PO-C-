#include "Antylopa.h"
#include "Swiat.h"

Antylopa::Antylopa(int x, int y) : Zwierze("Antylopa", 'A', x, y, 4, 4)
{
}

void Antylopa::akcja()
{
	postarz();
	int move = rand() % 8;
	while (!setPozycja({ getX() + ruchy[move][0], getY() + ruchy[move][1] }, false)) {
		move++;
		move %= 8;
	}
}

bool Antylopa::czyUcieczka()
{
	bool ucieczka = rand() % 2;
	if (ucieczka) {
		int move = 0;
		while (!setPozycja({ getX() + ruchy[move][0], getY() + ruchy[move][1] }, true)) {
			move++;
			if (move == 8) {
				swiat->dodajKomentarz(this, "Nie udalo siê uciec [*]");
				return false;
			}
		}
		swiat->dodajKomentarz(this, "karramba antylopa uciekla ");
		return true;
	}
	return false;
}

Antylopa* Antylopa::dziecko()
{
	return new Antylopa(*this);
}
