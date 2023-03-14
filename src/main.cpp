#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include "../inc/personalLibrary.h"
#include "../inc/textTool.h"

using namespace std;

// Functions 
void readOption();
void editMenu();

// Object
PersonalLibrary lib("Personal_Library");

int main()
{
    bool whileBool = true; // false for debug
    string choiceValue;

    if (lib.file_exist())
    {
        cout << "File Exist" << endl;
    }
    else
    {
        cout << "Original File Doesn't Exist" << endl;
        cout << "Do you want to create a new one? (Y/N)" << endl;
        getline(cin, choiceValue);
        if (asciitolower(choiceValue[0]) == 'y')
        {
            lib.createNewFile();
        }
        else
        {
            cout << "Bye" << endl;
            return 0;
        }
    }
    
    while (whileBool) { // Loading file
        uint8_t check = lib.collectFromFile();
        if (check == 0) {
            cout << "Successfully collected the data.\n\n";
            whileBool = false;
        }
        else if (check == 1) {
            cout << "Invalid File Name.\n";
            return 0;
        }
        else if (check == 2) {
            cout << "Some books where corrupted.\nThose books where excluded.\n\n";
            whileBool = false;
        }
    }

    whileBool = true;
    while (whileBool) { // Main Menu
        cout << "Menu: (choose first letter from the catagory)\n" << 
        "  R: Read\n  E: Edit\n  H: Help\n  Q: Quit" << endl;
        getline(cin, choiceValue);

        system("CLS"); // Clear Terminal
        switch (asciitolower(choiceValue[0]))
        {
        case 'r': // All Lines
            cout << "Choose to Read file" << endl;
            readOption();
            break;
        case 'e': // Single Lines
            cout << "Choose to create an entry" << endl;
            editMenu();
            break;
        case 'h': // Single Lines
            cout << "Help:\n //Add Details\n" << endl; 
            break;
        case 'q': // return to main menu
            cout << "Bye" << endl;
            whileBool = false;
            break;
        default:
            cout << "Invalid Entry.\nTry Again." << endl;
            break;
        }
    }
    return 0;
}


// Options Section Start
void findBooks() {
    string choiceValue;
    uint8_t index;
    bool whileBool = true;
    bool checkBool;
    while (whileBool) {
        cout << "What Catagory? (Use only the index number)\n" 
            << "  1: Title\n"
            << "  2: Author\n"
            << "  3: Genre\n"
            << "  4: Book Id\n"
            << "  5: Location\n"
            << "  6: NumOfCopies\n" 
            << "Input: ";
        getline(cin, choiceValue);
        if (choiceValue == "-back-") {
            return;
        }
        if (isdigit(choiceValue[0]))
        {
            char c = choiceValue[0];
            index = c - '0';
            cout << "What the name?\n";
            getline(cin, choiceValue);
            system("CLS");
            checkBool = lib.printBook(choiceValue, index);
            if (checkBool)
            {
                whileBool = false;
            }
            else 
            {
                cout << "Book not found\n";
            }
        }
        else
        {
            cout << "Not a number\n";
        }
    }
}


void readOption() {
    bool whileBool = true;
    bool printCheck;
    string choiceValue;
    while (whileBool) {
        cout << "Options\n" <<
            "  A : All Lines\n" <<
            "  F : Find Book\n" <<
            "  R : Return to Previous Menu\n";

        getline(cin, choiceValue);
        system("CLS");
        switch (asciitolower(choiceValue[0]))
        {
        case 'a': // All Lines
            printCheck = lib.printBook();
            if (printCheck == false)
            {
                cout << "No Data in the library";
            }
            cout << "\n";
            break;
        case 'f': // Single Lines
            // Go to new menu for choosing 
            // Category and string to look for
            findBooks();
            break;
        case 'r': // return to main menu
            whileBool = false;
            break;
        default:
            cout << "INCORRECT INPUT\n";
            break;
        }

    }
}

bool collect_book_data(string title, Book& tempBook) {
    const vector<string> dataStr =
    { "Title", "Author", "Genre", "ID of the Book", "Location", "Number of Copies" };
    int len = dataStr.size();
    bool whileBool = true;
    string userInput;
    int iter = 1; // Start at 1 because we aren't creating the title.

    tempBook.dataEntry(title, 1);

    while (whileBool)
    {
        
        if (1 <= iter && iter <= 5)
        {
            system("CLS");
            cout << tempBook << "\nEnter " << dataStr[iter] <<
                " Entry: Type -back- to return.\n Input: ";
            getline(cin, userInput);
            strCharSwap(userInput, '\t', ' '); // Prevents tabs from ruining the csv file. 
            if (userInput == "-back-")
            {
                tempBook.dataEntry("-", iter);
                iter--; // Moves back to a previous entry
                continue;
            }
            tempBook.dataEntry(userInput, iter + 1);
            iter++;
        }
        if (iter == 0)
        {
            return false;
        }
        if (iter == 6) {
            system("CLS");
            cout << "This is the book entry\n" << tempBook
                << "\nEnter this into the library? (Y\\N)\n";
            getline(cin, userInput);
            if (asciitolower(userInput[0]) == 'y') // enter book
            {
                return true;
            }
        }
    }

    return false;
}

void createMenu() {
    Book tempBook;
    bool whileBool = true;
    bool addBookBool;
    string choiceValue, newTitle;

    while (whileBool) {
        cout << "What is the new title?\n Input: ";
        getline(cin, newTitle);
        strCharSwap(newTitle, '\t', ' ');

        if (strToLower(newTitle) == "-back-")
        {
            whileBool = false;
        }

        if (!lib.nameTaken(newTitle, 1) && lib.validName(newTitle)) {
            addBookBool = collect_book_data(newTitle, tempBook);

            if (addBookBool) 
            { //Add book to library
                lib.addBook(tempBook);
            }

            cout << "Create a new entry? (Y\\N)\n";
            getline(cin, choiceValue);
            if (asciitolower(choiceValue[0]) == 'n') // end 
            {
                whileBool = false;
            }
        }
        else {
            cout << "Book Title is invalid\n";
        }

    }
}

void deleteOption() {
    string choiceTitle;
    bool whileBool = true;
    bool check;
    while (whileBool)
    {
        cout << "What book do you want to delete? (-back- to return)\n Input: ";
        getline(cin, choiceTitle);

        if (choiceTitle == "-back-")
        {
            whileBool = false;
            continue;
        }
        if (!lib.validName(choiceTitle))
        {
            cout << "Invalid Title used\n";
            continue;
        }

        strCharSwap(choiceTitle, '\t', ' ');
        // Maybe add a "Are you sure?" check
        check = lib.deleteEntry(choiceTitle);
        
        system("CLS");
        if (check) {
            cout << choiceTitle << " was removed.\n" 
                << "Continue? (Y\\N)\n Input: ";
            getline(cin, choiceTitle);
            if (asciitolower(choiceTitle[0]) == 'n')
            {
                whileBool = false;
                continue;
            }
            else {
                system("CLS");
            }
        }
        else {
            cout << choiceTitle << " is not a book.\n\n";

        }
    }
}

void editOption() {
    const vector<string> dataStr =
    { "Title", "Author", "Genre", "ID of the Book", "Location", "Number of Copies" };
    string choiceTitle, choiceValue;

    bool whileBool = true;
    bool check;
    int bookIndex;
    int catagory;
    uint8_t state = 0;

    while (whileBool)
    {
        if (state == 0)
        {
            cout << "What Book do you want to edit?(-back- to return)\n Input: ";
            getline(cin, choiceTitle);
            bookIndex = lib.findTitleIndex(choiceTitle);
            if (choiceTitle == "-back-") {
                return;
            }
            if (!lib.validName(choiceTitle))
            {
                system("CLS");
                cout << "Invalid Name\n";
                continue;
            }

            system("CLS");
            if (bookIndex == -1) { // Check if title doesn't exist
                cout << choiceTitle << "is not a book in the database.\n";
                continue;
            }
            else {
                cout << choiceTitle << " is in the database\n";
                state = 1;
                continue;
            }
        }
        else if (state == 1) {
            lib.printFromIndex(bookIndex);
            cout << "Choose a catagory to edit. (-back- to return)\n";
            for (size_t i = 1; i < dataStr.size(); i++)
            {
                cout << i << " : " << dataStr[i] << "\n";
            }
            cout << " Input: ";
            getline(cin, choiceValue);
            system("CLS");
            if (choiceValue == "-back-") {
                return;
            }

            if (isdigit(choiceValue[0])) {
                catagory = atoi(&choiceValue[0]);
            }
            else {
                system("CLS");
                cout << " Not a number\n";
                continue;
            }

            if (1 <= catagory && catagory <= 5)
            {
                cout << "\"" << dataStr[catagory] << "\" is currently \""
                    << lib.readBookCatagory(bookIndex ,catagory+1)
                    <<"\"\nWhat should be the replacement?\n Input: ";
                getline(cin, choiceValue);
                strCharSwap(choiceValue, '\t', ' ');
                
                system("CLS");
                if (!lib.validName(choiceValue))
                {
                    cout << "Invalid Name\n";
                    continue;
                }
                else {
                    lib.changeEntry(choiceValue, bookIndex, catagory+1);
                }

            }
        }
    }
}

void editMenu() {
    bool whileBool = true;
    string choiceValue;
    while (whileBool) {
        system("CLS"); // Clear Terminal
        cout << "Options\n" <<
            "  C : Create new entry\n" <<
            "  D : Delete entry\n" <<
            "  E : Edit entry\n" <<
            "  R : Return to Previous Menu\n" <<
            " Input: ";
        getline(cin, choiceValue);

        system("CLS"); // Clear Terminal
        switch (asciitolower(choiceValue[0]))
        {
        case 'c': // go to section for creating a new entry
            createMenu();
            break;
        case 'd': // Find a title of a given book and delete it
            deleteOption();
            break;
        case 'e': // Find a matching title and allow the user to edit the information
            editOption();
            break;
        case 'r': // return to main menu
            whileBool = false;
            break;
        default:
            break;
        }

    }
}

// Create Section





// Options Section End



//*/