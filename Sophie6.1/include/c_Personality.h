#ifndef C_PERSONALITY_H
#define C_PERSONALITY_H

#include <c_ShortTermMemory.h>


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
