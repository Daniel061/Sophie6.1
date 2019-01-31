#ifndef C_SUBJECTSTACK_H
#define C_SUBJECTSTACK_H

#include <vector>
#include<map>
#include <c_Sentence.h>
#include <c_SubjectData.h>

class c_SubjectStack :  public c_Sentence
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
        map<int,c_SubjectData>               SubjectDataMap;                //<Tokenized string strSubject,c_SubjectData>
        map<int,c_SubjectData>::iterator     sbjDataIT;
        c_SubjectData                        WorkingsbjData;

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
            //new version of SetSubjectInStack
            sbjDataIT = SubjectDataMap.find(Tokenize(strSubject));
            int Adjectives[30];
            int RelatedNouns[30];
            int adjCount,nounCount;
            bool Result = false;
            if(sbjDataIT == SubjectDataMap.end()){
                WorkingsbjData.InitializeAllSubjectVariables();
                WorkingsbjData.SetsbjSubjectPhrase(GetOriginalString());
                WorkingsbjData.SetsbjSubjectStringOriginal(GetWords(GetSubjectLocation()));
                WorkingsbjData.SetsbjSubjectStringLC(GetWordsLC(GetSubjectLocation()));
                WorkingsbjData.SetsbjSubjectContractionLongFormFirst(GetContractionLongFormFirst(GetSubjectLocation()));
                WorkingsbjData.SetsbjSubjectContractionLongFormSecond(GetContractionLongFormSecond(GetSubjectLocation()));
                WorkingsbjData.SetsbjSubjectPatternResolved(GetPattern());
                //WorkingsbjData.SetsbjSubjectPatternBeforeResolution(); //need this sent to me
                WorkingsbjData.SetsbjGenderClass(GetGenderClassInSentence(GetSubjectLocation()));
                WorkingsbjData.SetsbjWordType(GetWordType(GetSubjectLocation()));
                //WorkingsbjData.SetsbjWordTense(getWordTense); // needs to be added to c_Sentence and data storage
                WorkingsbjData.SetsbjIsSingular(GetIsPluralWord(GetSubjectLocation()));
                WorkingsbjData.SetsbjIsContraction(GetisContraction(GetSubjectLocation()));
                WorkingsbjData.SetsbjSingularLocation(Tokenize(GetPluralRoot(GetSubjectLocation())));
                WorkingsbjData.SetsbjPhraseToken(Tokenize(GetOriginalString(),false));
                WorkingsbjData.SetsbjSubjectLocation(GetSubjectLocation());
                WorkingsbjData.SetsbjIndirectObjectLocation(GetIndirectObjectLocation());
                adjCount  = GetMemoryCellAdjectives(GetWordTokens(GetSubjectLocation()),Adjectives);
                nounCount = GetMemoryCellRelatedNouns(GetWordTokens(GetSubjectLocation()),RelatedNouns);
                for(int x = 0; x< adjCount; x++){
                    WorkingsbjData.SetsbjAdjectiveInMap(GetMemoryCellRawStringData(Result,"",Adjectives[x]),Adjectives[x]);
                }
                for(int x = 0; x< nounCount; x++){
                    WorkingsbjData.SetsbjRelatedNounInMap(GetMemoryCellRawStringData(Result,"",Adjectives[x]),Adjectives[x]);
                }


            }


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
