#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include"scanner.h"
using namespace std;
// Token array
std::string tokens[5] = {"ERROR", "WORD1", "WORD2", "PERIOD"};

// reserved string
std::string reservedWords[38]= {"masu", "VERB", "masen", "VERBNEG", "mashita", "VERBPAST", "masendeshita",
			    "VERBPASTNEG", "desu", "IS", "deshita", "WAS", "o", "OBJECT", "wa", "SUBJECT", "ni", "DESTINATION",
			    "watashi","PRONOUN", "anata", "PRONOUN", "kare", "PRONOUN", "kanojo", "PRONOUN", "sore", "PRONOUN",
			    "mata", "CONNECTOR", "soshite", "CONNECTOR", "shikashi", "CONNECTOR", "dakara", "CONNECTOR", "eofm"
			    "EOFM"}; ;

//File stream to open file
std::ifstream fin;
//=====================================================
// File scanner.cpp written by: Group Number: 8
//=====================================================
bool vowel(char v)
{
	return (v == 'a' || v == 'e' || v == 'i' || v == 'o' || v == 'u' || v == 'I' || v == 'E');
}

bool cons1(char c)
{
	return (c == 'd' || c == 'j' || c == 'w' || c == 'y' || c == 'z');
}

bool cons2(char c)
{
	return (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'n' || c == 'p' || c == 'r');
}
// ** Add the PERIOD DFA here
bool periodDfa(string c)
{
	int state = 0;
	if(c == ".")
		state = 1;
	return state ==1;
}
token_type stringToToken(string s)
{
	if(s =="CONNECTOR")
			return CONNECTOR;
	else if(s =="VERB")
		return VERB;
	else if(s =="VERBPASTNEG")
		return VERBPASTNEG;
	else if(s =="VERBNEG")
		return VERBNEG;
	else if(s =="SUBJECT")
		return SUBJECT;
	else if(s =="VERBPAST")
		return VERBPAST;
	else if(s =="DESTINATION")
		return DESTINATION;
	else if(s =="IS")
		return IS;
	else if(s =="WAS")
		return WAS;
	else if(s =="PRONOUN")
		return PRONOUN;
	else if(s =="NOUN")
		return NOUN;
	else if(s =="OBJECT")
		return OBJECT;
	else if(s == "eofm")
		return EOFM;
	else
		return ERROR;
}
// ** MYTOKEN DFA to be replaced by the WORD DFA
//state 0 = q0, state 1 = qoqvn, state 2 = qcqy, state 3 = qc,
//state 4 = qch, state 5 = qcqch, state 6 = qcqts
bool wordDfa(string s)
{
  int state = 0;
  int charpos = 0;

  while (s[charpos] != '\0')
    {
      		if(state == 0 && vowel(s[charpos]))
				state = 1;
			else if(state == 0 && cons1(s[charpos]))
				state = 3;
	    	else if(state == 0 && cons2(s[charpos]))
				state = 2;
		 	else if(state == 0 && s[charpos] == 't')
				state = 6;
		  	else if(state == 0 && s[charpos] == 'c')
				state = 4;
			else if(state == 0 && s[charpos] == 's')
				state = 5;
			else if(state == 1 && (vowel(s[charpos]) || s[charpos] == 'n' ))
				state = 0;
		  	else if(state == 1 && cons2(s[charpos]))
				state = 2;
		  	else if(state == 1 && cons1(s[charpos]))
				state = 3;
		  	else if(state == 1 && s[charpos] == 'c')
				state = 4;
			else if(state == 1 && s[charpos] == 's')
				state = 5;
		  	else if(state == 1 && s[charpos] == 't')
				state = 6;
			else if(state == 2 && vowel(s[charpos]))
				state = 1;
		  	else if(state == 2 && s[charpos] == 'y')
				state = 3;
			else if(state == 3 && vowel(s[charpos]))
				state = 1;
		  	else if(state == 4 && s[charpos] == 'h')
				state = 3;
		  	else if(state == 5 && vowel(s[charpos]))
				state = 1;
		  	else if(state == 5 && s[charpos] == 'h')
				state = 3;
		  	else if(state == 6 && vowel(s[charpos]))
				state = 1;
		  	else if(state = 6 && s[charpos] == 's')
				state = 3;
		  	else return false;
     	charpos++;

    }//end of while

  // where did I end up????
  return (state == 0 || state == 1);
}

// ** Update the tokentype to be WORD1, WORD2, PERIOD and ERROR.
//enum tokentype {ERROR, WORD1, WORD2, PERIOD, RESERVED };
//list of japanese words and their english counterparts, if a japanese word is at index n its
//english counterpart is at n+1. Japanese words are in the odd indices while english words are
//in the even indices.

//list of reserved words in japanese. If the japanese word is at n then its part of speech is stored
//at n+1. Japanese words are at odd indices while their parts of speech are at even indices.


int checkReserved(string s)
{
	int i = 0;
	for(i =0; i < 38; i+=2)
	{
		if (reservedWords[i] == s)
			return i + 1;
	}
	return 0;
}
// ** Need the lexicon to be set up here (to be used in Part C)
// ** Need the reservedwords list to be set up here
// ** Do not require any file input for these.

//ifstream fin;
///string tokens[5] = {"ERROR", "WORD1", "WORD2", "PERIOD"};


// Scanner processes only one word each time it is called
void scanner(token_type& a, string& w, int& resIndex)
{

  // ** Grab the next word from the file
   fin >> w;
	 if(w == "eofm")
	 {
		 	a = EOFM;
		  return;
	 }
  /*
  2. Call the token functions one after another (if-then-else)
     And generate a lexical error if both DFAs failed.
     Let the token_type be ERROR in that case.
  3. Make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.
  4. Return the token type & string  (pass by reference)
  */

   if(wordDfa(w))
   {

      resIndex = checkReserved(w);

      if(resIndex)
       	a = stringToToken(reservedWords[resIndex]);
      else if(w[w.length()-1] <= 'Z')
        a = WORD2;
      else
        a = WORD1;


   }
   else if(periodDfa(w))
   {
       a = PERIOD;
   }
   else
   {
		cout << "Lexical error encounter: "<< w << " is not a valid word\n";
    a = ERROR;
   }
}//the end

/*


// The test driver to call the scanner repeatedly -- No Longer Needed 
int main()
{
  tokentype thetype;
  string theword;
  string fname;
  setfill(' ');
  cout << "Enter the name of your input file: ";
  cin >> fname;
  int resIndex = 0;
  fin.open(fname.c_str());
  if(!fin)
  {
  		cout << "Error opening file!\n";
  		return 0;
  }
  cout << setw(14) << left << "String" << setw(13) << "TOKEN-TYPE" << setw(14) << "\n=====" << setw(14) << "===========" <<endl;
  /*
1. get the input file name from the user
2. open the input file which contains a story written in Japanese (fin.open).
3. call Scanner repeatedly until the EOF marker is read, and
     each time cout the returned results
     e.g. STRING TOKEN-TYPE
          =====  ===========
          watashi PRONOUN  (from the first call)
          wa      SUBJECT  (from the second call)
          gakkou  WORD1
          etc.



  while (true)
    {

      scanner(thetype, theword, resIndex);  // call the scanner
      cout << setw(14) << theword;
	  if (theword == "eofm")
		  break;

	  if(thetype == RESERVED)
             cout <<setw(14) << reservedWords[resIndex];
      	  else
          cout << setw(14) << tokens[thetype];
      cout << endl;

       // ** display the actual type instead of a number

    }
  // ** close the input file

}*/
