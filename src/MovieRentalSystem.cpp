#include "../include/MovieRentalSystem.h"
#include "../include/Movie.h"
#include "../include/Client.h"
#include "../include/Rental.h"

MovieRentalSystem::MovieRentalSystem(const string& dbPath) : dbPath(dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        cerr << "err" << endl;
        exit(EXIT_FAILURE);
    }
    createTables();
}

MovieRentalSystem::~MovieRentalSystem() {
    sqlite3_close(db);
}

void MovieRentalSystem::run() {
    int option;
    do {
        option = selectOption();

        switch (option) {
            case 1:
                addMovie();
                break;
            case 2:
                rentMovie();
                break;
            case 3:
                returnMovie();
                break;
            case 4:
                deleteMovie();
                break;
            case 5:
                addClient();
                break;
            case 6:
                listClients();
                break;
            case 7:
                listMovies();
                break;
            case 8:
                cout << "Zamykanie programu..." << endl;
                break;
            default:
                cout << "Zla opcja, wybierz ponownie" << endl;
        }
    } while (option != 8);
}

int MovieRentalSystem::selectOption() {
    int option;
    cout << "===== MENU =====" << endl;
    cout << "1. Dodaj film" << endl;
    cout << "2. Wypozycz film" << endl;
    cout << "3. Zwroc film" << endl;
    cout << "4. Usun film" << endl;
    cout << "5. Dodaj klienta" << endl;
    cout << "6. Wyswietl klientow" << endl;
    cout << "7. Wyswietl filmy" << endl;
    cout << "8. Zakonczenie programu" << endl;
    cout << "Wybierz opcje: ";
    cin >> option;
    return option;
}

void MovieRentalSystem::createTables() {
    char* errMsg;
    string sql = "CREATE TABLE IF NOT EXISTS movies ("
                 "movie_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "title TEXT NOT NULL,"
                 "director TEXT NOT NULL,"
                 "release_year INTEGER NOT NULL,"
                 "genre TEXT NOT NULL"
                 ");"
                 "CREATE TABLE IF NOT EXISTS clients ("
                 "client_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "first_name TEXT NOT NULL,"
                 "last_name TEXT NOT NULL,"
                 "email TEXT NOT NULL"
                 ");"
                 "CREATE TABLE IF NOT EXISTS rentals ("
                 "rental_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "movie_id INTEGER NOT NULL,"
                 "client_id INTEGER NOT NULL,"
                 "rental_date TEXT NOT NULL,"
                 "return_date TEXT,"
                 "returned INTEGER NOT NULL,"
                 "FOREIGN KEY (movie_id) REFERENCES movies(movie_id),"
                 "FOREIGN KEY (client_id) REFERENCES clients(client_id)"
                 ");";
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

void MovieRentalSystem::addMovie() {
    string title, director, genre;
    int release_year;

    cin.ignore();
    cout << "Podaj tytul: ";
    getline(cin, title);
    cout << "Podaj rezysera: ";
    getline(cin, director);
    cout << "Podaj rok wydania filmu: ";
    cin >> release_year;
    cin.ignore();
    cout << "Podaj gatunek filmu: ";
    getline(cin, genre);

    Movie::addMovie(db, title, director, release_year, genre);
    cout << "Film dodany do bazy" << endl;
}

void MovieRentalSystem::deleteMovie() {
    int movie_id;
    cout << "Podaj ID filmu, ktory chcesz usunac: ";
    cin >> movie_id;

    Movie movie;
    movie.movie_id = movie_id;
    movie.deleteFromDatabase(db);
    cout << "Usunieto film o ID: " << movie_id << endl;
}

void MovieRentalSystem::rentMovie() {
    int movie_id, client_id;
    string rental_date, return_date;
    bool returned = false;

    cout << "Podaj ID filmu: ";
    cin >> movie_id;
    cout << "Podaj ID klienta: ";
    cin >> client_id;
    cout << "Podaj date wypozyczenia (DD-MM-YYYY): ";
    cin >> rental_date;
    cout << "Podaj date zwrotu (DD-MM-YYYY): ";
    cin >> return_date;

    Rental::addRental(db, movie_id, client_id, rental_date, return_date, returned);
    cout << "Wypozyczono film" << endl;
}

void MovieRentalSystem::returnMovie() {
    int rental_id;
    cout << "Podaj ID zwrotu: ";
    cin >> rental_id;

    Rental::returnMovie(db, rental_id);
    cout << "Zwrocono film" << endl;
}

void MovieRentalSystem::addClient() {
    string first_name, last_name, email;

    cin.ignore();
    cout << "Podaj imie: ";
    getline(cin, first_name);
    cout << "Podaj nazwisko: ";
    getline(cin, last_name);
    cout << "Podaj email: ";
    getline(cin, email);

    Client::addClient(db, first_name, last_name, email);
    cout << "Klient dodany" << endl;
}

void MovieRentalSystem::listClients() {
    Client::listClients(db);
}

void MovieRentalSystem::listMovies() {
    string sql = "SELECT * FROM movies;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        cout << "===== FILMY =====" << endl;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int movie_id = sqlite3_column_int(stmt, 0);
            const unsigned char* title = sqlite3_column_text(stmt, 1);
            const unsigned char* director = sqlite3_column_text(stmt, 2);
            int release_year = sqlite3_column_int(stmt, 3);
            const unsigned char* genre = sqlite3_column_text(stmt, 4);

            cout << "ID: " << movie_id << ", Tytul: " << title << ", Rezyser: " << director << ", Rok wydania: " << release_year << ", Gatunek: " << genre << endl;
        }
        cout << "===================" << endl;

        sqlite3_finalize(stmt);
    } else {
        cerr << "err" << endl;
    }
}
