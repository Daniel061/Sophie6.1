#ifndef C_LANGUAGE_H
#define C_LANGUAGE_H
#include <c_Personality.h>
#include <c2_Sentence.h>
#include <string>
#include <iostream>
extern bool Verbose;
using namespace std;
class c_Language : public c_Personality
{
    public:
        c_Language();
        virtual ~c_Language();


    protected:

    private:
       c2_Sentence SlowSentence;
       c2_Sentence tmpSentence;

    public:
//-------------------------Pattern Review  i.e. Language Helper ------------------------
 string PatternReview(string Pattern, int& ConfidenceLevel){

   string CorrectedPattern; CorrectedPattern = Pattern;
   ConfidenceLevel = -1;  // no suggestion

//    if(Pattern == "duu"){
//        CorrectedPattern = "dnv";
//        ConfidenceLevel = 100;}
    if(Pattern == "duvu"){
        CorrectedPattern = "dnvu";
        ConfidenceLevel = 100;}
    if(Pattern == "dun"){
        CorrectedPattern = "dan";
        ConfidenceLevel = 100;}
    if(Pattern == "duva"){
        CorrectedPattern = "dnva";
        ConfidenceLevel = 100;}
    if(Pattern == "uuv"){
        CorrectedPattern = "dnv";
        ConfidenceLevel = 100;}
    if(Pattern == "dvdun"){
        CorrectedPattern = "dvdan";
        ConfidenceLevel = 100;}
    if(Pattern == "dvdu"){
        CorrectedPattern = "dvdn";
        ConfidenceLevel = 100;}
    if(Pattern == "dnup"){
        CorrectedPattern = "dnvp";
        ConfidenceLevel = 100;}


   return CorrectedPattern;
 }
//--------------------------End Language Review------------------------------------------------


//-------------------------Find Word Type------------------------------------------------------
 char FindWordType(string tmpWord){




           string Determiners;
           string ProNouns;
           string Questions;
           string OrigWord;
           string Verbs;
           string SubjectReplacements;
           char tmpWordType;
           ProNouns =            " you your my mine yours me they them he him she her we i it that ";
           Determiners =         " the a an each every certain this that these those any all each some few either little many much ";
           Questions =           " what where how when who ";
           Verbs =               " be have do say get make go know take see is come think look want give use find tell ask work seem feel try leave call ";
           SubjectReplacements = " it that";
           int isDeterminer; isDeterminer = -1;
           int isProNoun;    isProNoun    = -1;
           int isQuestion;   isQuestion   = -1;
           int isVerb;       isVerb       = -1;
           int isSubRep;     isSubRep     = -1;
           tmpWordType = 'u';


              for(int t = 0; t < tmpWord.size(); t++){
                tmpWord[t] = tolower(tmpWord[t]);}
              OrigWord = tmpWord;
              tmpWord = " " + tmpWord + " ";
                isDeterminer = Determiners.find(tmpWord);
                isProNoun = ProNouns.find(tmpWord);
                isQuestion = Questions.find(tmpWord);
                isVerb = Verbs.find(tmpWord);
                isSubRep = SubjectReplacements.find(tmpWord);
                  if (isVerb >= 0){
                      tmpWordType = 'v';}
                  if (isDeterminer >= 0){
                       tmpWordType = 'd';}
                  if (isProNoun >= 0){
                       tmpWordType = 'p';}
                  if (isQuestion >= 0){
                       tmpWordType = 'q';}
                  if (isSubRep >=0){
                        tmpWordType = 'r';}
            if(Verbose)
                cout << "tmpWord " << tmpWord <<" type:" << tmpWordType << endl;
            return tmpWordType;

 }
//--------------------------------end Find Word Type--------------------------------------


void SlowSpeak(string str_Data)
{
     string WorkingWord;

     SlowSentence.Parse(str_Data);
     for(int x = 0; x < SlowSentence.GetWordCount(); x++){

        WorkingWord = SlowSentence.GetWords(x);
        for(int y = 0; y < WorkingWord.size(); y++){
            cout << WorkingWord[y];
            for(int dly = 0; dly < 30000000; dly++);
        }
        cout  << " ";

     }
     cout << "\b" << SlowSentence.GetPunctuation() << endl;
}

int RequestUserResponse()
{
    int Matched;

    string PositiveResponse;
    string NegativeResponse;
    string Response; Response = "";
    PositiveResponse = " yes Yes OK ok Ok correct Correct right Right Exactly exactly ";
    NegativeResponse = " No no wrong Wrong What what ";
    while (Response == ""){
        cout << ">>>";
        getline (cin,Response);}
    tmpSentence.Parse(Response);
    Response = tmpSentence.GetWords(0);
    Matched = PositiveResponse.find(" " + Response + " ");
    if(Matched >= 0) return 1;
    Matched = NegativeResponse.find(" " + Response + " ");
    if(Matched >= 0) return -1;

    return 0;
}

};

#endif // C_LANGUAGE_H
