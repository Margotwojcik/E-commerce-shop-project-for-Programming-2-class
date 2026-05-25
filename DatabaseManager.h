#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "sqlite3.h"
#include <vector>
#include <memory>
#include <string>
#include "Ogloszenie.h"
#include "KupTeraz.h"
#include "Aukcja.h"

class DatabaseManager {
private:
    sqlite3* db;
    void wykonajSQL(const std::string& sql);

public:
    DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

    void InicjalizujTabele();
    bool RejestrujUzytkownika(const std::string& login, const std::string& haslo);
    int LogujUzytkownika(const std::string& login, const std::string& haslo);
    bool DodajOgloszenie(const std::string& tytul, double cena, const std::string& typ, int wlascicielId);
    std::vector<std::unique_ptr<Ogloszenie>> PobierzWszystkieOgloszenia();
    bool UsunOgloszenie(int ogloszenieId, int uzytkownikId);
};

#endif