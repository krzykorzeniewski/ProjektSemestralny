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
    const string& getNazwa() const;
    void setNazwa(const string& nazwa);
    void dodajHaslo(Haslo* haslo);
    void usunHasla();
    void usunHaslo (Haslo* haslo);
    const vector<Haslo *> &getHasla() const;
};


#endif //PROJEKTSEMESTRALNY_KATEGORIA_H
