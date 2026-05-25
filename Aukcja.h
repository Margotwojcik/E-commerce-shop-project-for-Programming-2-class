#ifndef AUKCJA_H
#define AUKCJA_H

#include "Ogloszenie.h"

class Aukcja : public Ogloszenie {
private:
    double aktualnaCena;

public:
    Aukcja(int id, std::string tytul, double cena, int wId, std::string wNazwa, double aktCena);
    void wyswietl() const override;
};

#endif