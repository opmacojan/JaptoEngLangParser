# JaptoEngParser
A simple Japanese to English translator that uses a parser and scanner to translate very basic Japanese phrases to grammar tokens and determines whether they are grammatically correct.

For specifics on the program please read the report.

TL;DR The Translator works by using a Definitive Finite Automata of basic japanese grammar rules. There are two major components to this program, the Scanner and the Parser. The Scanner is responsible for checking if the input (words) are valid and for determining the state of the machine i.e. checks if the input is following proper grammar. If successful, the Scanner converts the input to tokens which are taken in by the parser. The parser then translates each token sequentially and provides information on each word such as whether it is a noun, connector, verb, verb negative, etc. 
