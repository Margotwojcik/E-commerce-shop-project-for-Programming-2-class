#ifndef KUPTERAZ_H
#define KUPTERAZ_H

#include "Ogloszenie.h"

class KupTeraz : public Ogloszenie {
public:
    using Ogloszenie::Ogloszenie; // Dziedziczenie konstruktora
    void wyswietl() const override;
};

#endif