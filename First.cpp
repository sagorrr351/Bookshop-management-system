#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

struct Book {
    int book_id;
    string title;
    string author;
    double price;
    int stock;
};

class Bookshop {
private:
    vector<Book> inventory;
    const string filename = "books.txt";

    void saveToFile() {
        ofstream file(filename, ios::trunc);
        for (auto &book : inventory) {
            file << book.book_id << "," << book.title << "," << book.author << "," << book.price << "," << book.stock << endl;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file(filename);
        if (!file) return;
        inventory.clear();
        Book book;
        while (file >> book.book_id) {
            file.ignore();
            getline(file, book.title, ',');
            getline(file, book.author, ',');
            file >> book.price;
            file.ignore();
            file >> book.stock;
            file.ignore();
            inventory.push_back(book);
        }
        file.close();
    }

public:
    Bookshop() { loadFromFile(); }

    void addBook(int id, string title, string author, double price, int stock) {
        inventory.push_back({id, title, author, price, stock});
        saveToFile();
        cout << "Book added successfully!\n";
    }

    void viewBooks() {
        cout << "\nAvailable Books:\n";
        cout << left << setw(10) << "ID" << setw(30) << "Title" << setw(20) << "Author" << setw(10) << "Price" << setw(10) << "Stock" << endl;
        for (auto &book : inventory) {
            cout << left << setw(10) << book.book_id << setw(30) << book.title << setw(20) << book.author << setw(10) << book.price << setw(10) << book.stock << endl;
        }
    }

    void sellBook(int id, int quantity) {
        for (auto &book : inventory) {
            if (book.book_id == id) {
                if (book.stock >= quantity) {
                    book.stock -= quantity;
                    saveToFile();
                    cout << "Sold " << quantity << " copies of '" << book.title << "'.\n";
                    return;
                } else {
                    cout << "Not enough stock available.\n";
                    return;
                }
            }
        }
        cout << "Book not found.\n";
    }

    void updatePrice(int id, double new_price) {
        for (auto &book : inventory) {
            if (book.book_id == id) {
                book.price = new_price;
                saveToFile();
                cout << "Price updated successfully!\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }
};

int main() {
    Bookshop shop;
    int choice, id, stock, quantity;
    string title, author;
    double price;

    while (true) {
        cout << "\n--- Bookshop Management System ---\n";
        cout << "1. Add Book\n2. View Books\n3. Sell Book\n4. Update Price\n5. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter Book ID: "; cin >> id;
                cin.ignore();
                cout << "Enter Title: "; getline(cin, title);
                cout << "Enter Author: "; getline(cin, author);
                cout << "Enter Price: "; cin >> price;
                cout << "Enter Stock: "; cin >> stock;
                shop.addBook(id, title, author, price, stock);
                break;

            case 2:
                shop.viewBooks();
                break;

            case 3:
                cout << "Enter Book ID to sell: "; cin >> id;
                cout << "Enter Quantity: "; cin >> quantity;
                shop.sellBook(id, quantity);
                break;

            case 4:
                cout << "Enter Book ID to update price: "; cin >> id;
                cout << "Enter New Price: "; cin >> price;
                shop.updatePrice(id, price);
                break;

            case 5:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice, try again.\n";
        }
    }
}
