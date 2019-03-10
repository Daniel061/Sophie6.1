#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include <string>
#include <time.h>
using namespace std;

bool    VerifyFileVersion(string);
string  MakeStringLowerCase(string);
int     Tokenize (string,bool);
int     GetDaysSinceDate();

#endif // LIBRARY_H_INCLUDED
