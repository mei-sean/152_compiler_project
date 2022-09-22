#include <iostream>
#include <cstring>
#include "scanner.h"
using namespace std;

bool Scanner::isSpecialSymbol(char ch) {
    // Check if there is a special character in the input stream. 
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == '.' || ch == ';' ||
        ch == ':=' || ch == '(' || ch == ')' || ch == '=' ||
        ch == '<' || ch == '>' || ch == '{' || ch == '}' ||
        ch == '[' || ch == ']' || ch == '^'|| ch == ':')
    {
        return true;
    }
    return false;
}
bool Scanner::isAlpha(char ch) {
    //check if character is a letter
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        return true;
    }
    return false;
}
bool Scanner::isDoubleSymbol(char ch) {
    if (ch == ':' || ch == '<' || ch == '>' ||
        ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '(') {
        return true;
    }
    return false;
}
bool Scanner::isDigit(char ch) {
    // Not an identifier if the first character is an int or a special symbol.
    if (ch == '0' || ch == '1' || ch == '2' ||
        ch == '3' || ch == '4' || ch == '5' ||
        ch == '6' || ch == '7' || ch == '8' ||
        ch == '9')
    {
        return true;
    }
    return false;
}
string Scanner::searchTable(string word) {    //implemented with linear Search O(n)
    int max = table.size();   //right bound of vector search
    for (int i = 0; i < max; i++) {
        if (word == table[i]) {
            return table[i];
        }
    }
    string emptyString = "";
    return emptyString;
}
string Scanner::convertToken(string token) {    //convert string into its keyword
    string returnToken;
    if (token == "+") {
        returnToken = "PLUSOP";
    }
    else if (token == "-") {
        returnToken = "MINUSOP";
    }
    else if (token == "*") {
        returnToken = "MULTOP";
    }
    else if (token == "/") {
        returnToken = "DIVOP";
    }
    else if (token == ":=") {
        returnToken = "ASSIGN";
    }
    else if (token == "=") {
        returnToken = "EQUAL";
    }
    else if (token == "<>") {
        returnToken = "NE";
    }
    else if (token == "<=") {
        returnToken = "LTEQ";
    }
    else if (token == ">=") {
        returnToken = "GTEQ";
    }
    else if (token == "<") {
        returnToken = "LT";
    }
    else if (token == ">") {
        returnToken = "GT";
    }
    else if (token == "+=") {
        returnToken = "PLUSEQUAL";
    }
    else if (token == "-=") {
        returnToken = "MINUSEQUAL";
    }
    else if (token == "*=") {
        returnToken = "MULTEQUAL";
    }
    else if (token == "/=") {
        returnToken = "DIVEQUAL";
    }
    else if (token == "^") {
        returnToken = "CARAT";
    }
    else if (token == ";") {
        returnToken = "SEMICOLON";
    }
    else if (token == ",") {
        returnToken = "COMMA";
    }
    else if (token == "(") {
        returnToken = "LPAREN";
    }
    else if (token == ")") {
        returnToken = "RPAREN";
    }
    else if (token == "[") {
        returnToken = "LBRACKET";
    }
    else if (token == "]") {
        returnToken = "RBRACKET";
    }
    else if (token == "{") {
        returnToken = "LBRACE";
    }
    else if (token == "}") {
        returnToken = "RBRACE";
    }
    else if (token == "(*") {
        returnToken = "LCOMMENT";
    }
    else if (token == "*)") {
        returnToken = "RCOMMENT";
    }
    else if (token == ".") {
        returnToken = "PERIOD";
    }
    else if (token == ":") {
        returnToken = "COLON";
    }
    return returnToken;
}
void token::initToken(string tokenType, string tokenName, string tokenValue, int tokenLine) {
    this->tokenType = tokenType;
    this->tokenName = tokenName;
    this->tokenValue = tokenValue;
    this->tokenLine = tokenLine;
}
token Scanner::nextToken(ifstream& ifs) {
    char ch;         //char to store next character in file
    string word;
    token newToken;
    word = "";    //string to store current word
    ch = this->nexttoken(ifs);    //scan the first character in file 
    if (ch == '\n') {
        newToken.initToken("END_OF_FILE", " ", " ", line);
    }
    if (this->isAlpha(ch)) {    //check if char is a letter
        //This block indicates word must be identifier or keyword
        word.push_back(ch);    //append letter to current word
        ch = this->nexttoken(ifs);    //get next character
        while (ch != '\n' && ch != '\t' && ch != ' ') {
            if (!this->isAlpha(ch)) {    //if not letter print error message
                cout << "TOKEN ERROR at line " << line << ": Invalid  at " << ch << endl;
                newToken.initToken(" ", " ", " ", line);
                break;
            }
            word.push_back(ch);
            ch = this->nexttoken(ifs);
        }
        string token = (str_upper(word));    //convert token to all uppercase
        if (this->searchTable(token) == token) {    //check if token matches any keyword in table
            newToken.initToken(token, word, " ", line);
        }
        else {
            newToken.initToken("IDENTIFIER", word, " ", line);
        }
    }
    else if (this->isDigit(ch)) {    //check if first char is a digit
        bool hasDecimal = false;
        bool invalid = false;
        word.push_back(ch);
        while (ch != '\n' && ch != '\t' && ch != ' ') {
            ch = this->nexttoken(ifs);
            if (ch == '.' && !hasDecimal) {    //if first decimal found
                hasDecimal = true;
                word.push_back(ch);
            }
            else if (ch == '.' && hasDecimal) {    //if another decimal is found
                invalid = true;                    //number is invalid 
                word.push_back(ch);
            }
            else {
                word.push_back(ch);
            }
        }
        if (!invalid) {
            newToken.initToken("INTEGER", " ", word, line); 
        }
        else {
            cout << "TOKEN ERROR at line " << line << ": Invalid number at " << word;
            newToken.initToken(" ", " ", " ", line);
        }
    }
    else if (this->isSpecialSymbol(ch)) {    //check if first char is an operator
        //This block indicates word must be a operator 
        word.push_back(ch);    //append letter to current word 
        while (ch != '\n' && ch != '\t' && ch != ' ') {    //while not end of word
            if (this->isDoubleSymbol(ch)) {    //check if operator can have two characters
                ch = this->nexttoken(ifs);
                string tempWord = word;    //create two character operator
                tempWord.push_back(ch);
                string token = this->searchTable(tempWord);    //check if operator is in table
                if (token != "") {    //if operator is in table
                    newToken.initToken(this->convertToken(token), tempWord, " ", line);
                    word = "";
                    return newToken;
                }
                else {
                    newToken.initToken(this->convertToken(word), word, " ", line);
                    word = "";
                    return newToken;
                }
            }
            else {
                string token = this->searchTable(word);
                newToken.initToken(this->convertToken(token), word, " ", line);
                word = "";
            }
            ch = this->nexttoken(ifs);
            if (ch != ' ' && ch != '\n' && ch != '\t') {
                word.push_back(ch);
            }
        }
    }
    else if (ch == '\'') {    //must be a string or character
        word.push_back(ch);
        bool endOfStr = false;
        while (ch != '\n' && ch != '\t') {
            ch = this->nexttoken(ifs);
            if (ch == '\'') {
                endOfStr = true;
            }
            word.push_back(ch);
            if (endOfStr) {
                if (word.length() == 3) {
                    newToken.initToken("CHARACTER", word, " ", line);
                }
                else {
                    newToken.initToken("STRING", word, " ", line);
                }
                break;
            }
        }
        if (!endOfStr) {
            cout << "TOKEN ERROR at line " << line << endl;
            newToken.initToken(" ", " ", " ", line);
        }
    }
    word = "";
    if (ch == '\n') {
        line++;
    }
    return newToken;
}
//code from assignmnet 2 to print all identifiers and keywords in a file
void Scanner::callScanner(ifstream &ifs, ofstream &ofs) {    //convert string into its keyword
    int line = 1;    //line to track which line we are in the input file
    char ch;         //char to store next character in file
    string word;
    word = "";    //string to store current word
    ch = this->nexttoken(ifs);    //scan the first character in file 
    if (this->isAlpha(ch)) {    //check if char is a letter
        //This block indicates word must be identifier or keyword
        word.push_back(ch);    //append letter to current word
        ch = this->nexttoken(ifs);    //get next character
        while (ch != '\n' && ch != '\t' && ch != ' ') {
            if (!this->isAlpha(ch)) {    //if not letter print error message
                cout << "TOKEN ERROR at line " << line << ": Invalid  at " << ch << endl;
                ofs << "TOKEN ERROR at line " << line << ": Invalid  at " << ch << endl;
                break;
            }
            word.push_back(ch);
            ch = this->nexttoken(ifs);
        }
        string token = (str_upper(word));    //convert token to all uppercase
        if (this->searchTable(token) == token) {    //check if token matches any keyword in table
            cout << token << " : " << word << endl;
            ofs << token << " : " << word << endl;
        }
        else {
            cout << "IDENTIFIER : " << word << endl;
            ofs << "IDENTIFIER : " << word << endl;
        }
    }
    else if (this->isDigit(ch)) {    //check if first char is a digit
        bool hasDecimal = false;
        bool invalid = false;
        word.push_back(ch);
        while (ch != '\n' && ch != '\t' && ch != ' ') {
            ch = this->nexttoken(ifs);
            if (ch == '.' && !hasDecimal) {    //if first decimal found
                hasDecimal = true;
                word.push_back(ch);
            }
            else if (ch == '.' && hasDecimal) {    //if another decimal is found
                invalid = true;                    //number is invalid 
            }
            else {
                word.push_back(ch);
            }
        }
        if (!invalid) {
            cout << "INTEGER : " << word << endl;
            ofs << "INTEGER : " << word << endl;
        }
        else {
            cout << "TOKEN ERROR at line " << line << ": Invalid number at " << word;
            ofs << "TOKEN ERROR at line " << line << ": Invalid number at " << word;
        }
    }
    else if (this->isSpecialSymbol(ch)) {    //check if first char is an operator
        //This block indicates word must be a operator 
        word.push_back(ch);    //append letter to current word 
        while (ch != '\n' && ch != '\t' && ch != ' ') {    //while not end of word
            if (this->isDoubleSymbol(ch)) {    //check if operator can have two characters
                ch = this->nexttoken(ifs);
                string tempWord = word;    //create two character operator
                tempWord.push_back(ch);
                string token = this->searchTable(tempWord);    //check if operator is in table
                if (token != "") {    //if operator is in table
                    cout << this->convertToken(token) << " : " << tempWord << endl;    //print the 2 character operator 
                    ofs << this->convertToken(token) << " : " << tempWord << endl;
                    word = "";
                }
                else {
                    cout << this->convertToken(word) << " : " << word << endl;
                    ofs << this->convertToken(word) << " : " << word << endl;
                    word = "";
                }
            }
            else {
                string token = this->searchTable(word);
                cout << this->convertToken(token) << " : " << word << endl;
                ofs << this->convertToken(token) << " : " << word << endl;
                word = "";
            }
            ch = this->nexttoken(ifs);
            if (ch != ' ' && ch != '\n' && ch != '\t') {
                word.push_back(ch);
            }
        }
    }
    else if (ch == '\'') {    //must be a string or character
        word.push_back(ch);
        bool endOfStr = false;
        while (ch != '\n' && ch != '\t') {
            ch = this->nexttoken(ifs);
            if (ch == '\'') {
                endOfStr = true;
            }
            word.push_back(ch);
            if (endOfStr) {
                if (word.length() == 3) {
                    cout << "CHARACTER : " << word << endl;
                    ofs << "CHARACTER : " << word << endl;
                }
                else {
                    cout << "STRING : " << word << endl;
                    ofs << "STRING : " << word << endl;
                }
                break;
            }
        }
        if (!endOfStr) {
            cout << "TOKEN ERROR at line " << line << endl;
            ofs << "TOKEN ERROR at line " << line << endl;
        }
    }
    word = "";
    if (ch == '\n') {
        line++;
    }
}
string Scanner::str_upper(string word) {    //converts a string to all uppercase 
    string new_word = word;
    for (int i = 0; i < new_word.size(); i++) {
        new_word.at(i) = toupper(new_word.at(i));
    }
    return new_word;
}
char Scanner::nexttoken(ifstream& in) {    //get next character in input stream from file
    char next_ch;
    in.get(next_ch);
    return next_ch;
}