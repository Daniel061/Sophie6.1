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
        c_Word cWords;                          // local word class copy

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
            //GLOBAL SENTENCE VARIABLES
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


       ///*******************ALL GLOBAL->SENTENCE DATA FUNCTIONS***************************
       ///**********'InSentence/FromSentence' is the function source flag******************


        bool   GetFromSentenceHasPronoun(){return HasPronoun;}
        void   SetInSentenceHasPronoun(bool newVal){HasPronoun = newVal;}

        int    GetFromSentencesDaysOld(){return sDaysOld;}
        void   SetInSentencesDaysOld(int newVal){sDaysOld = newVal;}

        int    GetFromSentencesUnderstandingLevel(){return sUnderstandingLevel;}
        void   SetInSentencesUnderstandingLevel(int newVal){sUnderstandingLevel = newVal;}

        void   SetInSentenceSecondSubjectLocation(int newVal){SecondSubjectLocation = newVal;}
        int    GetFromSentenceSecondSubjectLocation(){return SecondSubjectLocation;}

        void   SetInSentenceSecondSubject(string newVal){SecondSubject = newVal;}
        string GetFromSentenceSecondSubject(){return SecondSubject;}

        void   SetInSentenceHasDualSubjects(bool newVal){HasDualSubjects = newVal;}
        bool   GetFromSentenceHasDualSubjects(){return HasDualSubjects;}

        void   SetInSentenceSubGistOfSentence(string newVal){subGistOfSentence = newVal;}
        string GetFromSentenceSubGistOfSentence(){return subGistOfSentence;}

        void   SetInSentencePrepositionPosition(int newVal){PrepositionPosition = newVal;}
        int    GetFromSentencePrepositionPosition(){return PrepositionPosition;}

        void   SetInSentenceHasPreposition(bool newVal){HasPreposition = newVal;}
        bool   GetFromSentenceHasPreposition(){return HasPreposition;}

        void   SetInSentenceSentenceDirection(int newVal){SentenceDirection = newVal;}
        int    GetFromSentenceSentenceDirection(){return SentenceDirection;}

        void   SetInSentenceConjunctionLocation(int newVal){ConjunctionLocation = newVal;}
        int    GetFromSentenceConjunctionLocation(){return ConjunctionLocation;}

        void   SetInSentencePreProcessedPattern(string newVal){PreProcessedPattern = newVal;}
        string GetFromSentencePreProcessedPattern(){return PreProcessedPattern;}

        void   SetInSentenceGistOfSentence(string newVal){GistOfSentence = newVal;}
        string GetFromSentenceGistOfSentence(){return GistOfSentence;}

        void   SetInSentenceSupportivePhrase(string newVal){SupportivePhrase = newVal;}
        string GetFromSentenceSupportivePhrase(){return SupportivePhrase;}

        bool   GetFromSentenceHasGenderDeterminer(){return HasGenderDeterminer;}
        void   SetInSentenceHasGenderDeterminer(bool newVal){HasGenderDeterminer = newVal;}

        bool   GetFromSentenceHasBeenUnderstood(){return HasBeenUnderstood;}
        void   SetInSentenceHasBeenUnderstood(bool NewVal){HasBeenUnderstood = NewVal;}

        bool   GetFromSentenceHasGenderReference(){return HasGenderReference;}
        void   SetInSentenceHasGenderReference(bool NewVal){HasGenderReference = NewVal;}

        bool   GetFromSentenceHasGreetingsWord(){return HasGreetingsWord;}
        void   SetInSentenceHasGreetingsWord(bool NewVal){HasGreetingsWord = NewVal;}

        bool   GetFromSentenceHasContraction(){return HasContraction;}
        void   SetInSentenceHasContraction(bool NewVal){HasContraction = NewVal;}

        int    GetFromSentenceNamePointer(){return NamePointer;}
        void   SetInSentenceNamePointer(int NewLocation){NamePointer = NewLocation;}

        int    GetFromSentenceAdjectiveLocation(){return AdjectiveLocation;}
        void   SetInSentenceAdjectiveLocation(int NewVal){AdjectiveLocation = NewVal;}

        void   SetInSentenceVerbLocation(int NewLoc){VerbLocation = NewLoc;}
        int    GetFromSentenceVerbLocation(){return VerbLocation;}

        void   SetInSentenceNounCount(int NewCount){NounCount = NewCount;}
        int    GetFromSentenceNounCount(){return NounCount;}

        int    GetFromSentenceIndirectObjectLocation(){return IndirectObjectLocation;}
        void   SetInSentenceIndirectObjectLocation(int NewVal){IndirectObjectLocation = NewVal;}

        bool   GetFromSentenceHasPluralPronoun(){return HasPluralPronoun;}
        void   SetInSentenceHasPluralPronoun(bool newVal){HasPluralPronoun = newVal;}

        int    GetFromSentenceWordCount(){return WordCount;}
        void   SetInSentenceWordCount(int newVal){WordCount = newVal;}

        char   GetFromSentencePunctuation(){return Punctuation;}
        void   SetInSentencePunctuation(char newVal){Punctuation = newVal;}

        void   SetInSentenceHasPunctuation(bool newVal){HasPunctuation = newVal;}
        bool   GetFromSentenceHasPunctuation(){return HasPunctuation;}

        bool   GetFromSentenceIsQuestion(){return IsQuestion;}
        void   SetInSentenceIsQuestion(bool ISQ){IsQuestion = ISQ;}

        string GetFromSentenceOriginalString(){return OriginalString;}
        void   SetInSentenceOriginalString(string strData){OriginalString = strData;}

        void   SetInSentenceSubjectLocation(int newLoc){SubjectLocation = newLoc;}
        int    GetFromSentenceSubjectLocation(){return SubjectLocation;}

        void   SetInSentencePattern(string strData){Pattern = strData;}
        string GetFromSentencePattern(){return Pattern;}

        void   SetInSentenceAdverbLocation(int newVal){AdverbLocation = newVal;}
        ///*****************END SENTENCE DATA FUNCTIONS***************************



        ///******************ALL WORD DATA FUNCTIONS GET/SET PAIRS*************************
        ///+++++++++++++++++++++++++'sw' is the function source flag***********************
        ///*******Location = which place in the sentence***********************************

        string GetswMiniDefinition(int Location, int intWhich){return WordMap[Location].Getw_MiniDefinition(intWhich);}
        void   SetswMiniDefinition(int Location,string newVal){WordMap[Location].Setw_MiniDefinition(newVal);}
        int    GetswMiniDefinitionCount(int Location){return WordMap[Location].Getw_MiniDefinitionCount();}

        string GetswSingularForm(int Location){return WordMap[Location].Getw_SingularForm();}
        void   SetswSingularForm(int Location, string SingularForm){WordMap[Location].Setw_SingularForm(SingularForm);}

        char   GetswPossessiveRootType(int Location){return WordMap[Location].Getw_PossessiveRootType();}
        void   SetswPossessiveRootType(int Location, char newVal){WordMap[Location].Setw_PossessiveRootType(newVal);}

        string GetswPossessiveRoot(int Location){return WordMap[Location].Getw_PossessiveRoot();}
        void   SetswPossessiveRoot(int Location,string newVal){WordMap[Location].Setw_PossessiveRoot(newVal);}

        bool   GetswisSingularPossessive(int Location){return WordMap[Location].Getw_SingularPossessive();}
        void   SetswisSingularPossessive(int Location, bool newVal){WordMap[Location].Setw_SingularPossessive(newVal);}

        bool   GetswisPluralPossessive(int Location){return WordMap[Location].Getw_PluralPossessive();}
        void   SetswisPluralPossessive(int Location, bool newVal){WordMap[Location].Setw_PluralPossessive(newVal);}

        char   GetswPluralWordFlag(int Location){return WordMap[Location].Getw_PluralWordFlag();}
        void   SetswPluralWordFlag(int Location, char newVal){WordMap[Location].Setw_PluralWordFlag(newVal);}

        string GetswPluralRoot(int Location){return WordMap[Location].Getw_PluralRoot();}
        void   SetswPluralRoot(int Location, string strRoot){WordMap[Location].Setw_PluralRoot(strRoot);}

        bool   GetswIsPluralWord(int Location){return WordMap[Location].Getw_isPlural();}
        void   SetswIsPluralWord(int Location, bool newVal){WordMap[Location].Setw_isPlural(newVal);}

        string GetswContractionLongFormFirst(int Location){return WordMap[Location].Getw_ContractionFormFirst();}
        void   SetswContractionLongFormFirst(int Location,string newVal){WordMap[Location].Setw_ContractionFormFirst(newVal);}

        string GetswContractionLongFormSecond(int Location){return WordMap[Location].Getw_ContractionFormSecond();}
        void   SetswContractionLongFormSecond(int Location,string newVal){WordMap[Location].Setw_ContractionFormSecond(newVal);}

        char   GetswGenderClassInSentence(int Location){return WordMap[Location].Getw_GenderClass();}
        void   SetswGenderClassInSentence(int Location, char NewGenderClass){WordMap[Location].Setw_GenderClass(NewGenderClass);}

        char   GetswSecondaryType(int Location){return WordMap[Location].Getw_SecondaryType();}
        void   SetswSecondaryType(char Type,int Location){WordMap[Location].Setw_SecondaryType(Type);}

        char   GetswAlternateType(int Location){return WordMap[Location].Getw_AlternateType();}
        void   SetswAlternateType(char Type,int Location){WordMap[Location].Setw_AlternateType(Type);}

        int    GetswWordTokens(int Location){return WordMap[Location].Getw_WordTokens();}
        void   SetswWordTokens(int Location, int token){WordMap[Location].Setw_WordTokens(token);}

        string GetswWords(int Location){return WordMap[Location].Getw_WordForm();}
        void   SetswWords(int Location,string strData){WordMap[Location].Setw_WordForm(strData);}

        string GetswWordsLC(int Location){return WordMap[Location].Getw_WordFormLC();}
        void   SetswWordsLC(int Location,string newVal){WordMap[Location].Setw_WordFormLC(newVal);}

        char   GetswWordType(int Location){return WordMap[Location].Getw_WordType();}
        void   SetswWordType(char Type, int Location){WordMap[Location].Setw_WordType(Type);}


        void   SetswSubWords(int Location,string strData){WordMap[Location].Setw_SubWord(strData);}
        string GetswSubWords(int Location){return WordMap[Location].Getw_SubWord();}

        bool   GetswisContraction(int Location){return WordMap[Location].Getw_isContraction();}
        void   SetswisContraction(int Location, bool newVal){WordMap[Location].Setw_isContraction(newVal);}

        int    GetswQuoteLocation(int Location){return WordMap[Location].Getw_QuoteLocation();}
        void   SetswQuoteLocation(int Location,int newVal){WordMap[Location].Setw_QuoteLocation(newVal);}

        char   GetswWordTense(int Location){return WordMap[Location].Getw_WordTense();}
        void   SetswWordTense(int Location, char newTense){WordMap[Location].Setw_WordTense(newTense);}

        void   SetswAdverbToWord(int Location, string AdverbToSet){WordMap[Location].Setw_Adverb(AdverbToSet);}
        string GetswAdverbFromWord(int Location, int WhichAdverb){return WordMap[Location].Getw_Adverb(WhichAdverb);}
        int    GetswAdverbFromWordCount(int Location){return WordMap[Location].Getw_AdverbCount();}

        void   SetswAdjectiveToWord(int Location, string AdjectiveToSet){WordMap[Location].Setw_Adjective(AdjectiveToSet);}
        string GetswAdjectiveFromWord(int Location, int WhichAdjective){return WordMap[Location].Getw_Adjective(WhichAdjective);}
        int    GetswAdjectiveFromWordCount(int Location){return WordMap[Location].Getw_AdjectiveCount();}

        void   SetswNounToWord(int Location, string RelatedNoun){WordMap[Location].Setw_RelatedNoun(RelatedNoun);}
        string GetswNounFromWord(int Location, int WhichNoun){return WordMap[Location].Getw_RelatedNoun(WhichNoun);}
        int    GetswNounFromWordCount(int Location){return WordMap[Location].Getw_RelatedNounCount();}

        ///*******************END ALL WORD DATA FUNCTIONS*********************



        int    GetAdverbLocation(){
          for(int x =0; x < WordCount; x++){
            if(GetswWordType(x)=='A')AdverbLocation = x;}
            return AdverbLocation;
          }



        void RebuildPattern(){
            Pattern = "";
            for(int x =0; x < GetFromSentenceWordCount(); x++) Pattern += GetswWordType(x);}



        int GetVerbPointingToAdjective(){
            int VerbLoc; VerbLoc = -1;
            for(int x = 0; x < GetFromSentenceWordCount(); x++)
                if((GetswWordType(x)=='v') & (GetswWordType(x+1)=='a')) VerbLoc = x;
            if(VerbLoc == -1){
                for(int x = 0; x< GetFromSentenceWordCount(); x++){
                    if(GetswWordType(x) == 'v')VerbLoc = x;}}
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
                    QuoteLoc = tmpWordData.find('\'');
                    if((QuoteLoc >=0)&(QuoteLoc<int_Last_Pos)){
                        WordMap[x].Setw_WordType('C');              //Set Contraction flag
                        WordMap[x].Setw_isContraction(true);        //flag the word
                        HasContraction = true;}
                    WordMap[x].Setw_QuoteLocation(QuoteLoc);        //store pointer to quote
                    string tmpWord;
                    tmpWord = WordMap[x].Getw_WordForm();           //retrieve original word

                        for(int t = 0; t < int(tmpWord.size()); t++)
                            tmpWord[t] =  tolower(tmpWord[t]);
                        WordMap[x].Setw_WordFormLC(tmpWord);        //store the lower case version
                        //WordsLC[x] = tmpWord;
                     //----------------------------------------
                     WordMap[x].Setw_WordTokens(Tokenize(tmpWord)); //store the tokenized version of the lowercase word
                }
              //-----------------------------END OF TOKENIZE AND CONTRACTION CHECK----------------------------------------


            }// --------END OF PARSE-------------------------------------
};

#endif // C_SENTENCE_H
