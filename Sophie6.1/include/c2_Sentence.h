#ifndef C2_SENTENCE_H
#define C2_SENTENCE_H


#include <string>
#include <iostream>
using namespace std;
class c2_Sentence
{
    public:
        c2_Sentence();
        virtual ~c2_Sentence();

    protected:

    private:
        int WordCount;
        int WordTokens[30];
        int SubjectLocation;
        string Words[30];
        string WordsLC[30];
        string SubWords[30];
        string OriginalString;
        string Pattern;
        char Punctuation;
        bool HasPunctuation;
        bool IsQuestion;
        char WordType[30];       //n-noun v-verb p-pronoun a-adjective d-determiner(the) r-subject representative(it that) u-unknown c-connecting word(and)
        char SecondaryType[30];
        char AlternateType[30];

    public:
        char GetSecondaryType(int Location){return SecondaryType[Location];}
        void SetSecondaryType(char Type,int Location){SecondaryType[Location] = Type;}
        char GetAlternateType(int Location){return AlternateType[Location];}
        void SetAlternateType(char Type,int Location){AlternateType[Location] = Type;}
        int GetWordCount(){return WordCount;}
        char GetPunctuation(){return Punctuation;}
        bool GetHasPunctuation(){return HasPunctuation;}
        bool GetIsQuestion(){return IsQuestion;}
        int GetWordTokens(int loc){return WordTokens[loc];}
        string GetWords(int loc){return Words[loc];}
        string GetWordsLC(int loc){return WordsLC[loc];}
        string GetOriginalString(){return OriginalString;}
        char GetWordType(int loc){return WordType[loc];}
        void SetWordType(char Type, int loc){WordType[loc] = Type;}
        void SetIsQuestion(bool ISQ){IsQuestion = ISQ;}
        void SetSubjectLocation(int newLoc){SubjectLocation = newLoc;}
        int  GetSubjectLocation(){return SubjectLocation;}
        void SetWords(string strData,int Loc){Words[Loc]=strData;}
        void SetSubWords(int loc,string strData){SubWords[loc] = strData;}
        string GetSubWords(int loc){return SubWords[loc];}
        void SetPattern(string strData){Pattern = strData;}
        string GetPattern(){return Pattern;}

void Parse (string str_Sentence_Data)
{
//----------------------Initialize-------------------------------------------------------------------------------------------------
    WordCount = 0;
    Punctuation = '\0';    //set to null
    Pattern = "";
    int int_Word_Count;
    int_Word_Count = 0;
    int x; x = 0; int int_Sentence_Length;
    int int_Last_Pos;
    int int_Sentence_Token_Position;
    int t; t = 0;
    int_Sentence_Length = str_Sentence_Data.size();
    int_Last_Pos = int_Sentence_Length;
    HasPunctuation = false;
    IsQuestion     = false;                                                    //SET Public Variable

    if(int_Sentence_Length <=0){
        return;
    }


    while (str_Sentence_Data[x] == ' ')
        {                                                                       //trim leading spaces
            x++;
            int_Sentence_Token_Position++;
        }
    while (str_Sentence_Data[int_Last_Pos-1]==' ')                              //trim trailing spaces
        {
        int_Last_Pos--;
        }

//--------------------------Punctuation Check----------------------------------------------------------------
    char c_tmp_char;
    char c_Punctuation;
    IsQuestion = false;
    c_tmp_char = str_Sentence_Data[int_Last_Pos-1];
    if( !(((c_tmp_char >= 'A') & (c_tmp_char <= 'Z')) |
            ((c_tmp_char >= 'a') & (c_tmp_char <= 'z')))
       )
      {

        HasPunctuation = true;                                                                                          //SET Public Variable
        c_Punctuation = str_Sentence_Data[int_Last_Pos-1];
        Punctuation = c_Punctuation;
        if(Punctuation == '?') IsQuestion = true;
                                                                                                                        //SET Public Variable
        int_Last_Pos --;
      }
//---------------------------------------------------------------------------------------------------------------
     while (str_Sentence_Data[int_Last_Pos-1]==' ')                              //trim trailing spaces once more
      {
        int_Last_Pos--;
      }
//--------------------------------NOW PARSE THE SENTENCE---------------------------------------------------------

    t = str_Sentence_Data.find(" ",x);                              //find first occurrence of space after word

    while ( (t > 0) & (t  < int_Last_Pos))
    {
        Words[int_Word_Count] = str_Sentence_Data.substr(x,t-x);    //extract word
        x = t+1;                                                    //move pointer
        t = str_Sentence_Data.find(" ",x);                          //find next space
        int_Word_Count++;
        while ((str_Sentence_Data[x] == ' ') & (t < int_Last_Pos))
         {
                x++;
                t = str_Sentence_Data.find(" ",x);
         }

    }




    Words[int_Word_Count] = str_Sentence_Data.substr(x,int_Last_Pos-x);
    int_Word_Count++;


    WordCount = int_Word_Count;

//-----------------------------------------TOKENIZE ALL WORDS----------------------------------------------
    for (x = 0; x < int_Word_Count; x++)
    {
        WordTokens[x] = Tokenize(Words[x]);
        WordType[x] = 'u';
        SecondaryType[x] = 'u';
        AlternateType[x] = 'u';
        string tmpWord;
        tmpWord = Words[x];
        WordsLC[x] = "";
         //Set WordsLC-----------------------------
            for(int t = 0; t < int(Words[x].size()); t++)
                tmpWord[t] =  tolower(tmpWord[t]);
            WordsLC[x] = tmpWord;
         //----------------------------------------
    }
}



        int Tokenize (string str_Data,bool ForceUpperCase = true)
        {
            int z          = str_Data.size();
            int y;
            int PlaceValue = 1;
            int tmpToken   = 0;
            int tmpHolder  = 0;

                if(ForceUpperCase){
                for( y = z; y > 0; y--){
                    tmpHolder  = int(toupper(str_Data[y-1]))-64; //'A' to 'Z'
                    if(tmpHolder <= 0) tmpHolder = str_Data[y-1];
                    tmpToken   = tmpToken + (tmpHolder*PlaceValue);
                    PlaceValue = PlaceValue * 10;}}
                  else {
                    for( y = z; y > 0; y--){
                    tmpHolder  = str_Data[y-1] - 64;
                    if(tmpHolder <= 0) tmpHolder = str_Data[y-1];
                    tmpToken   = tmpToken + (tmpHolder*PlaceValue);
                    PlaceValue = PlaceValue * 10;}
                  }

            return tmpToken;

        }
};

#endif // C2_SENTENCE_H
