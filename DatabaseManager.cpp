#include "DatabaseManager.h"
#include <iostream>

void DatabaseManager::wykonajSQL(const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Błąd SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

DatabaseManager::DatabaseManager(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Nie można otworzyć bazy danych!\\n";
        exit(1);
    }
    InicjalizujTabele();
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(db);
}

void DatabaseManager::InicjalizujTabele() {
    wykonajSQL("CREATE TABLE IF NOT EXISTS Uzytkownicy ("
               "Id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "Login TEXT UNIQUE NOT NULL, "
               "Haslo TEXT NOT NULL);");

    wykonajSQL("CREATE TABLE IF NOT EXISTS Ogloszenia ("
               "Id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "Tytul TEXT NOT NULL, "
               "Cena double NOT NULL, "
               "Typ TEXT NOT NULL, "
               "WlascicielId INTEGER, "
               "AktualnaCena double, "
               "FOREIGN KEY(WlascicielId) REFERENCES Uzytkownicy(Id));");
}

bool DatabaseManager::RejestrujUzytkownika(const std::string& login, const std::string& haslo) {
    std::string sql = "INSERT INTO Uzytkownicy (Login, Haslo) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    bool sukces = false;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, haslo.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_DONE) sukces = true;
    }
    sqlite3_finalize(stmt);
    return sukces;
}

int DatabaseManager::LogujUzytkownika(const std::string& login, const std::string& haslo) {
    std::string sql = "SELECT Id FROM Uzytkownicy WHERE Login = ? AND Haslo = ?;";
    sqlite3_stmt* stmt;
    int userId = -1;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, haslo.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            userId = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return userId;
}

bool DatabaseManager::DodajOgloszenie(const std::string& tytul, double cena, const std::string& typ, int wlascicielId) {
    std::string sql = "INSERT INTO Ogloszenia (Tytul, Cena, Typ, WlascicielId, AktualnaCena) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    bool sukces = false;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, tytul.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 2, cena);
        sqlite3_bind_text(stmt, 3, typ.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 4, wlascicielId);
        sqlite3_bind_double(stmt, 5, cena);
        if (sqlite3_step(stmt) == SQLITE_DONE) sukces = true;
    }
    sqlite3_finalize(stmt);
    return sukces;
}

std::vector<std::unique_ptr<Ogloszenie>> DatabaseManager::PobierzWszystkieOgloszenia() {
    std::vector<std::unique_ptr<Ogloszenie>> lista;
    std::string sql = "SELECT o.Id, o.Tytul, o.Cena, o.Typ, o.WlascicielId, o.AktualnaCena, u.Login "
                      "FROM Ogloszenia o JOIN Uzytkownicy u ON o.WlascicielId = u.Id;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string tytul = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            double cena = sqlite3_column_double(stmt, 2);
            std::string typ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            int wlascicielId = sqlite3_column_int(stmt, 4);
            double aktCena = sqlite3_column_double(stmt, 5);
            std::string wlascicielNazwa = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

            if (typ == "KupTeraz") {
                lista.push_back(std::make_unique<KupTeraz>(id, tytul, cena, wlascicielId, wlascicielNazwa));
            } else if (typ == "Aukcja") {
                lista.push_back(std::make_unique<Aukcja>(id, tytul, cena, wlascicielId, wlascicielNazwa, aktCena));
            }
        }
    }
    sqlite3_finalize(stmt);
    return lista;
}

bool DatabaseManager::UsunOgloszenie(int ogloszenieId, int uzytkownikId) {
    std::string sql = "DELETE FROM Ogloszenia WHERE Id = ? AND WlascicielId = ?;";
    sqlite3_stmt* stmt;
    bool sukces = false;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, ogloszenieId);
        sqlite3_bind_int(stmt, 2, uzytkownikId);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            if (sqlite3_changes(db) > 0) sukces = true;
        }
    }
    sqlite3_finalize(stmt);
    return sukces;
}