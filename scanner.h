#ifndef SCANNER_H
#define SCANNER_H

#include<iostream>
#include<fstream> 
#include<string>
// enum
enum token_type {ERROR, WORD1, WORD2, PERIOD, RESERVED, CONNECTOR, DESTINATION, VERB, VERBPAST, VERBPASTNEG, VERBNEG, IS, WAS, PRONOUN, OBJECT, SUBJECT, NOUN, EOFM};

// Token array 
extern std::string tokens[5];

// reserved string 
extern std::string reservedWords[38];

//File stream to open file
extern std::ifstream fin;

// Checks if the character is a vowel
bool vowel(char v);
bool cons1(char c);
bool cons2(char c);
bool periodDfa(std::string c);
bool wordDfa(std::string s);
int checkReserved(std::string s);
void scanner(token_type& a, std::string& w, int& resIndex);

#endif
