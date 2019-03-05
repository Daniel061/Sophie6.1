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
//        unordered_map <int,string> SentenceStorage;
//        unordered_map <int,string>::iterator ssIT;
        map <int,string>                         SentenceStorage;
        map <int,string>::iterator               ssIT;
        unordered_map <int,c_Sentence>           CopySentenceMap;
        unordered_map <int,c_Sentence>::iterator csIT;
        vector <int>                             SentenceOrder;
        vector <int>::iterator                   soIT;
        string Deliminator                      ="\n";


        void CopyCurrentSentence(){
            CopySentence.InitializeVars();
            for (int x =0; x<GetFromSentenceWordCount(); x++){
                CopySentence.SetswWords(x,GetswWords(x));                                         //1
                CopySentence.SetswWordTokens(x,GetswWordTokens(x));                               //2
                CopySentence.SetswQuoteLocation(x,GetswQuoteLocation(x));                         //3
                CopySentence.SetswisContraction(x,GetswisContraction(x));                         //4
                CopySentence.SetswWordsLC(x,GetswWordsLC(x));                                     //5
                CopySentence.SetswSubWords(x,GetswSubWords(x));                                   //6
                CopySentence.SetswWordType(GetswWordType(x),x);                                   //7
                CopySentence.SetswSecondaryType(GetswSecondaryType(x),x);                        //8
                CopySentence.SetswAlternateType(GetswAlternateType(x),x);                        //9
                CopySentence.SetswGenderClassInSentence(x,GetswGenderClassInSentence(x));        //10
                CopySentence.SetswContractionLongFormFirst(x,GetswContractionLongFormFirst(x));  //11
                CopySentence.SetswContractionLongFormSecond(x,GetswContractionLongFormSecond(x));//12
                CopySentence.SetswIsPluralWord(x,GetswIsPluralWord(x));                          //13
                CopySentence.SetswPluralRoot(x,GetswPluralRoot(x));                              //14
                CopySentence.SetswPluralWordFlag(x,GetswPluralWordFlag(x));                      //15
                CopySentence.SetswWordTense(x,GetswWordTense(x));                                 //16
                CopySentence.SetswisPluralPossessive(x,GetswisPluralPossessive(x));              //17
                CopySentence.SetswisSingularPossessive(x,GetswisSingularPossessive(x));          //18
                //                                                                            //lacking mini def but not a problem, stored in memory cell file
                }
              CopySentence.SetInSentenceWordCount(GetFromSentenceWordCount());
              CopySentence.SetInSentenceSubjectLocation(GetFromSentenceSubjectLocation());
              CopySentence.SetInSentenceOriginalString(GetFromSentenceOriginalString());
              CopySentence.SetInSentenceConjunctionLocation(GetFromSentenceConjunctionLocation());
              CopySentence.SetInSentenceSentenceDirection(GetFromSentenceSentenceDirection());
              CopySentence.SetInSentencePattern(GetFromSentencePattern());
              CopySentence.SetInSentencePreProcessedPattern(GetFromSentencePreProcessedPattern());
              CopySentence.SetInSentenceHasPluralPronoun(GetFromSentenceHasPluralPronoun());
              CopySentence.SetInSentenceHasPunctuation(GetFromSentenceHasPunctuation());
              CopySentence.SetInSentencePunctuation(GetFromSentencePunctuation());
              CopySentence.SetInSentenceIsQuestion(GetFromSentenceIsQuestion());
              CopySentence.SetInSentenceHasContraction(GetFromSentenceHasContraction());
              CopySentence.SetInSentenceHasGreetingsWord(GetFromSentenceHasGreetingsWord());
              CopySentence.SetInSentenceHasGenderReference(GetFromSentenceHasGenderReference());
              CopySentence.SetInSentenceHasBeenUnderstood(GetFromSentenceHasBeenUnderstood());
              CopySentence.SetInSentenceAdverbLocation(GetAdverbLocation());
              CopySentence.SetInSentenceNounCount(GetFromSentenceNounCount());
              CopySentence.SetInSentenceVerbLocation(GetFromSentenceVerbLocation());
              CopySentence.SetInSentenceAdjectiveLocation(GetFromSentenceAdjectiveLocation());
              CopySentence.SetInSentenceNamePointer(GetFromSentenceNamePointer());
              CopySentence.SetInSentenceIndirectObjectLocation(GetFromSentenceIndirectObjectLocation());
              CopySentence.SetInSentenceHasGenderDeterminer(GetFromSentenceHasGenderDeterminer());
              CopySentence.SetInSentenceGistOfSentence(GetFromSentenceGistOfSentence());
              CopySentence.SetInSentenceSubGistOfSentence(GetFromSentenceSubGistOfSentence());
              CopySentence.SetInSentenceSupportivePhrase(GetFromSentenceSupportivePhrase());
              CopySentence.SetInSentenceHasDualSubjects(GetFromSentenceHasDualSubjects());
              CopySentence.SetInSentenceSecondSubject(GetFromSentenceSecondSubject());
              CopySentence.SetInSentenceSecondSubjectLocation(GetFromSentenceSecondSubjectLocation());
              CopySentence.SetInSentencesUnderstandingLevel(GetFromSentencesUnderstandingLevel());
              CopySentence.SetInSentencesDaysOld(GetFromSentencesDaysOld());
              CopySentence.SetInSentenceHasPronoun(GetFromSentenceHasPronoun());
              CopySentence.SetInSentencePrepositionPosition(GetFromSentencePrepositionPosition());


            }//-------------------END COPYCURRENTSENTENCE----------------------------


    public:


        void SaveSentenceInLongTermMemory(string strData){
             SentenceStorage.emplace(Tokenize(strData),strData);
        }

        int  GetNumberOfSentencesSaved(){
             return SentenceStorage.size();
        }

        void SaveCurrentSentenceInMap(){
            int SentenceToken = 0;
            if(!GetFromSentenceIsQuestion()){
                CopyCurrentSentence();
                SentenceToken = Tokenize(CopySentence.GetFromSentenceOriginalString());
                CopySentenceMap.emplace(SentenceToken,CopySentence);
                soIT = SentenceOrder.begin();
                SentenceOrder.emplace(soIT,SentenceToken);
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
            int x = 1;
            for(soIT = SentenceOrder.begin(); soIT != SentenceOrder.end(); soIT++){
                csIT = CopySentenceMap.find(*soIT);
                cout << x << ": " << *soIT << " " << csIT->second.GetFromSentenceOriginalString() << endl;
                x++;
            }
        }


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
                SetMemoryCellpCellSingularForm(GetswWordsLC(x),GetswSingularForm(x));                        /// 8   singular form
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

                for(int y = 0; y < GetswAdjectiveFromWordCount(x); y++){
                    if (Verbose)
                        cout << "Adjective count for " << GetswWords(x) << " is " << GetswAdjectiveFromWordCount(x) << endl;
                    SetMemoryCellAdjectiveInList(GetswWordsLC(x),GetswAdjectiveFromWord(x,y));}

                for(int y = 0; y < GetswAdverbFromWordCount(x); y++){
                    SetMemoryCellAdverbInList(GetswWordsLC(x),GetswAdverbFromWord(x,y));}

                for(int y = 0; y < GetswNounFromWordCount(x); y++){
                    SetMemoryCellNounInList(GetswWordsLC(x),GetswNounFromWord(x,y));}

// TODO (Dan#1#): finish storing to memory cells the remaining lists


            }// end for word count loop x iterator


        }

        void LTMSaveSentencesInFile(){
            ofstream SentenceDataFile ("SentenceDataFile.dat", ios::out);
            if (SentenceDataFile.is_open()){
                SentenceDataFile << "VERSION " << Version << Deliminator;
                for (csIT = CopySentenceMap.begin(); csIT != CopySentenceMap.end(); csIT++){
                      if(!csIT->second.GetFromSentenceIsQuestion()){
                        SentenceDataFile << "Original string           ,";
                        SentenceDataFile << csIT->second.GetFromSentenceOriginalString() << Deliminator;
                        SentenceDataFile << "Gist of sentence          ,";
                        SentenceDataFile << csIT->second.GetFromSentenceGistOfSentence() << Deliminator;
                        SentenceDataFile << "subGist of sentence       ,";
                        SentenceDataFile << csIT->second.GetFromSentenceSubGistOfSentence() << Deliminator;
                        SentenceDataFile << "Supportive phrase         ,";
                        SentenceDataFile << csIT->second.GetFromSentenceSupportivePhrase() << Deliminator;
                        SentenceDataFile << "Word Count                ,";
                        SentenceDataFile << csIT->second.GetFromSentenceWordCount() << Deliminator;
                        SentenceDataFile << "Subject Location          ,";
                        SentenceDataFile << csIT->second.GetFromSentenceSubjectLocation() << Deliminator;
                        SentenceDataFile << "Indirect object location  ,";
                        SentenceDataFile << csIT->second.GetFromSentenceIndirectObjectLocation() << Deliminator;
                        SentenceDataFile << "Direct Object Location    ,";
                        SentenceDataFile << csIT->second.GetFromSentenceDirectObjectLocation() << Deliminator;
                        SentenceDataFile << "Preposition Position      ,";
                        SentenceDataFile << csIT->second.GetFromSentencePrepositionPosition() << Deliminator;
                        SentenceDataFile << "Final pattern             ,";
                        SentenceDataFile << csIT->second.GetFromSentencePattern() << Deliminator;
                        SentenceDataFile << "First pattern             ,";
                        SentenceDataFile << csIT->second.GetFromSentencePreProcessedPattern()<< Deliminator;
                        SentenceDataFile << "bool Has plural pronoun   ,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasPluralPronoun() << Deliminator;
                        SentenceDataFile << "bool Has punctuation      ,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasPunctuation() << Deliminator;
                        SentenceDataFile << "Punctuation character     ,";
                        SentenceDataFile << csIT->second.GetFromSentencePunctuation() << Deliminator;
                        SentenceDataFile << "bool Is question          ,";
                        SentenceDataFile << csIT->second.GetFromSentenceIsQuestion() << Deliminator;
                        SentenceDataFile << "bool Has contraction      ,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasContraction() << Deliminator;
                        SentenceDataFile << "bool Has greeting word    ,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasGreetingsWord() << Deliminator;
                        SentenceDataFile << "bool Has gender reference ,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasGenderReference() << Deliminator;
                        SentenceDataFile << "bool Has been understood  ,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasBeenUnderstood() << Deliminator;
                        SentenceDataFile << "bool Has dual subjects    ,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasDualSubjects() << Deliminator;
                        SentenceDataFile << "bool Has Pronoun reference,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasPronoun() << Deliminator;
                        SentenceDataFile << "Second subject string     ,";
                        SentenceDataFile << csIT->second.GetFromSentenceSecondSubject() << Deliminator;
                        SentenceDataFile << "Second subject location   ,";
                        SentenceDataFile << csIT->second.GetFromSentenceSecondSubjectLocation() << Deliminator;
                        SentenceDataFile << "Adverb location           ,";
                        SentenceDataFile << csIT->second.GetAdverbLocation() << Deliminator;
                        SentenceDataFile << "Noun count                ,";
                        SentenceDataFile << csIT->second.GetFromSentenceNounCount() << Deliminator;
                        SentenceDataFile << "Verb location             ,";
                        SentenceDataFile << csIT->second.GetFromSentenceVerbLocation() << Deliminator;
                        SentenceDataFile << "Adjective location        ,";
                        SentenceDataFile << csIT->second.GetFromSentenceAdjectiveLocation() << Deliminator;
                        SentenceDataFile << "Name pointer              ,";
                        SentenceDataFile << csIT->second.GetFromSentenceNamePointer() << Deliminator;
                        SentenceDataFile << "bool Has Gender determiner,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasGenderDeterminer() << Deliminator;
                        SentenceDataFile << "Conjunction location      ,";
                        SentenceDataFile << csIT->second.GetFromSentenceConjunctionLocation() << Deliminator;
                        SentenceDataFile << "Sentence direction        ,";
                        SentenceDataFile << csIT->second.GetFromSentenceSentenceDirection() << Deliminator;
                        SentenceDataFile << "Days since 2019           ,";
                        SentenceDataFile << csIT->second.GetFromSentencesDaysOld() << Deliminator;
                        SentenceDataFile << "Understanding level       ,";
                        SentenceDataFile << csIT->second.GetFromSentencesUnderstandingLevel() << Deliminator;


                        for(int x = 0; x <= csIT->second.GetFromSentenceWordCount()-1; x++){
                            SentenceDataFile << "Word data                    ,";
                            SentenceDataFile << csIT->second.GetswWords(x) << Deliminator;
                            SentenceDataFile << "Word token                ,";
                            SentenceDataFile << csIT->second.GetswWordTokens(x) << Deliminator;
                            SentenceDataFile << "Quote Location            ,";
                            SentenceDataFile << csIT->second.GetswQuoteLocation(x) << Deliminator;
                            SentenceDataFile << "bool is contraction       ,";
                            SentenceDataFile << csIT->second.GetswisContraction(x) << Deliminator;
                            SentenceDataFile << "Word data LC              ,";
                            SentenceDataFile << csIT->second.GetswWordsLC(x) << Deliminator;
                            SentenceDataFile << "Substitute word           ,";
                            SentenceDataFile << csIT->second.GetswSubWords(x) << Deliminator;
                            SentenceDataFile << "Word type                 ,";
                            SentenceDataFile << csIT->second.GetswWordType(x) << Deliminator;
                            SentenceDataFile << "Secondary word type       ,";
                            SentenceDataFile << csIT->second.GetswSecondaryType(x) << Deliminator;
                            SentenceDataFile << "Alternate word type       ,";
                            SentenceDataFile << csIT->second.GetswAlternateType(x) << Deliminator;
                            SentenceDataFile << "Gender class              ,";
                            SentenceDataFile << csIT->second.GetswGenderClassInSentence(x) << Deliminator;
                            SentenceDataFile << "Contraction root 1st      ,";
                            SentenceDataFile << csIT->second.GetswContractionLongFormFirst(x) << Deliminator;
                            SentenceDataFile << "Contraction root 2nd      ,";
                            SentenceDataFile << csIT->second.GetswContractionLongFormSecond(x) << Deliminator;
                            SentenceDataFile << "bool is plural            ,";
                            SentenceDataFile << csIT->second.GetswIsPluralWord(x) << Deliminator;
                            SentenceDataFile << "Plural root               ,";
                            SentenceDataFile << csIT->second.GetswPluralRoot(x) << Deliminator;
                            SentenceDataFile << "Plural word flag          ,";
                            SentenceDataFile << csIT->second.GetswPluralWordFlag(x) << Deliminator;
                            SentenceDataFile << "Word tense                ,";
                            SentenceDataFile << csIT->second.GetswWordTense(x) << Deliminator;
                            SentenceDataFile << "bool Is SingularPossessive,";
                            SentenceDataFile << csIT->second.GetswisSingularPossessive(x) << Deliminator;
                            SentenceDataFile << "bool Is Plural Possive    ,";
                            SentenceDataFile << csIT->second.GetswisPluralPossessive(x) << Deliminator;
                            SentenceDataFile << "Possessive Root           ,";
                            SentenceDataFile << csIT->second.GetswPossessiveRoot(x) << Deliminator;
                            SentenceDataFile << "Possessive Root Type      ,";
                            SentenceDataFile << csIT->second.GetswPossessiveRootType(x) << Deliminator;

                        }

                      }//end if not question sentence

                }//end for count
            }
            else {
                cout << "file didn't open" << endl;
            }
            SentenceDataFile.close();

//            ofstream SentenceDataOrderFile ("SentenceDataOrderFile.dat", ios::out);
//            if (SentenceDataOrderFile.is_open()){
//               SentenceDataOrderFile << "VERSION " << Version << Deliminator;
//               if(SentenceOrder.size()>=1){
//                 soIT = SentenceOrder.end();
//                 soIT--;
//
//                 while(soIT != SentenceOrder.begin()){
//                    SentenceDataOrderFile << *soIT << Deliminator;
//                    soIT--;
//                 }
//               SentenceDataOrderFile << *soIT << Deliminator;
//               SentenceDataOrderFile.close();
//
//            }
//            }
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
                CopySentence.SetInSentencesDaysOld(stoi(strLineData,&decType)); //set Days since 2019
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentencesUnderstandingLevel(stoi(strLineData,&decType));//set understanding level
                getline (SentenceDataFile,strLineData,',');

                for(int x = 0; x<=CopySentence.GetFromSentenceWordCount()-1; x++){
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswWords(x,strLineData);                       //set string Words[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswWordTokens(x,stoi(strLineData,&decType));    //set int WordTokens[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswQuoteLocation(x,stoi(strLineData,&decType)); //set int QuoteLocation[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswisContraction(x,stoi(strLineData,&decType)); //set bool isContraction[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswWordsLC(x,strLineData);             //set string WordsLC[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswSubWords(x,strLineData);            //set string SubWords[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswWordType(strLineData[0],x);         //set char WordType[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswSecondaryType(strLineData[0],x);    //set char SecondaryType[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswAlternateType(strLineData[0],x);    //set char AlternateType[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswGenderClassInSentence(x,strLineData[0]); //set char GenderClassInSentence[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswContractionLongFormFirst(x,strLineData); //set string ContractionLongFormFirst[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswContractionLongFormSecond(x,strLineData);//set string ContractionLongFormSecond[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswIsPluralWord(x,stoi(strLineData,&decType));  //set bool IsPluralWord[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswPluralRoot(x,strLineData);          //set string PluralRoot[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswPluralWordFlag(x,strLineData[0]);   //set char PluralWordFlag[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswWordTense(x,strLineData[0]);        //set char word tense
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswisSingularPossessive(x,stoi(strLineData,&decType));//set bool IsSingularPossessive
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswisPluralPossessive(x,stoi(strLineData,&decType)); //set bool IsPluralPossessive
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswPossessiveRoot(x,strLineData);                        // set string possessive root
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetswPossessiveRootType(x,strLineData[0]);               // set char possessive root type
                    getline (SentenceDataFile,strLineData,',');

                }//end for loop
                    CopySentenceMap.emplace(Tokenize(CopySentence.GetFromSentenceOriginalString()),CopySentence);  //store in map
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
