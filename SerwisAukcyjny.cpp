#include "SerwisAukcyjny.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h> // Ta biblioteka jest wymagana dla _getch()

std::string wczytajUkryteHaslo() {
    std::string haslo = "";
    char znak;
    
    while (true) {
        znak = _getch(); 

        if (znak == 13) {
            break;
        }
        
        else if (znak == 8) {
            if (!haslo.empty()) {
                haslo.pop_back(); 
                std::cout << "\b \b"; 
            }
        }
       
        else if (znak == 0 || znak == -32) {
            _getch(); 
        }
        
        else if (znak >= 32 && znak <= 126) { 
            haslo += znak;
            std::cout << '*';
        }
    }
    std::cout << std::endl; 
    return haslo;
}

void SerwisAukcyjny::czyscEkran() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

SerwisAukcyjny::SerwisAukcyjny() : db("allegro_mini.db"), aktualnyUzytkownikId(-1), aktualnyUzytkownikLogin("") {}

bool SerwisAukcyjny::czyZalogowany() const { return aktualnyUzytkownikId != -1; }
std::string SerwisAukcyjny::getZalogowanyLogin() const { return aktualnyUzytkownikLogin; }

void SerwisAukcyjny::EkranRejestracji() {
    std::string login, haslo;
    czyscEkran();
    std::cout << "=== REJESTRACJA NOWEGO KONTA ==="<<std::endl;
    std::cout << "Podaj login: ";
    std::cin >> login;
    std::cout << "Podaj haslo: ";
    haslo = wczytajUkryteHaslo();

    if (db.RejestrujUzytkownika(login, haslo)) {
        std::cout << "Konto utworzone pomyslnie!" << std::endl;
    } else {
        std::cout << "Blad! Login zajety." << std::endl;
    }
    std::cout << "Nacisnij Enter...";
    std::cin.ignore(); std::cin.get();
}

void SerwisAukcyjny::EkranLogowania() {
    std::string login, haslo;
    czyscEkran();
    std::cout << "=== LOGOWANIE ===" << std::endl;
    std::cout << "Login: "; 
    std::cin >> login;
    std::cout << "Haslo: "; 
    haslo = wczytajUkryteHaslo();

    int id = db.LogujUzytkownika(login, haslo);
    if (id != -1) {
        aktualnyUzytkownikId = id;
        aktualnyUzytkownikLogin = login;
        std::cout << "Zalogowano jako " << login << "!" << std::endl;
    } else {
        std::cout << "Bledne dane." << std::endl;
    }
    std::cout << "Nacisnij Enter...";
    std::cin.ignore(); std::cin.get();
}

void SerwisAukcyjny::Wyloguj() {
    aktualnyUzytkownikId = -1;
    aktualnyUzytkownikLogin = "";
    std::cout << "Wylogowano."<< std::endl;
    std::cout << "Nacisnij Enter...";
    std::cin.ignore(); std::cin.get();
}

void SerwisAukcyjny::WyswietlOferty() {
    czyscEkran();
    std::cout << "=== AKTUALNE OFERTY ==="<<std::endl;
    auto oferty = db.PobierzWszystkieOgloszenia();

    if (oferty.empty()) {
        std::cout << "Brak ofert." << std::endl;
    } else {
        for (const auto& o : oferty) {
            o->wyswietl(); 
        }
    }
    std::cout << "Nacisnij Enter...";
    std::cin.ignore(); std::cin.get();
}

void SerwisAukcyjny::DodajWlasnaOferte() {
    czyscEkran();
    std::cout << "=== DODAWANIE OFERTY ==="<<std::endl;
    std::cin.ignore();

    std::string tytul;
    std::cout << "Tytul: ";
    while (std::getline(std::cin, tytul) && tytul.empty()) {
   }

    double cena;
    std::cout << "Cena (PLN): ";
    while (!(std::cin >> cena) || cena <= 0) {
        std::cout << "Blad! Podaj jeszcze raz: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    int typWybor;
    std::string typStr = "KupTeraz";
    std::cout << "Typ:"<<std::endl;
    std::cout << "1. Kup Teraz" << std::endl;
    std::cout<<  "2. Aukcja" << std::endl;
    std::cout << "Wybor: ";
    std::cin >> typWybor;
    if (typWybor == 2) typStr = "Aukcja";

    if (db.DodajOgloszenie(tytul, cena, typStr, aktualnyUzytkownikId)) {
        std::cout << "Dodano oferte!" << std::endl;
    }
    std::cout << "Nacisnij Enter...";
    std::cin.ignore();
    std::cin.get();
}

void SerwisAukcyjny::UsunWlasnaOferte() {
    czyscEkran();
    std::cout << "=== TWOJE OFERTY ==="<<std::endl;
    auto oferty = db.PobierzWszystkieOgloszenia();
    int licznik = 0;

    for (const auto& o : oferty) {
        if (o->getWlascicielId() == aktualnyUzytkownikId) {
            o->wyswietl();
            licznik++;
        }
    }

    if (licznik == 0) {
        std::cout << "Brak ofert do usuniecia." << std::endl;
        std::cout << "Nacisnij Enter...";
        std::cin.ignore(); std::cin.get();
        return;
    }

    int idDoUsuniecia;
    std::cout << "Podaj ID ogloszenia do usuniecia: ";
    std::cin >> idDoUsuniecia;

    if (db.UsunOgloszenie(idDoUsuniecia, aktualnyUzytkownikId)) {
        std::cout << "Usunieto ogloszenie." << std::endl;
    } else {
        std::cout << "Blad usuwania (niepoprawne ID lub brak uprawnień)." << std::endl;
    }
    std::cout << "Nacisnij Enter...";
    std::cin.ignore(); std::cin.get();
}
