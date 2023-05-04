#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

class User {
public:
    User(const std::string& id, const std::string& name) : id(id), name(name) {}

    std::string getId() const { return id; }
    std::string getName() const { return name; }

private:
    std::string id;
    std::string name;
};

class Book {
public:
    Book(const std::string& title, const std::string& author, const std::string& isbn)
        : title(title), author(author), isbn(isbn) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getISBN() const { return isbn; }

private:
    std::string title;
    std::string author;
    std::string isbn;
};

class Library {
public:
    void addUser(const std::string& id, const std::string& name) {
        if (users.find(id) == users.end()) {
            users[id] = User(id, name);
        }
        else {
            throw std::runtime_error("User with this ID already exists.");
        }
    }

    void addBook(const std::string& title, const std::string& author, const std::string& isbn) {
        if (books.find(isbn) == books.end()) {
            books[isbn] = Book(title, author, isbn);
        }
        else {
            throw std::runtime_error("Book with this ISBN already exists.");
        }
    }

    void borrowBook(const std::string& userId, const std::string& isbn) {
        auto it_user = users.find(userId);
        auto it_book = books.find(isbn);

        if (it_user == users.end()) {
            throw std::runtime_error("User not found.");
        }
        else if (it_book == books.end()) {
            throw std::runtime_error("Book not found.");
        }
        else if (borrowedBooks.find(isbn) != borrowedBooks.end()) {
            throw std::runtime_error("Book is already borrowed.");
        }
        else {
            borrowedBooks[isbn] = userId;
        }
    }

    void returnBook(const std::string& isbn) {
        auto it = borrowedBooks.find(isbn);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
        else {
            throw std::runtime_error("Book is not borrowed or not found.");
        }
    }

private:
    std::map<std::string, User> users;
    std::map<std::string, Book> books;
    std::map<std::string, std::string> borrowedBooks;
};

int main() {
    Library library;

    try {
        library.addUser("1", "John Doe");
        library.addBook("C++ Programming", "Bjarne Stroustrup", "1234567890");
        library.borrowBook("1", "1234567890");
        library.returnBook("1234567890");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
