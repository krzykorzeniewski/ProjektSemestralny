#include <iostream>
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
    auto path = filesystem::current_path();
    if (filesystem::is_directory(path)) {
        auto dir = filesystem::recursive_directory_iterator(path);
            for (auto e : dir)
                if (e.path().extension() == ".txt")
                    cout << e.path().filename() << endl;
    }
    cout << "Podaj sciezke do pliku lub nazwe nowego pliku" << endl;
    string userInput;
    cin >> userInput;
    menadzerHasel.otworzStrumien(userInput);
    wyswietlMenu();

    int userNumber;

    while (stillWork) {
        cin >> userNumber;
        switch (userNumber) {
            case 1:
                menadzerHasel.wyszukajHasla();
                wyswietlMenu();
                break;
            case 2:
                menadzerHasel.posortujHasla();
                wyswietlMenu();
                break;
            case 3:
                menadzerHasel.dodajHaslo();
                wyswietlMenu();
                break;
            case 4:
                menadzerHasel.edytujHaslo();
                wyswietlMenu();
                break;
            case 5:
                menadzerHasel.usunHaslo();
                wyswietlMenu();
                break;
            case 6:
                menadzerHasel.dodajKategorie();
                wyswietlMenu();
                break;
            case 7:
                menadzerHasel.usunKategorie();
                wyswietlMenu();
                break;
            case 8:
                menadzerHasel.zaszyfrujPlik(userInput);
                wyswietlMenu();
                break;
            case 9:
                menadzerHasel.odszyfrujPlik(userInput);
                wyswietlMenu();
                break;
            case 10:
                stillWork = false;
                break;
            default:
                cout << "Podano zla opcje - sprobuj ponownie" << endl;
                wyswietlMenu();
                break;
        }
    }

    return 0;
}