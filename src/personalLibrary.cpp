#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "../inc/personalLibrary.h"
#include "../inc/textTool.h"

using namespace std;


// Book Struct
struct Book;
Book::Book() {
    title = "-";
    author = "-";
    genre = "-";
    book_id = "-";
    location = "-";
    numOfCopies = "-";
}
Book::Book(string Title, string Author, string Genre, string Book_id, string Location, string NumOfCopies) {
    title = Title;
    author = Author;
    genre = Genre;
    book_id = Book_id;
    location = Location;
    numOfCopies = NumOfCopies;
}

string Book::dataSelect(uint8_t index) { // index is 1 to 6. Title, Author, Genre, Book_id, Location, NumOfCopies
    switch (index)
    {
    case 1:
        return title;
        break;
    case 2:
        return author;
        break;
    case 3:
        return genre;
        break;
    case 4:
        return book_id;
        break;
    case 5:
        return location;
        break;
    case 6:
        return numOfCopies;
        break;
    default:
        return title;
        break;
    }
}
bool Book::dataEntry(string str, uint8_t index) {
    switch (index)
    {
    case 1:
        title = str;
        return true;
        break;
    case 2:
        author = str;
        return true;
        break;
    case 3:
        genre = str;
        return true;
        break;
    case 4:
        book_id = str;
        return true;
        break;
    case 5:
        location = str;
        return true;
        break;
    case 6:
        numOfCopies = str;
        return true;
        break;
    default:
        break;
    }
    return false;
}
ostream& operator << (ostream& os, const Book& b) {
    os << b.title << ", "
        << b.author << ", "
        << b.genre << ", "
        << b.book_id << ", "
        << b.location << ", "
        << b.numOfCopies;
    return os;
}



// Conctructor
PersonalLibrary::PersonalLibrary(string f) {
    fileName = f;
}

// Class Members
void PersonalLibrary::setFilename(std::string f) {
    fileName = f;
}
string PersonalLibrary::getFilename() {
    return fileName;
}


// Class Functions
void PersonalLibrary::createNewFile() {
    ofstream csvFile;
    csvFile.open((fileName + ".csv"));
    csvFile << "title\tauthor\tgenre\tbook_id\tdescription\tlocation\tnumOfCopies\t\n";
    csvFile.close();
}

bool PersonalLibrary::file_exist()
{
    fstream csvFile;
    csvFile.open((fileName + ".csv"));
    if (csvFile)
    {
        csvFile.close();
        return true;
    }
    csvFile.close();
    return false;
}

uint8_t PersonalLibrary::collectFromFile() {
    uint8_t status = 0;
    int len, row = 0;

    // Check if file is real // Error code 1
    if (!file_exist())
    {
        return 1;
    }

    ifstream csvFile;
    csvFile.open((fileName + ".csv"));

    string line, item;

    Book tempBook = Book();
    // 
    while (getline(csvFile, line))
    {
        len = 0;
        istringstream iss(line);
        while (getline(iss, item, '\t')) {
            tempBook.dataEntry(item, len + 1);
            len++;
        }
        if (len == 6) { 
            // if correct num of entrys,
            // then sumbit Book struct to library
            addBook(tempBook);
            //cout << len << "\n";
            //cout << tempBook << endl;
        } 
        else {
            //cout << "Wrong Size\n";
            status = 2;
        }

    }

    return status;
    //0: success
    //1: invalid file name
    //2: invild csv lines
}


// Read Options
bool PersonalLibrary::printBook() {
    int len = bookVec.size();
    if (len == 0)
    {
        return false;
    }

    for (int i = 0; i < bookVec.size(); i++)
    {
        cout << bookVec[i] << "\n";
    }
    return true;
}

bool PersonalLibrary::printBook(string title, uint8_t index) {
    // !!! needs a stronger search
    // example: title harry potter, then print all harry potter books.
    
    
    int len = bookVec.size();
    bool found = false; // If found, then true

    for (int i = 0; i < bookVec.size(); i++)
    {
        if (title == bookVec[i].dataSelect(index))  
        {
            cout << bookVec[i] << "\n";
            found = true;
        }
    }
    return found;
}

// --

// Edit Options

void PersonalLibrary::addBook(Book b) {
    bookVec.push_back(b);
}
bool PersonalLibrary::removeBook(string title) {
    for (int i = 0; i < bookVec.size(); i++)
    {
        if (bookVec[i].title == title)
        {
            bookVec.erase(bookVec.begin() + i);
            return true;
        }
    }
    return false;
}
bool PersonalLibrary::removeAllBooks() {
    int len = bookVec.size();
    if (len == 0) {
        return false;
    }
    
    bookVec.clear();
    return true;
}
