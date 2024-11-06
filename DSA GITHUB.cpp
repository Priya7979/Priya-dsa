#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Movie {
    string name, time;
    int totalSeats, availableSeats;

    Movie(string n, string t, int seats) : name(n), time(t), totalSeats(seats), availableSeats(seats) {}
};

class MovieSystem {
    vector<Movie> movies;
    map<int, pair<string, string>> bookings;
    int bookingID = 1;

public:
    void addMovie(const string& name, const string& time, int seats) {
        movies.emplace_back(name, time, seats);
        cout << "Movie added successfully!\n";
    }

    void searchMovie(const string& name) const {
        for (const auto& movie : movies) {
            if (movie.name == name) {
                cout << "Movie Found: " << movie.name << " | Time: " << movie.time << " | Available Seats: " << movie.availableSeats << '\n';
                return;
            }
        }
        cout << "Movie not found!\n";
    }

    void bookTicket(const string& name, const string& time, int numTickets) {
        for (auto& movie : movies) {
            if (movie.name == name && movie.time == time && movie.availableSeats >= numTickets) {
                cout << "Enter payment method (credit/debit/cash): ";
                string paymentMethod;
                cin >> paymentMethod;

                if (paymentMethod == "credit" || paymentMethod == "debit") {
                    string cardNumber;
                    cout << "Enter your card number: ";
                    cin >> cardNumber;
                    cout << "Processing payment of $" << numTickets * 10 << " using " << paymentMethod << " card...\n";
                    cout << "Payment successful!\n";
                } else if (paymentMethod == "cash") {
                    cout << "Please pay at the counter.\n";
                    cout << "Payment recorded!\n";
                } else {
                    cout << "Invalid payment method.\n";
                    return;
                }

                bookings[bookingID++] = {name, time};
                movie.availableSeats -= numTickets;
                cout << "Ticket booked successfully! Booking ID: " << bookingID - 1 << '\n';
                return;
            }
        }
        cout << "Booking failed: Movie not found or no seats available.\n";
    }

    void cancelBooking(int id) {
        if (bookings.count(id)) {
            auto [name, time] = bookings[id];
            for (auto& movie : movies) {
                if (movie.name == name && movie.time == time) {
                    movie.availableSeats++;
                    bookings.erase(id);
                    cout << "Booking canceled successfully!\n";
                    return;
                }
            }
        }
        cout << "Invalid Booking ID!\n";
    }

    void viewAllMovies() const {
        if (movies.empty()) {
            cout << "No movies available!\n";
            return;
        }
        for (const auto& movie : movies) {
            cout << "Name: " << movie.name << " | Time: " << movie.time << " | Available Seats: " << movie.availableSeats << '\n';
        }
    }
};

int main() {
    MovieSystem system;
    int choice, seats, bookingID;
    string name, time;

    while (true) {
        cout << "\n1. Add Movie\n2. Search Movie\n3. Book Ticket\n4. Cancel Booking\n5. View All Movies\n6. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();  // Clear the input buffer

        switch (choice) {
            case 1:
                cout << "Enter movie name: ";
                getline(cin, name);
                cout << "Enter show time: ";
                getline(cin, time);
                cout << "Enter total seats: ";
                cin >> seats;
                system.addMovie(name, time, seats);
                break;

            case 2:
                cout << "Enter movie name to search: ";
                getline(cin, name);
                system.searchMovie(name);
                break;

            case 3:
                cout << "Enter movie name: ";
                getline(cin, name);
                cout << "Enter show time: ";
                getline(cin, time);
                cout << "Enter number of tickets: ";
                cin >> seats;
                system.bookTicket(name, time, seats);
                break;

            case 4:
                cout << "Enter Booking ID to cancel: ";
                cin >> bookingID;
                system.cancelBooking(bookingID);
                break;

            case 5:
                system.viewAllMovies();
                break;

            case 6:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}