#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctype.h>
#include <stdio.h>
#include "LexicalFunctions.h"
#include "Assembly.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using namespace std;

int main()
{
    // File Input and creation
    string filename("Input.txt");
    FILE *Inputfile = fopen(filename.c_str(), "r");
    ofstream file("SymbolTable.txt");
    ofstream Assembly("Assembly.asm");

    // If file is not found, exits
    if (Inputfile == nullptr)
    {
        return EXIT_FAILURE;
    }

    // Setting Column correlations
    int letter = 0;
    int Digit = 1;
    int space = 2;
    int equal = 3;
    int comma = 4;
    int semicolon = 5;
    int addition = 6;
    int subtraction = 7;
    int multiply = 8;
    int divide = 9;
    int LP = 10;
    int RP = 11;
    int lessthan = 12;
    int greaterthan = 13;
    int LB = 14;
    int RB = 15;
    int DN = 16;

    // 2D Array Decision Table (Row x Column)
    // Column Order: Let,Dig,space, = , ',' , ; , + , - , *, / , ( , ) , < , > , { , } , !
    int DecTable[10][18] = {
        {1, 3, 0, 4, 2, 9, 9, 9, 9, 8, 1, 2, 5, 6, 2, 2, 7},
        {1, 1, 2, 3, 2, 2, 3, 3, 3, 3, 1, 3, 3, 3, 2, 2, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 3, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 1, 3, 3, 3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}};

    // What I need to read and compare!
    unsigned char character = 0;
    std::string word = "";
    int currentstate = 0;
    string code[100];
    int counter2 = 0;

    // For Symbol Table
    string SymbolArray[100];
    int counter = 0;

    // First Pass
    for (int i = 0; i <= 3; i++)
    {
        character = getc(Inputfile);
        word += character;
    }
    if (word != "Clas")
    {
        currentstate = 3;
    }

    // while it is not to the end of the file, get next input.
    while (!feof(Inputfile))
    {
        switch (currentstate)
        {

        case 0:
            character = getc(Inputfile);
            // If input is a letter
            if (character == 'A' || character == 'B' || character == 'C' || character == 'D' || character == 'E' || character == 'F' || character == 'G' || character == 'H' || character == 'I' || character == 'J' || character == 'K' || character == 'L' || character == 'M' || character == 'N' || character == 'O' || character == 'P' || character == 'Q' || character == 'R' || character == 'S' || character == 'T' || character == 'U' || character == 'V' || character == 'W' || character == 'X' || character == 'Y' || character == 'Z' || character == 'a' || character == 'b' || character == 'c' || character == 'd' || character == 'e' || character == 'f' || character == 'g' || character == 'h' || character == 'i' || character == 'j' || character == 'k' || character == 'l' || character == 'm' || character == 'n' || character == 'o' || character == 'p' || character == 'q' || character == 'r' || character == 's' || character == 't' || character == 'u' || character == 'v' || character == 'w' || character == 'x' || character == 'y' || character == 'z')
            {
                word += character;
                currentstate = DecTable[currentstate][letter];
            }

            // If input is a number
            else if (character == '0' || character == '1' || character == '2' || character == '3' || character == '4' || character == '5' || character == '6' || character == '7' || character == '8' || character == '9')
            {
                currentstate = DecTable[currentstate][Digit];
            }

            // If input is a space
            else if (character == ' ')
            {
                currentstate = DecTable[currentstate][space];
            }

            // If input is a = sign
            else if (character == '=')
            {
                word += character;
                currentstate = DecTable[currentstate][equal];
            }

            // If input is a comma
            else if (character == ',')
            {
                currentstate = DecTable[currentstate][comma];
            }

            // If input is a semcolon
            else if (character == ';')
            {
                currentstate = DecTable[currentstate][semicolon];
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
                cout << character << "\t\tsemicolon\n";
            }

            // If input is a +
            else if (character == '+')
            {
                cout << character << "\t\t"
                     << "addition\n";
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
                currentstate = DecTable[currentstate][addition];
            }

            // If input is a -
            else if (character == '-')
            {
                cout << character << "\t\t"
                     << "subtraction\n";
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
                currentstate = DecTable[currentstate][subtraction];
            }

            // If input is a *
            else if (character == '*')
            {
                cout << character << "\t\t"
                     << "multiply\n";
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
                currentstate = DecTable[currentstate][multiply];
            }

            // Handling comments
            else if (character == '/')
            {
                word += character;
                currentstate = DecTable[currentstate][divide];
            }

            // If input is a (
            else if (character == '(')
            {
                currentstate = DecTable[currentstate][LP];
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
                CheckDelim(character);
            }

            // If input is a )
            else if (character == ')')
            {
                currentstate = DecTable[currentstate][RP];
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
                CheckDelim(character);
            }

            // If input is a <
            else if (character == '<')
            {
                word += character;
                currentstate = DecTable[currentstate][lessthan];
            }

            // If input is a >
            else if (character == '>')
            {
                word += character;
                currentstate = DecTable[currentstate][greaterthan];
            }

            // If input is a {
            else if (character == '{')
            {
                currentstate = DecTable[currentstate][LB];
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
                CheckDelim(character);
            }

            // If input is a }
            else if (character == '}')
            {
                currentstate = DecTable[currentstate][RB];
                cout << character << "\t\t"
                     << "RB\n";
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
            }

            // If input is a !
            else if (character == '!')
            {
                word += character;
                currentstate = DecTable[currentstate][DN];
            }

            break;

        case 1:
            character = getc(Inputfile);
            // If character is a letter
            if (character == 'A' || character == 'B' || character == 'C' || character == 'D' || character == 'E' || character == 'F' || character == 'G' || character == 'H' || character == 'I' || character == 'J' || character == 'K' || character == 'L' || character == 'M' || character == 'N' || character == 'O' || character == 'P' || character == 'Q' || character == 'R' || character == 'S' || character == 'T' || character == 'U' || character == 'V' || character == 'W' || character == 'X' || character == 'Y' || character == 'Z' || character == 'a' || character == 'b' || character == 'c' || character == 'd' || character == 'e' || character == 'f' || character == 'g' || character == 'h' || character == 'i' || character == 'j' || character == 'k' || character == 'l' || character == 'm' || character == 'n' || character == 'o' || character == 'p' || character == 'q' || character == 'r' || character == 's' || character == 't' || character == 'u' || character == 'v' || character == 'w' || character == 'x' || character == 'y' || character == 'z')
            {
                word += character;
                currentstate = DecTable[currentstate][letter];
            }
            // If character is a digit
            else if (character == '0' || character == '1' || character == '2' || character == '3' || character == '4' || character == '5' || character == '6' || character == '7' || character == '8' || character == '9')
            {
                word += character;
                currentstate = DecTable[currentstate][Digit];
            }
            else if (word == "IF")
            {
                checkReserve(word);
                code[counter2] = word;
                counter2++;
                word = "";
                if (character == ' ')
                {
                    while (word != "THEN")
                    {
                        character = getc(Inputfile);
                        // If character is a letter
                        if (character == 'A' || character == 'B' || character == 'C' || character == 'D' || character == 'E' || character == 'F' || character == 'G' || character == 'H' || character == 'I' || character == 'J' || character == 'K' || character == 'L' || character == 'M' || character == 'N' || character == 'O' || character == 'P' || character == 'Q' || character == 'R' || character == 'S' || character == 'T' || character == 'U' || character == 'V' || character == 'W' || character == 'X' || character == 'Y' || character == 'Z' || character == 'a' || character == 'b' || character == 'c' || character == 'd' || character == 'e' || character == 'f' || character == 'g' || character == 'h' || character == 'i' || character == 'j' || character == 'k' || character == 'l' || character == 'm' || character == 'n' || character == 'o' || character == 'p' || character == 'q' || character == 'r' || character == 's' || character == 't' || character == 'u' || character == 'v' || character == 'w' || character == 'x' || character == 'y' || character == 'z')
                        {
                            word += character;
                        }
                        // If character is a digit
                        else if (character == '0' || character == '1' || character == '2' || character == '3' || character == '4' || character == '5' || character == '6' || character == '7' || character == '8' || character == '9')
                        {
                            word += character;
                        }
                        else if (character == '+')
                        {
                            word += character;
                        }

                        // If input is a -
                        else if (character == '-')
                        {
                            word += character;
                        }
                        // If input is a *
                        else if (character == '*')
                        {
                            word += character;
                        }
                        // Handling division
                        else if (character == '/')
                        {
                            word += character;
                        }
                        // If character is a space
                        else if (character == ' ')
                        {
                            if (word == "==")
                            {
                                cout << word << "\t\tisequalto\n";
                                code[counter2++] = word;
                                word = "";
                            }
                            else
                            {
                                code[counter2] = word;
                                counter2++;
                                checkReserve(word);
                                word = "";
                            }
                        }
                        else if (character == '<')
                        {
                            word += character;
                            character = getc(Inputfile);
                            if (character == ' ')
                            {
                                cout << word << "\t\tlessthan\n";
                            }
                            else
                            {
                                word += character;
                                cout << word << "\t\tlessthanequalto\n";
                                character = getc(Inputfile);
                            }
                            code[counter2] = word;
                            counter2++;
                            word = "";
                        }
                        // If input is a >
                        else if (character == '>')
                        {
                            word += character;
                            character = getc(Inputfile);
                            if (character == ' ')
                            {
                                cout << word << "\t\tgreaterthan\n";
                            }
                            else
                            {
                                word += character;
                                cout << word << "\t\tgreaterthanequalto\n";
                                character = getc(Inputfile);
                            }
                            code[counter2] = word;
                            counter2++;
                            word = "";
                        }
                        else if (character == '=')
                        {
                            word += character;
                        }
                    }
                    if (word == "THEN")
                    {
                        code[counter2] = word;
                        counter2++;
                        checkReserve(word);
                        word = "";
                        currentstate = 0;
                    }
                }
                else
                {
                    currentstate = 3;
                }
            }
            // If character is a space
            else if (character == ' ')
            {
                checkReserve(word);
                SymbolArray[counter] = word;
                counter++;
                code[counter2] = word;
                counter2++;
                word = "";
                currentstate = DecTable[currentstate][space];
            }
            else if (character == '(')
            {
                currentstate = DecTable[currentstate][LP];
                CheckDelim(character);
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
                SymbolArray[counter] = s;
                counter++;
            }
            // If character is a , ; { }
            else if (character == ',' || character == ';' || character == '{' || character == '}' || character == ')')
            {
                if (character != '(')
                {
                    checkReserve(word);
                    currentstate = 2;
                }
                SymbolArray[counter] = word;
                counter++;
                code[counter2] = word;
                counter2++;
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
                CheckDelim(character);
                SymbolArray[counter] = s;
                counter++;
                character = getc(Inputfile);
                if (character == ';')
                {
                    std::string s(1, character);
                    code[counter2] = s;
                    counter2++;
                    CheckDelim(character);
                    SymbolArray[counter] = s;
                    counter++;
                }
            }

            break;

        case 2:

            // SUCCESS
            word = "";
            currentstate = 0;
            break;

        case 3:
            // ERROR
            cout << "Unable to create tokens! Good-Bye!";
            exit(EXIT_FAILURE);
            break;

        case 4:
            character = getc(Inputfile);
            // If character is a space, print out and reset currentstate
            if (character == ' ')
            {
                cout << word << "\t\t"
                     << "assignment\n";
                SymbolArray[counter] = word;
                counter++;
                code[counter2] = word;
                counter2++;
                currentstate = DecTable[currentstate][space];
                word = "";
            }

            // If character is another equal sign, print out and reset current state
            else if (character == '=')
            {
                word += character;
                cout << word << "\t"
                     << "equalto";
                code[counter2] = word;
                counter2++;
                word = "";
                currentstate = DecTable[currentstate][equal];
            }

            else
            {
                currentstate = 3;
            }

            break;

        case 5:
            character = getc(Inputfile);
            if (character == ' ')
            {
                cout << character << "\t\t"
                     << "lessthan";
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
                currentstate = DecTable[currentstate][space];
            }

            else if (character == '=')
            {
                word += character;
                cout << word << "\t\t"
                     << "lessthan_or_equalto";
                code[counter2] = word;
                counter2++;
                currentstate = DecTable[currentstate][equal];
            }

            else
            {
                currentstate = 3;
            }

            word = "";
            break;

        case 6:
            character = getc(Inputfile);
            if (character == ' ')
            {
                cout << character << "\t\t"
                     << "greaterthan";
                std::string s(1, character);
                code[counter2] = s;
                counter2++;
                currentstate = DecTable[currentstate][space];
            }

            else if (character == '=')
            {
                word += character;
                cout << word << "\t\t"
                     << "greaterthan_or_equalto";
                code[counter2] = word;
                counter2++;
                currentstate = DecTable[currentstate][equal];
            }

            else
            {
                currentstate = 3;
            }
            word = "";
            break;

        case 7:
            character = getc(Inputfile);
            if (character == '=')
            {
                word += character;
                cout << word << "\t\t"
                     << "doesnotequal";
                code[counter2] = word;
                counter2++;
                currentstate = DecTable[currentstate][equal];
            }
            else
            {
                currentstate = 3;
            }

            word = "";
            break;

        case 8:
            character = getc(Inputfile);
            // regular divide
            if (character == ' ')
            {
                cout << word << "\t\t"
                     << "divide\n";
                code[counter2] = word;
                counter2++;
                currentstate = DecTable[currentstate][space];
            }
            // Comment
            else if (character == '*')
            {
                word += character;
                cout << word << "\t\t"
                     << "Lcomment\n";
                while (character != '/')
                {
                    character = getc(Inputfile);
                }

                currentstate = DecTable[currentstate][multiply];
                cout << "*/"
                     << "\t\t"
                     << "Rcomment\n";
            }
            else
            {
                currentstate = 3;
            }

            word = "";
            break;

        case 9:
            character = getc(Inputfile);
            if (character == ' ')
            {
                currentstate = DecTable[currentstate][space];
            }
            else if (character == '}')
            {
                cout << character << "\t\tRB\n";
            }
        }
    }

    // Closing files and calling symbol table function
    fclose(Inputfile);
    SymbolTable(file, Assembly, SymbolArray, counter);
    PDA(code, Assembly);
    FinishAssembly(Assembly);
    return EXIT_SUCCESS;
}
