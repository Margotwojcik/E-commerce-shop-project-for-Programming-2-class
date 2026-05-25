#ifndef OGLOSZENIE_H
#define OGLOSZENIE_H

#include <string>
#include <iostream>

class Ogloszenie {
protected:
    int id;
    std::string tytul;
    double cenaPoczatkowa;
    int wlascicielId;
    std::string nazwaWlasciciela;

public:
    Ogloszenie(int id, std::string tytul, double cena, int wId, std::string wNazwa);
    virtual ~Ogloszenie() = default; 

    virtual void wyswietl() const = 0; 

    int getId() const;
    int getWlascicielId() const;
    std::string getTytul() const;
};

#endif