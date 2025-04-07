#include <iostream> // a library for input and output
#include <cctype>   // a library for character classification
#include <string>   // a library for using std::string

using namespace std;

// Character classes 
#define LETTER 0 // Alphabets
#define DIGIT 1 // Digits
#define UNKNOWN 99 // Anything else as operators
#define EOF_TOKEN -1 // End of file

// Token codes 
#define INT_LIT 10 // Integer literal
#define IDENT 11 // Identifier ( x , y ... )
#define ASSIGN_OP 20 // equal sign ( = )
#define ADD_OP 21 // Addition operator ( + )
#define SUB_OP 22 // Subtraction operator ( - )
#define MULT_OP 23 // Multiplication operator ( * )
#define DIV_OP 24 // Division operator ( / )
#define LEFT_PAREN 25 // Left parenthesis " ( "
#define RIGHT_PAREN 26 // Right parenthesis " ) "

// Global variables 
int charClass; // Current character class
char nextChar; // Actual character 
string lexeme; // Current lexeme
int nextToken; // the token after the current lexeme

// Function declarations 
void addChar(); // Adding next character to the lexeme
void getChar(); // Getting the value of the next character
void getNonBlank(); // Skips over whitespace
int lex(); // Lexical analyzer
int lookup(char ch); // Adding operators to tokens

// Main function
int main() {
    cout << "Enter the input text (press Enter and then Ctrl+D to stop input):" << endl;

    // Start reading the input directly from user input (cin)
    getChar(); // Getting the value of character
    do { // Starting a loop
        lex(); // A function to get the lexical analyzer
    } while (nextToken != EOF_TOKEN); // if the next token doesn't equal the end of file token

    return 0; // Return value 0 when finished
} // A curly brace to end the main function


void addChar() { // Adds nextChar to lexeme 
    lexeme += nextChar; // Lexeme will be added to the next character
} // A curly brace to end the addChar function


void getChar() { // Reads next character and sets charClass
    if (cin.get(nextChar)) { // If the next character is successfully got
        if (isalpha(nextChar)) // Checking if the next character is a letter
            charClass = LETTER; // The current character class is a letter
        else if (isdigit(nextChar)) // Another condition to check if the next character is a digit
            charClass = DIGIT; // The current character is a digit
        else // Another condition to check if the next character is something else
            charClass = UNKNOWN; // The current character is something else ( operator )
    }
    else { // If input ends
        charClass = EOF_TOKEN; // End of file
    } // A curly brace to end the else condition
} // A curly brace to end the getChar function


void getNonBlank() { // Skips whitespace
    while (isspace(nextChar)) { // Using a while loop to read the next characters till we meet a non space character
        getChar(); // A function that calls the non space character
    } // A curly brace to end the while loop
} // A curly brace to end the getNonBlank function


int lookup(char ch) { // A function that adds operators to tokens
    switch (ch) { // Using switch case to add characters to parenthesis and operators
    case '(':
        addChar();
        return LEFT_PAREN; //  ( 
    case ')':
        addChar();
        return RIGHT_PAREN; //  ) 
    case '+':
        addChar();
        return ADD_OP; // +
    case '-':
        addChar();
        return SUB_OP; // -
    case '*':
        addChar();
        return MULT_OP; // *
    case '/':
        addChar();
        return DIV_OP; // ' / '
    case '=':
        addChar();
        return ASSIGN_OP; // =
    default: // If none of the above cases is true
        addChar(); // Unknown character
        return EOF_TOKEN; // End of file

    } // A curly brace to end the switch case
} // A curly brace to end the lookup function


int lex() { // Lexical analyzer 
    lexeme.clear(); // Starting with empty lexeme
    getNonBlank(); // Skips whitespace

    switch (charClass) { // Using switch case
    case LETTER: // In case the current character is a letter
        addChar(); // Add character to lexeme
        getChar(); // Reading characters
        while (charClass == LETTER || charClass == DIGIT) {
            addChar(); // Add letter or digit to lexeme
            getChar(); // Read characters
        } // A curly brace to end the while loop
        nextToken = IDENT; // The next token is an identifier
        break; // Stop loop

    case DIGIT: // In case the current character is a digit
        addChar(); // Add character to lexeme
        getChar(); // Read characters
        while (charClass == DIGIT) {
            addChar(); // Add digit to lexeme
            getChar(); // Read characters
        } // A curly brace to end the while loop
        nextToken = INT_LIT; // The next token is an integer
        break; // Stop loop

    case UNKNOWN:
        nextToken = lookup(nextChar); /* In case the current character is an operator
        look up the next character */
        getChar(); // Read characters
        break; // Finish the case

    case EOF_TOKEN:
        lexeme = "EOF"; // In case of end of file the lexeme equals EOF
        nextToken = EOF_TOKEN;
        break; // Finish the case
    } // A curly brace to end the switch cases

    cout << "Next token is: " << nextToken << ", Next lexeme is: " << lexeme << endl; // Output the token and lexeme
    return nextToken;
} // A curly brace to end the lex function

