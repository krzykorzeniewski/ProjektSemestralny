//
// Created by Krzysiek on 27.05.2023.
//

#ifndef PROJEKTSEMESTRALNY_MENADZERHASEL_H
#define PROJEKTSEMESTRALNY_MENADZERHASEL_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Kategoria.h"
#include "Haslo.h"

class MenadzerHasel {
private:
    std::vector<Kategoria> wszystkieKategorie;
    std::vector<Haslo> zapisaneHasla;
    bool zaszyfrowany;
    std::ofstream plikHasel;
    std::string hasloDoPliku;

public:
    void otworzStrumien(std::string s);
    void zamknijStrumien();
    void odszyfrujPlik(const std::string &nazwaPliku);
    void zaszyfrujPlik(const std::string &nazwaPliku);
    void dodajHaslo();
    void dodajKategorie();
    void usunKategorie();
    void posortujHasla();
    void edytujHaslo();
    void usunHaslo(const std::string &nazwaPliku);
    void wyszukajHasla();
    void wygenerujHaslo();
    void utworzHasloIKategorie(int a);
    void sprawdzHaslo(const Haslo &haslo);
    void zapiszDoPliku(const Haslo &haslo);
    Kategoria* znajdzKategorie(const string &nazwa);
};


#endif //PROJEKTSEMESTRALNY_MENADZERHASEL_H
