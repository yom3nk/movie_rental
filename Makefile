CC = g++
LDFLAGS = -lsqlite3

TARGET = MovieRental

$(TARGET): main.cpp src/Movie.cpp src/Client.cpp src/Rental.cpp src/MovieRentalSystem.cpp
	$(CC) $(LDFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(TARGET)
