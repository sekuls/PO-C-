#pragma once
#include <string>
#include <iostream>

using namespace std;
class Swiat;

class Organizm
{
	bool czyZyje = true;
	bool czyKolizja = false;
	int sila;
	int inicjatywa;
	char znak;
	int wiek;
	string nazwa;
	pair<int, int> pozycja;
	pair<int, int> poprzedniaPozycja;
protected:
	Swiat* swiat;
	const int ruchy[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
public:
	Organizm(string nazwa, char znak,  int x, int y, int sila, int inicjatywa);

	virtual void akcja() = 0;
	Organizm(const Organizm& a);
	bool czyBylaKolizja();
	void skolizjonowany();
	void setKolizja();
	void rysowanie();
	char getZnak();
	bool getczyZyje();
	string toString();
	int getX();
	int getY();
	void wzmocnij(int wartosc);
	int getSila();
	int getWiek();
	int getInicjatywa();
	void postarz();
	virtual void kolizja(Organizm* inny) = 0;
	virtual bool czyUcieczka();
	void cofnijRuch();
	bool setPozycja(pair<int, int> pozycja, bool musiBycPuste);
	virtual Organizm* dziecko() = 0;
	void zabij();
	static int pierwszenstwo(Organizm* a, Organizm* b);
};

