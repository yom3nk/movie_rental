#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <sqlite3.h>

using namespace std;

class Movie {
public:
    int movie_id;
    string title;
    string director;
    int release_year;
    string genre;

    static void addMovie(sqlite3* db, const string& title, const string& director, int release_year, const string& genre);
    void deleteFromDatabase(sqlite3* db);
};

#endif