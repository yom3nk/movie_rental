#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <sqlite3.h>

using namespace std;

class Client {
public:
    int client_id;
    string first_name;
    string last_name;
    string email;

    static void addClient(sqlite3* db, const string& first_name, const string& last_name, const string& email);
    static void listClients(sqlite3* db);
};

#endif
