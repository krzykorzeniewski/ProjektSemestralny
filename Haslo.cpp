//
// Created by krysm on 24.05.2023.
//

#include "Haslo.h"
#include <string>

    Haslo::Haslo( const string &nazwa,  const string &tresc,  const Kategoria &kategoria) {
        this->nazwa = nazwa;
        this->tresc = tresc;
        this->kategoria = kategoria;
    }
    Haslo::Haslo(const string &nazwa, const string &tresc, const Kategoria &kategoria, const string &stronaInternetowa,const string &login) {
        this->nazwa = nazwa;
        this->tresc = tresc;
        this->kategoria = kategoria;
        this->stronaInternetowa = stronaInternetowa;
        this->login = login;
    }

    const string &Haslo::getNazwa() const {
        return nazwa;
    }

    const string &Haslo::getTresc() const {
        return tresc;
    }

    const Kategoria &Haslo::getKategoria() const {
        return kategoria;
    }

    const string &Haslo::getStronaInternetowa() const {
        return stronaInternetowa;
    }

    const string &Haslo::getLogin() const {
        return login;
    }



