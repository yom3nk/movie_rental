#include "../include/Rental.h"

void Rental::addRental(sqlite3* db, int movie_id, int client_id, const string& rental_date, const string& return_date, bool returned) {
    string sql = "INSERT INTO rentals (movie_id, client_id, rental_date, return_date, returned) "
                 "VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, movie_id);
        sqlite3_bind_int(stmt, 2, client_id);
        sqlite3_bind_text(stmt, 3, rental_date.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, return_date.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 5, returned ? 1 : 0);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Blad przy dodawaniu wypozyczenia" << endl;
        }
        
        sqlite3_finalize(stmt);
    } else {
        cerr << "err" << endl;
    }
}

void Rental::returnMovie(sqlite3* db, int rental_id) {
    string sql = "UPDATE rentals SET returned = 1 WHERE rental_id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, rental_id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Blad przy aktualizacji statusu wypozyczenia" << endl;
        }

        sqlite3_finalize(stmt);
    } else {
        cerr << "err" << endl;
    }
}
