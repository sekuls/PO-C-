#include "Organizm.h"
#include "Swiat.h"
#include "conio2.h"
Organizm::Organizm(string nazwa, char znak, int x, int y, int sila, int inicjatywa) {
	this->swiat = Swiat::getInstance();
	this->znak = znak;
	this->sila = sila;
	this->wiek = wiek;
	this->nazwa = nazwa;
	this->inicjatywa = inicjatywa;
	this->pozycja = { x, y };
	swiat->dodajOrganizm(this);
}

bool Organizm::getczyZyje()
{
	return czyZyje;
}

void Organizm::wzmocnij(int wartosc)
{
	sila += wartosc;
}
void Organizm::cofnijRuch()
{
	setPozycja(poprzedniaPozycja, false);
}
bool Organizm::czyUcieczka()
{
	return false;
}

string Organizm::toString()
{
	string out = "";
	out += typeid(*this).name();
	out += ";";
	out += to_string(pozycja.first);
	out += ";";
	out += to_string(pozycja.second);
	out += ";";
	out += to_string(sila);
	out += ";";
	out += to_string(wiek);
	out += ";";
	return out;
}


void Organizm::postarz() {
	wiek++;
}
Organizm::Organizm(const Organizm& a)
{
	this->swiat = a.swiat;
	this->znak = a.znak;
	this->sila = a.sila;
	this->inicjatywa = a.inicjatywa;
	this->pozycja = a.pozycja;
	this->wiek = 0;
	swiat->dodajOrganizm(this);
}

char Organizm::getZnak()
{
	return znak;
}


void Organizm::zabij()
{
	czyZyje = false;
	//swiat->dodajKomentarz(this, "Zostal zabity");
	//swiat->unicestwOrganizm(this);
}

void Organizm::skolizjonowany()
{
	czyKolizja = true;
}

void Organizm::setKolizja()
{
	czyKolizja = false;
}


void Organizm::rysowanie()
{
	gotoxy(pozycja.second + 2, pozycja.first  + 2);
	putch(znak);

}

bool Organizm::setPozycja(pair<int, int> pozycja, bool musiBycPuste)
{
	if (pozycja.first < 0 || pozycja.first >= swiat->getSzerokosc() || pozycja.second < 0 || pozycja.second >= swiat->getWysokosc())
		return false;
	if (musiBycPuste && swiat->getOrganizm(pozycja) != nullptr)
		return false;
	poprzedniaPozycja = this->pozycja;
	Organizm* inny = swiat->getOrganizm(pozycja);
	this->pozycja = pozycja;
	swiat->dodajKomentarz(this, "Ruch (" + to_string(poprzedniaPozycja.first) + "," + to_string(poprzedniaPozycja.second) + ") -> (" + to_string(pozycja.first) + "," + to_string(pozycja.second) + ")");
	if (inny != nullptr)
	{
		inny->kolizja(this);
	} 
	return true;
}

bool Organizm::czyBylaKolizja()
{
	return czyKolizja;
}


int Organizm::getX() {
	return pozycja.first;
}

int Organizm::getY() {
	return pozycja.second;
}

int Organizm::getSila(){
	return sila;
}

int Organizm::getWiek() {
	return wiek;
}

int Organizm::pierwszenstwo(Organizm* a, Organizm* b)
{
	if (a->inicjatywa > b->inicjatywa)
		return 1;
	else if (a->inicjatywa < b->inicjatywa)
		return 0;
	else
	{
		if (a->wiek > b->wiek)
			return 1;
		else
			return 0;
	}
}

int Organizm::getInicjatywa()
{
	return inicjatywa;
}