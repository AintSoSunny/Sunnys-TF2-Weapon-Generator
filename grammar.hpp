#ifndef GRAMMAR
#define GRAMMAR
#include "data.hpp"
extern int isVowel(int c);
extern int isPlural(string s); 
//idk what this means I found it on stackexchange and cppreference.com
template <class InputIt, class OutputIt>
extern OutputIt seperateSentence(InputIt first, InputIt last, OutputIt container);
extern string toSingular(string s, bool check = false);
extern string toPlural(string s, bool check = false); 
extern string autoPlural(string s, int c, bool check = false);
extern string swapSingPlur(string s);
template <class InputIt, class OutputIt>
extern OutputIt toSingular(InputIt first, InputIt last, OutputIt newStr, bool check = false);
template <class InputIt, class OutputIt>
extern OutputIt toPlural(InputIt first, InputIt last, OutputIt newStr, bool check = false);
template <class InputIt, class OutputIt>
extern OutputIt autoPlural(InputIt first, InputIt last, OutputIt newStr, int c, bool check = false);  
#endif