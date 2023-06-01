#include "Haslo.h"
#include "Kategoria.h"
#include <string>
using namespace std;

Haslo::Haslo(const string &nazwa, const string &tresc, Kategoria* kategoria) : nazwa(nazwa), tresc(tresc), kategoria(kategoria) {}
Haslo::Haslo(const string &nazwa, const string &tresc, Kategoria* kategoria, const string &stronaInternetowa,const string &login) : nazwa(nazwa), tresc(tresc), kategoria(kategoria), stronaInternetowa(stronaInternetowa),login(login) {}

const string &Haslo::getNazwa() const {
    return nazwa;
}

void Haslo::zmienNazweKategorii(const string &nazwa) {
    kategoria->setNazwa(nazwa);
}

void Haslo::setNazwa(const string &nazwa) {
    Haslo::nazwa = nazwa;
}

void Haslo::setKategoria(Kategoria* kategoria) {
    Haslo::kategoria = kategoria;
}

void Haslo::setStronaInternetowa(const string &stronaInternetowa) {
    Haslo::stronaInternetowa = stronaInternetowa;
}

void Haslo::setLogin(const string &login) {
    Haslo::login = login;
}

void Haslo::setTresc(const string &tresc) {
    Haslo::tresc = tresc;
}

const string &Haslo::getTresc() const {
    return tresc;
}

Kategoria *const Haslo::getKategoria() const {
    return kategoria;
}

const string &Haslo::getStronaInternetowa() const {
    return stronaInternetowa;
}

const string &Haslo::getLogin() const {
    return login;
}
