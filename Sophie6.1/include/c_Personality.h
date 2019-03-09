#ifndef C_PERSONALITY_H
#define C_PERSONALITY_H

#include <c_ShortTermMemory.h>

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

class c_Personality : public c_ShortTermMemory
{
    public:
        c_Personality();
        virtual ~c_Personality();

    protected:


    private:
        string MyName;
        char MyGender;
        int MoodLevel;
        string UserName = "";
        char UserGender = '\0';

    public:
        void SetName(string NewVal){MyName = NewVal;}
        void SetGender(char NewVal){MyGender = NewVal;}
        char GetMyGender(){return MyGender;}
        string GetMyName() {return MyName;}
        void SetMyName(string NewVal){MyName = NewVal;}
        void IncreaseMoodLevel(){MoodLevel++;}
        void DecreaseMoodLevel(){MoodLevel--;}
        int GetMoodLevel(){return MoodLevel;}
        string GetUserName(){return UserName;}
        void   SetUserName(string NewVal){UserName = NewVal;}
        char   GetUserGender(){return UserGender;}
        void   SetUserGender(char NewVal){UserGender = NewVal;}



};

#endif // C_PERSONALITY_H
