#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class Haslo;
class Kategoria;

class Kategoria {
private:
    string nazwa;
    vector<Haslo> hasla;

public:
    Kategoria(const string &nazwa) : nazwa(nazwa) {}

    const string &getNazwa() const {
        return nazwa;
    }

    bool operator<(const Kategoria& other) const {
        return nazwa < other.nazwa;
    }

    void dodajHaslo (Haslo &haslo) {
        hasla.push_back(haslo);
    }

    const vector<Haslo> getHasla() const{
        return hasla;
    }

    void setHasla(const vector<Haslo> &hasla) {
        Kategoria::hasla = hasla;
    }

    void usunHasla () {
        hasla.clear();
    }
};

class Haslo {
private:
    string nazwa;
    string tresc;
    Kategoria kategoria;
    string stronaInternetowa;
    string login;

public:
    Haslo(const string &nazwa, const string &tresc, const Kategoria &kategoria) : nazwa(nazwa), tresc(tresc), kategoria(kategoria) {}
    Haslo(const string &nazwa, const string &tresc, const Kategoria &kategoria, const string &stronaInternetowa,const string &login) : nazwa(nazwa), tresc(tresc), kategoria(kategoria), stronaInternetowa(stronaInternetowa),login(login) {}

    const string &getNazwa() const {
        return nazwa;
    }

    const string &getTresc() const {
        return tresc;
    }

    const Kategoria &getKategoria() const {
        return kategoria;
    }

    const string &getStronaInternetowa() const {
        return stronaInternetowa;
    }

    const string &getLogin() const {
        return login;
    }
};

class MenadzerHasel {
private:
    string hasloDoMenadzera;
    vector<Kategoria> wszystkieKategorie;
    vector<string> wszystkieHaslaDoMenadzera;
    vector<Haslo> zapisaneHasla;
    bool autoryzowany;
    ofstream plikHasel;

public:

    void otworzStrumien (string s) {
        plikHasel.open(s);
    }

    void zamknijStrumien () {
        plikHasel.close();
    }

    void ustawHasloDoMenadzera() { //dziala
        if (hasloDoMenadzera.empty()) {
            cout << "Podaj haslo, ktore chcesz ustawic!" << endl;
            string userInput;
            cin >> userInput;
            hasloDoMenadzera = userInput;
            wszystkieHaslaDoMenadzera.push_back(userInput);
            cout << "Haslo ustawione!" << endl;
        }
        else {
            cout << "Podaj aktualne haslo!" << endl;
            string userInput;
            cin >> userInput;
            if (userInput == hasloDoMenadzera) {
                cout << "Podaj nowe haslo!" << endl;
                string userPassword;
                cin >> userPassword;
                hasloDoMenadzera = userPassword;
                wszystkieHaslaDoMenadzera.push_back(userPassword);
                cout << "Haslo zmienione!" << endl;
            }
            else {
                cout << "Haslo niepoprawne - sprobuj ponownie!" << endl;
            }
        }
    }

    void usunHasloDoMenadzera() { //dziala
        if (!hasloDoMenadzera.empty()) {
            cout << "Podaj aktualne haslo" << endl;
            string userPassword;
            cin >> userPassword;
            if (userPassword == hasloDoMenadzera) {
                auto range = std::ranges::remove_if(wszystkieHaslaDoMenadzera, [this](string haslo)->bool {return haslo == this -> hasloDoMenadzera;});
                wszystkieHaslaDoMenadzera.erase(range.begin(), range.end());
                hasloDoMenadzera = "";
                cout << "Haslo zostalo usuniete!" << endl;
            }
            else {
                cout << "Haslo niepoprawne - sprobuj ponownie!" << endl;
            }
        }
        else {
            cout << "Nie ma ustalonego hasla!" << endl;
        }
    }

    void odczytajZawartoscPliku() {
        // implementacja odczytu zawartości pliku
    }

    void zaszyfrujPlik() {
        // implementacja szyfrowania pliku
    }

    void dodajHaslo() { //zeby nie robic za kazdym razem nowej kategorii jesli zadana juz istnieje
        autoryzacja();
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

    void dodajKategorie() {
        autoryzacja();
        cout << "Podaj nazwe kategorii" << endl;
        string userInput;
        cin >> userInput;
        Kategoria kategoria(userInput);
        wszystkieKategorie.push_back(kategoria);
        for (auto e : wszystkieKategorie)
            cout << e.getNazwa() << endl;
        cout << "Dodano kategorie!" << endl;
    }

    void usunKategorie() {
        autoryzacja();
        string userInput;
        cout << "Podaj nazwe kategorii, ktora chcesz usunac" << endl;
        for (auto e : wszystkieKategorie)
            cout << e.getNazwa() << endl;
        cin >> userInput;
        for (auto& e: wszystkieKategorie)
            if (userInput == e.getNazwa())
               e.usunHasla();
        auto range = std::ranges::remove_if(wszystkieKategorie, [&userInput](Kategoria kategoria) -> bool {return kategoria.getNazwa() == userInput;});
        wszystkieKategorie.erase(range.begin(), range.end());
        for (auto e : wszystkieKategorie)
            cout << e.getNazwa() << endl;
        cout << "Usunieto kategorie" << endl;
    }

    void posortujHasla() { // dziala
        autoryzacja();
        int userInput;

        for (auto e : zapisaneHasla)
            cout << e.getTresc() << endl;

        cout << "Jak chcesz posortowac hasla?" << endl;
        cout << "1 - po kategorii" << endl;
        cout << "2 - po dlugosci hasla " << endl;
        cin >> userInput;

        switch (userInput) {
            case 1:
                std::sort(zapisaneHasla.begin(), zapisaneHasla.end(), [](Haslo a, Haslo b) -> bool {return a.getKategoria().getNazwa().size() > b.getKategoria().getNazwa().size();});
                break;
            case 2:
                std::sort(zapisaneHasla.begin(), zapisaneHasla.end(), [](Haslo a, Haslo b) -> bool {return a.getTresc().size() > b.getTresc().size();});
                break;
            default:
                cout << "Cos poszlo nie tak" << endl;
                break;
        }
        for (auto e : zapisaneHasla)
            cout << e.getTresc() << endl;
    }

    void edytujHaslo() {
        autoryzacja();

    }

    void usunHaslo() { //dziala
        autoryzacja();
        if (zapisaneHasla.empty()) {
            cout << "Brak zapisanych hasel" << endl;
        }
        else {
            string usserPasswd;
            cout << "Podaj jakie haslo chcesz usunac, wpisujac jego tresc" << endl;
            for (auto e: zapisaneHasla) {
                cout << e.getTresc() << endl;
            }
            cin >> usserPasswd;
            auto range = std::ranges::remove_if(zapisaneHasla, [&usserPasswd](Haslo haslo) -> bool {return haslo.getTresc() == usserPasswd;});
            zapisaneHasla.erase(range.begin(), range.end());
            cout << "Haslo usuniete!" << endl;
            for (auto e: zapisaneHasla) {
                cout << e.getTresc() << endl;
            }
        }
    }

    void wyszukajHasla() { //jak wczytać jedną linijkę kodu
        autoryzacja();
        cout << "Podaj parametry (nazwa, tresc, kategoria, strona WWW, login)" << endl;
        string userInput;
        cin >> userInput;
        for (auto e : zapisaneHasla) {
            if (e.getTresc() == userInput || e.getNazwa() == userInput || e.getKategoria().getNazwa() == userInput || e.getLogin() == userInput || e.getStronaInternetowa() == userInput)
                cout << "Haslo spelniajace conajmniej jeden parametr: " << e.getTresc() << endl;
        }
    }

    void wygenerujHaslo() { //dziala
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
                cin >> passName >> categoryName;
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, password, kategoria);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(haslo);
                zapisaneHasla.push_back(haslo);
                plikHasel << haslo.getNazwa() << " " << haslo.getTresc() << " " << haslo.getKategoria().getNazwa() << endl;
                cout << "Haslo dodane" << endl;
                break;
            }
            case 2: {
                cout << "Podaj nazwe pod jaka ma byc zapisane haslo, pozniej kategorie, potem Strone WWW i na koncu login" << endl;
                string passName, categoryName, site, login;
                cin >> passName >> categoryName >> site >> login;
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, password, kategoria, site, login);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(haslo);
                zapisaneHasla.push_back(haslo);
                plikHasel << haslo.getNazwa() << " " << haslo.getTresc() << " " << haslo.getKategoria().getNazwa() << endl;
                cout << "Haslo dodane" << endl;
                break;
            }
        }
    }

    void autoryzacja() { //dziala
        if (wszystkieHaslaDoMenadzera.empty())
            return;
        else if (!autoryzowany){
        string userPass;
        cout << "Podaj haslo do menadzera aby moc przejsc dalej" << endl;
        cin >> userPass;
        if (userPass == hasloDoMenadzera) {
            cout << "Haslo prawidlowe" << endl;
            autoryzowany = true;
        }
        else {
            cout << "Haslo niepoprawnem, sprobuj ponownie" << endl;
            return;
        }
    }
}

    void utworzHasloIKategorie(int a) {
        switch (a) {
            case 2: {
                cout << "Podaj nazwe pod jaka ma byc zapisane haslo, pozniej jego tresc, nastepnie kategorie" << endl;
                string passName, pass, categoryName;
                cin >> passName >> pass >> categoryName;

                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, pass, kategoria);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(haslo);
                zapisaneHasla.push_back(haslo);
                plikHasel << haslo.getNazwa() << " " << haslo.getTresc() << " " << haslo.getKategoria().getNazwa() << endl;
                cout << "Haslo dodane" << endl;
                break;
            }
            case 4: {
                cout << "Podaj nazwe pod jaka ma byc zapisane haslo, nastepnie jego tresc, pozniej kategorie, potem Strone WWW i na koncu login" << endl;
                string passName, pass, categoryName, site, login;
                cin >> passName >> pass >> categoryName >> site >> login;

                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                Haslo haslo(passName, pass, kategoria, site, login);
                sprawdzHaslo(haslo);
                kategoria.dodajHaslo(haslo);
                zapisaneHasla.push_back(haslo);
                plikHasel << haslo.getNazwa() << " " << haslo.getTresc() << " " << haslo.getKategoria().getNazwa() << endl;
                cout << "Haslo dodane" << endl;
                break;
            }
            default:
                cout << "cos poszlo nie tak" << endl;
            break;
        }

    }

    void sprawdzHaslo (Haslo haslo) {
        int counter = 0;
        for (auto e : zapisaneHasla)
            if (e.getTresc() == haslo.getTresc())
                counter++;
        if (counter > 0)
            cout << "Haslo zostalo juz wczesniej uzyte" << endl;
    }
};

void wyswietlMenu() {
    cout << "1 - wyszukaj hasla" << endl;
    cout << "2 - posortuj hasla" << endl;
    cout << "3 - dodaj haslo" << endl;
    cout << "4 - edytuj haslo" << endl;
    cout << "5 - usun haslo" << endl;
    cout << "6 - dodaj kategorie" << endl;
    cout << "7 - usun kategorie" << endl;
    cout << "8 - edytuj haslo do menadzera" << endl;
    cout << "9 - usun haslo do menadzera" << endl;
    cout << "10 - wyjscie" << endl;
}

int main() {
    MenadzerHasel menadzerHasel;
    bool stillWork = true;
    cout << "Podaj sciezke do pliku" << endl;
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
                menadzerHasel.ustawHasloDoMenadzera();
                break;
            case 9:
                menadzerHasel.usunHasloDoMenadzera();
                break;
            case 10:
                stillWork = false;
                break;
        }
    }

    menadzerHasel.zamknijStrumien();

    return 0;
}