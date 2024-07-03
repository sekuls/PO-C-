#include <iostream>
#include <fstream>
#include"conio2.h"
#include <windows.h>
#include <time.h>
//#include <chrono>
//#include <string>
#include "Swiat.h"
#include "Czlowiek.h"


#ifndef __cplusplus
Conio2_Init();
#endif


using namespace std;

enum klawisze { gora = 0x4b, dol = 0x4d, lewo = 0x48, prawo = 0x50, umiejetnosc = 'r', enter = 13, zapisz = 'e', wczytaj = 'q' };

int main()
{ 
    
    srand(time(NULL));
    settitle("natalia, sekula, 197913");

    int wysokosc, szerokosc;
    cout << "Wysokosc swiata: ";
    cin >> wysokosc;
    cout << wysokosc << endl;
    cout << "Szerokosc swiata: ";
    cin >> szerokosc;
    cout << wysokosc;
    
    _setcursortype(_NOCURSOR);
    system("cls");

    Swiat* swiat = Swiat::getInstance(szerokosc, wysokosc);
    swiat->poczatkowaPopulacja();
    swiat->rysujSwiat();
    char klawisz;
    ifstream plik;
    string linia;
   
    while (1) {
        Czlowiek* czlowiek = dynamic_cast<Czlowiek*>(swiat->getCzlowiek());
        klawisz = getch();
        _setcursortype(_NOCURSOR);
        if (czlowiek != nullptr)
            switch (klawisz) {
            case gora:
                if (!czlowiek->setKierunek({ 0,-1 }))
                    continue;
                break;
            case dol:
                if (!czlowiek->setKierunek({ 0, 1 }))
                    continue;
                break;
            case lewo:
                if (!czlowiek->setKierunek({ -1, 0 }))
                    continue;
                break;
            case prawo:
                if (!czlowiek->setKierunek({ 1, 0 }))
                    continue;
                break;
            case umiejetnosc:
                czlowiek->aktywujUmiejetnosc();
                continue;
            case enter:
                break;
            case zapisz:
                swiat->zapiszStan();
                continue;
            case wczytaj:
               // swiat->dodajKomentarz(czlowiek, "Podaj nr pliku do wczytania: ");
                cout << "Podaj nr pliku do wczytania : ";
                int numer;
                cin >> numer;
                plik = ifstream("zapisz" + to_string(numer) + ".csv");
                if (plik.is_open())
                    swiat = Swiat::getInstance(plik);
                swiat->rysujSwiat();
                plik.close();
                continue;
            default:
                continue;
            }
        if (klawisz != enter)
            continue;
        swiat->wykonajTure();
        swiat->rysujSwiat();
    }
    return 0;
}