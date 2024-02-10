#include "include/MovieRentalSystem.h"

int main() {
    MovieRentalSystem rentalSystem("database.db");
    rentalSystem.run();

    return 0;
}