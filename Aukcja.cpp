#include "Aukcja.h"

Aukcja::Aukcja(int id, std::string tytul, double cena, int wId, std::string wNazwa, double aktCena)
    : Ogloszenie(id, tytul, cena, wId, wNazwa), aktualnaCena(aktCena) {}

void Aukcja::wyswietl() const {
    std::cout << "----------------------------------------\n";
    std::cout << "[TYP]:        AUKCJA (LICYTACJA)\n";
    std::cout << "[ID]:         " << id << "\n";
    std::cout << "[TYTUL]:      " << tytul << "\n";
    std::cout << "[SPRZEDAWCA]: " << nazwaWlasciciela << "\n";
    std::cout << "[WYWOLAWCZA]: " << cenaPoczatkowa << " PLN\n";
    std::cout << "[AKTUALNA]:   " << aktualnaCena << " PLN\n";
    std::cout << "----------------------------------------\n";
}