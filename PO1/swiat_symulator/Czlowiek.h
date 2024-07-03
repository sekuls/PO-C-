#pragma once
#include "Zwierze.h"

class Czlowiek: public Zwierze
{
	private:
		int umiejetnosc;
		pair<int,int> kierunek;
	public:
		Czlowiek(int x, int y);
		void akcja();

		int setKierunek(pair<int,int> kierunek);
		void aktywujUmiejetnosc();

		void kolizja(Organizm* inny);

		//te dziecko to by tylko program dzia³a³ ale nie ma sensu
		Czlowiek* dziecko () override;
};

