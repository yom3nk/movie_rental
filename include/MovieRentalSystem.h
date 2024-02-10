#ifndef MOVIERENTALSYSTEM_H
#define MOVIERENTALSYSTEM_H

#include <iostream>
#include <sqlite3.h>

using namespace std;

class MovieRentalSystem {
public:
    MovieRentalSystem(const string& dbPath);
    ~MovieRentalSystem();

    void run();

private:
    string dbPath;
    sqlite3* db;

    int selectOption();
    void createTables();
    void addMovie();
    void deleteMovie();
    void rentMovie();
    void returnMovie();
    void addClient();
    void listClients();
    void listMovies();
};

#endif
