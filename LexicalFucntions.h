Shortcuts simplify My Drive … 
In the coming weeks, items in more than one folder will be replaced by shortcuts. Access to files and folders won't change.Learn more
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <stack>

using std::cout;
using std::ifstream;
using std::string;
using namespace std;

bool isNumber(const string &str)
{
    for (char const &c : str)
    {
        if (isdigit(c) == 0)
            return false;
    }
    return true;
}

// RESERVED WORD CHECK
void checkReserve(const string &word)
{

    int number = isNumber(word);

    if (word == "Class")
    {
        cout << word << "\t"
             << "CLASS\n";
    }
    else if (number == true)
    {
        cout << word << "\t\t"
             << "integer\n";
    }
    else if (word == "CONST")
    {
        cout << word << "\t"
             << "CONST\n";
    }
    else if (word == "GET")
    {
        cout << word << "\t\t"
             << "GET\n";
    }
    else if (word == "PUT")
    {
        cout << word << "\t\t"
             << "PUT\n";
    }
    else if (word == "IF")
    {
        cout << word << "\t\t"
             << "IF\n";
    }
    else if (word == "VAR")
    {
        cout << word << "\t\t"
             << "VAR\n";
    }
    else if (word == "THEN")
    {
        cout << word << "\t"
             << "THEN\n";
    }
    else if (word == "ELSE")
    {
        cout << word << "\tELSE\n";
    }
    else if (word == "PROCEDURE")
    {
        cout << word << "\t"
             << "PROCEDURE\n";
    }
    else if (word == "WHILE")
    {
        cout << word << "\t"
             << "WHILE\n";
    }
    else if (word == "CALL")
    {
        cout << word << "\t"
             << "CALL\n";
    }
    else if (word == "DO")
    {
        cout << word << "\t"
             << "DO\n";
    }
    else if (word == "ODD")
    {
        cout << word << "\t"
             << "ODD\n";
    }

    // SPECIAL CASE BECAUSE IT WAS BEING WONKY (ONLY USED FOR IF STATEMENTS)
    // Sorry Dr.Burris I know this makes it uglier than it already is..
    else if (word == "+")
    {
        cout << word << "\t\t"
             << "addition\n";
    }
    else if (word == "-")
    {
        cout << word << "\t\t"
             << "subtraction\n";
    }
    else if (word == "*")
    {
        cout << word << "\t\t"
             << "multiplication\n";
    }
    else if (word == "/")
    {
        cout << word << "\t\t"
             << "division\n";
    }
    else if (word == "")
    {
    }
    else
    {
        cout << word << "\t\t"
             << "variable\n";
    }
}

// Check for delimeters that could come after variables or reserve words
void CheckDelim(unsigned char character)
{
    if (character == ',')
    {
        cout << character << "\t\t"
             << "comma\n";
    }
    else if (character == ';')
    {
        cout << character << "\t\t"
             << "semi\n";
    }
    else if (character == '(' || character == ')')
    {
        cout << character << "\t\t"
             << "parenthesis\n";
    }
    else if (character == '{')
    {
        cout << character << "\t\t"
             << "LB\n";
    }
    else if (character == '}')
    {
        cout << character << "\t\t"
             << "RB\n";
    }
}
