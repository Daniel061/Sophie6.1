#ifndef C_SENTENCE_H
#define C_SENTENCE_H

#include <c_Personality.h>
#include <c_Word.h>
#include <map>

class c_Sentence : public c_Personality
{
    public:
        c_Sentence();
        virtual ~c_Sentence();

    protected:
        map <int,c_Word>  WordMap;              // map of words and their data in the sentence
        map <int,c_Word>::iterator WordIT;      // iterator for word map
        c_Word cWords;                          // word class

    public:
        int    WordCount;                       // no. of words in sentence not counting punctuation  initialize to 0
        int    SubjectLocation;                 // from 0 to WordCount, -1 = subject not located
        int    IndirectObjectLocation;          // usually the second noun
        int    AdverbLocation;                  // -1 means none
        int    AdjectiveLocation;               // -1 means none
        int    SentenceDirection;               // [0]-to me(Sophie) [1]-to the user  [6]-no direction  [-1]-undetermined
        int    ConjunctionLocation;             // -1 means none
        int    NounCount;                       // number of nouns in this sentence
        int    VerbLocation;                    // position of verb
        int    NamePointer;                     // position of the word name
        int    PrepositionPosition;             // position of preposition
        string OriginalString;                  // the whole unedited string  initialize to ""
        string Pattern;                         // i.e. dnvua  initialize to ""
        string PreProcessedPattern;             // i.e. duvu
        string GistOfSentence;                  // the meat of the phrase. i.e the dog is black = is black, initialize to ""
        string subGistOfSentence;               // usually follows a preposition to the verb or end of sentence
        string SupportivePhrase;                // Data before the verb
        string SecondSubject;                   // For DualSubjects
        int    SecondSubjectLocation;           // For Dual subjects
        char   Punctuation;                     // !  initialize to null
        bool   HasPunctuation;                  // true / false initialize to false
        bool   HasPluralPronoun;                // true / false initialize to false
        bool   IsQuestion;                      // true / false initialize to false
        bool   HasContraction;                  // true / false initialize to false
        bool   HasGreetingsWord;                // true / false initialize to false
        bool   HasGenderReference;              // true / false initialize to false
        bool   HasPreposition;                  // true / false initialize to false
        bool   HasDualSubjects;                 // i.e. Jack and Jill
        bool   HasBeenUnderstood;               // initialized to false, set externally
        bool   HasGenderDeterminer;             // the word 'gender' was used
        bool   HasPronoun;                      // flag pronoun usage
        int    sDaysOld;                        // day number stamp from 2019 beginning
        int    sUnderstandingLevel;             // the degree this sentence is known




    public:
        void InitializeVars(){
                WordCount                     = 0;
                SubjectLocation               = -1;
                OriginalString                = "";
                Pattern                       = "";
                PreProcessedPattern           = "";
                SecondSubject                 = "";
                GistOfSentence                = "";
                subGistOfSentence             = "";
                SupportivePhrase              = "";
                HasPreposition                = false;
                HasPluralPronoun              = false;
                HasPunctuation                = false;
                IsQuestion                    = false;
                HasContraction                = false;
                HasGreetingsWord              = false;
                HasGenderReference            = false;
                HasBeenUnderstood             = false;
                HasGenderDeterminer           = false;
                HasDualSubjects               = false;
                HasPronoun                    = false;
                SentenceDirection             = -1;
                Punctuation                   = 'x';  //not set or does not have
                ConjunctionLocation           = -1;
                AdverbLocation                = -1;
                NounCount                     = -1;
                VerbLocation                  = -1;
                AdjectiveLocation             = -1;
                NamePointer                   = -1;
                PrepositionPosition           = -1;
                SecondSubjectLocation         = -1;
                IndirectObjectLocation        = -1;
                sUnderstandingLevel           = -1;
                sDaysOld                      = 0;
                WordMap.clear();}


       ///*******************ALL SENTENCE DATA FUNCTIONS***************************

        bool   GetHasPronoun(){return HasPronoun;}
        void   SetHasPronoun(bool newVal){HasPronoun = newVal;}

        int    GetsDaysOld(){return sDaysOld;}
        void   SetsDaysOld(int newVal){sDaysOld = newVal;}

        int    GetsUnderstandingLevel(){return sUnderstandingLevel;}
        void   SetsUnderstandingLevel(int newVal){sUnderstandingLevel = newVal;}

        void   SetSecondSubjectLocation(int newVal){SecondSubjectLocation = newVal;}
        int    GetSecondSubjectLocation(){return SecondSubjectLocation;}

        void   SetSecondSubject(string newVal){SecondSubject = newVal;}
        string GetSecondSubject(){return SecondSubject;}

        void   SetHasDualSubjects(bool newVal){HasDualSubjects = newVal;}
        bool   GetHasDualSubjects(){return HasDualSubjects;}

        void   SetSubGistOfSentence(string newVal){subGistOfSentence = newVal;}
        string GetSubGistOfSentence(){return subGistOfSentence;}

        void   SetPrepositionPosition(int newVal){PrepositionPosition = newVal;}
        int    GetPrepositionPosition(){return PrepositionPosition;}

        void   SetHasPreposition(bool newVal){HasPreposition = newVal;}
        bool   GetHasPreposition(){return HasPreposition;}

        void   SetSentenceDirection(int newVal){SentenceDirection = newVal;}
        int    GetSentenceDirection(){return SentenceDirection;}

        void   SetConjunctionLocation(int newVal){ConjunctionLocation = newVal;}
        int    GetConjunctionLocation(){return ConjunctionLocation;}

        void   SetPreProcessedPattern(string newVal){PreProcessedPattern = newVal;}
        string GetPreProcessedPattern(){return PreProcessedPattern;}

        void   SetGistOfSentence(string newVal){GistOfSentence = newVal;}
        string GetGistOfSentence(){return GistOfSentence;}

        void   SetSupportivePhrase(string newVal){SupportivePhrase = newVal;}
        string GetSupportivePhrase(){return SupportivePhrase;}

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

        int    GetWordCount(){return WordCount;}
        void   SetWordCount(int newVal){WordCount = newVal;}

        char   GetPunctuation(){return Punctuation;}
        void   SetPunctuation(char newVal){Punctuation = newVal;}

        void   SetHasPunctuation(bool newVal){HasPunctuation = newVal;}
        bool   GetHasPunctuation(){return HasPunctuation;}

        bool   GetIsQuestion(){return IsQuestion;}
        void   SetIsQuestion(bool ISQ){IsQuestion = ISQ;}

        string GetOriginalString(){return OriginalString;}
        void   SetOriginalString(string strData){OriginalString = strData;}

        void   SetSubjectLocation(int newLoc){SubjectLocation = newLoc;}
        int    GetSubjectLocation(){return SubjectLocation;}

        void   SetPattern(string strData){Pattern = strData;}
        string GetPattern(){return Pattern;}

        void   SetAdverbLocation(int newVal){AdverbLocation = newVal;}
        ///*****************END SENTENCE DATA FUNCTIONS***************************



        ///******************ALL WORD DATA FUNCTIONS GET/SET PAIRS*************************
        bool   GetisSingularPossessive(int Location){return WordMap[Location].Getw_SingularPossessive();}
        void   SetisSingularPossessive(int Location, bool newVal){WordMap[Location].Setw_SingularPossessive(newVal);}

        bool   GetisPluralPossessive(int Location){return WordMap[Location].Getw_PluralPossessive();}
        void   SetisPluralPossessive(int Location, bool newVal){WordMap[Location].Setw_PluralPossessive(newVal);}

        char   GetPluralWordFlag(int Location){return WordMap[Location].Getw_PluralWordFlag();}
        void   SetPluralWordFlag(int Location, char newVal){WordMap[Location].Setw_PluralWordFlag(newVal);}

        string GetPluralRoot(int Location){return WordMap[Location].Getw_PluralRoot();}
        void   SetPluralRoot(int Location, string strRoot){WordMap[Location].Setw_PluralRoot(strRoot);}

        bool   GetIsPluralWord(int Location){return WordMap[Location].Getw_isPlural();}
        void   SetIsPluralWord(int Location, bool newVal){WordMap[Location].Setw_isPlural(newVal);}

        string GetContractionLongFormFirst(int Location){return WordMap[Location].Getw_ContractionFormFirst();}
        void   SetContractionLongFormFirst(int Location,string newVal){WordMap[Location].Setw_ContractionFormFirst(newVal);}

        string GetContractionLongFormSecond(int Location){return WordMap[Location].Getw_ContractionFormSecond();}
        void   SetContractionLongFormSecond(int Location,string newVal){WordMap[Location].Setw_ContractionFormSecond(newVal);}

        char   GetGenderClassInSentence(int Location){return WordMap[Location].Getw_GenderClass();}
        void   SetGenderClassInSentence(int Location, char NewGenderClass){WordMap[Location].Setw_GenderClass(NewGenderClass);}

        char   GetSecondaryType(int Location){return WordMap[Location].Getw_SecondaryType();}
        void   SetSecondaryType(char Type,int Location){WordMap[Location].Setw_SecondaryType(Type);}

        char   GetAlternateType(int Location){return WordMap[Location].Getw_AlternateType();}
        void   SetAlternateType(char Type,int Location){WordMap[Location].Setw_AlternateType(Type);}

        int    GetWordTokens(int loc){return WordMap[loc].Getw_WordTokens();}
        void   SetWordTokens(int loc, int token){WordMap[loc].Setw_WordTokens(token);}

        string GetWords(int loc){return WordMap[loc].Getw_WordForm();}
        void   SetWords(int loc,string strData){WordMap[loc].Setw_WordForm(strData);}

        string GetWordsLC(int loc){return WordMap[loc].Getw_WordFormLC();}
        void   SetWordsLC(int loc,string newVal){WordMap[loc].Setw_WordFormLC(newVal);}

        char   GetWordType(int loc){return WordMap[loc].Getw_WordType();}
        void   SetWordType(char Type, int loc){WordMap[loc].Setw_WordType(Type);}


        void   SetSubWords(int loc,string strData){WordMap[loc].Setw_SubWord(strData);}
        string GetSubWords(int loc){return WordMap[loc].Getw_SubWord();}

        bool   GetisContraction(int Location){return WordMap[Location].Getw_isContraction();}
        void   SetisContraction(int Location, bool newVal){WordMap[Location].Setw_isContraction(newVal);}

        int    GetQuoteLocation(int Location){return WordMap[Location].Getw_QuoteLocation();}
        void   SetQuoteLocation(int Location,int newVal){WordMap[Location].Setw_QuoteLocation(newVal);}

        char   GetWordTense(int loc){return WordMap[loc].Getw_WordTense();}
        void   SetWordTense(int loc, char newTense){WordMap[loc].Setw_WordTense(newTense);}

        ///*******************END ALL WORD DATA FUNCTIONS*********************



        int    GetAdverbLocation(){
          for(int x =0; x < WordCount; x++){
            if(GetWordType(x)=='A')AdverbLocation = x;}
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
        //  Sets the follow values in cWords class and stores the class in the map WordMap
        //   [Initialize all vars including the wordmap for this sentence]
        //    string  c_WordForm
        //    string  c_WordFormLC
        //    char    c_WordType = 'C' if contraction
        //    bool    c_isContraction = true if contraction
        //    int     c_QuoteLocation = quote pointer
        //    int     c_WordTokens = the tokenized value of the lowercase word
        //  Sets the following values inc_Sentence class variables
        //    bool    HasPunctuation = true if so
        //    char    Punctuation character if there is one, default is 'x'
        //    bool    isQuestion if punctuation character is '?'
        //    int     WordCount

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
                    //Words[int_Word_Count] = str_Sentence_Data.substr(x,t-x);    //extract word
                    cWords.Setw_WordForm(str_Sentence_Data.substr(x,t-x));      //extract word to c_Words
                    WordMap.emplace(int_Word_Count,cWords);                     //place this word in the map

                    x = t+1;                                                    //move pointer
                    t = str_Sentence_Data.find(" ",x);                          //find next space
                    int_Word_Count++;
                    while ((str_Sentence_Data[x] == ' ') & (t < int_Last_Pos))
                     {
                            x++;
                            t = str_Sentence_Data.find(" ",x);
                     }

                }




                //Words[int_Word_Count] = str_Sentence_Data.substr(x,int_Last_Pos-x);
                cWords.Setw_WordForm(str_Sentence_Data.substr(x,int_Last_Pos-x)); //extract word to cWords class
                WordMap.emplace(int_Word_Count,cWords);                           //place this word in the map
                int_Word_Count++;


                WordCount = int_Word_Count;

            //-----------------------------------------TOKENIZE ALL WORDS AND CHECK FOR CONTRACTION WORDS-------------
                int     QuoteLoc    = -1;
                string  tmpWordData = "";
                for (x = 0; x < int_Word_Count; x++)
                {
                    tmpWordData = WordMap[x].Getw_WordForm();       //pull the raw word data from the map
                    //QuoteLoc = Words[x].find('\'');
                    QuoteLoc = tmpWordData.find('\'');
                    if((QuoteLoc >=0)&(QuoteLoc<int_Last_Pos)){
                        //WordType[x] = 'C';                          //Contraction flag~ Possible plural possessive
                        WordMap[x].Setw_WordType('C');              //Set Contraction flag
                        //isContraction[x] = true;
                        WordMap[x].Setw_isContraction(true);        //flag the word
                        HasContraction = true;}
                    //QuoteLocation[x] = QuoteLoc;
                    WordMap[x].Setw_QuoteLocation(QuoteLoc);        //store pointer to quote
                    string tmpWord;
                    tmpWord = WordMap[x].Getw_WordForm();           //retrieve original word
                    //tmpWord = Words[x];

                    //WordsLC[x] = "";
                     //Set WordsLC-----------------------------
                        //for(int t = 0; t < int(Words[x].size()); t++)
                        for(int t = 0; t < int(tmpWord.size()); t++)
                            tmpWord[t] =  tolower(tmpWord[t]);
                        WordMap[x].Setw_WordFormLC(tmpWord);        //store the lower case version
                        //WordsLC[x] = tmpWord;
                     //----------------------------------------
                     //WordTokens[x] = Tokenize(WordsLC[x]);
                     WordMap[x].Setw_WordTokens(Tokenize(tmpWord)); //store the tokenized version of the lowercase word
                }
              //-----------------------------END OF TOKENIZE AND CONTRACTION CHECK----------------------------------------


            }// --------END OF PARSE-------------------------------------
};

#endif // C_SENTENCE_H
