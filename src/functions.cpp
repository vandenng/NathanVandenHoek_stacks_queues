//Author Nathan Vanden Hoek

//File I/O info from already some knowlege of C, and
//https://www.uow.edu.au/~lukes/TEXTBOOK/notes-cpp/io/readtextfile.html

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <fstream>
#include "functions.h"

/*******************************************************************************************
 * This method will return ture if all symbols (,{,[, have a corrisponding ),},], and false
 * if they do not.
 *******************************************************************************************/
bool balancedSymbols(std::string input){
	std::stack <char, std::deque<char> > symbols;
	
	for( auto it = input.begin(); it != input.end(); ++it ){
		if( *it == '(' || *it == '{' || *it == '[' )
			symbols.push(*it);
		else if( *it == ')' && symbols.top() == '(')
			symbols.pop();
		else if( *it == ']' && symbols.top() == '[' )
			symbols.pop();
		else if ( *it == '}' && symbols.top() == '{' )
			symbols.pop();
	}
	
	return symbols.size();
}

/*******************************************************************************************
 *iToP stands for Infix to Postfix. This method withh take an input string, and convert it
 *to postfix as the returned string. 
 *******************************************************************************************/
std::string iToP( std::string input ){
	std::string postFix;
	std::stack <char, std::deque<char> > operators;

	if( balancedSymbols( input ) ){
		std::cout << "ERROR: Input error, please try again." << std::endl;
		return postFix;
	}

	for( auto it = input.begin( ); it != input.end(); ++it ){
		if( *it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '(' || *it == ')' || *it == '^' ){	
				
			while( operators.size() > 0 && prec(operators.top(), *it) ){
				postFix.push_back( operators.top() );
				operators.pop();	
			}

			if( operators.size() == 0 || *it != ')' ){
				operators.push( *it );
			}else{
				operators.pop();	
			}

		}else if( *it != ' ' ){
			postFix.push_back( *it );
		}	
	}
	
	while ( operators.size() > 0 ){ 
		postFix.push_back( operators.top() );
		operators.pop();
	}
	
	return postFix;
}

/*******************************************************************************************
 * This is a helper method to state the precedance of the operatores used in iToP(). 
 *******************************************************************************************/
bool prec( char ch, char ch2 ){
	if( ch == '(' )
		return false;
	else if( ch2 == '(' )
		return false;
	else if( ch2 == ')' )
		return true;
	else if( ch == '^' )
		return true;
	else if ( ch == '^' )
		return false;
	else if( ch == '*' || ch == '/' )
		return true;
	else if ( ch2 == '+' || ch2 == '-' )
		return true;
	else
		return false;
}

/*******************************************************************************************
 *Used to test the functionality of iToP() & Balanced Symbols! 
 *******************************************************************************************/
int main( int argc, char** argv ){
	
	if(argc != 2){
		std::cout << "ERROR, please enter a file to test!!" << std::endl;
		exit(1);
	}

	std::ifstream myFile;
	std::string input;

	myFile.open( argv[1] );
	
	if( !myFile ){
		std::cout << "Unable to open file" << std::endl;
		exit(1);
	}

	while( myFile.eof()  ){
		myFile >> input;
	}

	myFile.close();
	
	if( !balancedSymbols(input) )
		std::cout << "WORKED!" << std::endl;

	std::cout << iToP("A + B * C + D") << std::endl;
	std::cout << iToP("(A + B) * (C + D)") << std::endl;
	std::cout << iToP("A * B + C * D") << std::endl;
	std::cout << iToP("A + B + C + D") << std::endl;
	std::cout << iToP("A * B + C / D") << std::endl;
	std::cout << iToP("A * (B + C) / D") << std::endl;
	std::cout << iToP("A * (B + C / D)") << std::endl;
	std::cout << iToP("A + B * C - D / E * F") << std::endl;
	std::cout << iToP("(A + B * C - D) / (E * F)") << std::endl;
	std::cout << iToP("((A + B) * (C - D ) + E) / (F + G)") << std::endl;
	std::cout << iToP("A ^ B * C - D + E") << std::endl;
	std::cout << iToP("(A + B) ^ G * B") << std::endl;
	std::cout << iToP(" ((((a + b) + c) - d) + { g }") << std::endl;

        return EXIT_SUCCESS;
}
