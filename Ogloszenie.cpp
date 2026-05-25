#include "Ogloszenie.h"

Ogloszenie::Ogloszenie(int id, std::string tytul, double cena, int wId, std::string wNazwa)
    : id(id), tytul(tytul), cenaPoczatkowa(cena), wlascicielId(wId), nazwaWlasciciela(wNazwa) {}

int Ogloszenie::getId() const { return id; }
int Ogloszenie::getWlascicielId() const { return wlascicielId; }
std::string Ogloszenie::getTytul() const { return tytul; }