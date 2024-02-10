#ifndef RENTAL_H
#define RENTAL_H

#include <iostream>
#include <sqlite3.h>

using namespace std;

class Rental {
public:
    int rental_id;
    int movie_id;
    int client_id;
    string rental_date;
    string return_date;
    bool returned;

    static void addRental(sqlite3* db, int movie_id, int client_id, const string& rental_date, const string& return_date, bool returned);
    static void returnMovie(sqlite3* db, int rental_id);
};

#endif