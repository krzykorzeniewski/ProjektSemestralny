/**
 * @file Kategoria.cpp
 * @brief Definicja klasy Kategoria.
 */
#include "Kategoria.h"
#include "Haslo.h"
using namespace std;
#include <string>
#include <algorithm>

Kategoria::Kategoria(const string &nazwa) : nazwa(nazwa) {}

const string &Kategoria::getNazwa() const {
    return nazwa;
}

void Kategoria::setNazwa(const string &nazwa) {
    this->nazwa = nazwa;
}
/**
* @brief Dodaje obiekt Haslo do wektora danej kategorii.
* @param haslo Wskaźnik do obiektu Haslo, który ma być dodany.
*/
void Kategoria::dodajHaslo (Haslo* haslo) {
    hasla.push_back(haslo);
}

/**
* @brief Usuwa wszystkie obiekty Haslo z danej kategorii.
*/
void Kategoria::usunHasla () {
    hasla.clear();
}

/**
* @brief Usuwa obiekt Haslo w wektorze w kategorii.
* @param haslo Wskaźnik do obiektu Haslo, który ma być usuniety.
*/
 void Kategoria::usunHaslo (Haslo* haslo) {
    auto range = std::ranges::remove_if(hasla, [haslo](Haslo* temp) -> bool {return haslo->getTresc() == temp->getTresc();});
    hasla.erase(range.begin(), range.end());
}

const vector<Haslo *> &Kategoria::getHasla() const {
    return hasla;
}

