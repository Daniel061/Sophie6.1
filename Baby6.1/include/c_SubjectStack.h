#ifndef C_SUBJECTSTACK_H
#define C_SUBJECTSTACK_H

#include <vector>
#include<map>
#include <c_Personality.h>
#include <c_SubjectData.h>

class c_SubjectStack :  public c_Personality
{
    public:
        c_SubjectStack();
        virtual ~c_SubjectStack();
    private:

        int                                  Subjects[15];                           //These Subjects are tokenized words
        string                               strSubjects[15];
        string                               strTmpSubject;
        int                                  SubjectCount;
        int                                  tmpSubject;
        vector <int>                         SubjectStack;
        vector <string>                      strSubjectStack;
        vector <int>::iterator               stackIT;
        vector <string>::iterator            strStackIT;
        vector <string>                      strSentenceStack;
        map<int,c_SubjectData>               SubjectDataMap;
        map<int,c_SubjectData>::iterator     sbjDataIT;

    public:


        void SetSubjectInStack(int NewSubject,string strSubject,string OriginalString){
            stackIT = SubjectStack.begin();
            int FirstSubject = -1;
            if(SubjectStack.size()!= 0){
               FirstSubject = SubjectStack[0];}
            if(FirstSubject != NewSubject){
                SubjectStack.emplace(stackIT,NewSubject);
                strStackIT = strSubjectStack.begin();
                strSubjectStack.emplace(strStackIT,strSubject);
                strStackIT = strSentenceStack.begin();
                strSentenceStack.emplace(strStackIT,OriginalString);}
        }

        int GetSubjectInStack(int Location = 0){
            stackIT = SubjectStack.begin()+Location;
            return *stackIT;

        }
        string GetstrSubjectInStack(int Location){
            strStackIT = strSubjectStack.begin()+Location;
            return *strStackIT;
        }

        string GetOriginalStringInStack(int Location){
            return strSentenceStack[Location];
        }

        int GetSubjectStackCount(){
            return SubjectStack.size();
        }
};

#endif // C_SUBJECTSTACK_H
