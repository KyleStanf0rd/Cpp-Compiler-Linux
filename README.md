# JAVA0Compiler
This is a compiler coded 100% by me. 
It implements a FSA, decision table, PDA and a complete precedence table. 
It reads the input code character by character and then goes through the decision table to see if it is valid grammar.
It converts all input code into assembly code.
It implements I/O calls and executes them.
This compiler generates a token table, symboltable, and a .asm file that you can execute on a Linux environment. 

HOW TO RUN:
Create a input file that follows the JAVA0 programming language syntax named "Input.txt" (remember it must be in the same directory code files to run).
From there, you can run the code and play around with Java0 and execute the .asm file the compiler generates.

INPUT EXAMPLES:

1.)
Class PGM1{
	/* Comment */
	VAR A, B, F;
	CONST M = 13, N = 56;
	GET F;
	A = (27 + 15) - 28 * 18 + 122;
	B = A + 2 - 299;
	IF A >= B THEN{
		GET A;
	}
	ELSE{
		M = N;
	}
	F = 28 * (90 + A);
	PUT F;
	PUT B;
}


2.)
Class Test{
    /* Comment Here */
    VAR a, b;
    GET a;
    GET b;
    IF a > b THEN{
        PUT a;
    }
    ELSE{
        PUT b;
    }
}

3.)
Class Burris{
    VAR a, b, c, Bob, Jane, ans;
    GET a;
    GET b;
    GET c;
    GET Bob;
    GET Jane;
    ans = a * ((Bob + Jane - 10) / 2 * 4) / (b + c);
    PUT ans;
}

