#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include <string>
#include <time.h>
using namespace std;

bool    VerifyFileVersion(string);
string  MakeStringLowerCase(string);
int     Tokenize (string,bool);
int     GetDaysSinceDate();

// TODO (Dan#1#): transfer SlowSpeak and RequestUserResponse to here

#endif // LIBRARY_H_INCLUDED
