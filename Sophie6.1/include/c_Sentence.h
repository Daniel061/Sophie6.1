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

    private:
        int    sWordCount;                       // no. of words in sentence not counting punctuation  initialize to 0
        int    sSubjectLocation;                 // from 0 to WordCount, -1 = subject not located
        int    sIndirectObjectLocation;          // usually the second noun
        int    sDirectObjectLocation;            // verb acting on this
        int    sAdverbLocation;                  // -1 means none
        int    sAdjectiveLocation;               // -1 means none
        int    sSentenceDirection;               // [0]-to me(Sophie) [1]-to the user  [6]-no direction  [-1]-undetermined
        int    sConjunctionLocation;             // -1 means none
        int    sNounCount;                       // number of nouns in this sentence
        int    sVerbLocation;                    // position of verb
        int    sNamePointer;                     // position of the word name
        int    sPrepositionPosition;             // position of preposition
        string sOriginalString;                  // the whole unedited string  initialize to ""
        string sPatternString;                   // i.e. dnvua  initialize to ""
        string sPreProcessedPattern;             // i.e. duvu
        string sGistOfSentence;                  // the meat of the phrase. i.e the dog is black = is black, initialize to ""
        string sSubGistOfSentence;               // usually follows a preposition to the verb or end of sentence
        string sSupportivePhrase;                // Data before the verb
        string sSecondSubject;                   // For DualSubjects
        int    sSecondSubjectLocation;           // For Dual subjects
        char   sPunctuation;                     // !  initialize to null
        bool   sHasPunctuation;                  // true / false initialize to false
        bool   sHasPluralPronoun;                // true / false initialize to false
        bool   sIsQuestion;                      // true / false initialize to false
        bool   sHasContraction;                  // true / false initialize to false
        bool   sHasGreetingsWord;                // true / false initialize to false
        bool   sHasGenderReference;              // true / false initialize to false
        bool   sHasPreposition;                  // true / false initialize to false
        bool   sHasDualSubjects;                 // i.e. Jack and Jill
        bool   sHasBeenUnderstood;               // initialized to false, set externally
        bool   sHasGenderDeterminer;             // the word 'gender' was used
        bool   sHasPronoun;                      // flag pronoun usage
        int    sDaysOld;                         // day number stamp from 2019 beginning
        int    sUnderstandingLevel;              // the degree this sentence is known

//TODO: Set variable sPolarity, store in files


    public:
        void InitializeVars(){
            //GLOBAL SENTENCE VARIABLES
                sWordCount                     = 0;
                sSubjectLocation               = -1;
                sOriginalString                = "";
                sPatternString                 = "";
                sPreProcessedPattern           = "";
                sSecondSubject                 = "";
                sGistOfSentence                = "";
                sSubGistOfSentence             = "";
                sSupportivePhrase              = "";
                sHasPreposition                = false;
                sHasPluralPronoun              = false;
                sHasPunctuation                = false;
                sIsQuestion                    = false;
                sHasContraction                = false;
                sHasGreetingsWord              = false;
                sHasGenderReference            = false;
                sHasBeenUnderstood             = false;
                sHasGenderDeterminer           = false;
                sHasDualSubjects               = false;
                sHasPronoun                    = false;
                sSentenceDirection             = -1;
                sPunctuation                   = 'x';  //not set or does not have
                sConjunctionLocation           = -1;
                sAdverbLocation                = -1;
                sNounCount                     = -1;
                sVerbLocation                  = -1;
                sAdjectiveLocation             = -1;
                sNamePointer                   = -1;
                sPrepositionPosition           = -1;
                sSecondSubjectLocation         = -1;
                sIndirectObjectLocation        = -1;
                sDirectObjectLocation          = -1;
                sUnderstandingLevel            = -1;
                sDaysOld                       = 0;
                WordMap.clear();}


       ///*******************ALL GLOBAL->SENTENCE DATA FUNCTIONS***************************
       ///**********'InSentence/FromSentence' is the function source flag******************

        int    GetFromSentenceDirectObjectLocation(){return sDirectObjectLocation;}
        void   SetInSentenceDirectObjectLocation(int newVal){sDirectObjectLocation = newVal;}

        bool   GetFromSentenceHasPronoun(){return sHasPronoun;}
        void   SetInSentenceHasPronoun(bool newVal){sHasPronoun = newVal;}

        int    GetFromSentencesDaysOld(){return sDaysOld;}
        void   SetInSentencesDaysOld(int newVal){sDaysOld = newVal;}

        int    GetFromSentencesUnderstandingLevel(){return sUnderstandingLevel;}
        void   SetInSentencesUnderstandingLevel(int newVal){sUnderstandingLevel = newVal;}

        void   SetInSentenceSecondSubjectLocation(int newVal){sSecondSubjectLocation = newVal;}
        int    GetFromSentenceSecondSubjectLocation(){return sSecondSubjectLocation;}

        void   SetInSentenceSecondSubject(string newVal){sSecondSubject = newVal;}
        string GetFromSentenceSecondSubject(){return sSecondSubject;}

        void   SetInSentenceHasDualSubjects(bool newVal){sHasDualSubjects = newVal;}
        bool   GetFromSentenceHasDualSubjects(){return sHasDualSubjects;}

        void   SetInSentenceSubGistOfSentence(string newVal){sSubGistOfSentence = newVal;}
        string GetFromSentenceSubGistOfSentence(){return sSubGistOfSentence;}

        void   SetInSentencePrepositionPosition(int newVal){sPrepositionPosition = newVal;}
        int    GetFromSentencePrepositionPosition(){return sPrepositionPosition;}

        void   SetInSentenceHasPreposition(bool newVal){sHasPreposition = newVal;}
        bool   GetFromSentenceHasPreposition(){return sHasPreposition;}

        void   SetInSentenceSentenceDirection(int newVal){sSentenceDirection = newVal;}
        int    GetFromSentenceSentenceDirection(){return sSentenceDirection;}

        void   SetInSentenceConjunctionLocation(int newVal){sConjunctionLocation = newVal;}
        int    GetFromSentenceConjunctionLocation(){return sConjunctionLocation;}

        void   SetInSentencePreProcessedPattern(string newVal){sPreProcessedPattern = newVal;}
        string GetFromSentencePreProcessedPattern(){return sPreProcessedPattern;}

        void   SetInSentenceGistOfSentence(string newVal){sGistOfSentence = newVal;}
        string GetFromSentenceGistOfSentence(){return sGistOfSentence;}

        void   SetInSentenceSupportivePhrase(string newVal){sSupportivePhrase = newVal;}
        string GetFromSentenceSupportivePhrase(){return sSupportivePhrase;}

        bool   GetFromSentenceHasGenderDeterminer(){return sHasGenderDeterminer;}
        void   SetInSentenceHasGenderDeterminer(bool newVal){sHasGenderDeterminer = newVal;}

        bool   GetFromSentenceHasBeenUnderstood(){return sHasBeenUnderstood;}
        void   SetInSentenceHasBeenUnderstood(bool NewVal){sHasBeenUnderstood = NewVal;}

        bool   GetFromSentenceHasGenderReference(){return sHasGenderReference;}
        void   SetInSentenceHasGenderReference(bool NewVal){sHasGenderReference = NewVal;}

        bool   GetFromSentenceHasGreetingsWord(){return sHasGreetingsWord;}
        void   SetInSentenceHasGreetingsWord(bool NewVal){sHasGreetingsWord = NewVal;}

        bool   GetFromSentenceHasContraction(){return sHasContraction;}
        void   SetInSentenceHasContraction(bool NewVal){sHasContraction = NewVal;}

        int    GetFromSentenceNamePointer(){return sNamePointer;}
        void   SetInSentenceNamePointer(int NewLocation){sNamePointer = NewLocation;}

        int    GetFromSentenceAdjectiveLocation(){return sAdjectiveLocation;}
        void   SetInSentenceAdjectiveLocation(int NewVal){sAdjectiveLocation = NewVal;}

        void   SetInSentenceVerbLocation(int NewLoc){sVerbLocation = NewLoc;}
        int    GetFromSentenceVerbLocation(){return sVerbLocation;}

        void   SetInSentenceNounCount(int NewCount){sNounCount = NewCount;}
        int    GetFromSentenceNounCount(){return sNounCount;}

        int    GetFromSentenceIndirectObjectLocation(){return sIndirectObjectLocation;}
        void   SetInSentenceIndirectObjectLocation(int NewVal){sIndirectObjectLocation = NewVal;}

        bool   GetFromSentenceHasPluralPronoun(){return sHasPluralPronoun;}
        void   SetInSentenceHasPluralPronoun(bool newVal){sHasPluralPronoun = newVal;}

        int    GetFromSentenceWordCount(){return sWordCount;}
        void   SetInSentenceWordCount(int newVal){sWordCount = newVal;}

        char   GetFromSentencePunctuation(){return sPunctuation;}
        void   SetInSentencePunctuation(char newVal){sPunctuation = newVal;}

        void   SetInSentenceHasPunctuation(bool newVal){sHasPunctuation = newVal;}
        bool   GetFromSentenceHasPunctuation(){return sHasPunctuation;}

        bool   GetFromSentenceIsQuestion(){return sIsQuestion;}
        void   SetInSentenceIsQuestion(bool ISQ){sIsQuestion = ISQ;}

        string GetFromSentenceOriginalString(){return sOriginalString;}
        void   SetInSentenceOriginalString(string strData){sOriginalString = strData;}

        void   SetInSentenceSubjectLocation(int newLoc){sSubjectLocation = newLoc;}
        int    GetFromSentenceSubjectLocation(){return sSubjectLocation;}

        void   SetInSentencePattern(string strData){sPatternString = strData;}
        string GetFromSentencePattern(){return sPatternString;}

        void   SetInSentenceAdverbLocation(int newVal){sAdverbLocation = newVal;}
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

        void   SetswVerbToWord(int Location, string VerbToSet){WordMap[Location].Setw_Verb(VerbToSet);}
        string GetswVerbFromWord(int Location, int WhichVerb){return WordMap[Location].Getw_Verb(WhichVerb);}
        int    GetswVerbFromWordCount(int Location){return WordMap[Location].Getw_VerbCount();}
        ///*******************END ALL WORD DATA FUNCTIONS*********************



        int    GetAdverbLocation(){
          for(int x =0; x < sWordCount; x++){
            if(GetswWordType(x)=='A') sAdverbLocation = x;}
            return sAdverbLocation;
          }



        void RebuildPattern(){
            string LocalPattern = "";
            for(int x =0; x < GetFromSentenceWordCount(); x++) LocalPattern += GetswWordType(x);
            SetInSentencePattern(LocalPattern);}



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
                sOriginalString = str_Sentence_Data;
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
                sIsQuestion = false;
                c_tmp_char = str_Sentence_Data[int_Last_Pos-1];
                if( !(((c_tmp_char >= 'A') & (c_tmp_char <= 'Z')) |
                        ((c_tmp_char >= 'a') & (c_tmp_char <= 'z')))
                   )
                  {

                    sHasPunctuation = true;                                                                                          //SET Public Variable
                    c_Punctuation = str_Sentence_Data[int_Last_Pos-1];
                    sPunctuation = c_Punctuation;
                    if(sPunctuation == '?') sIsQuestion = true;
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


                sWordCount = int_Word_Count;

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
                        sHasContraction = true;}
                    WordMap[x].Setw_QuoteLocation(QuoteLoc);        //store pointer to quote
                    string tmpWord;
                    tmpWord = WordMap[x].Getw_WordForm();           //retrieve original word

                        for(int t = 0; t < int(tmpWord.size()); t++)
                            tmpWord[t] =  tolower(tmpWord[t]);
                        WordMap[x].Setw_WordFormLC(tmpWord);        //store the lower case version
                     //----------------------------------------
                     WordMap[x].Setw_WordTokens(Tokenize(tmpWord)); //store the tokenized version of the lowercase word
                }
              //-----------------------------END OF TOKENIZE AND CONTRACTION CHECK----------------------------------------


            }// --------END OF PARSE-------------------------------------
};

#endif // C_SENTENCE_H
