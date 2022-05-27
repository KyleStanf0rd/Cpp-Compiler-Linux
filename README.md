# JAVA0Compiler
This is a quick and dirty compiler coded 100% by me. 
It implements a FSA, decision table, PDA and a complete precedence table. 
It reads the input code character by character and then goes through the decision table to see if it is valid grammar.
It converts all input code into assembly code.
It implements I/O calls and executes them.

HOW TO RUN:
Create a input file that follows the JAVA0 programming language syntax named "Input.txt" (remember it must be in the same directory code files to run, if you do not want the input file to be in the same directory, then you will need to specify what directory yopu want to fetch it from on line ____).
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

