#ifndef C_SENTENCE_H
#define C_SENTENCE_H

#include <c_SubjectStack.h>


class c_Sentence : public c_SubjectStack
{
    public:
        c_Sentence();
        virtual ~c_Sentence();

    protected:

    public:
        int    WordCount;                       // no. of words in sentence not counting punctuation  initialize to 0
        int    SubjectLocation;                 // from 0 to WordCount, -1 = subject not located
        int    WordTokens[30];                  // dog = 625 initialize to 0
        bool   isContraction[30];               // true / false  initialize to false  initialize to ""
        int    QuoteLocation[30];               // "can't" set to 3 for this, set to -1 for "dog"
        int    PluralWordFlag[30];              // u - undefined p - plural s - singular
        int    IndirectObjectLocation;          // usually the second noun
        int    AdverbLocation;                  // -1 means none
        int    AdjectiveLocation;               // -1 means none
        int    NounCount;                       // number of nouns in this sentence
        int    VerbLocation;                    // position of verb
        int    NamePointer;                     // position of the word name
        string Words[30];                       // Dog  i.e. original unedited word  initialize to ""
        string WordsLC[30];                     // dog  initialize to ""
        string SubWords[30];                    // replacement words, usually from subject stack
        string ContractionLongFormFirst[30];    // i.e.he's to he
        string ContractionLongFormSecond[30];   // i.e he's  to is
        string PluralRoot[30];                  // i.e. colors = color
        char   GenderClassInSentence[30];       // i.e m-male f-female n-neutral   initialize to u-undefined
        string OriginalString;                  // the whole unedited string  initialize to ""
        string Pattern;                         // i.e. dnvua  initialize to ""
        char   Punctuation;                     // !  initialize to null
        bool   HasPunctuation;                  // true / false initialize to false
        bool   HasPluralPronoun;                // true / false initialize to false
        bool   IsQuestion;                      // true / false initialize to false
        bool   HasContraction;                  // true / false initialize to false
        bool   HasGreetingsWord;                // true / false initialize to false
        bool   HasGenderReference;              // true / false initialize to false
        bool   HasBeenUnderstood;               // initialized to false, set externally
        bool   HasGenderDeterminer;             // the word 'gender' was used
        bool   IsPluralWord[30];                // indicates plural - read PluralRoot for base word
        char   WordType[30];                    // n-noun v-verb p-pronoun a-adjective d-determiner(the) r-subject representative(it that) u-unknown c-connecting word(and)  C(cap) Contraction word
                                                // n-noun p-pronoun v-verb q-question word a-adjective r-subject replacement P(cap) ProperNoun i.e. name A(cap) Adverb D(cap) Direct Object d(LC) Indirect object
                                                // initialize to 'u'
        char   SecondaryType[30];               // same as WordType[]
        char   AlternateType[30];               // same as WordType[]


    public:
        void InitializeVars(){
            for(int x =0; x < 30; x++){
                Words[x]                      = "";
                WordTokens[x]                 = 0;
                QuoteLocation[x]              = -1;
                isContraction[x]              = false;
                IsPluralWord[x]               = false;
                PluralWordFlag[x]             = 'u';
                PluralRoot[x]                 = "";
                WordsLC[x]                    = "";
                SubWords[x]                   = "";
                ContractionLongFormFirst[x]   = "";
                ContractionLongFormSecond[x]  = "";
                WordType[x]                   = 'u';
                SecondaryType[x]              = 'u';
                AlternateType[x]              = 'u';
                GenderClassInSentence[x]      = 'u';}

                WordCount                     = 0;
                SubjectLocation               = -1;
                OriginalString                = "";
                Pattern                       = "";
                HasPluralPronoun              = false;
                HasPunctuation                = false;
                IsQuestion                    = false;
                HasContraction                = false;
                HasGreetingsWord              = false;
                HasGenderReference            = false;
                HasBeenUnderstood             = false;
                HasGenderDeterminer           = false;
                AdverbLocation                = -1;
                NounCount                     = -1;
                VerbLocation                  = -1;
                AdjectiveLocation             = -1;
                NamePointer                   = -1;
                IndirectObjectLocation        = -1;}

        char   GetPluralWordFlag(int Location){return PluralWordFlag[Location];}
        void   SetPluralWordFlag(int Location, char newVal){PluralWordFlag[Location]=newVal;}
        string GetPluralRoot(int Location){return PluralRoot[Location];}
        void   SetPluralRoot(int Location, string strRoot){PluralRoot[Location]=strRoot;}
        bool   GetIsPluralWord(int Location){return IsPluralWord[Location];}
        void   SetIsPluralWord(int Location, bool newVal){IsPluralWord[Location]=newVal;}
        string GetContractionLongFormFirst(int Location){return ContractionLongFormFirst[Location];}
        string GetContractionLongFormSecond(int Location){return ContractionLongFormSecond[Location];}
        void   SetContractionLongFormFirst(int Location,string newVal){ContractionLongFormFirst[Location]=newVal;}
        void   SetContractionLongFormSecond(int Location,string newVal){ContractionLongFormSecond[Location]=newVal;}
        bool   GetHasGenderDeterminer(){return HasGenderDeterminer;}
        void   SetHasGenderDeterminer(bool newVal){HasGenderDeterminer = newVal;}
        bool   GetHasBeenUnderstood(){return HasBeenUnderstood;}
        void   SetHasBeenUnderstood(bool NewVal){HasBeenUnderstood = NewVal;}
        bool   GetHasGenderReference(){return HasGenderReference;}
        void   SetHasGenderReference(bool NewVal){HasGenderReference = NewVal;}
        bool   GetHasGreetingsWord(){return HasGreetingsWord;}
        void   SetHasGreetingsWord(bool NewVal){HasGreetingsWord = NewVal;}
        bool   GetHasContraction(){return HasContraction;}
        void   SetHasContraction(bool NewVal){HasContraction = NewVal;}
        int    GetNamePointer(){return NamePointer;}
        void   SetNamePointer(int NewLocation){NamePointer = NewLocation;}
        char   GetGenderClassInSentence(int Location){return GenderClassInSentence[Location];}
        void   SetGenderClassInSentence(int Location, char NewGenderClass){GenderClassInSentence[Location]=NewGenderClass;}
        int    GetAdjectiveLocation(){return AdjectiveLocation;}
        void   SetAdjectiveLocation(int NewVal){AdjectiveLocation = NewVal;}
        void   SetVerbLocation(int NewLoc){VerbLocation = NewLoc;}
        int    GetVerbLocation(){return VerbLocation;}
        void   SetNounCount(int NewCount){NounCount = NewCount;}
        int    GetNounCount(){return NounCount;}
        int    GetIndirectObjectLocation(){return IndirectObjectLocation;}
        void   SetIndirectObjectLocation(int NewVal){IndirectObjectLocation = NewVal;}
        bool   GetHasPluralPronoun(){return HasPluralPronoun;}
        void   SetHasPluralPronoun(bool newVal){HasPluralPronoun = newVal;}
        char   GetSecondaryType(int Location){return SecondaryType[Location];}
        void   SetSecondaryType(char Type,int Location){SecondaryType[Location] = Type;}
        char   GetAlternateType(int Location){return AlternateType[Location];}
        void   SetAlternateType(char Type,int Location){AlternateType[Location] = Type;}
        int    GetWordCount(){return WordCount;}
        void   SetWordCount(int newVal){WordCount = newVal;}
        char   GetPunctuation(){return Punctuation;}
        void   SetPunctuation(char newVal){Punctuation = newVal;}
        void   SetHasPunctuation(bool newVal){HasPunctuation = newVal;}
        bool   GetHasPunctuation(){return HasPunctuation;}
        bool   GetIsQuestion(){return IsQuestion;}
        void   SetIsQuestion(bool ISQ){IsQuestion = ISQ;}
        int    GetWordTokens(int loc){return WordTokens[loc];}
        void   SetWordTokens(int loc, int token){WordTokens[loc]=token;}
        string GetWords(int loc){return Words[loc];}
        string GetWordsLC(int loc){return WordsLC[loc];}
        void   SetWordsLC(int loc,string newVal){WordsLC[loc]=newVal;}
        string GetOriginalString(){return OriginalString;}
        void   SetOriginalString(string strData){OriginalString = strData;}
        char   GetWordType(int loc){return WordType[loc];}
        void   SetWordType(char Type, int loc){WordType[loc] = Type;}
        void   SetSubjectLocation(int newLoc){SubjectLocation = newLoc;}
        int    GetSubjectLocation(){return SubjectLocation;}
        void   SetWords(string strData,int Loc){Words[Loc]=strData;}
        void   SetSubWords(int loc,string strData){SubWords[loc] = strData;}
        string GetSubWords(int loc){return SubWords[loc];}
        void   SetPattern(string strData){Pattern = strData;}
        string GetPattern(){return Pattern;}
        bool   GetisContraction(int Location){return isContraction[Location];}
        void   SetisContraction(int loc, bool newVal){isContraction[loc]=newVal;}
        int    GetQuoteLocation(int Location){return QuoteLocation[Location];}
        void   SetQuoteLocation(int loc,int newVal){QuoteLocation[loc]=newVal;}
        void   SetAdverbLocation(int newVal){AdverbLocation = newVal;}
        int    GetAdverbLocation(){
          for(int x =0; x < WordCount; x++){
            if(WordType[x]=='A')AdverbLocation = x;}
            return AdverbLocation;
          }



        void RebuildPattern(){
            Pattern = "";
            for(int x =0; x < GetWordCount(); x++) Pattern += GetWordType(x);}



        int GetVerbPointingToAdjective(){
            int VerbLoc; VerbLoc = -1;
            for(int x = 0; x < GetWordCount(); x++)
                if((GetWordType(x)=='v') & (GetWordType(x+1)=='a')) VerbLoc = x;
            if(VerbLoc == -1){
                for(int x = 0; x< GetWordCount(); x++){
                    if(GetWordType(x) == 'v')VerbLoc = x;}}
            return VerbLoc;
            }

//----------------------PARSE---------------------------------------------------------------------------------------------------------
        void Parse (string str_Sentence_Data)
{
    //----------------------Initialize-------------------------------------------------------------------------------------------------
                if(Verbose)cout << "[c_Sentence.h::Parse] " << str_Sentence_Data << endl;
                InitializeVars();
                OriginalString = str_Sentence_Data;
                int int_Word_Count;
                int_Word_Count = 0;
                int x; x = 0; int int_Sentence_Length;
                int int_Last_Pos;
                int int_Sentence_Token_Position=0; // Initialize Token Position to start
                int t; t = 0;
                int_Sentence_Length = str_Sentence_Data.size();
                int_Last_Pos = int_Sentence_Length;

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

            //-----------------------------------------TOKENIZE ALL WORDS AND CHECK FOR CONTRACTION WORDS-------------
                int QuoteLoc;
                for (x = 0; x < int_Word_Count; x++)
                {

                    QuoteLoc = Words[x].find('\'');
                    if((QuoteLoc >=0)&(QuoteLoc<int_Last_Pos)){
                        WordType[x] = 'C';  //Contraction flag~ Possible plural possessive
                        isContraction[x] = true;
                        HasContraction = true;}
                    QuoteLocation[x] = QuoteLoc;
                    string tmpWord;
                    tmpWord = Words[x];
                    WordsLC[x] = "";
                     //Set WordsLC-----------------------------
                        for(int t = 0; t < int(Words[x].size()); t++)
                            tmpWord[t] =  tolower(tmpWord[t]);
                        WordsLC[x] = tmpWord;
                     //----------------------------------------
                     WordTokens[x] = Tokenize(WordsLC[x]);
                }
              //-----------------------------END OF TOKENIZE AND CONTRACTION CHECK----------------------------------------


            }// --------END OF PARSE-------------------------------------
};

#endif // C_SENTENCE_H
