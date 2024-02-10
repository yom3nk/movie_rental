#include "../include/Movie.h"

void Movie::addMovie(sqlite3* db, const string& title, const string& director, int release_year, const string& genre) {
    string sql = "INSERT INTO movies (title, director, release_year, genre) "
                 "VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, director.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, release_year);
        sqlite3_bind_text(stmt, 4, genre.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Blad podczas dodawania filmu" << endl;
        }

        sqlite3_finalize(stmt);
    } else {
        cerr << "err" << endl;
    }
}

void Movie::deleteFromDatabase(sqlite3* db) {
    string sql = "DELETE FROM movies WHERE movie_id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, movie_id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Blad podczas usuwania filmu" << endl;
        }

        sqlite3_finalize(stmt);
    } else {
        cerr << "err" << endl;
    }
}