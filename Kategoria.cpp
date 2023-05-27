//
// Created by Krzysiek on 27.05.2023.
//

#include "Kategoria.h"
#include "Haslo.h"
using namespace std;
#include <string>

Kategoria::Kategoria(const string &nazwa) : nazwa(nazwa) {}

const string &Kategoria::getNazwa() const {
    return nazwa;
}

void Kategoria::setNazwa(const string &nazwa) {
    this->nazwa = nazwa;
}

bool Kategoria::operator<(const Kategoria& other) const {
    return nazwa < other.nazwa;
}

void Kategoria::dodajHaslo (Haslo* haslo) {
    hasla.push_back(haslo);
}

void Kategoria::usunHasla () {
    hasla.clear();
}