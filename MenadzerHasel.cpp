/**
 * @file MenadzerHasel.h
 * @brief Definicja klasy MenadzerHasel.
 */
#include <ctime>
#include "MenadzerHasel.h"
using namespace std;

/**
 * @brief Otwiera strumien do zapisu.
 * @param s Nazwa pliku.
 */
void MenadzerHasel::otworzStrumien(string s) {
    plikHasel.open(s, ios::app);
}
/**
 * @brief Zamyka strumien do zapisu.
 */
void MenadzerHasel::zamknijStrumien() {
    plikHasel.close();
}
/**
 * @brief Odszyfrowuje wskazany plik oraz zapisuje timestamp kazdej proby odszyfrowania.
 * @param nazwaPliku Nazwa pliku do odszyfrowania.
 */
void MenadzerHasel::odszyfrujPlik(const string &nazwaPliku) {
    time_t result = time(nullptr);
    auto currentTime = std::asctime(std::localtime(&result));
    auto testStream = fstream(nazwaPliku, ios::in | ios::out);
    char end = '.';
    bool autoryzacja = false;
    string klucz;
    char temp;
    string znakiKlucza;
    while (testStream.get(temp)) {
        if (temp == end)
            break;
        else
            znakiKlucza += temp;
    }
    cout << "Podaj haslo do pliku" << endl;
    cin >> klucz;
    if (klucz == znakiKlucza)
        autoryzacja = true;
    if (zaszyfrowany && autoryzacja) {
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
        cout << "odszyfrowano plik" << endl;
        testStream.seekp(0, ios_base::cur);
        testStream << currentTime;
        testStream.close();
        zaszyfrowany = false;
    }
        else {
            cout << "Nie udalo sie odszyfrowac pliku - sprobuj ponownie!" << endl;
            testStream.seekp(0, ios::end);
                stringstream buffer;
                buffer << currentTime;
                string content = buffer.str();
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
    }
}
/**
 * @brief Zaszyfrowuje wskazany plik haslem pobranym od uzytkownika.
 * @param nazwaPliku Nazwa pliku, ktory powinien zostac zaszyfrowany.
 */
void MenadzerHasel::zaszyfrujPlik(const string &nazwaPliku) {
    if (!zaszyfrowany) {
        auto testStream = fstream(nazwaPliku, ios::in | ios::out);
        auto pierwszyZnak = testStream.peek();
        if (pierwszyZnak != '[') {
            cout << "Plik jest juz zaszyfrowany!" << endl;
            return;
        }
        cout << "Pod jakim haslem zaszyfrowac plik?" << endl;
        string klucz;
        cin >> klucz;
        stringstream buffer;
        buffer << testStream.rdbuf();
        string content = buffer.str();
        testStream.seekp(0);
        testStream << klucz;
        testStream << '.';
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
        zaszyfrowany = true;
    }
    else
        cout << "Plik jest juz zaszyfrowany!" << endl;
}
/**
 * @brief Tworzy nowe haslo zgodne z poleceniami uzytkownika.
 */
void MenadzerHasel::dodajHaslo() {
    if (!zaszyfrowany) {
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
        else
            cout << "Nie mozna dodac hasla - odszyfruj plik" << endl;
}
/**
 * @brief Tworzy nowa kategorie.
 */
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
/**
 * @brief Usuwa kategorie wskazana przez uzytkownika.
 */
void MenadzerHasel::usunKategorie() {// dodaj dekonstruktor
    if (!wszystkieKategorie.empty()) {
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
        else
            cout << "Lista kategorii jest pusta!" << endl;
}
/**
 * @brief Sortuje hasla zgodnie z poleceniem uzytkownika.
 */
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
/**
 * @brief Edytuje haslo wskazane przez uzytkownika.
 */
void MenadzerHasel::edytujHaslo() {
    if (!zapisaneHasla.empty()) {
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
    else
        cout << "Lista hasel jest pusta!" << endl;
}
/**
 * @brief Usuwa haslo wskazane przez uzytkownika.
 * @param nazwaPliku plik, z ktorego ma zostać usunięte haslo
 */
void MenadzerHasel::usunHaslo(const string& nazwaPliku) { //dziala, ma też usuwac haslo z pliku, dodaj dekonstruktor
    auto stream = fstream (nazwaPliku, ios::in | ios::out);
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
/**
 * @brief Szuka hasel pasujacych do parametrow podanych przez uzytkownika.
 */
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
/**
 * @brief Generuje losowe haslo w zaleznosci od polecen uzytkownika.
 */
void MenadzerHasel::wygenerujHaslo() {
    int userLength;
    cout << "Podaj dlugosc: " << endl;
    cin >> userLength;

    string userInput, userInput1;
    cout << "Czy haslo ma zawierac znaki specjalne? (tak lub nie): " << endl;
    cin >> userInput;
    cout << "Czy haslo ma zawierac zarowno male i duze litery? (tak lub nie): " << endl;
    cin >> userInput1;

    string characters = "abcdefghijklmnopqrstuvwxyz";
    string password = "";
    int passLength = userLength;

    if (userInput == "tak")
        characters += "!@#$%^&*()-_=+/?.>,<:;~`]}[{";
    if (userInput1 == "tak")
        characters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < passLength; i++) {
        int rand = std::rand() % passLength;
        password += characters[rand];
    }

    cout << "Wygenerowane haslo: " << password << endl;

    cout << "Wybierz opcje:" << endl;
    cout << "1 - haslo z dwoma parametrami" << endl;
    cout << "2 - haslo z czterema parametrami" << endl;
    int number;
    cin >> number;

    string passName, categoryName, site, login;
    switch (number) {
        case 1: {
            cin.ignore();
            cout << "Podaj nazwe pod jaka ma byc zapisane haslo: " << endl;
            getline(cin, passName);
            cout << "Podaj kategorie: " << endl;
            getline(cin, categoryName);

            Kategoria *kategoriaPtr = znajdzKategorie(categoryName);
            if (kategoriaPtr == nullptr) {
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                kategoriaPtr = &wszystkieKategorie.back();
            }

            Haslo haslo(passName, password, kategoriaPtr);
            sprawdzHaslo(haslo);
            kategoriaPtr->dodajHaslo(&haslo);
            zapisaneHasla.push_back(haslo);
            zapiszDoPliku(haslo);

            cout << "Haslo dodane" << endl;
            break;
        }
        case 2: {
            cin.ignore();
            cout << "Podaj nazwe pod jaka ma byc zapisane haslo: " << endl;
            getline(cin, passName);
            cout << "Podaj kategorie: " << endl;
            getline(cin, categoryName);
            cout <<  "Podaj strone internetowa: " << endl;
            getline(cin, site);
            cout << "Podaj login: " << endl;
            getline(cin, login);

            Kategoria *kategoriaPtr = znajdzKategorie(categoryName);
            if (kategoriaPtr == nullptr) {
                Kategoria kategoria(categoryName);
                wszystkieKategorie.push_back(kategoria);
                kategoriaPtr = &wszystkieKategorie.back();
            }

            Haslo haslo(passName, password, kategoriaPtr, site, login);
            sprawdzHaslo(haslo);
            kategoriaPtr->dodajHaslo(&haslo);
            zapisaneHasla.push_back(haslo);
            zapiszDoPliku(haslo);

            cout << "Haslo dodane" << endl;
            break;
        }
        default:
            cout << "Podales zla opcje - sprobuj ponownie!" << endl;
            break;
    }
}
/**
 * @brief Znajduje kategorię o podanej nazwie.
 * @param nazwa Nazwa kategorii do wyszukania.
 * @return Wskaźnik do znalezionej kategorii lub nullptr, jeśli kategoria nie została znaleziona.
 */
Kategoria* MenadzerHasel::znajdzKategorie(const string& nazwa) {
    for (auto& kategoria : wszystkieKategorie) {
        if (kategoria.getNazwa() == nazwa) {
            return &kategoria;
        }
    }
    return nullptr;
}
/**
 * @brief Tworzy nowe hasło i przypisuje je do kategorii.
 * @param a Wybrana opcja (2 - hasło podstawowe, 4 - hasło z dodatkowymi informacjami).
 */
void MenadzerHasel::utworzHasloIKategorie(int a) {
    string passName, pass, categoryName, site, login;

    switch (a) {
        case 2:
            cin.ignore();
            cout << "Podaj nazwe pod jaka ma byc zapisane haslo: " << endl;
            getline(cin, passName);
            cout << "Podaj tresc hasla: "<< endl;
            getline(cin, pass);
            cout << "Podaj kategorie: "<< endl;
            getline(cin, categoryName);
            break;
        case 4:
            cin.ignore();
            cout << "Podaj nazwe pod jaka ma byc zapisane haslo: " << endl;
            getline(cin, passName);
            cout << "Podaj tresc hasla: "<< endl;
            getline(cin, pass);
            cout << "Podaj kategorie: " << endl;
            getline(cin, categoryName);
            cout << "Podaj strone WWW: " << endl;
            getline(cin, site);
            cout << "Podaj login: "<< endl;
            getline(cin, login);
            break;
        default:
            cout << "Nieprawidlowa opcja" << endl;
            return;
    }

    Kategoria* kategoriaPtr = znajdzKategorie(categoryName);
    if (kategoriaPtr == nullptr) {
        Kategoria kategoria(categoryName);
        wszystkieKategorie.push_back(kategoria);
        kategoriaPtr = &wszystkieKategorie.back();
    }

    Haslo haslo(passName, pass, kategoriaPtr, site, login);
    sprawdzHaslo(haslo);
    kategoriaPtr->dodajHaslo(&haslo);
    zapisaneHasla.push_back(haslo);
    zapiszDoPliku(haslo);

    cout << "Haslo dodane" << endl;
}
/**
 * @brief Sprawdza siłę hasła i wyświetla odpowiedni komunikat oraz czy haslo nie zostalo wczesniej uzyte.
 * @param haslo Referencja do obiektu Haslo, które ma zostać sprawdzone.
 */
void MenadzerHasel::sprawdzHaslo(const Haslo &haslo) {
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
/**
 * @brief Zapisuje informacje o haśle do pliku.
 * @param haslo Referencja do obiektu Haslo, którego informacje mają zostać zapisane.
 */
void MenadzerHasel::zapiszDoPliku(const Haslo &haslo) {
    plikHasel << "[" <<haslo.getNazwa() << "]" << " " << "[" << haslo.getTresc() << "]" << " "
              << "[" << haslo.getKategoria()->getNazwa() << "]" << " " << "[" << haslo.getStronaInternetowa() << "]"
              << " " << "[" << haslo.getLogin() << "]" << endl;
}
