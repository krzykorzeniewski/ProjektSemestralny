//
// Created by krysm on 24.05.2023.
//
#include "Kategoria.h"
#include <string>
#include <vector>

    const string &Kategoria::getNazwa() const {
        return nazwa;
    }

    bool Kategoria::operator<(const Kategoria& other) const {
        return nazwa < other.nazwa;
    }

    void Kategoria::dodajHaslo (Haslo &haslo) {
        hasla.push_back(haslo);
    }

    const vector<Haslo> Kategoria::getHasla() const{
        return hasla;
    }

    void Kategoria::usunHasla () {
        hasla.clear();
    }

    Kategoria::Kategoria(const string &nazwa) {
    this->nazwa = nazwa;
    }
