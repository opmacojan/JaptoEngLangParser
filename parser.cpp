#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include "scanner.h"
using namespace std;

//=================================================
// File parser.cpp written by Group Number: 8
//=================================================

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)

// ** Need the updated match and next_token (with 2 global vars)

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function

//Global Variables
// Token array

//File stream to open file



bool token_available;       // global flag indicating whether
                            // we have saved a token to eat up or not
void noun();
void rule_s();
void rule_s1();
void rule_s2();
void rule_s3();
void verb();
void tense();
void be();

token_type saved_token;     // global buffer for the scanner token
string tokenToString(token_type t);
int resIndex = 0;

//syntax_error1(token_type token, string saved_lexeme)
//Takes in 2 args, the token type and the saved lexeme
//Only called if match fails
void syntax_error1(token_type token, string saved_lexeme)
{
  cout << "SYNTAX ERROR: expected " << tokenToString(token) << " but found " << saved_lexeme << "." << endl;
  cout << "Halting parser...." << endl;

  exit(1);
}

//syntax_error2(string saved_lexeme, string parser_function)
//Takes in 2 args, the saved lexeme and the parser function that the error occurred in
//Only called if switch case fails in a parser function when goes to default
void syntax_error2(string saved_lexeme, string parser_function)
{
  cout << "SYNTAX ERROR: unexpected " << saved_lexeme << " found in " << parser_function << "." << endl;
  cout << "Halting parser...." << endl;

  exit(1);
}

// next_token(void)
//    Looks ahead to see what token comes next from the scanner.
//    HOW: checks first to see if the token_available flag is false.
//    If so, saved_token gets scanner() result.
//           and the flag is set true.
//    Thus a token is grabbed but is not eaten up.
//    Returns the saved_token
//
token_type next_token()
{
  string lexeme;
  if (!token_available)   // if there is no saved token from previous lookahead
  {
		cout << "Scanner was called . . . " <<	endl;
    scanner(saved_token, lexeme, resIndex);  // call scanner to grab a new token
    token_available = true;                  // mark that fact that you have saved it
  }
  return saved_token;    // return the saved token
}

string tokenToString(token_type t)
{
  switch (t) {
  case ERROR:
    return "ERROR";
  case WORD1:
    return "WORD1";
  case WORD2:
    return "WORD2";
  case PERIOD:
    return "PERIOD";
  case RESERVED:
    return "RESERVED";
	case CONNECTOR:
		return "CONNECTOR";
	case DESTINATION:
		return "DESTINATION";
		case VERB:
			return "VERB";
		case VERBPAST:
			return "VERBPAST";
		case VERBPASTNEG:
			return "VERBPASTNEG";
		case VERBNEG:
			return "VERBNEG";
		case IS:
			return "IS";
		case WAS:
			return "WAS";
		case PRONOUN:
			return "PRONOUN";
		case OBJECT:
			return "OBJECT";
		case SUBJECT:
			return "SUBJECT";
		case NOUN:
			return "NOUN";

  }
}

//match(expected)
//  Checks and eats up the expected token.
//  HOW: checks to see if expected is different from next_token()
//  and if so, generates a syntax error and handles the error
//  else token_available becomes false (eat up) and returns true.
bool match(token_type expected)
{

  if (next_token() != expected)  // mismatch has occurred with the next token
  {
    // generate a syntax error message here
    // do error handling here if any
    syntax_error1(expected, tokenToString(next_token()));
  }
  else  // match has occurred
  {
		cout << "MATCHED " << tokenToString(expected) << endl;
    token_available = false;  // eat up the token
    return true;              // say there was a match
  }
}


void story()
{
	cout << "Processing story. . ." << endl;
	rule_s();
	while(true)
	{
		cout << "\n======= Processing <s> =======\n" << endl;
		switch(next_token())
		{
			case WORD1:
			case PRONOUN:         //If next word is <noun>
					 noun();          //Process noun
		 match(SUBJECT);  //Make sure SUBJECT is found/matched
		 rule_s1();       //Process <s1>
		 break;
			case CONNECTOR:       //If next word is CONNECTOR
					 match(CONNECTOR);//Make sure CONNECTOR is found/matched
		 noun();          //Process noun
					 match(SUBJECT);  //Make sure subject is found/matched
					 rule_s1();       //Process <s1>
					 break;
			case EOFM:
				cout << "END OF FILE REACHED" << endl;
					exit(1);
			default:
					 syntax_error2(tokenToString(saved_token), "rule_s"); //If next_token is not what was expected, syntax error
		}
	}
}

//Rule <s>: Has 2 choices
//<s> -> <noun> SUBJECT <s1>
//<s> -> CONNECTOR <noun> SUBJECT <s1>
void rule_s()
{

  cout << "\n======= Processing <s> =======\n" << endl;

  switch(next_token())    //Look ahead for next token
  {
    case WORD1:
    case PRONOUN:         //If next word is <noun>
         noun();          //Process noun
	 match(SUBJECT);  //Make sure SUBJECT is found/matched
	 rule_s1();       //Process <s1>
	 break;
    case CONNECTOR:       //If next word is CONNECTOR
         match(CONNECTOR);//Make sure CONNECTOR is found/matched
	 noun();          //Process noun
         match(SUBJECT);  //Make sure subject is found/matched
         rule_s1();       //Process <s1>
         break;
			case EOFM:
				cout << "END OF FILE REACHED" << endl;
					exit(1);
    default:
         syntax_error2(tokenToString(saved_token), "rule_s"); //If next_token is not what was expected, syntax error

  }//End switch
}//End rule_s

//Rule <s1>: Has 2 choices
//<s1> -> <verb> <tense> PERIOD
//<s1> -> <noun> <s2>
void rule_s1()
{

  cout << "Processing <rule_s1>" << endl;

  switch(next_token())    //Look ahead for next token
  {
    case WORD2:
         verb();          //Process verb
	 tense();         //Process tense
	 match(PERIOD);   //Make sure PERIOD is found/matched
         break;
    case WORD1:
    case PRONOUN:         //If next word is <noun>
         noun();          //Process noun
         rule_s2();       //Process <s2>
	 break;
    default:
         syntax_error2(tokenToString(saved_token), "rule_s1"); //If next_token is not what was expected, syntax error

    }//End switch

}//End rule_s1

//Rule <s2>: Has 3 choices
//<s2> -> <be> PERIOD
//<s2> -> DESTINATION <verb> <tense>
//<s2> -> OBJECT <s3>
void rule_s2()
{
  cout << "Processing <rule_s2>" << endl;

  switch(next_token())
  {
    case IS:
    case WAS:
         be();          //Process be
         match(PERIOD); //Make sure PERIOD is found/matched
	 break;
    case DESTINATION:
         match(DESTINATION);  //Make sure DESTINATION is found/matched
	 			 verb();              //Process verb
	       tense();             //Process tense
			   match(PERIOD); //Make sure PERIOD is found/matched
	       break;
    case OBJECT:
         match(OBJECT);       //Make sure OBJECT is found/matched
	       rule_s3();           //Process rule_s3
	       break;
    default:
         syntax_error2(tokenToString(saved_token), "rule_s2"); //If next_token is not what was expected, syntax error
  }//End switch statement
}//End rule_s2

//Rule <s3>: Has 2 choices
//<s3> -> <verb> <tense> PERIOD
//<s3> -> <noun> DESTINATION <verb> <tense> PERIOD
void rule_s3()
{
  cout << "Processing <rule_s3>" << endl;

  switch(next_token())
  {
    case WORD2:
         verb();         //Process verb
         tense();        //Process tense
         match(PERIOD);  //Make sure PERIOD is found/matched
         break;
    case NOUN:
		case WORD1:
    case PRONOUN:
         noun();              //Process noun
         match(DESTINATION);  //Make sure DESTINATION is found/matched
         verb();              //Process verb
         tense();             //Process tense
         match(PERIOD);       //Make sure PERIOD is found/matched
         break;
    default:
         syntax_error2(tokenToString(saved_token), "rule_s3"); //If next_token is not what was expected, syntax error
  }//End switch

}//End rule_s3

//Rule <noun>: Has 2 options
//<noun> -> WORD1
//<noun> -> PRONOUN
void noun()
{

  cout << "Processing <noun>" << endl;

  switch(next_token())
  {
    case WORD1:
         match(WORD1);    //Make sure WORD1 is found/matched
	 break;
    case PRONOUN:
         match(PRONOUN);  //Make sure PRONOUN is found/matched
         break;
    default:
         syntax_error2(tokenToString(saved_token), "noun"); //If next_token is not what was expected, syntax error
  }//End switch
}//End noun()

//Rule <verb>: Has 1 option
//<verb> -> WORD2
void verb()
{

  cout << "Processing <verb>" << endl;

  switch(next_token())
  {
    case WORD2:
         match(WORD2);    //Make sure WORD2 is found/matched
         break;
    default:
         syntax_error2(tokenToString(saved_token), "verb"); //If next_token is not what was expected, syntax error
  }//End switch
}//End verb()

//Rule <be>: Has 2 options
//<be> -> IS
//<be> -> WAS
void be()
{

  cout << "Processing <be>" << endl;

  switch(next_token())
  {
    case IS:
         match(IS);    //Make sure IS is found/matched
         break;
    case WAS:
         match(WAS);  //Make sure WAS is found/matched
         break;
    default:
         syntax_error2(tokenToString(saved_token), "be"); //If next_token is not what was expected, syntax error
  }//End switch
}//End be()

//Rule <tense>: Has 4 options
//<tense> -> VERBPAST
//<tense> -> VERBPASTNEG
//<tense> -> VERB
//<tense> -> VERBNEG
void tense()
{

  cout << "Processing <tense>" << endl;

  switch(next_token())
  {
    case VERBPAST:
         match(VERBPAST);    //Make sure VERBPAST is found/matched
         break;
    case VERBPASTNEG:
         match(VERBPASTNEG);  //Make sure VERBPASTNEG is found/matched
         break;
    case VERB:
         match(VERB);  //Make sure VERB is found/matched
         break;
    case VERBNEG:
         match(VERBNEG);  //Make sure VERBNEG is found/matched
    default:
         syntax_error2(tokenToString(saved_token), "tense"); //If next_token is not what was expected, syntax error
  }//End switch
}//End tense()

// The driver to start the parser
int main()
{

  string fileName;

  //Asks user for name of file to open
  cout << "Enter the name of the file to open: ";
  cin >> fileName;
  cout << "Opening file " << fileName << "...\n";

  fin.open(fileName.c_str());

  //Checks if file is open successfully
  //Terminates if not open
  if(!fin)
  {
    cerr << "Unable to open file " << fileName << "...\n";
    exit(1);
  }
  story();
  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file

  //Closes the file
  fin.close();
}// end
//** should require no other input files!
