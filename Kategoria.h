//
// Created by krysm on 24.05.2023.
//

#ifndef PROJEKTSEMESTRALNY_KATEGORIA_H
#define PROJEKTSEMESTRALNY_KATEGORIA_H
#include <string>
#include <vector>
#include "Haslo.h"
using namespace std;

class Kategoria {
private:
    string nazwa;
    vector<Haslo> hasla; //do zrobienia nadklasa

public:
    Kategoria(const string &nazwa);

    const string &getNazwa() const;

    bool operator<(const Kategoria& other) const ;


    void dodajHaslo (Haslo &haslo) ;



    const vector<Haslo> getHasla() const;



    void usunHasla ();

};


#endif //PROJEKTSEMESTRALNY_KATEGORIA_H
