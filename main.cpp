#include <iostream>
#include <clocale>
#include "SerwisAukcyjny.h"

int main() {
    std::setlocale(LC_ALL, "pl_PL.UTF-8");
    SerwisAukcyjny serwis;
    int wybor = 0;

    while (true) {
        if (!serwis.czyZalogowany()) {
            std::cout << "=== SERWIS AUKCYJNY ==="<<std::endl;
            std::cout << "1. Logowanie"<<std::endl;
            std::cout << "2. Rejestracja"<<std::endl;
            std::cout << "3. Oferty jako Gosc"<<std::endl;
            std::cout << "4. Wyjscie"<<std::endl;
            std::cout << "Wybor: ";
            if (!(std::cin >> wybor)) { std::cin.clear(); std::cin.ignore(10000, '\n'); continue; }
            if (wybor == 1) serwis.EkranLogowania();
            else if (wybor == 2) serwis.EkranRejestracji();
            else if (wybor == 3) serwis.WyswietlOferty();
            else if (wybor == 4) return 0;
        } else {
            std::cout << "=== MENU (Zalogowany: " << serwis.getZalogowanyLogin() << ") ==="<<std::endl;
            std::cout << "1. Przegladaj oferty"<<std::endl;
            std::cout << "2. Dodaj ogloszenie"<<std::endl;
            std::cout << "3. Usun ogloszenie"<<std::endl;
            std::cout << "4. Wyloguj"<<std::endl;
            std::cout << "Wybor: ";
            if (!(std::cin >> wybor)) { std::cin.clear(); std::cin.ignore(10000, '\n'); continue; }
            if (wybor == 1) serwis.WyswietlOferty();
            else if (wybor == 2) serwis.DodajWlasnaOferte();
            else if (wybor == 3) serwis.UsunWlasnaOferte();
            else if (wybor == 4) serwis.Wyloguj();
        }
    }
    return 0;
}