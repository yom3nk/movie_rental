#include "../include/Client.h"

void Client::addClient(sqlite3* db, const string& first_name, const string& last_name, const string& email) {
    string sql = "INSERT INTO clients (first_name, last_name, email) "
                 "VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, first_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, last_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, email.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Blad podczas dodawania uzytkownika" << endl;
        }

        sqlite3_finalize(stmt);
    } else {
        cerr << "err" << endl;
    }
}

void Client::listClients(sqlite3* db) {
    string sql = "SELECT * FROM clients;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        cout << "===== Klienci =====" << endl;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int client_id = sqlite3_column_int(stmt, 0);
            const unsigned char* first_name = sqlite3_column_text(stmt, 1);
            const unsigned char* last_name = sqlite3_column_text(stmt, 2);
            const unsigned char* email = sqlite3_column_text(stmt, 3);

            cout << "ID: " << client_id << ", Nazwa: " << first_name << " " << last_name << ", Email: " << email << endl;
        }
        cout << "===================" << endl;

        sqlite3_finalize(stmt);
    } else {
        cerr << "err" << endl;
    }
}
