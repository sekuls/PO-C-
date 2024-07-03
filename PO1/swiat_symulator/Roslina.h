#pragma once
#include "Organizm.h"
class Roslina : public Organizm
{
public:
	Roslina(string nazwa , char znak, int x, int y, int sila);
	virtual void akcja() override;
	virtual void kolizja(Organizm* inny) override;

	virtual Organizm* dziecko() override;


};

