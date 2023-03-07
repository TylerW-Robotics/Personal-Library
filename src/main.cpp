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
void edit_options();

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
            edit_options();
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

void edit_options() {
    bool whileBool = true;
    string choiceValue;
    while (whileBool) {
        cout << "Options\n" <<
            "  C : Create new entry\n" <<
            "  E : Edit single entry\n" <<
            "  R : Return to Previous Menu\n";
        getline(cin, choiceValue);

        system("CLS"); // Clear Terminal
        switch (asciitolower(choiceValue[0]))
        {
        case 'c': // go to section for creating a new entry
            //
            break;
        case 'e': // Find a matching title and allow the user to edit the information
            //
            break;
        case 'd': // Find a title of a given book and delete it
            //
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

// Create Section





// Options Section End



//*/