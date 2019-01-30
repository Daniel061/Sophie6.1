#ifndef C_SUBJECTDATA_H
#define C_SUBJECTDATA_H

#include <map>
#include <string>
using namespace std;
class c_SubjectData
{
    public:
        c_SubjectData();
        virtual ~c_SubjectData();



    protected:

    private:
        string            sbjSubjectPhrase;                         // the original phase this subject located in, i.e the [dog] is black
        string            sbjSubjectStringOriginal;                 // upper or mixed case, i.e. Dog or dog
        string            sbjSubjectStringLC;                       // forced lower case i.e. dog
        string            sbjSubjectContractionLongFormFirst;       // i.e. what's  = what
        string            sbjSubjectContractionLongFormSecond;      // i.e. what's  = is
        string            sbjSubjectPatternResolved;                // final pattern product
        string            sbjSubjectPatternBeforeResolution;        // Pattern before processing
        char              sbjGenderClass;                           // u-undefined m-male f-female n-neutral
        char              sbjWordType;                              // normal word type definitions - see c_MemoryCell
        char              sbjWordTense;                             // u-undefined p-past P-present f-future
        bool              sbjIsSingular;                            // true/false
        bool              sbjIsContraction;                         // true/false
        int               sbjSingularLocation;                      // address of the singular form if this is plural
        int               sbjPhraseToken;                           // the entire phrased tokenized, not forced lower case
        int               sbjSubjectLocation;                       // the location of the subject in the sentence of this subject
        int               sbjIndirectObjectLocation;                // the location of the indirect object in the sentence of the indirection object, -1 = none

        map<int,string>   sbjAdjectiveMap;                          // adjectives associated with this subject
        map<int,string>   sbjRelatedNounsMap;                       // nouns related to this subject



    public:
        void InitializeAllSubjectVariables(){

                sbjSubjectPhrase                        = "";
                sbjSubjectStringOriginal                = "";
                sbjSubjectStringLC                      = "";
                sbjSubjectContractionLongFormFirst      = "";
                sbjSubjectContractionLongFormSecond     = "";
                sbjGenderClass                          = 'u';
                sbjWordType                             = 'u';
                sbjWordTense                            = 'u';
                sbjIsSingular                           = true;
                sbjIsContraction                        = false;
                sbjSingularLocation                     = -1;
                sbjPhraseToken                          = 0;
                sbjSubjectLocation                      = -1;
                sbjIndirectObjectLocation               = -1;
                sbjAdjectiveMap.clear();
                sbjRelatedNounsMap.clear();

        }



        void    SetsbjSubjectPhrase(string newVal){sbjSubjectPhrase = newVal;}
        string  GetsbjSubjectPhrase(){return sbjSubjectPhrase;}
        void    SetsbjSubjectStringOriginal(string newVal){sbjSubjectStringOriginal = newVal;}
        string  GetsbjSubjectStringLC(){return sbjSubjectStringLC;}
        void    SetsbjSubjectContractionLongFormFirst(string newVal){sbjSubjectContractionLongFormFirst = newVal;}
        string  GetsbjSubjectContractionLongFormFirst(){return sbjSubjectContractionLongFormFirst;}
        void    SetsbjSubjectContractionLongFormSecond(string newVal){sbjSubjectContractionLongFormSecond = newVal;}
        string  GetsbjSubjectContractionLongFormSecond(){return sbjSubjectContractionLongFormSecond;}
        void    SetsbjSubjectPatternResolved(string newVal){sbjSubjectPatternResolved = newVal;}
        string  GetsbjSubjectPatternResolved(){return sbjSubjectPatternResolved;}
        void    SetsbjSubjectPatternBeforeResolution(string newVal){sbjSubjectPatternBeforeResolution = newVal;}
        string  GetsbjSubjectPatternBeforeResolution(){return sbjSubjectPatternBeforeResolution;}
        void    SetsbjGenderClass(char newVal){sbjGenderClass = newVal;}
        char    GetsbjGenderClass(){return sbjGenderClass;}
        void    SetsbjWordType(char newVal){sbjWordType = newVal;}
        char    GetsbjWordType(){return sbjWordType;}
        void    SetsbjWordTense(char newVal){sbjWordTense = newVal;}
        char    GetsbjWordTense(){return sbjWordTense;}
        void    SetsbjIsSingular(bool newVal){sbjIsSingular = newVal;}
        bool    GetsbjIsSingular(){return sbjIsSingular;}
        void    SetsbjIsContraction(bool newVal){sbjIsContraction = newVal;}
        bool    GetsbjIsContraction(){return sbjIsContraction;}
        void    SetsbjSingularLocation(int newVal){sbjSingularLocation = newVal;}
        int     GetsbjSingularLocation(){return sbjSingularLocation;}
        void    SetsbjPhraseToken(int newVal){sbjPhraseToken = newVal;}
        int     GetsbjPhraseToken(){return sbjPhraseToken;}
        void    SetsbjSubjectLocation(int newVal){sbjSubjectLocation = newVal;}
        int     GetsbjSubjectLocation(){return sbjSubjectLocation;}
        void    SetsbjIndirectObjectLocation(int newVal){sbjIndirectObjectLocation = newVal;}
        int     GetsbjIndirectObjectLocation(){return sbjIndirectObjectLocation;}



        void    SetsbjAdjectiveInMap(string AdjectiveToSave, int TokenizedAdjective){
                sbjAdjectiveMap.emplace(TokenizedAdjective,AdjectiveToSave);}

        void    SetsbjRelatedNounInMap(string RelatedNounToSave, int TokenizedNoun){
                sbjRelatedNounsMap.emplace(TokenizedNoun,RelatedNounToSave);}

        int     GetsbjAdjectiveMapCount(){return sbjAdjectiveMap.size();}

        int     GetsbjRelatedNounsMapCount(){return sbjRelatedNounsMap.size();}

};

#endif // C_SUBJECTDATA_H
