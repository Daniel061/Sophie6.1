#ifndef C_LONGTERMMEMORY_H
#define C_LONGTERMMEMORY_H
#include <c_Sentence.h>
#include <c_SubjectStack.h>
#include <unordered_map>
#include <cstdio>
#include <fstream>
#include <map>
#include <vector>
#include <string>

/** SOPHIE 6.1
     author - Daniel W. Ankrom ©2019

     GNU General Public License v3.0
     Permissions of this strong copyleft license are conditioned
      on making available complete source code of licensed works
       and modifications, which include larger works using a licensed
       work, under the same license.
       Copyright and license notices must be preserved.
       Contributors provide an express grant of patent rights.

     see - https://github.com/Daniel061/Sophie6.1/blob/master/LICENSE
*/

extern string Version;

class c_LongTermMemory : public c_SubjectStack
{

    public:
        c_LongTermMemory();
        virtual ~c_LongTermMemory();
        c_LongTermMemory(const c_LongTermMemory& other);

        c_Sentence  CopySentence;

    protected:

    private:
        map <int,string>                         SentenceStorage;
        map <int,string>::iterator               ssIT;

        unordered_map <string, c_Sentence>                 StringIndexedSentenceMap;
        unordered_map <string, c_Sentence>::iterator       strMapIT;

        unordered_map <int,c_Sentence>           CopySentenceMap;
        unordered_map <int,c_Sentence>::iterator csIT;
        vector <int>                             SentenceOrder;
        vector <int>::iterator                   soIT;
        string Deliminator                      ="\n";


        void CopyCurrentSentence(){
            CopySentence.InitializeVars();
            for (int x =0; x<GetFromSentenceWordCount(); x++){
                CopySentence.SetswWords(x,GetswWords(x));                                         //1  raw data
                CopySentence.SetswWordTokens(x,GetswWordTokens(x));                               //2  token
                CopySentence.SetswQuoteLocation(x,GetswQuoteLocation(x));                         //3  quote location
                CopySentence.SetswisContraction(x,GetswisContraction(x));                         //4  is contraction
                CopySentence.SetswWordsLC(x,GetswWordsLC(x));                                     //5  lower case data
                CopySentence.SetswSubWords(x,GetswSubWords(x));                                   //6  sub word
                CopySentence.SetswWordType(GetswWordType(x),x);                                   //7  word type
                CopySentence.SetswSecondaryType(GetswSecondaryType(x),x);                         //8  secondary type
                CopySentence.SetswAlternateType(GetswAlternateType(x),x);                         //9  alternate type
                CopySentence.SetswGenderClassInSentence(x,GetswGenderClassInSentence(x));         //10 gender class
                CopySentence.SetswContractionLongFormFirst(x,GetswContractionLongFormFirst(x));   //11 contraction long form first
                CopySentence.SetswContractionLongFormSecond(x,GetswContractionLongFormSecond(x)); //12 contraction long form second
                CopySentence.SetswIsPluralWord(x,GetswIsPluralWord(x));                           //13 is plural
                CopySentence.SetswPluralRoot(x,GetswPluralRoot(x));                               //14 plural root
                CopySentence.SetswPluralWordFlag(x,GetswPluralWordFlag(x));                       //15 plural word flag
                CopySentence.SetswWordTense(x,GetswWordTense(x));                                 //16 word tense
                CopySentence.SetswisPluralPossessive(x,GetswisPluralPossessive(x));               //17 is plural possessive
                CopySentence.SetswisSingularPossessive(x,GetswisSingularPossessive(x));           //18 is singular possessive
                CopySentence.SetswPolarity(x,GetswPolarity(x));                                   //19 polarity
                CopySentence.SetswSingularForm(x,GetswSingularForm(x));                           //20 singular form
                CopySentence.SetswPossessiveRoot(x,GetswPossessiveRoot(x));                       //21 possessive root
                CopySentence.SetswPossessiveRootType(x,GetswPossessiveRootType(x));               //22 possessive root type
                CopySentence.SetswVowelPattern(x,GetswVowelPattern(x));                           //23 vowel pattern
                CopySentence.SetswPresentTenseForm(x,GetswPresentTenseForm(x));                   //23 present tense form
                //                                                                                //lacking mini def but not a problem, stored in memory cell file
                }
              CopySentence.SetInSentenceWordCount(GetFromSentenceWordCount());                      // 1)  word count
              CopySentence.SetInSentenceSubjectLocation(GetFromSentenceSubjectLocation());          // 2)  subject location
              CopySentence.SetInSentenceOriginalString(GetFromSentenceOriginalString());            // 3)  original sentence
              CopySentence.SetInSentenceConjunctionLocation(GetFromSentenceConjunctionLocation());  // 4)  conjunction location
              CopySentence.SetInSentenceSentenceDirection(GetFromSentenceSentenceDirection());      // 5)  sentence direction
              CopySentence.SetInSentencePattern(GetFromSentencePattern());                          // 6)  pattern
              CopySentence.SetInSentencePreProcessedPattern(GetFromSentencePreProcessedPattern());  // 7)  preprocessed pattern
              CopySentence.SetInSentenceHasPluralPronoun(GetFromSentenceHasPluralPronoun());        // 8)  has plural pronoun
              CopySentence.SetInSentenceHasPunctuation(GetFromSentenceHasPunctuation());            // 9)  has punctuation
              CopySentence.SetInSentencePunctuation(GetFromSentencePunctuation());                  // 10) punctuation char
              CopySentence.SetInSentenceIsQuestion(GetFromSentenceIsQuestion());                    // 11) is question
              CopySentence.SetInSentenceHasContraction(GetFromSentenceHasContraction());            // 12) has contraction
              CopySentence.SetInSentenceHasGreetingsWord(GetFromSentenceHasGreetingsWord());        // 13) has greeting word
              CopySentence.SetInSentenceHasGenderReference(GetFromSentenceHasGenderReference());    // 14) has gender reference
              CopySentence.SetInSentenceHasBeenUnderstood(GetFromSentenceHasBeenUnderstood());      // 15) has been understood
              CopySentence.SetInSentenceAdverbLocation(GetAdverbLocation());                        // 16) adverb location
              CopySentence.SetInSentenceNounCount(GetFromSentenceNounCount());                      // 17) sentence noun count
              CopySentence.SetInSentenceVerbLocation(GetFromSentenceVerbLocation());                // 18) verb location
              CopySentence.SetInSentenceAdjectiveLocation(GetFromSentenceAdjectiveLocation());      // 19) adjective location
              CopySentence.SetInSentenceNamePointer(GetFromSentenceNamePointer());                  // 20) name pointer
              CopySentence.SetInSentenceIndirectObjectLocation(GetFromSentenceIndirectObjectLocation());// 21) indirect object location
              CopySentence.SetInSentenceHasGenderDeterminer(GetFromSentenceHasGenderDeterminer());  // 22) gender determiner
              CopySentence.SetInSentenceGistOfSentence(GetFromSentenceGistOfSentence());            // 23) gist of sentence
              CopySentence.SetInSentenceSubGistOfSentence(GetFromSentenceSubGistOfSentence());      // 24) subgist of sentence
              CopySentence.SetInSentenceSupportivePhrase(GetFromSentenceSupportivePhrase());        // 25) supportive phrase
              CopySentence.SetInSentenceHasDualSubjects(GetFromSentenceHasDualSubjects());          // 26) has dual subjects
              CopySentence.SetInSentenceSecondSubject(GetFromSentenceSecondSubject());              // 27) second subject
              CopySentence.SetInSentenceSecondSubjectLocation(GetFromSentenceSecondSubjectLocation());// 28) second subject location
              CopySentence.SetInSentencesUnderstandingLevel(GetFromSentencesUnderstandingLevel());  // 29) understanding level
              CopySentence.SetInSentencesDaysOld(GetFromSentencesDaysOld());                        // 30) day stamp
              CopySentence.SetInSentenceHasPronoun(GetFromSentenceHasPronoun());                    // 31) has pronoun
              CopySentence.SetInSentencePrepositionPosition(GetFromSentencePrepositionPosition());  // 32) preposition position
              CopySentence.SetInSentenceHasPreposition(GetFromSentenceHasPreposition());            // 33) has preposition
              CopySentence.SetInSentenceDirectObjectLocation(GetFromSentenceDirectObjectLocation());// 34) direct object location
              CopySentence.SetInSentencesPolarity(GetFromSentencesPolarity());                      // 35) polarity
              CopySentence.SetInSentencesSentenceTense(GetFromSentencesSentenceTense());            // 36) sentence tense p-past c-current u-undefined



            }//-------------------END COPYCURRENTSENTENCE----------------------------


    public:

//**************************LINKRELATEDWORDS()******************************************************************************
        void LinkRelatedWords(){
         if(Verbose)
                cout << "[c_LongTermMemory::LinkRelatedWords()]\n";
             int   LocalSubjectPos         = GetFromSentenceSubjectLocation();
             int   LocalSecondSubjectPos   = GetFromSentenceSecondSubjectLocation();
             int   LocalNounCount          = GetFromSentenceNounCount();
             int   LocalIndirectObjectPos  = GetFromSentenceIndirectObjectLocation();
             int   LocalDirectObjectPos    = GetFromSentenceDirectObjectLocation();
             int   LocalWordCount          = GetFromSentenceWordCount();
             int   LocalVerbPos            = GetFromSentenceVerbLocation();
             int   SecondNounPos           = -1;
             int   LocalAdjectivePos       = GetFromSentenceAdjectiveLocation();
             bool  LocalDualSubjects       = GetFromSentenceHasDualSubjects();

             if(LocalNounCount >1){
                if(Verbose) cout << "Linking " << GetswWordsLC(LocalIndirectObjectPos) << " with " << GetswWordsLC(LocalSubjectPos) << endl;
                SetswNounToWord(LocalSubjectPos,GetswWordsLC(LocalIndirectObjectPos));  // Link Subject to noun
                SetswNounToWord(LocalIndirectObjectPos,GetswWordsLC(LocalSubjectPos));  // link noun to subject
                if(LocalDualSubjects) SetswNounToWord(LocalSecondSubjectPos,GetswWordsLC(LocalIndirectObjectPos));}

            if( (LocalNounCount >= 1) && (GetswWordType(LocalSubjectPos)== 'P') ) {
                SetswNounToWord(LocalSubjectPos,GetswWordsLC(LocalIndirectObjectPos));  // link proper noun to indirect object
                SetswNounToWord(LocalIndirectObjectPos,GetswWordsLC(LocalSubjectPos));  // link indirect object to proper noun
            }


                SetswAdjectiveToWord(LocalSubjectPos,GetswWordsLC(LocalAdjectivePos));  // link adjective to subject
                SetswVerbToWord(LocalSubjectPos,GetswWordsLC(LocalVerbPos));            // link verb to subject


        }//End LinkRelatedWords
//*******************************************************************************************************************************




        void SaveSentenceInLongTermMemory(string strData){
             SentenceStorage.emplace(Tokenize(strData),strData);
        }

        int  GetNumberOfSentencesSaved(){
             return StringIndexedSentenceMap.size();
        }

        void SaveCurrentSentenceInMap(){
            string OldPreprocessedPattern = "";
            if(Verbose)
                cout << "[c_LongTermMemory;;SaveCurrentSentenceInMap()]\n";

            //*********NEW STRING MAP STORAGE*********************
            //*********Original string is index*******************
            CopyCurrentSentence();
            strMapIT = StringIndexedSentenceMap.find(GetFromSentenceOriginalString());
            if(strMapIT == StringIndexedSentenceMap.end()){
               if(Verbose)
                  cout << "First pass pattern:" << CopySentence.GetFromSentencePreProcessedPattern() << endl;
               StringIndexedSentenceMap.emplace(GetFromSentenceOriginalString(),CopySentence);}
            else{
               OldPreprocessedPattern = strMapIT->second.GetFromSentencePreProcessedPattern();
               if(Verbose)
                  cout << "Second pass Pattern:" << OldPreprocessedPattern << endl;
               StringIndexedSentenceMap.erase(strMapIT);
               CopySentence.SetInSentencePreProcessedPattern(OldPreprocessedPattern);    //preserve original first pattern
               StringIndexedSentenceMap.emplace(GetFromSentenceOriginalString(),CopySentence);
            }

        }

        bool FindPhraseInSentenceMap(string PhraseToFind){
            PhraseToFind = " " + PhraseToFind;
            if(PhraseToFind[int(PhraseToFind.size()-1)] != ' '){
                PhraseToFind += " ";
            }
            int    MatchedLocation = -1;
            bool   ResultOfSearch  = false;
            string strOrigString   = "";
            string endPhrase       = "";

            endPhrase = PhraseToFind.substr(0,PhraseToFind.size()-1);
            csIT = CopySentenceMap.begin();
            for(int x = 0; x< int(CopySentenceMap.size()); x++){
                strOrigString = csIT->second.GetFromSentenceOriginalString();
                MatchedLocation = strOrigString.find(PhraseToFind);
                if(MatchedLocation >=0){
                  ResultOfSearch = true;
                  break;}
                MatchedLocation = strOrigString.find(endPhrase);
                if(MatchedLocation >=0){
                  ResultOfSearch = true;
                  break;}
                csIT++;
            }
            return ResultOfSearch;
        }


        string GetSubjectWithMatchingPhraseInSentenceMap(string PhraseToFind,string &strSecondSubject, bool &HasDualSubs){
            PhraseToFind = " " + PhraseToFind ;
            if(PhraseToFind[int(PhraseToFind.size()-1)] != ' '){
                PhraseToFind += " ";
            }
            int    MatchedLocation = -1;
            int    SubLoc          = -1;
            string strOrigString   = "";
            string endPhrase       = "";

            endPhrase = PhraseToFind.substr(0,PhraseToFind.size()-1);
            csIT = CopySentenceMap.begin();
            for(int x = 0; x< int(CopySentenceMap.size()); x++){
                strOrigString = csIT->second.GetFromSentenceOriginalString();
                MatchedLocation = strOrigString.find(PhraseToFind);
                if(MatchedLocation >=0){
                  SubLoc = csIT->second.GetFromSentenceSubjectLocation();
                  strSecondSubject = csIT->second.GetFromSentenceSecondSubject();
                  HasDualSubs      = csIT->second.GetFromSentenceHasDualSubjects();
                  return csIT->second.GetswWords(SubLoc);
                  break;}
                MatchedLocation = strOrigString.find(endPhrase);
                if(MatchedLocation >=0){
                  SubLoc = csIT->second.GetFromSentenceSubjectLocation();
                  strSecondSubject = csIT->second.GetFromSentenceSecondSubject();
                  HasDualSubs      = csIT->second.GetFromSentenceHasDualSubjects();
                  return csIT->second.GetswWords(SubLoc);
                  break;}
                csIT++;
            }
            return "";
        }


        bool IsThisSentenceDuplicated(string strData){
            int TokenizedSentence = Tokenize(strData);
            csIT = CopySentenceMap.find(TokenizedSentence);
            if(csIT != CopySentenceMap.end())
                return true;
            else
                return false;
        }

        int GetSentenceStorageCountInMap(){
            return CopySentenceMap.size();
        }


        void DumpSentencesInMap(){

            for(strMapIT = StringIndexedSentenceMap.begin(); strMapIT != StringIndexedSentenceMap.end(); strMapIT++){
                cout << strMapIT->first << endl;
                cout << strMapIT->second.GetFromSentenceGistOfSentence() << endl;
                cout << strMapIT->second.GetFromSentenceSubGistOfSentence() << endl;
            }
        }

//********************************SaveAllSentenceWordDataToMemory()************************************************
        /// Function to ensure all word data gathered and worked on is stored in memory cells,
        ///  this should be called when all processing is complete,
        ///  Sentence word data has 20 variables,
        ///  Word.h has 23 variables,
        ///  Memory Cell has 25 variables.
// TODO (Dan#1#): finish saving all word and sentence data to memory

        void SaveAllSentenceWordDataToMemory(){
            if (Verbose)
                cout << "[c_LongTermMemory::SaveAllSentenceDataToMemory]\n";

            int     NewWordCount     = 0;
            int     UpDatedWordCount = 0;
            bool    Result           = false;

            for(int x = 0; x < GetFromSentenceWordCount(); x++){
                //start storing all the word data
                Result = SetMemoryCellpCellData(GetswWords(x));                                              /// 1   raw data
                if(Result)
                    NewWordCount++;
                else
                    UpDatedWordCount++;
                SetMemoryCellpCellDataLC(GetswWordsLC(x));                                                   /// 2   LC data
                SetMemorypWordType(GetswWordsLC(x),GetswWordType(x));                                        /// 3   Word type
                SetMemoryCellContractionLongFirst(GetswWordsLC(x),GetswContractionLongFormFirst(x));         /// 4   Contraction first form
                SetMemoryCellContractionLongSecond(GetswWordsLC(x),GetswContractionLongFormSecond(x));       /// 5   Contraction second form
                SetMemorypGenderClass(GetswWordsLC(x),GetswGenderClassInSentence(x));                        /// 6   Gender class
                SetMemoryCellpCellIsSingular(GetswWordsLC(x),GetswPluralWordFlag(x));                        /// 7   plural word flag
                SetMemoryCellpSingularForm(GetswWordsLC(x),GetswSingularForm(x));                            /// 8   singular form
                SetMemoryCellpIsSingularPossessive(GetswWordsLC(x),GetswisSingularPossessive(x));            /// 9   singular possessive-bool
                SetMemorypCellPurpose(GetswWordsLC(x),'w');                                                  /// 10  cell purpose
                SetMemoryCellpIsPluralPossessive(GetswWordsLC(x),GetswisPluralPossessive(x));                /// 11  plural possessive-bool
                SetMemoryCellPossessiveRoot(GetswWordsLC(x),GetswPossessiveRoot(x));                         /// 12  possessive root
                SetMemoryCellPossessiveRootType(GetswWordsLC(x),GetswPossessiveRootType(x));                 /// 13  possessive root type
                SetMemorypWordTense(GetswWordsLC(x),GetswWordTense(x));                                      /// 14  word tense
                SetMemorypSecondaryType(GetswWordsLC(x),GetswSecondaryType(x));                              /// 15  secondary type
                SetMemorypAlternateType(GetswWordsLC(x),GetswAlternateType(x));                              /// 16  alternate type
                if((x == GetFromSentenceSubjectLocation()) && (!GetFromSentenceIsQuestion()) ){
                    SetMemorypCellMiniDefinition(GetswWordsLC(x),GetFromSentenceGistOfSentence());}                      //use gist if subject & not a question sentence
                                                                                                             /// 17  mini def
                GetMemoryCellpDaysOld(GetswWordsLC(x),Result);
                if(Result){
                    SetMemoryCellpDaysOld(GetswWordsLC(x),GetDaysSinceDate());}                              /// 18  pDaysOld
                SetMemoryCellpPolarity(GetswWordsLC(x),GetswPolarity(x));                                    /// 19  polarity
                SetMemoryCellpVowelPattern(GetswWordsLC(x),GetswVowelPattern(x));                            /// 20  Vowel Pattern
                SetMemoryCellpPresentTenseForm(GetswWordsLC(x),GetswPresentTenseForm(x));                    /// 21  Present tense form

                if (Verbose)
                    cout << "Adjective count for " << GetswWords(x) << " is " << GetswAdjectiveFromWordCount(x) << endl;
                for(int y = 0; y < GetswAdjectiveFromWordCount(x); y++){                                     /// 22  adjective list

                    SetMemoryCellAdjectiveInList(GetswWordsLC(x),GetswAdjectiveFromWord(x,y));}

                for(int y = 0; y < GetswAdverbFromWordCount(x); y++){                                        /// 23  adverb list
                    SetMemoryCellAdverbInList(GetswWordsLC(x),GetswAdverbFromWord(x,y));}
                if (Verbose)
                    cout << "Noun count for " << GetswWords(x) << " is " << GetswNounFromWordCount(x) << endl;
                for(int y = 0; y < GetswNounFromWordCount(x); y++){                                          /// 24  noun list
                    SetMemoryCellNounInList(GetswWordsLC(x),GetswNounFromWord(x,y));}

                for(int y = 0; y < GetswVerbFromWordCount(x); y++){                                          /// 25  verb list
                    SetMemoryCellVerbInList(GetswWordsLC(x),GetswVerbFromWord(x,y));}

// TODO (Dan#1#): finish storing to memory cells the remaining lists
                if(GetFromSentenceSubjectLocation()==x) SetMemoryCellSubjectUsageCounterUpOne(GetswWordsLC(x));/// 26 subject usage count

            }// end for word count loop x iterator
        }
//********************END OF SaveAllSentenceWordDataToMemory()***********************************************



        void LTMSaveSentencesInFile(){
            ofstream SentenceDataFile ("SentenceDataFile.dat", ios::out);
            if (SentenceDataFile.is_open()){
                SentenceDataFile << "VERSION " << Version << Deliminator;
                //for (csIT = CopySentenceMap.begin(); csIT != CopySentenceMap.end(); csIT++){
                for (strMapIT = StringIndexedSentenceMap.begin(); strMapIT != StringIndexedSentenceMap.end(); strMapIT++){
                      //if(!strMapIT->second.GetFromSentenceIsQuestion()){
                        SentenceDataFile << "Original string           ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceOriginalString() << Deliminator;
                        SentenceDataFile << "Gist of sentence          ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceGistOfSentence() << Deliminator;
                        SentenceDataFile << "subGist of sentence       ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceSubGistOfSentence() << Deliminator;
                        SentenceDataFile << "Supportive phrase         ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceSupportivePhrase() << Deliminator;
                        SentenceDataFile << "Word Count                ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceWordCount() << Deliminator;
                        SentenceDataFile << "Subject Location          ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceSubjectLocation() << Deliminator;
                        SentenceDataFile << "Indirect object location  ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceIndirectObjectLocation() << Deliminator;
                        SentenceDataFile << "Direct Object Location    ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceDirectObjectLocation() << Deliminator;
                        SentenceDataFile << "Preposition Position      ,";
                        SentenceDataFile << strMapIT->second.GetFromSentencePrepositionPosition() << Deliminator;
                        SentenceDataFile << "Final pattern             ,";
                        SentenceDataFile << strMapIT->second.GetFromSentencePattern() << Deliminator;
                        SentenceDataFile << "First pattern             ,";
                        SentenceDataFile << strMapIT->second.GetFromSentencePreProcessedPattern()<< Deliminator;
                        SentenceDataFile << "bool Has plural pronoun   ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceHasPluralPronoun() << Deliminator;
                        SentenceDataFile << "bool Has punctuation      ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceHasPunctuation() << Deliminator;
                        SentenceDataFile << "Punctuation character     ,";
                        SentenceDataFile << strMapIT->second.GetFromSentencePunctuation() << Deliminator;
                        SentenceDataFile << "bool Is question          ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceIsQuestion() << Deliminator;
                        SentenceDataFile << "bool Has contraction      ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceHasContraction() << Deliminator;
                        SentenceDataFile << "bool Has greeting word    ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceHasGreetingsWord() << Deliminator;
                        SentenceDataFile << "bool Has gender reference ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceHasGenderReference() << Deliminator;
                        SentenceDataFile << "bool Has been understood  ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceHasBeenUnderstood() << Deliminator;
                        SentenceDataFile << "bool Has dual subjects    ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceHasDualSubjects() << Deliminator;
                        SentenceDataFile << "bool Has Pronoun reference,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceHasPronoun() << Deliminator;
                        SentenceDataFile << "Second subject string     ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceSecondSubject() << Deliminator;
                        SentenceDataFile << "Second subject location   ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceSecondSubjectLocation() << Deliminator;
                        SentenceDataFile << "Sentence Polarity         ,";
                        SentenceDataFile << strMapIT->second.GetFromSentencesPolarity() << Deliminator;
                        SentenceDataFile << "Sentence Tense            ,";
                        SentenceDataFile << strMapIT->second.GetFromSentencesSentenceTense() << Deliminator;
                        SentenceDataFile << "Adverb location           ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceAdverbLocation() << Deliminator;
                        SentenceDataFile << "Noun count                ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceNounCount() << Deliminator;
                        SentenceDataFile << "Verb location             ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceVerbLocation() << Deliminator;
                        SentenceDataFile << "Adjective location        ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceAdjectiveLocation() << Deliminator;
                        SentenceDataFile << "Name pointer              ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceNamePointer() << Deliminator;
                        SentenceDataFile << "bool Has Gender determiner,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceHasGenderDeterminer() << Deliminator;
                        SentenceDataFile << "Conjunction location      ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceConjunctionLocation() << Deliminator;
                        SentenceDataFile << "Sentence direction        ,";
                        SentenceDataFile << strMapIT->second.GetFromSentenceSentenceDirection() << Deliminator;
                        SentenceDataFile << "Sentence polarity         ,";
                        SentenceDataFile << strMapIT->second.GetFromSentencesPolarity() << Deliminator;
                        SentenceDataFile << "Days since 2019           ,";
                        SentenceDataFile << strMapIT->second.GetFromSentencesDaysOld() << Deliminator;
                        SentenceDataFile << "Understanding level       ,";
                        SentenceDataFile << strMapIT->second.GetFromSentencesUnderstandingLevel() << Deliminator;
                    //  }//end if not question sentence

                }//end for count
            }
            else {
                cout << "file didn't open" << endl;
            }
            SentenceDataFile.close();
        }


        void LTMReadSentencesInFile(){
            string strLineData  = "";
            string::size_type decType;
            cout << "...";
            ifstream SentenceDataFile ("SentenceDataFile.dat");
            if (SentenceDataFile.is_open()){
               getline (SentenceDataFile,strLineData);
               //if(strLineData != "VERSION " + Version){
               if(!VerifyFileVersion(strLineData)){
                SentenceDataFile.close();
                remove("SentenceDataFile.dat");
                strLineData = "";
               }
               else{
                getline (SentenceDataFile,strLineData,',');  //skip past version
                getline (SentenceDataFile,strLineData);
               }

              while(strLineData !=""){

                CopySentence.InitializeVars();
                CopySentence.SetInSentenceOriginalString(strLineData);                    //set OriginalString
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceGistOfSentence(strLineData);                    //set Gist data
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceSubGistOfSentence(strLineData);                 //set subGist data
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceSupportivePhrase(strLineData);                  //set supportive phrase data
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceWordCount(stoi(strLineData,&decType));          //set WordCount
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceSubjectLocation(stoi(strLineData,&decType));    //set SubjectLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceIndirectObjectLocation(stoi(strLineData,&decType)); //set int IndirectObjectLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceDirectObjectLocation(stoi(strLineData,&decType)); //set int DirectObjectLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentencePrepositionPosition(stoi(strLineData,&decType)); //set int PrepositionPosition
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentencePattern(strLineData);                           //set Pattern
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentencePreProcessedPattern(strLineData);               //set PreProcessedPattern
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceHasPluralPronoun(stoi(strLineData,&decType));   //set bool HasPluralPronoun
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceHasPunctuation(stoi(strLineData,&decType));     //set bool HasPunctuation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentencePunctuation(strLineData[0]);                    //set char Punctuation character
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceIsQuestion(stoi(strLineData,&decType));         //set bool isQuestion
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceHasContraction(stoi(strLineData,&decType));     //set bool HasContraction
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceHasGreetingsWord(stoi(strLineData,&decType));   //set bool HasGreetingsWord
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceHasGenderReference(stoi(strLineData,&decType)); //set bool HasGenderReference
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceHasBeenUnderstood(stoi(strLineData,&decType));  //set bool HasBeenUnderstood
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceHasDualSubjects(stoi(strLineData,&decType));    //set bool HasDualSubjects
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceHasPronoun(stoi(strLineData,&decType));//set bool HasPronoun
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceSecondSubject(strLineData);           //set second Subject
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceSecondSubjectLocation(stoi(strLineData,&decType));//set Second Subject location
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentencesPolarity(strLineData[0]);                      //set sentence polarity
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentencesSentenceTense(strLineData[0]);                 //set sentence tense
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceAdverbLocation(stoi(strLineData,&decType));     //set int AdverbLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceNounCount(stoi(strLineData,&decType));          //set int NounCount
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceVerbLocation(stoi(strLineData,&decType));       //set int VerbLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceAdjectiveLocation(stoi(strLineData,&decType));  //set int AdjectiveLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceNamePointer(stoi(strLineData,&decType));        //set int NamePointer
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceHasGenderDeterminer(stoi(strLineData,&decType));//set bool HasGenderDeterminer
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceConjunctionLocation(stoi(strLineData,&decType));//set Conjunction Location
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceSentenceDirection(stoi(strLineData,&decType));  //set Sentence Direction
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentencesPolarity(strLineData[0]);                      //set Sentence Polarity
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentencesDaysOld(stoi(strLineData,&decType)); //set Days since 2019
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentencesUnderstandingLevel(stoi(strLineData,&decType));//set understanding level
                getline (SentenceDataFile,strLineData,',');

//                for(int x = 0; x<=CopySentence.GetFromSentenceWordCount()-1; x++){
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswWords(x,strLineData);                       //set string Words[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswWordTokens(x,stoi(strLineData,&decType));    //set int WordTokens[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswQuoteLocation(x,stoi(strLineData,&decType)); //set int QuoteLocation[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswisContraction(x,stoi(strLineData,&decType)); //set bool isContraction[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswWordsLC(x,strLineData);             //set string WordsLC[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswSubWords(x,strLineData);            //set string SubWords[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswWordType(strLineData[0],x);         //set char WordType[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswSecondaryType(strLineData[0],x);    //set char SecondaryType[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswAlternateType(strLineData[0],x);    //set char AlternateType[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswGenderClassInSentence(x,strLineData[0]); //set char GenderClassInSentence[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswContractionLongFormFirst(x,strLineData); //set string ContractionLongFormFirst[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswContractionLongFormSecond(x,strLineData);//set string ContractionLongFormSecond[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswIsPluralWord(x,stoi(strLineData,&decType));  //set bool IsPluralWord[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswPluralRoot(x,strLineData);          //set string PluralRoot[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswPluralWordFlag(x,strLineData[0]);   //set char PluralWordFlag[x]
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswWordTense(x,strLineData[0]);        //set char word tense
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswisSingularPossessive(x,stoi(strLineData,&decType));//set bool IsSingularPossessive
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswisPluralPossessive(x,stoi(strLineData,&decType)); //set bool IsPluralPossessive
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswPossessiveRoot(x,strLineData);                        // set string possessive root
//                    getline (SentenceDataFile,strLineData,',');
//                    getline (SentenceDataFile,strLineData);
//                    CopySentence.SetswPossessiveRootType(x,strLineData[0]);               // set char possessive root type
//                    getline (SentenceDataFile,strLineData,',');
//
//                }//end for loop
                    CopySentenceMap.emplace(Tokenize(CopySentence.GetFromSentenceOriginalString()),CopySentence);  //store in map
                    StringIndexedSentenceMap.emplace(CopySentence.GetFromSentenceOriginalString(),CopySentence);   //store in new string indexed map form
                    getline (SentenceDataFile,strLineData);
                }//end while loop
                }//end if file open

                SentenceDataFile.close();
            cout << "...";
//            ifstream SentenceDataOrderFile ("SentenceDataOrderFile.dat");
//            if (SentenceDataOrderFile.is_open()){
//                    getline (SentenceDataOrderFile,strLineData);
//                    //if(strLineData != "VERSION " + Version){
//                    if(!VerifyFileVersion(strLineData)){
//                        SentenceDataOrderFile.close();
//                        remove("SentenceDataOrderFile.dat");
//                        strLineData = "";
//                    }
//                    else{
//                        getline (SentenceDataOrderFile,strLineData);
//                    }
//                while(strLineData != ""){
//                    soIT = SentenceOrder.begin();
//                    SentenceOrder.emplace(soIT,stoi(strLineData,&decType));
//                    getline (SentenceDataOrderFile,strLineData);
//                 }
//            }
//            SentenceDataOrderFile.close();
        }
};

#endif // C_LONGTERMMEMORY_H
