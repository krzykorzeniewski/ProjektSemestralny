//
// Created by Krzysiek on 27.05.2023.
//

#include "MenadzerHasel.h"
using namespace std;

void MenadzerHasel::otworzStrumien(string s) {
    plikHasel.open(s);
}
void MenadzerHasel::zamknijStrumien() {
    plikHasel.close();
}
void MenadzerHasel::odszyfrujPlik(const string &nazwaPliku) {
    auto testStream = fstream(nazwaPliku, ios::in | ios::out);
    stringstream buffer;
    buffer << testStream.rdbuf();
    string content = buffer.str();
    testStream.seekp(0);
    for (int i = 0; i < content.size(); i++)
        if (content[i] == '&')
            testStream << 'a';
        else if (content[i] == 'u')
            testStream << 'e';
        else if (content[i] == 'a')
            testStream << 'i';
        else if (content[i] == 'e')
            testStream << 'o';
        else if (content[i] == 'i')
            testStream << 'u';
        else if (content[i] == 'o')
            testStream << 'y';
        else if (content[i] == '$')
            testStream << 'j';
        else if (content[i] == '@')
            testStream << ' ';
        else if (content[i] == '#')
            testStream << ']';
        else if (content[i] == '*')
            testStream << '[';
        else
            testStream << content[i];
    testStream.close();
    cout << "odszyfrowano plik" << endl;
}
void MenadzerHasel::zaszyfrujPlik(const string &nazwaPliku) {
    auto testStream = fstream(nazwaPliku, ios::in | ios::out);
    stringstream buffer;
    buffer << testStream.rdbuf();
    string content = buffer.str();
    testStream.seekp(0);
    for (int i = 0; i < content.size(); i++)
        if (content[i] == 'a')
            testStream << '&';
        else if (content[i] == 'e')
            testStream << 'u';
        else if (content[i] == 'i')
            testStream << 'a';
        else if (content[i] == 'o')
            testStream << 'e';
        else if (content[i] == 'u')
            testStream << 'i';
        else if (content[i] == 'y')
            testStream << 'o';
        else if (content[i] == 'j')
            testStream << '$';
        else if (content[i] == ' ')
            testStream << '@';
        else if (content[i] == ']')
            testStream << '#';
        else if (content[i] == '[')
            testStream << '*';
        else
            testStream << content[i];
    testStream.close();
    cout << "zaszyfrowano plik" << endl;
}
void MenadzerHasel::dodajHaslo() {
    cout << "Wybierz opcje" << endl;
    cout << "1 - podaj wlasne haslo" << endl;
    cout << "2 - wygeneruj haslo" << endl;
    int userInput;
    cin >> userInput;
    switch (userInput) {
        case 1: {
            cout << "Wybierz opcje" << endl;
            cout << "1 - haslo z dwoma parametrami" << endl;
            cout << "2 - haslo z czterema parametrami" << endl;
            int number;
            cin >> number;
            switch (number) {
                case 1: {
                    utworzHasloIKategorie(2);
                    break;
                }
                case 2: {
                    utworzHasloIKategorie(4);
                    break;
                }
            }
            break;
        }
        case 2: {
            wygenerujHaslo();
            break;
        }
        default:
            cout << "Cos poszlo nie tak - sprobuj ponownie!" << endl;
            break;
    }
}

void MenadzerHasel::dodajKategorie() {
    cout << "Podaj nazwe kategorii" << endl;
    string userInput;
    cin.ignore();
    getline(cin, userInput);
    Kategoria kategoria(userInput);
    wszystkieKategorie.push_back(kategoria);
    for (auto e: wszystkieKategorie)
        cout << e.getNazwa() << endl;
    cout << "Dodano kategorie!" << endl;
}
void MenadzerHasel::usunKategorie() {// dodaj dekonstruktor
    string userInput;
    cout << "Podaj nazwe kategorii, ktora chcesz usunac" << endl;
    for (auto e: wszystkieKategorie)
        cout << e.getNazwa() << endl;
    cin >> userInput;
    for (auto &e: wszystkieKategorie)
        if (userInput == e.getNazwa())
            e.usunHasla();
    auto range = std::ranges::remove_if(wszystkieKategorie, [&userInput](Kategoria kategoria) -> bool {
        return kategoria.getNazwa() == userInput;
    });
    wszystkieKategorie.erase(range.begin(), range.end());
    for (auto e: wszystkieKategorie)
        cout << e.getNazwa() << endl;
    cout << "Usunieto kategorie" << endl;
}
void MenadzerHasel::posortujHasla() {
    bool stillWork = true;
    int userInput;

    for (auto e: zapisaneHasla)
        cout << e.getTresc() << endl;

    cout << "Jak chcesz posortowac hasla?" << endl;
    cout << "1 - po kategorii" << endl;
    cout << "2 - po dlugosci hasla " << endl;
    cout << "3 - zakoncz sortowanie" << endl;

    while (stillWork) {
        cin >> userInput;
        switch (userInput) {
            case 1:
                std::sort(zapisaneHasla.begin(), zapisaneHasla.end(), [](Haslo a, Haslo b) -> bool {
                    return a.getKategoria()->getNazwa().size() > b.getKategoria()->getNazwa().size();
                });
                for (auto e: zapisaneHasla)
                    cout << e.getTresc() << endl;
                break;
            case 2:
                std::sort(zapisaneHasla.begin(), zapisaneHasla.end(),
                          [](Haslo a, Haslo b) -> bool { return a.getTresc().size() > b.getTresc().size(); });
                for (auto e: zapisaneHasla)
                    cout << e.getTresc() << endl;
                break;
            case 3:
                stillWork = false;
                cout << "Tu menu powinno byc" << endl;
                break;
            default:
                cout << "Cos poszlo nie tak" << endl;
                break;
        }
    }
    for (auto e: zapisaneHasla)
        cout << e.getTresc() << endl;
}
void MenadzerHasel::edytujHaslo() {
    cout << "Wpisz haslo, ktore chesz edytowac" << endl;
    for (auto e: zapisaneHasla)
        cout << e.getTresc() << " ";
    cout << endl;
    bool czyIstnieje = false;
    int index;
    string userPassword;
    string userChange;
    int userNumber;
    cin >> userPassword;

    for (int i = 0; i < zapisaneHasla.size(); i++) {
        if (userPassword == zapisaneHasla.at(i).getTresc()) {
            index = i;
            czyIstnieje = true;
        }
    }

    cout << "Wybierz co, chcesz edytowac" << endl;
    cout << "1 - nazwa hasla" << endl;
    cout << "2 - tresc hasla" << endl;
    cout << "3 - kategoria" << endl;

    cin >> userNumber;

    switch (userNumber) {
        case 1: {
            if (czyIstnieje) {
                cout << "Podaj nowa nazwe hasla" << endl;
                cin >> userChange;
                zapisaneHasla.at(index).setNazwa(userChange);
            } else
                cout << "Nie ma takiego hasla - sprobuj ponowie!" << endl;
            break;
        }
        case 2: {
            if (czyIstnieje) {
                cout << "Podaj nowa tresc hasla" << endl;
                cin >> userChange;
                zapisaneHasla.at(index).setTresc(userChange);
            } else
                cout << "Nie ma takiego hasla - sprobuj ponowie!" << endl;
            break;
        }
        case 3: {
            if (czyIstnieje) {
                cout << "Podaj nowa kategorie hasla" << endl;
                cin >> userChange;
                zapisaneHasla.at(index).zmienNazweKategorii(userChange);
            } else
                cout << "Nie ma takiego hasla - sprobuj ponowie!" << endl;
            break;
        }
        default:
            cout << "cos poszlo nie tak" << endl;
            break;
    }
}
void MenadzerHasel::usunHaslo() { //dziala, ma też usuwac haslo z pliku, dodaj dekonstruktor
    if (zapisaneHasla.empty()) {
        cout << "Brak zapisanych hasel" << endl;
    } else {
        string usserPasswd;
        cout << "Podaj jakie haslo chcesz usunac, wpisujac jego tresc" << endl;
        for (auto e: zapisaneHasla) {
            cout << e.getTresc() << endl;
        }
        cin >> usserPasswd;
        auto range = std::ranges::remove_if(zapisaneHasla, [&usserPasswd](Haslo haslo) -> bool {
            return haslo.getTresc() == usserPasswd;
        });
        zapisaneHasla.erase(range.begin(), range.end());
        cout << "Haslo usuniete!" << endl;
        for (auto e: zapisaneHasla) {
            cout << e.getTresc() << endl;
        }
    }
}
void MenadzerHasel::wyszukajHasla() {
    cout << "Podaj parametry (nazwa, tresc, kategoria, strona WWW, login)" << endl;
    string userName, userPass, userCat, userSite, userLogin;
    cin.ignore();
    getline(cin, userName);
    getline(cin, userPass);
    getline(cin, userCat);
    getline(cin, userSite);
    getline(cin, userLogin);
    for (auto e: zapisaneHasla) {
        if (e.getTresc() == userPass || e.getNazwa() == userName || e.getKategoria()->getNazwa() == userCat ||
            e.getLogin() == userLogin || e.getStronaInternetowa() == userSite)
            cout << "Haslo spelniajace conajmniej jeden parametr: " << e.getTresc() << endl;
    }
}
void MenadzerHasel::wygenerujHaslo() {
    cout << "Podaj dlugosc" << endl;
    int userLength;
    cin >> userLength;
    cout << "Czy haslo ma zawierac znaki specjalne (tak lub nie)" << endl;
    string userInput;
    cin >> userInput;
    cout << "Czy haslo ma zawierac zarowno male i duze litery? (tak lub nie)" << endl;
    string userInput1;
    cin >> userInput1;
    string characters = "abcdefghijklmnopqrstuvwxyz";
    string password = "";
    int passLength = 0;
    bool uppercase = false;
    bool special = false;
    passLength = userLength;

    if (userInput == "tak")
        special = true;
    if (userInput1 == "tak")
        uppercase = true;

    if (special)
        characters += "!@#$%^&*()-_=+/?.>,<:;~`]}[{";
    if (uppercase)
        characters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < passLength; i++) {
        int rand = std::rand() % passLength;
        password += characters[rand];
    }

    cout << "Wygenerowane haslo: " << password << endl;

    cout << "Wybierz opcje" << endl;
    cout << "1 - haslo z dwoma parametrami" << endl;
    cout << "2 - haslo z czterema parametrami" << endl;
    int number;
    cin >> number;
    switch (number) {
        case 1: {
            cout << "Podaj nazwe pod jaka ma byc zapisane haslo, pozniej kategorie" << endl;
            string passName, categoryName;
            cin.ignore();
            getline(cin, passName);
            getline(cin, categoryName);
            bool czyDodane = false;
            for (auto e: wszystkieKategorie) {
                if (e.getNazwa() == categoryName) {
                    czyDodane = true;
                    Haslo haslo(passName, password, &e);
                    sprawdzHaslo(haslo);
                    zapisaneHasla.push_back(haslo);
                    zapiszDoPliku(haslo);
                }
            }
            if (!czyDodane) {
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, password, &kategoria);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(&haslo);
                zapisaneHasla.push_back(haslo);
                zapiszDoPliku(haslo);
            }
            cout << "Haslo dodane" << endl;
            break;
        }
        case 2: {
            cout << "Podaj nazwe pod jaka ma byc zapisane haslo, pozniej kategorie, potem Strone WWW i na koncu login"<< endl;
            string passName, categoryName, site, login;
            cin.ignore();
            getline(cin, passName);
            getline(cin, categoryName);
            getline(cin, site);
            getline(cin, login);
            bool czyDodane = false;
            for (auto e: wszystkieKategorie) {
                if (e.getNazwa() == categoryName) {
                    czyDodane = true;
                    Haslo haslo(passName, password, &e, site, login);
                    sprawdzHaslo(haslo);
                    zapisaneHasla.push_back(haslo);
                    zapiszWiecejDoPliku(haslo);
                }
            }
            if (!czyDodane) {
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, password, &kategoria, site, login);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(&haslo);
                zapisaneHasla.push_back(haslo);
                zapiszWiecejDoPliku(haslo);
            }
            cout << "Haslo dodane" << endl;
            break;
        }
    }
}
void MenadzerHasel::utworzHasloIKategorie(int a) {
    switch (a) {
        case 2: {
            cout << "Podaj nazwe pod jaka ma byc zapisane haslo, pozniej jego tresc, nastepnie kategorie" << endl;
            string passName, pass, categoryName;
            cin.ignore();
            getline(cin, passName);
            getline(cin, pass);
            getline(cin, categoryName);
            bool czyDodane = false;
            for (auto e: wszystkieKategorie) {
                if (e.getNazwa() == categoryName) {
                    czyDodane = true;
                    Haslo haslo(passName, pass, &e);
                    sprawdzHaslo(haslo);
                    zapisaneHasla.push_back(haslo);
                    zapiszDoPliku(haslo);
                }
            }
            if (!czyDodane) {
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, pass, &kategoria);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(&haslo);
                zapisaneHasla.push_back(haslo);
                zapiszDoPliku(haslo);
            }
            cout << "Haslo dodane" << endl;
            break;
        }
        case 4: {
            cout
                    << "Podaj nazwe pod jaka ma byc zapisane haslo, nastepnie jego tresc, pozniej kategorie, potem Strone WWW i na koncu login"
                    << endl;
            string passName, pass, categoryName, site, login;
            cin.ignore();
            getline(cin, passName);
            getline(cin, pass);
            getline(cin, categoryName);
            getline(cin, site);
            getline(cin, login);
            bool czyDodane = false;
            for (auto e: wszystkieKategorie) {
                if (e.getNazwa() == categoryName) {
                    czyDodane = true;
                    Haslo haslo(passName, pass, &e, site, login);
                    sprawdzHaslo(haslo);
                    zapisaneHasla.push_back(haslo);
                    zapiszWiecejDoPliku(haslo);
                }
            }
            if (!czyDodane) {
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, pass, &kategoria, site, login);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(&haslo);
                zapisaneHasla.push_back(haslo);
                zapiszWiecejDoPliku(haslo);
            }
            cout << "Haslo dodane" << endl;
            break;
        }
        default:
            cout << "cos poszlo nie tak" << endl;
            break;
    }

}
void MenadzerHasel::sprawdzHaslo(const Haslo &haslo) { //dodac sprawdzenie trudnosci hasla (flagi na dlugosc, znaki specjalne)
    string specialCharacters = "!@#$%^&*()-_=+/?.>,<:;~`]}[{";
    string upperLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int poziomTrudnosci = 0;

    for (const auto &e: zapisaneHasla)
        if (e.getTresc() == haslo.getTresc())
            cout << "Haslo zostalo juz wczesniej uzyte" << endl;

    if (haslo.getTresc().size() > 7)
        poziomTrudnosci+=1;

    for (int i = 0; i < upperLetters.size(); i++)
        for (int j = 0; j < haslo.getTresc().size(); j++)
            if (upperLetters.at(i) == haslo.getTresc().at(j))
                poziomTrudnosci+=1;

    for (int i = 0; i < specialCharacters.size(); i++)
        for (int j = 0; j < haslo.getTresc().size(); j++)
            if (specialCharacters.at(i) == haslo.getTresc().at(j))
                poziomTrudnosci+=1;

    if (poziomTrudnosci <= 1)
        cout << "Haslo jest slabe" << endl;
    else if (poziomTrudnosci <= 2)
        cout << "Haslo jest przecietnie" << endl;
    else
        cout << "Haslo jest silne" << endl;
}
void MenadzerHasel::zapiszDoPliku(const Haslo &haslo) {
    plikHasel << "[" <<haslo.getNazwa() << "]" << " " << "[" << haslo.getTresc() << "]" << " "
              << "[" << haslo.getKategoria()->getNazwa() << "]" << endl;
}
void MenadzerHasel::zapiszWiecejDoPliku(const Haslo &haslo) {
    plikHasel << "[" <<haslo.getNazwa() << "]" << " " << "[" << haslo.getTresc() << "]" << " "
              << "[" << haslo.getKategoria()->getNazwa() << "]" << " " << "[" << haslo.getStronaInternetowa() << "]"
              << " " << "[" << haslo.getLogin() << "]" << endl;
}
