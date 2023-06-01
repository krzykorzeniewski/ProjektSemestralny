#ifndef PROJEKTSEMESTRALNY_HASLO_H
#define PROJEKTSEMESTRALNY_HASLO_H
#include <string>
#include "Kategoria.h"
using namespace std;

class Kategoria;

class Haslo {
private:
    string nazwa;
    string tresc;
    Kategoria* kategoria;
    string stronaInternetowa;
    string login;
public:
    Haslo(const string& nazwa, const string& tresc, Kategoria* kategoria);
    Haslo(const string& nazwa, const string& tresc, Kategoria* kategoria, const string& stronaInternetowa, const string& login);
    const string& getNazwa() const;
    void zmienNazweKategorii(const string& nazwa);
    void setNazwa(const string& nazwa);
    void setKategoria(Kategoria* kategoria);
    void setStronaInternetowa(const string& stronaInternetowa);
    void setLogin(const string& login);
    void setTresc(const string& tresc);
    const string& getTresc() const;
    Kategoria *const getKategoria() const;
    const string& getStronaInternetowa() const;
    const string& getLogin() const;
};


#endif //PROJEKTSEMESTRALNY_HASLO_H
