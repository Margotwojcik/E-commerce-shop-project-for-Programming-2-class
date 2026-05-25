#ifndef SERWISAUKCYJNY_H
#define SERWISAUKCYJNY_H

#include "DatabaseManager.h"
#include <string>

class SerwisAukcyjny {
private:
    DatabaseManager db;
    int aktualnyUzytkownikId;
    std::string aktualnyUzytkownikLogin;
    void czyscEkran();

public:
    SerwisAukcyjny();

    bool czyZalogowany() const;
    std::string getZalogowanyLogin() const;

    void EkranRejestracji();
    void EkranLogowania();
    void Wyloguj();
    void WyswietlOferty();
    void DodajWlasnaOferte();
    void UsunWlasnaOferte();
};

#endif