#include "KupTeraz.h"

void KupTeraz::wyswietl() const {
    std::cout << "----------------------------------------\n";
    std::cout << "[TYP]:        KUP TERAZ\n";
    std::cout << "[ID]:         " << id << "\n";
    std::cout << "[TYTUL]:      " << tytul << "\n";
    std::cout << "[SPRZEDAWCA]: " << nazwaWlasciciela << "\n";
    std::cout << "[CENA]:       " << cenaPoczatkowa << " PLN\n";
    std::cout << "----------------------------------------\n";
}