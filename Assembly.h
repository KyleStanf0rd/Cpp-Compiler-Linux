#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <stack>
#include "LexicalFunctions.h" //For IsNumber function

using std::cout;
using std::ifstream;
using std::string;
using namespace std;

// Create Beginning of Assembly code
void AssemblyStart(ofstream &Assembly, vector<string> Const, vector<string> Vars, vector<string> Nums)
{
    Assembly << "sys_exit equ 1\nsys_read equ 3\nsys_write equ 4\nstdin equ 0 ; default keyboard | I/O redirection \nstdout equ 1 ; default terminal screen \nstderr equ 3\n\n";
    Assembly << "section .data\nuserMsg	db 'Enter an integer(less than 32,765): '\nlenUserMsg equ $-userMsg\ndisplayMsg	db 'You entered: '\nlenDisplayMsg equ $-displayMsg\nnewline	db 0xA 	; 0xA 0xD is ASCII <LF><CR>\n";
    Assembly << "Ten DW 10  ;Used converting to base ten.\n;printTempchar db 'Tempchar = : '\n;lenprintTempchar	equ $-printTempchar\n\nResult db 'Ans = '\nResultValue db	'aaaaa'\n\t\tdb	 0xA		;return\nResultEnd equ $-Result\n\t\t\t; $=> here - address Result = length to print\n\nnum times 6 db 'ABCDEF' ;cheat NASM\nnumEnd equ	$-num\n\n";
    for (int i = 0; i < Const.size(); i += 2)
    {
        Assembly << Const[i] << "  DW " << Const[i + 1] << "\n";
    }
    for (int i = 0; i < Nums.size(); i++)
    {
        Assembly << "Lit" << Nums[i] << " DW " << Nums[i] << endl;
    }
    Assembly << "\n\n\nsection .bss\n\nTempChar RESB 1\ntestchar RESB 1\nReadInt RESW 1\ntempint RESW 1\nnegflag RESB 1\n\n";
    for (int i = 0; i < Vars.size(); i++)
    {
        Assembly << Vars[i] << "  RESW 1\n";
    }
    Assembly << "\n";
    for (int i = 0; i < 11; i++)
    {
        Assembly << "T" << i << "  RESW 1\n";
    }
    Assembly << "\n\nsection .text\n\tglobal _start\n_start: \n";
}

// SYMBOL TABLE METHOD

void SymbolTable(ofstream &file, ofstream &Assembly, string symbol[], int counter)
{
    int c2 = 0;
    int c3 = 0;
    string word;
    char chararray[5];
    vector<string> Const;
    vector<string> Vars;
    vector<string> Nums;
    bool repeat = false;
    int state = 0;
    int address = 0;
    string value;
    file << "Token\t\tClass\t\tValue\t\tAddress\t\tSegment\n---------------------------------------------------------\n";
    while (c2 <= counter)
    {
        switch (state)
        {

        case 0:
            if (symbol[c2] == "Class")
            {
                c2++;
                file << symbol[c2] << "\t\tCLASS\t\t0\t\t\t0\t\t\tCS\n";
                state = 2;
            }
            else if (symbol[c2] == "{" || symbol[c2] == "}")
            {
                state = 2;
            }
            else if (symbol[c2] == "CONST")
            {
                state = 1;
            }
            else if (symbol[c2] == "VAR")
            {
                state = 3;
            }
            else
            {
                state = 4;
            }
            break;

        // FOR CONST
        case 1:
            c2++;
            c3 = c2 + 1;
            if (symbol[c3] == "=")
            {
                c3++;
                // change string symbol to char symbol
                word = symbol[c3];
                strcpy(chararray, word.c_str());
                if (isdigit(chararray[0]))
                {
                    file << symbol[c2] << "\t\t\tCONST\t\t" << symbol[c3] << "\t\t\t" << address << "\t\t\tDS\n";
                    address += 2;
                    Const.push_back(symbol[c2]);
                    Const.push_back(symbol[c3]);
                    c3++;
                    if (symbol[c3] == ",")
                    {
                        state = 1;
                        c2 = c3;
                    }
                    else if (symbol[c3] == ";")
                    {
                        state = 2;
                        c2 = c3;
                    }
                }
            }
            break;

        // FOR DONE
        case 2:
            c2++;
            state = 0;
            break;

        // FOR VAR
        case 3:
            c2++;
            c3 = c2 + 1;
            if (symbol[c3] == ",")
            {
                file << symbol[c2] << "\t\t\tVAR\t\t\t" << 0 << "\t\t\t" << address << "\t\t\tDS\n";
                address += 2;
                state = 3;
                Vars.push_back(symbol[c2]);
                c2 = c3;
            }
            else if (symbol[c3] == ";")
            {
                file << symbol[c2] << "\t\t\tVAR\t\t\t" << 0 << "\t\t\t" << address << "\t\t\tDS\n";
                address += 2;
                state = 2;
                Vars.push_back(symbol[c2]);
                c2 = c3;
            }
            break;
        case 4:
            c2++;
            word = symbol[c2];
            strcpy(chararray, word.c_str());
            if (isdigit(chararray[0]))
            {
                if (Nums.size() == 0)
                {
                    Nums.push_back(symbol[c2]);
                }
                if (Nums.size() > 0)
                {
                    for (int i = 0; i < Nums.size(); i++)
                    {
                        if (Nums[i] == symbol[c2])
                        {
                            repeat = true;
                        }
                    }
                    if (repeat == false)
                    {
                        Nums.push_back(symbol[c2]);
                    }
                }
                repeat = false;
                file << symbol[c2] << "\t\t\tNUMLIT\t\t" << symbol[c2] << "\t\t\t" << address << "\t\t\tDS\n";
                c2++;
                word = symbol[c2];
                strcpy(chararray, word.c_str());
                if (isdigit(chararray[0]))
                {
                    state = 5;
                }
                else
                {
                    c2--;
                    state = 2;
                }
            }
            else if (symbol[c2] == ";")
            {
                state = 2;
            }
            else
            {
                state = 4;
            }
            break;
        case 5:
            if (Nums.size() > 0)
            {
                for (int i = 0; i < Nums.size(); i++)
                {
                    if (Nums[i] == symbol[c2])
                    {
                        repeat = true;
                    }
                }
                if (repeat == false)
                {
                    Nums.push_back(symbol[c2]);
                }
            }
            repeat = false;
            file << symbol[c2] << "\t\t\tNUMLIT\t\t" << symbol[c2] << "\t\t\t" << address << "\t\t\tDS\n";
            c2++;
            word = symbol[c2];
            strcpy(chararray, word.c_str());
            if (isdigit(chararray[0]))
            {
                state = 5;
            }
            else
            {
                state = 2;
                c2--;
            }
        }
    }
    file.close();
    AssemblyStart(Assembly, Const, Vars, Nums);
}

string precedence(string code[], int counter, string top)
{

    int row = 0;
    int column = 0;

    int terminator = 0;
    int assign = 1;
    int add = 2;
    int subtract = 3;
    int lp = 4;
    int rp = 5;
    int mult = 6;
    int divide = 7;
    int IF = 8;
    int THEN = 9;
    int ODD = 10;
    int isequal = 11;
    int notequal = 12;
    int greaterthan = 13;
    int lessthan = 14;
    int greatorequal = 15;
    int lessorequal = 16;
    int lb = 17;
    int rb = 18;
    int CALL = 19;

    string precTable[21][20] = {
        {"", "<", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
        {">", "", "<", "<", ">", "", "<", "<", "", "", "", "", "", "", "", "", "", "", "", ""},
        {">", "", ">", ">", ">", ">", "<", "<", "", ">", "", ">", ">", ">", ">", ">", ">", "", "", ""},
        {">", "", ">", ">", ">", ">", "<", "<", "", ">", "", ">", ">", ">", ">", ">", ">", "", "", ""},
        {"", "", "<", "<", ">", "=", "<", "<", "", "", "", "", "", "", "", "", "", "", "", ""},
        {">", "", ">", ">", "", ">", ">", ">", "", "", "", "", "", "", "", "", "", "", "", ""},
        {">", "", ">", ">", ">", ">", ">", ">", "", ">", "", ">", ">", ">", ">", ">", ">", "", "", ""},
        {">", "", ">", ">", ">", ">", ">", ">", "", ">", "", ">", ">", ">", ">", ">", ">", "", "", ""},
        {"", "", "<", "<", ">", "", "<", "<", "", "=", "<", "<", "<", "<", "<", "<", "<", "", "", ""},
        {"", "<", "", "", "", "", "", "", "<", "", "", "", "", "", "", "", "", "<", "", "<"},
        {"", "", "<", "<", "<", "", "<", "<", "", ">", "", "", "", "", "", "", "", "", "", ""},
        {"", "", "<", "<", "<", "", "<", "<", "", ">", "", "", "", "", "", "", "", "", "", ""},
        {"", "", "<", "<", "<", "", "<", "<", "", ">", "", "", "", "", "", "", "", "", "", ""},
        {"", "", "<", "<", "<", "", "<", "<", "", ">", "", "", "", "", "", "", "", "", "", ""},
        {"", "", "<", "<", "<", "", "<", "<", "", ">", "", "", "", "", "", "", "", "", "", ""},
        {"", "", "<", "<", "<", "", "<", "<", "", ">", "", "", "", "", "", "", "", "", "", ""},
        {"", "", "<", "<", "<", "", "<", "<", "", ">", "", "", "", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}};

    // seeing what to assign for row
    if (code[counter] == "=")
    {
        row = assign;
    }
    else if (code[counter] == "+")
    {
        row = add;
    }
    else if (code[counter] == "-")
    {
        row = subtract;
    }
    else if (code[counter] == "/")
    {
        row = divide;
    }
    else if (code[counter] == "*")
    {
        row = mult;
    }
    else if (code[counter] == "(")
    {
        row = lp;
    }
    else if (code[counter] == ")")
    {
        row = rp;
    }
    else if (code[counter] == "IF")
    {
        row = IF;
    }
    else if (code[counter] == "THEN")
    {
        row = THEN;
    }
    else if (code[counter] == ">")
    {
        row = greaterthan;
    }
    else if (code[counter] == ">=")
    {
        row = greatorequal;
    }
    else if (code[counter] == "<=")
    {
        row = lessorequal;
    }
    else if (code[counter] == "<")
    {
        row = lessthan;
    }
    else if (code[counter] == "==")
    {
        row = isequal;
    }
    // Seeing what to assign for column
    if (top == "=")
    {
        column = assign;
    }
    else if (top == "+")
    {
        column = add;
    }
    else if (top == "-")
    {
        column = subtract;
    }
    else if (top == "/")
    {
        column = divide;
    }
    else if (top == "*")
    {
        column = mult;
    }
    else if (top == "(")
    {
        column = lp;
    }
    else if (top == ")")
    {
        column = rp;
    }
    else if (top == "IF")
    {
        column = IF;
    }
    else if (top == "THEN")
    {
        column = THEN;
    }
    else if (top == ">")
    {
        column = greaterthan;
    }
    else if (top == ">=")
    {
        column = greatorequal;
    }
    else if (top == "<=")
    {
        column = lessorequal;
    }
    else if (top == "<")
    {
        column = lessthan;
    }
    else if (top == "==")
    {
        column = isequal;
    }

    // Returning PRECEDENCE
    return precTable[row][column];
}

int LocateOperator(string &oper, vector<string> Stack, int &numTokens)
{
    for (int i = 0; i < numTokens; i++)
    {
        oper = Stack[i];
        if (oper == "+" || oper == "-" || oper == "/" || oper == "*")
        {
            return i;
        }
    }
    return -1;
}

// Finish the remainder of the assembly code !
void FinishAssembly(ofstream &Assembly)
{
    Assembly << "\n\n\nPrintString:\n\tpush ax\n\tpush dx\n\tmov eax, 4\n\tmov ebx, 1\n\tmov ecx, userMsg\n\tmov edx, lenUserMsg\n\tint 80h\n\tpop dx\n\tpop ax\n\tret\n\t;DONE\n\n\n";
    Assembly << "GetAnInteger:\n\tmov eax, 3\n\tmov ebx, 2\n\tmov ecx, num\n\tmov edx, 6\n\tint 0x80\n\tmov edx, eax\n\tmov eax, 4\n\tmov ebx, 1\n\tmov ecx, num\n\tint 80h\n\n\n";
    Assembly << "ConvertStringToInteger:\n\tmov ax, 0\n\tmov [ReadInt], ax\n\tmov ecx, num\n\tmov bx, 0\n\tmov bl, byte [ecx]\n";
    Assembly << "Next:\n\tsub bl, '0'\n\tmov ax, [ReadInt]\n\tmov dx, 10\n\tmul dx\n\tadd ax, bx\n\tmov [ReadInt], ax\n\tmov bx, 0\n\tadd ecx, 1\n\tmov bl, byte[ecx]\n\tcmp bl, 0xA\n\tjne Next\n\tret\n\n\n";
    Assembly << "ConvertIntegerToString:\n\tmov ebx, ResultValue + 4\n\nConvertLoop:\n\tsub dx, dx\n\tmov cx, 10\n\tdiv cx\n\tadd dl, '0'\n\tmov [ebx], dl\n\tdec ebx\n\tcmp ebx, ResultValue\n\tjge ConvertLoop\n\tret\n\n\n";
    Assembly.close();
}

// Create assembly for computations
void createAssembly(vector<string> Stack, string assignment, ofstream &file)
{
    int operAt = 0;
    int tempKnt = 0;
    int i = 0;
    int location = 0;
    string oper;
    int numTokens = Stack.size();
    bool isNum;

    string tempLoc[10];
    tempLoc[0] = "T1";
    tempLoc[1] = "T2";
    tempLoc[2] = "T3";
    tempLoc[3] = "T4";
    tempLoc[4] = "T5";
    tempLoc[5] = "T6";
    tempLoc[6] = "T7";
    tempLoc[7] = "T8";
    tempLoc[8] = "T9";
    tempLoc[9] = "T10";

    if (numTokens != 1)
    {
        do
        {

            operAt = LocateOperator(oper, Stack, numTokens);
            oper = Stack[operAt];
            isNum = isNumber(Stack[operAt - 2]);
            if (oper == "+")
            {
                if (isNum == true)
                {
                    file << "\tmov ax, [Lit" << Stack[operAt - 2] << "]" << endl;
                    isNum = isNumber(Stack[operAt - 1]);
                }
                else
                {
                    file << "\tmov ax,[" << Stack[operAt - 2] << "]" << endl;
                    isNum = isNumber(Stack[operAt - 1]);
                }
                if (isNum == true)
                {
                    file << "\tadd ax," << Stack[operAt - 1] << endl;
                }
                else
                {
                    file << "\tadd ax,[" << Stack[operAt - 1]
                         << "]" << endl;
                }
                file << "\tmov [" << tempLoc[tempKnt] << "], ax" << endl;
            }
            else if (oper == "-")
            {
                if (isNum == true)
                {
                    file << "\tmov ax, [Lit" << Stack[operAt - 2] << "]" << endl;
                    isNum = isNumber(Stack[operAt - 1]);
                }
                else
                {
                    file << "\tmov ax,[" << Stack[operAt - 2] << "]" << endl;
                    isNum = isNumber(Stack[operAt - 1]);
                }
                if (isNum == true)
                {
                    file << "\tsub ax," << Stack[operAt - 1] << endl;
                }
                else
                {
                    file << "\tsub ax,[" << Stack[operAt - 1]
                         << "]" << endl;
                }
                file << "\tmov [" << tempLoc[tempKnt] << "], ax" << endl;
            }
            else if (oper == "/")
            {
                file << "\tmov dx, 0" << endl;
                if (isNum == true)
                {
                    file << "\tmov ax, [Lit" << Stack[operAt - 2] << "]" << endl;
                    isNum = isNumber(Stack[operAt - 1]);
                }
                else
                {
                    file << "\tmov ax,[" << Stack[operAt - 2] << "]" << endl;
                    isNum = isNumber(Stack[operAt - 1]);
                }
                if (isNum == true)
                {
                    file << "\tmov bx, [Lit" << Stack[operAt - 1] << "]" << endl;
                    file << "\tdiv bx" << endl;
                }
                else
                {
                    file << "\tmov bx, [" << Stack[operAt - 1] << "]" << endl;
                    file << "\tdiv bx" << endl;
                }
                file << "\tmov [" << tempLoc[tempKnt] << "], eax" << endl;
            }
            else if (oper == "*")
            {
                if (isNum == true)
                {
                    file << "\tmov ax, [Lit" << Stack[operAt - 2] << "]" << endl;
                    isNum = isNumber(Stack[operAt - 1]);
                }
                else
                {
                    file << "\tmov ax,[" << Stack[operAt - 2] << "]" << endl;
                    isNum = isNumber(Stack[operAt - 1]);
                }
                if (isNum == true)
                {
                    file << "\tmov bx, [Lit" << Stack[operAt - 1] << "]" << endl;
                    file << "\tmul bx" << endl;
                }
                else
                {
                    file << "\tmov bx, [" << Stack[operAt - 1] << "]" << endl;
                    file << "\tmul bx" << endl;
                }
                file << "\tmov [" << tempLoc[tempKnt] << "], eax" << endl;
            }
            Stack[operAt - 2] = tempLoc[tempKnt++];
            Stack.erase(Stack.begin() + operAt);
            Stack.erase(Stack.begin() + (operAt - 1));
            numTokens -= 2;
        } while (numTokens >= 3);
        file << "\tmov ax,[" << tempLoc[tempKnt - 1] << "]" << endl;
    }
    else
    {
        isNum = isNumber(Stack[0]);
        if (isNum == true)
        {
            file << "\tmov ax," << Stack[0] << endl;
        }
        else
        {
            file << "\tmov ax, [" << Stack[0] << "]" << endl;
        }
    }
    file << "\tmov [" << assignment << "], ax" << endl;
}

// Push-Down Automata Pusher
void PDAPusher(int &counter, string code[], string assignment, ofstream &file)
{
    vector<string> output;
    vector<string> operatorStk;

    string top = "";
    bool equal = false;
    string presedence = "";

    while (code[counter] != ";")
    {
        if (code[counter] == " ")
        {
            counter++;
        }
        else if (code[counter] == "=" || code[counter] == "+" || code[counter] == "-" || code[counter] == "/" || code[counter] == "*")
        {
            if (!operatorStk.empty())
            {
                top = operatorStk.back();
                presedence = precedence(code, counter, top);
                if (presedence == ">")
                {
                    operatorStk.push_back(code[counter]);
                }
                else
                {
                    while (!operatorStk.empty() && (presedence == "<" || presedence == "="))
                    {
                        output.push_back(top);
                        operatorStk.pop_back();
                        if (!operatorStk.empty())
                        {
                            top = operatorStk.back();
                        }
                    }
                    operatorStk.push_back(code[counter]);
                }
            }
            else
            {
                operatorStk.push_back(code[counter]);
            }
            counter++;
        }
        else if (code[counter] == "(" || code[counter] == ")")
        {
            if (!operatorStk.empty())
            {
                top = operatorStk.back();
                if (code[counter] == "(")
                {
                    operatorStk.push_back(code[counter]);
                }
                else if (code[counter] == ")")
                {
                    while (top != "(")
                    {
                        top = operatorStk.back();
                        output.push_back(top);
                        operatorStk.pop_back();
                    }
                }
            }
            else
            {
                operatorStk.push_back(code[counter]);
            }
            counter++;
        }
        else
        {
            output.push_back(code[counter]);
            counter++;
        }
    }
    if (code[counter] == ";")
    {
        counter++;
        while (!operatorStk.empty())
        {
            output.push_back(operatorStk.back());
            operatorStk.pop_back();
        }
        int counter2 = 0;
        while (output.size() > counter2)
        {

            if (output[counter2] == "(")
            {
                output.erase(output.begin() + counter2);
                continue;
            }
            counter2++;
        }
        // CREATE ASSEMBLY
        createAssembly(output, assignment, file);
        // Resetting all local variables :)
        output.clear();
    }
}

// Get/Put Assembly :)
void GetPutAssembly(ofstream &Assembly, string code[], int &counter)
{
    if (code[counter] == "GET")
    {
        counter++;
        Assembly << "\tcall PrintString\n\tcall GetAnInteger\n\tmov ax, [ReadInt]\n";
        Assembly << "\tmov [" << code[counter] << "], ax\n";
    }
    else
    {
        counter++;
        Assembly << "\tmov ax, [" << code[counter] << "]\n";
        Assembly << "\tcall ConvertIntegerToString\n\tmov eax, 4\n\tmov ebx, 1\n\tmov ecx, Result\n\tmov edx, ResultEnd\n\tint 80h\n";
    }
    counter += 2;
}

void IfAssembly(int &counter, string code[], int &labelKnt, ofstream &file)
{
    string Label[10];
    int tempLabel;
    int tempLabel2;
    Label[0] = "L1";
    Label[1] = "L2";
    Label[2] = "L3";
    Label[3] = "L4";
    Label[4] = "L5";
    Label[5] = "L6";
    Label[6] = "L7";
    Label[7] = "L8";
    Label[8] = "L9";
    Label[9] = "L10";

    counter++;
    file << "\tmov ax,[" << code[counter] << "]\n";
    counter++;

    // Picking up the operators it needs
    string judgement = code[counter];
    if (code[counter] == ">" || code[counter] == ">=" || code[counter] == "<" || code[counter] == "<=")
    {
        counter++;
        tempLabel = labelKnt;
        file << "\tcmp ax,[" << code[counter] << "]\n";
        if (judgement == ">")
        {
            file << "JLE " << Label[labelKnt++] << "\n";
        }
        else if (judgement == ">=")
        {
            file << "JL " << Label[labelKnt++] << "\n";
        }
        else if (judgement == "<")
        {
            file << "JGE " << Label[labelKnt++] << "\n";
        }
        else if (judgement == "<=")
        {
            file << "JG " << Label[labelKnt++] << "\n";
        }
        else if (judgement == "==")
        {
            file << "JNE " << Label[labelKnt++] << "\n";
        }
    }
    counter++;
    if (code[counter] == "THEN")
    {
        counter += 2;
        if (code[counter] == "IF")
        {
            IfAssembly(counter, code, labelKnt, file);
        }
        else if (code[counter] == "GET" || code[counter] == "PUT")
        {
            GetPutAssembly(file, code, counter);
        }
        else
        {
            while (code[counter] != "}")
            {
                while (code[counter] != "=")
                {
                    counter++;
                }
                string assignment = code[counter - 1];
                counter++;
                PDAPusher(counter, code, assignment, file);
            }
        }
        counter++;
    }
    if (code[counter] == "ELSE")
    {
        tempLabel2 = labelKnt;
        file << "JMP " << Label[labelKnt++] << "\n";
        file << Label[tempLabel] << ": NOP\n";
        counter += 2;
        if (code[counter] == "IF")
        {
            counter++;
            IfAssembly(counter, code, labelKnt, file);
        }
        else if (code[counter] == "GET" || code[counter] == "PUT")
        {
            GetPutAssembly(file, code, counter);
        }
        else
        {
            while (code[counter] != "}")
            {
                while (code[counter] != "=")
                {
                    counter++;
                }
                string assignment = code[counter - 1];
                counter++;
                PDAPusher(counter, code, assignment, file);
            }
            counter++;
        }
    }
    file << Label[tempLabel2] << ": NOP\n";
}

// PDA METHOD
void PDA(string code[], ofstream &file)
{
    // Making everything for QUADS
    vector<string> output;
    vector<string> operatorStk;

    string top = "";
    bool equal = false;
    string presedence = "";
    string assignment = "";
    int labelKnt = 0;

    int counter = 0;
    int numTokens = 0;
    int state = 0;

    // Getting to the meat of the code
    while (code[counter] != "")
    {
        if (code[counter] == "Class")
        {
            counter++;
            while (code[counter] != "{")
            {
                counter++;
            }
            // Getting out of bracket
            counter++;
        }

        // CASES

        switch (state)
        {
        // Checking for const or var, if they have that, just skip over as we are only looking for arithmetic or If statements!
        case 0:
            if (code[counter] == "CONST" || code[counter] == "VAR")
            {
                while (code[counter] != ";")
                {
                    counter++;
                }
                counter++;
                if (code[counter] == "CONST" || code[counter] == "VAR")
                {
                    state = 0;
                }
            }
            else if (code[counter] == "}")
            {
                counter++;
            }
            else if (code[counter] == "IF")
            {
                state = 2;
            }
            else if (code[counter] == "GET" || code[counter] == "PUT")
            {
                state = 3;
                // counter++;
            }
            else
            {
                while (code[counter] != "=")
                {
                    counter++;
                }
                assignment = code[counter - 1];
                counter++;
                state = 1;
            }
            break;

        case 1:
            PDAPusher(counter, code, assignment, file);
            state = 0;
            break;

        case 2:
            IfAssembly(counter, code, labelKnt, file);
            state = 0;
            break;

        case 3:
            GetPutAssembly(file, code, counter);
            state = 0;
            break;
        }
    }
    file << "\n\t;exit code\n\tmov eax, sys_exit\n\txor ebx, ebx\n\tint 80h\n\n";
}
