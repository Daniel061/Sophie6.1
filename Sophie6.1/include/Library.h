#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include <string>
#include <time.h>

/** SOPHIE 6.1
     author - Daniel W. Ankrom ©2019

     GNU General Public License v3.0
     Permissions of this strong copyleft license are conditioned
      on making available complete source code of licensed works
       and modifications, which include larger works using a licensed
       work, under the same license.
       Copyright and license notices must be preserved.
       Contributors provide an express grant of patent rights.

     see - https://github.com/Daniel061/Sophie6.1/blob/master/LICENSE
*/

using namespace std;

bool    VerifyFileVersion(string);
string  MakeStringLowerCase(string);
int     Tokenize (string,bool);
int     GetDaysSinceDate();

// TODO (Dan#1#): transfer SlowSpeak and RequestUserResponse to here

#endif // LIBRARY_H_INCLUDED
