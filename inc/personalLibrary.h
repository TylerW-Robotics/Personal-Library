#pragma once

#include <string>
#include <vector>

#ifndef PERSONALLIBRARY_H
#define PERSONALLIBRARY_H

struct Book {
    std::string title;
    std::string author;
    std::string genre;
    std::string book_id;
    std::string location;
    std::string numOfCopies;
    Book();
    Book(std::string Title,
        std::string Author, 
        std::string Genre, 
        std::string Book_id, 
        std::string Location, 
        std::string NumOfCopies);
    std::string dataSelect(uint8_t index); // index is 1 to 6. Title, Author, Genre, Book_id, Location, NumOfCopies
    bool dataEntry(std::string str, uint8_t index);
    friend std::ostream& operator << (std::ostream& os, const Book& vec);
};

class PersonalLibrary
{
	std::string fileName;
	std::vector<Book> bookVec;
public:

	PersonalLibrary(std::string f);
	// Filename Functions
	void setFilename(std::string f);
    std::string getFilename();
	bool file_exist();
    // Book Functions
    void addBook(Book b); // Use Struct constructor for creating the new entry
    bool removeBook(std::string title);
    bool removeAllBooks();
    bool printBook(); // default will print all. bool is for it was successful.
    bool printBook(std::string title, uint8_t index); // string only searches for book to print. bool is for it was successful.
    // Class Functions
    uint8_t collectFromFile(); // 0: success, 1: invalid filename used, 2: Bad csv file set up
    void createNewFile();
};

#endif
