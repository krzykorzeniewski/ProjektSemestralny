#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "MenadzerHasel.h"
using namespace std;

void wyswietlMenu() {
    cout << "1 - wyszukaj hasla" << endl;
    cout << "2 - posortuj hasla" << endl;
    cout << "3 - dodaj haslo" << endl;
    cout << "4 - edytuj haslo" << endl;
    cout << "5 - usun haslo" << endl;
    cout << "6 - dodaj kategorie" << endl;
    cout << "7 - usun kategorie" << endl;
    cout << "8 - zaszyfruj plik" << endl;
    cout << "9 - odszyfruj plik" << endl;
    cout << "10 - wyjscie" << endl;
}

int main() {
    MenadzerHasel menadzerHasel;
    bool stillWork = true;
    string path = "C:\\Users\\Krzysiek\\CLionProjects\\ProjektSemestralny\\cmake-build-debug";
    for (const auto &entry : filesystem::directory_iterator(path))
        cout << entry.path() << endl;
    cout << "Podaj sciezke do pliku lub nazwe nowego pliku" << endl;
    string userInput;
    cin >> userInput;
    menadzerHasel.otworzStrumien(userInput);
    vector<char> znaki;
    wyswietlMenu();

    int userNumber;

    while (stillWork) {
        cin >> userNumber;
        switch (userNumber) {
            case 1:
                menadzerHasel.wyszukajHasla();
                break;
            case 2:
                menadzerHasel.posortujHasla();
                break;
            case 3:
                menadzerHasel.dodajHaslo();
                break;
            case 4:
                menadzerHasel.edytujHaslo();
                break;
            case 5:
                menadzerHasel.usunHaslo();
                break;
            case 6:
                menadzerHasel.dodajKategorie();
                break;
            case 7:
                menadzerHasel.usunKategorie();
                break;
            case 8:
                menadzerHasel.zaszyfrujPlik(userInput);
                break;
            case 9:
                menadzerHasel.odszyfrujPlik(userInput, znaki);
                break;
            case 10:
                stillWork = false;
                break;
            default:
                cout << "cos poszlo nie tak - sprobuj ponownie" << endl;
                break;
        }
    }


    return 0;
}