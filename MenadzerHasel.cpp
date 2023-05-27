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

void MenadzerHasel::odszyfrujPlik(const string &nazwaPliku, const vector<char> &znaki) {
    auto testStream = fstream(nazwaPliku, ios::in | ios::out);
    std::stringstream buffer;
    buffer << testStream.rdbuf();
    std::string content = buffer.str();
    for (std::size_t i = 0; i < content.size(); i++) {
        if (content[i] == '$' && i < znaki.size()) {
            content[i] = znaki[i];
        }
    }

    testStream.seekp(0);
    testStream << content;
    testStream.close();

    std::cout << "odszyfrowano plik." << std::endl;
}

void MenadzerHasel::zaszyfrujPlik(const string &nazwaPliku) {
    auto testStream = fstream(nazwaPliku, ios::in | ios::out);
    vector<char> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    vector<char> znaki;
    stringstream buffer;
    buffer << testStream.rdbuf();
    string content = buffer.str();
    for (int i = 0; i < alphabet.size(); i++) {
        for (int j = 0; j < content.size(); j++)
            if (alphabet[i] == content[j]) {
                znaki.push_back(content[j]);
                content[j] = '.' + i;
            }
    }
    testStream.seekp(0);
    testStream << content;
    testStream.close();
    cout << "zaszyfrowano plik" << endl;
    for (auto e : znaki)
        cout << e << " ";
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

void MenadzerHasel::usunKategorie() {
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
                cout << "Powinno sie wylaczyc" << endl;
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

void MenadzerHasel::usunHaslo() { //dziala, ma też usuwac haslo z pliku
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
    string userInput;
    cin.ignore();
    getline(cin, userInput);
    for (auto e: zapisaneHasla) {
        if (e.getTresc() == userInput || e.getNazwa() == userInput || e.getKategoria()->getNazwa() == userInput ||
            e.getLogin() == userInput || e.getStronaInternetowa() == userInput)
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
                    plikHasel << "[" <<haslo.getNazwa() << "]" << " " << "[" << haslo.getTresc() << "]" << " "
                              << "[" << haslo.getKategoria()->getNazwa() << "]" << endl;
                }
            }
            if (!czyDodane) {
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, password, &kategoria);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(&haslo);
                zapisaneHasla.push_back(haslo);
                plikHasel << "[" <<haslo.getNazwa() << "]" << " " << "[" << haslo.getTresc() << "]" << " "
                          << "[" << haslo.getKategoria()->getNazwa() << "]" << endl;
            }
            cout << "Haslo dodane" << endl;
            break;
        }
        case 2: {
            cout
                    << "Podaj nazwe pod jaka ma byc zapisane haslo, pozniej kategorie, potem Strone WWW i na koncu login"
                    << endl;
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
                    plikHasel << "[" <<haslo.getNazwa() << "]" << " " << "[" << haslo.getTresc() << "]" << " "
                              << "[" << haslo.getKategoria()->getNazwa() << "]" << endl;
                }
            }
            if (!czyDodane) {
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, password, &kategoria, site, login);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(&haslo);
                zapisaneHasla.push_back(haslo);
                plikHasel << "[" <<haslo.getNazwa() << "]" << " " << "[" << haslo.getTresc() << "]" << " "
                          << "[" << haslo.getKategoria()->getNazwa() << "]" << endl;
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
                    plikHasel << "[" <<haslo.getNazwa() << "]" << " " << "[" << haslo.getTresc() << "]" << " "
                              << "[" << haslo.getKategoria()->getNazwa() << "]" << endl;
                }
            }
            if (!czyDodane) {
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, pass, &kategoria);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(&haslo);
                zapisaneHasla.push_back(haslo);
                plikHasel << "[" <<haslo.getNazwa() << "]" << " " << "[" << haslo.getTresc() << "]" << " "
                          << "[" << haslo.getKategoria()->getNazwa() << "]" << endl;
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
                    plikHasel << "[" <<haslo.getNazwa() << "]" << " " << "[" << haslo.getTresc() << "]" << " "
                              << "[" << haslo.getKategoria()->getNazwa() << "]" << endl;
                }
            }
            if (!czyDodane) {
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, pass, &kategoria, site, login);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(&haslo);
                zapisaneHasla.push_back(haslo);
                plikHasel << "[" <<haslo.getNazwa() << "]" << " " << "[" << haslo.getTresc() << "]" << " "
                          << "[" << haslo.getKategoria()->getNazwa() << "]" << endl;
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
