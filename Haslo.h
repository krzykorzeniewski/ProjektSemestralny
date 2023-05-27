//
// Created by Krzysiek on 27.05.2023.
//

#ifndef PROJEKTSEMESTRALNY_HASLO_H
#define PROJEKTSEMESTRALNY_HASLO_H
#include <string>
#include "Kategoria.h"

class Kategoria;

class Haslo {
private:
    std::string nazwa;
    std::string tresc;
    Kategoria* kategoria;
    std::string stronaInternetowa;
    std::string login;

public:
    Haslo(const std::string& nazwa, const std::string& tresc, Kategoria* kategoria);
    Haslo(const std::string& nazwa, const std::string& tresc, Kategoria* kategoria, const std::string& stronaInternetowa, const std::string& login);

    const std::string& getNazwa() const;
    void zmienNazweKategorii(const std::string& nazwa);
    void setNazwa(const std::string& nazwa);
    void setKategoria(Kategoria* kategoria);
    void setStronaInternetowa(const std::string& stronaInternetowa);
    void setLogin(const std::string& login);
    void setTresc(const std::string& tresc);

    const std::string& getTresc() const;
    const Kategoria* getKategoria() const;
    const std::string& getStronaInternetowa() const;
    const std::string& getLogin() const;
};


#endif //PROJEKTSEMESTRALNY_HASLO_H
