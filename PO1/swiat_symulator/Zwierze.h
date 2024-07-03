#pragma once
#include "Organizm.h"
#include "Swiat.h"
class Zwierze : public Organizm
{
public:
	Zwierze(string nazwa, char znak, int x, int y, int sila, int inicjatywa);
	virtual void akcja();
	virtual void kolizja(Organizm* inny);
	virtual Organizm* dziecko() override;
};

