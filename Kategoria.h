//
// Created by Krzysiek on 27.05.2023.
//

#ifndef PROJEKTSEMESTRALNY_KATEGORIA_H
#define PROJEKTSEMESTRALNY_KATEGORIA_H
#include <string>
#include <vector>
#include "Haslo.h"
using namespace std;

class Haslo;

class Kategoria {
private:
    string nazwa;
    vector<Haslo*> hasla;
public:
    Kategoria(const string& nazwa);
    const std::string& getNazwa() const;
    void setNazwa(const string& nazwa);
    bool operator<(const Kategoria& other) const;
    void dodajHaslo(Haslo* haslo);
    void usunHasla();
};


#endif //PROJEKTSEMESTRALNY_KATEGORIA_H
