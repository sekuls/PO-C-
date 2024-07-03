#include "Swiat.h"
#include "Organizm.h"
#include "Czlowiek.h"
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"
#include <fstream>
#include "conio2.h"
#include <time.h>
#include <iomanip>
using namespace std;

Swiat::Swiat(int szerokosc, int wysokosc)
{
	this->szerokosc = szerokosc;
	this->wysokosc = wysokosc;
	this->tura = 0;
    ileKomentarzy = 0;
    czlowiek = nullptr;
}

Swiat* Swiat::instance = nullptr;

Swiat* Swiat::getInstance() {
    return instance;
}

Swiat* Swiat::getInstance(int szerokosc, int wysokosc) {
    if (instance != nullptr)
        delete instance;
    instance = new Swiat(szerokosc, wysokosc);
    return instance;
}

void Swiat::dodajKomentarz(Organizm* zrodlo, string kom)
{
    int znak = zrodlo->getZnak();     
    string komentarz = string(1, znak) + "  " + kom;
    komentarze.push_back(komentarz);
  
}

void Swiat::unicestwOrganizm(Organizm* organizm)
{
                organizm -> zabij();
}

Organizm* Swiat::getCzlowiek()
{
    return czlowiek;
}
Organizm* Swiat::getOrganizm(pair<int, int> pozycja)
{
    if (pozycja.first < 0 || pozycja.first >= szerokosc || pozycja.second < 0 || pozycja.second >= wysokosc)
        return nullptr;
    for (Organizm* o : organizmy)
    {
        if( o -> getczyZyje() )
        {
            if (o->getX() == pozycja.first && o->getY() == pozycja.second)
            {
                return o;
            }
        }
    }
    return nullptr;
}

void Swiat::wykonajTure() {
    tura++;

    organizmy.sort(Organizm::pierwszenstwo);
    for (Organizm* o : organizmy)
    {
        if( o -> getczyZyje() )
        {
            o->akcja();
        }

    }
}

void Swiat::rysujSwiat()
{
    system("cls");
    for (int i = 0; i < szerokosc  + 2; i++)
    {
        putch('#');
    }
    cout << endl;
    for (int i = 0; i < wysokosc; i++) {

        for (int j = 0; j < szerokosc +2; j++)
        {
            if (j == 0 || j == szerokosc  + 1)
                putch('#');
            else
                putch(' ');
        }
        cout << endl;

    }
    for (int i = 0; i < szerokosc + 2; i++)
    {
        putch('#');
    }
    cout << endl;
    cout << "TURA " << tura << endl;
    
    for (string kom : komentarze)
    {
        string prevKom = "     ";
        if( kom[0] != prevKom[0] && kom[4] != prevKom[4])
        cout << kom << endl;
    }
    komentarze.clear();
    for (Organizm* o : organizmy)
    {
        if( o -> getczyZyje())
            o->rysowanie();
    }

};

void Swiat::poczatkowaPopulacja() {
    czlowiek = new Czlowiek(rand() % szerokosc, rand() % wysokosc);
    new Owca(rand() % szerokosc, rand() % wysokosc);
    new Wilk(rand() % szerokosc, rand() % wysokosc);
    new Guarana(rand() % szerokosc, rand() % wysokosc);
    new Trawa(rand() % szerokosc, rand() % wysokosc);
    new Lis(rand() % szerokosc, rand() % wysokosc);
    new Mlecz(rand() % szerokosc, rand() % wysokosc);
    new Antylopa(rand() % szerokosc, rand() % wysokosc);
    new WilczeJagody(rand() % szerokosc, rand() % wysokosc);
    new Zolw(rand() % szerokosc, rand() % wysokosc);
    new Lis(rand() % szerokosc, rand() % wysokosc);
    new WilczeJagody(rand() % szerokosc, rand() % wysokosc);

    new Lis(rand() % szerokosc, rand() % wysokosc);



   
}
void Swiat::dodajOrganizm(Organizm* organizm)
{
    organizmy.push_back(organizm);
}

int Swiat::getSzerokosc() {
    return szerokosc;
}

int Swiat::getWysokosc()
{
    return wysokosc;
}
Swiat::~Swiat()
{
}

Swiat* Swiat::getInstance(ifstream& plik) 
{
    delete instance;
    int tura, szerokosc, wysokosc;
    string linia;
    getline(plik, linia, ';');
    tura = stoi(linia);
    getline(plik, linia, ';');
    szerokosc = stoi(linia);
    getline(plik, linia);
    wysokosc = stoi(linia);
    instance = new Swiat(szerokosc, wysokosc);
    instance->tura = tura;
    while (getline(plik, linia, ';'))
    {
        Organizm* obj = nullptr;
        if (linia.size() < 2)
            continue;
        string nazwa = linia.substr(linia.find(' ') + 1, linia.length());
        getline(plik, linia, ';');
        int x = stoi(linia);
        getline(plik, linia, ';');
        int y = stoi(linia);
        getline(plik, linia, ';');
        int sila = stoi(linia);
        getline(plik, linia, ';');
        int wiek = stoi(linia);
        if (nazwa == "Czlowiek") {
            obj = new Czlowiek(x, y);
            instance->czlowiek = obj;
            getline(plik, linia, ';');
        }
        else if (nazwa == "Wilk")
            obj = new Wilk(x, y);
        else if (nazwa == "Owca")
            obj = new Owca(x, y);
        else if (nazwa == "Lis")
            obj = new Lis(x, y);
        else if (nazwa == "Zolw")
            obj = new Zolw(x, y);
        else if (nazwa == "Antylopa")
            obj = new Antylopa(x, y);
        else if (nazwa == "Trawa")
            obj = new Trawa(x, y);
        else if (nazwa == "Mlecz")
            obj = new Mlecz(x, y);
        else if (nazwa == "Guarana")
            obj = new Guarana(x, y);
        else if (nazwa == "WilczeJagody")
            obj = new WilczeJagody(x, y);
        else if (nazwa == "BarszczSosnowskiego")
            obj = new BarszczSosnowskiego(x, y);
        obj->wzmocnij(sila - obj->getSila());

    }
    return instance;
}



void Swiat::zapiszStan()
{
    ofstream plik;
    string nazwa = "zapisz" + to_string(rand()%1000) + ".csv";
    plik.open(nazwa);
    plik << tura << ";" << szerokosc << ";" << wysokosc << endl;
    for (Organizm* o : organizmy)
    {
        if (o->getSila() > -1)
        {
            plik << o->toString() << endl;
        }
    }
    plik.close();

    dodajKomentarz(czlowiek, "Zapisano stan gry");
}