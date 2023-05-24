//
// Created by krysm on 24.05.2023.
//

#ifndef PROJEKTSEMESTRALNY_HASLO_H
#define PROJEKTSEMESTRALNY_HASLO_H
#include <string>
#include "Kategoria.h"

using namespace std;

class Haslo {
    private:
    string nazwa;
        string tresc;
        Kategoria kategoria;
        string stronaInternetowa;
        string login;

    public:
        Haslo( const string &nazwa, const string &tresc, const Kategoria &kategoria);
        Haslo(const string &nazwa, const string &tresc, const Kategoria &kategoria, const string &stronaInternetowa,const string &login);

        const string &getNazwa() const;


        const string &getTresc() const;

        const Kategoria &getKategoria() const;

        const string &getStronaInternetowa() const;

        const string &getLogin() const;


};


#endif //PROJEKTSEMESTRALNY_HASLO_H
