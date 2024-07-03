#pragma once
#include <list>
#include "Organizm.h"
class Swiat
{
private:
	list<Organizm*> organizmy;
	list<string> komentarze;
	Organizm* czlowiek;
	int wysokosc;
	int szerokosc;
	int tura;
	static Swiat* instance;
	int ileKomentarzy;


public:
	static Swiat* getInstance();
	static Swiat* getInstance(int szerokosc, int wysokosc);
	static Swiat* getInstance(ifstream& plik);
	Swiat(int szerokosc, int wysokosc);
	int getWysokosc();
    int getSzerokosc();
	void rysujSwiat();
	void poczatkowaPopulacja();
	void unicestwOrganizm(Organizm* organizm);
	Organizm* getOrganizm(pair<int, int> pozycja);
	void dodajOrganizm(Organizm* organizm);
	Organizm* getCzlowiek();

	void wykonajTure();
	void dodajKomentarz(Organizm* zrodlo, string komentarz);
	void zapiszStan();

	~Swiat();

};

