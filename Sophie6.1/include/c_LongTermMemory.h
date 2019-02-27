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
            for (int x =0; x<=GetFromSentenceWordCount(); x++){
                CopySentence.SetWords(x,GetWords(x));                                         //1
                CopySentence.SetWordTokens(x,GetWordTokens(x));                               //2
                CopySentence.SetQuoteLocation(x,GetQuoteLocation(x));                         //3
                CopySentence.SetisContraction(x,GetisContraction(x));                         //4
                CopySentence.SetWordsLC(x,GetWordsLC(x));                                     //5
                CopySentence.SetSubWords(x,GetSubWords(x));                                   //6
                CopySentence.SetWordType(GetWordType(x),x);                                   //7
                CopySentence.SetSecondaryType(GetSecondaryType(x),x);                         //8
                CopySentence.SetAlternateType(GetAlternateType(x),x);                         //9
                CopySentence.SetGenderClassInSentence(x,GetGenderClassInSentence(x));         //10
                CopySentence.SetContractionLongFormFirst(x,GetContractionLongFormFirst(x));   //11
                CopySentence.SetContractionLongFormSecond(x,GetContractionLongFormSecond(x)); //12
                CopySentence.SetIsPluralWord(x,GetIsPluralWord(x));                           //13
                CopySentence.SetPluralRoot(x,GetPluralRoot(x));                               //14
                CopySentence.SetPluralWordFlag(x,GetPluralWordFlag(x));                       //15
                CopySentence.SetWordTense(x,GetWordTense(x));                                 //16
                CopySentence.SetisPluralPossessive(x,GetisPluralPossessive(x));               //17
                CopySentence.SetisSingularPossessive(x,GetisSingularPossessive(x));           //18
                //                                                                            //lacking mini def but not a problem, stored in memory cell file
                }
              CopySentence.WordCount                      =GetFromSentenceWordCount();
              CopySentence.SubjectLocation                =GetFromSentenceSubjectLocation();
              CopySentence.OriginalString                 =GetFromSentenceOriginalString();
              CopySentence.ConjunctionLocation            =GetFromSentenceConjunctionLocation();
              CopySentence.SentenceDirection              =GetFromSentenceSentenceDirection();
              CopySentence.Pattern                        =GetFromSentencePattern();
              CopySentence.PreProcessedPattern            =GetFromSentencePreProcessedPattern();
              CopySentence.HasPluralPronoun               =GetFromSentenceHasPluralPronoun();
              CopySentence.HasPunctuation                 =GetFromSentenceHasPunctuation();
              CopySentence.Punctuation                    =GetFromSentencePunctuation();
              CopySentence.IsQuestion                     =GetFromSentenceIsQuestion();
              CopySentence.HasContraction                 =GetFromSentenceHasContraction();
              CopySentence.HasGreetingsWord               =GetFromSentenceHasGreetingsWord();
              CopySentence.HasGenderReference             =GetFromSentenceHasGenderReference();
              CopySentence.HasBeenUnderstood              =GetFromSentenceHasBeenUnderstood();
              CopySentence.AdverbLocation                 =GetAdverbLocation();
              CopySentence.NounCount                      =GetFromSentenceNounCount();
              CopySentence.VerbLocation                   =GetFromSentenceVerbLocation();
              CopySentence.AdjectiveLocation              =GetFromSentenceAdjectiveLocation();
              CopySentence.NamePointer                    =GetFromSentenceNamePointer();
              CopySentence.IndirectObjectLocation         =GetFromSentenceIndirectObjectLocation();
              CopySentence.HasGenderDeterminer            =GetFromSentenceHasGenderDeterminer();
              CopySentence.GistOfSentence                 =GetFromSentenceGistOfSentence();
              CopySentence.subGistOfSentence              =GetFromSentenceSubGistOfSentence();
              CopySentence.SupportivePhrase               =GetFromSentenceSupportivePhrase();
              CopySentence.HasDualSubjects                =GetFromSentenceHasDualSubjects();
              CopySentence.SecondSubject                  =GetFromSentenceSecondSubject();
              CopySentence.SecondSubjectLocation          =GetFromSentenceSecondSubjectLocation();
              CopySentence.sUnderstandingLevel            =GetFromSentencesUnderstandingLevel();
              CopySentence.sDaysOld                       =GetFromSentencesDaysOld();
              CopySentence.HasPronoun                     =GetFromSentenceHasPronoun();


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
                SentenceToken = Tokenize(CopySentence.OriginalString);
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
                  return csIT->second.GetWords(SubLoc);
                  break;}
                MatchedLocation = strOrigString.find(endPhrase);
                if(MatchedLocation >=0){
                  SubLoc = csIT->second.GetFromSentenceSubjectLocation();
                  strSecondSubject = csIT->second.GetFromSentenceSecondSubject();
                  HasDualSubs      = csIT->second.GetFromSentenceHasDualSubjects();
                  return csIT->second.GetWords(SubLoc);
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
        ///  Memory Cell has 25 variables.
        void SaveAllSentenceWordDataToMemory(){
            int     NewWordCount     = 0;
            int     UpDatedWordCount = 0;
            bool    Result           = false;

            for(int x = 0; x <= GetFromSentenceWordCount(); x++){
                //start storing all the word data
                Result = SetMemoryCellpCellData(GetWords(x));                                              /// 1   raw data
                if(Result)
                    NewWordCount++;
                else
                    UpDatedWordCount++;
                SetMemoryCellpCellDataLC(GetWordsLC(x));                                                   /// 2   LC data
                SetMemorypWordType(GetWordsLC(x),GetWordType(x));                                          /// 3   Word type
                SetMemoryCellContractionLongFirst(GetWordsLC(x),GetContractionLongFormFirst(x));           /// 4   Contraction first form
                SetMemoryCellContractionLongSecond(GetWordsLC(x),GetContractionLongFormSecond(x));         /// 5   Contraction second form
                SetMemorypGenderClass(GetWordsLC(x),GetGenderClassInSentence(x));                          /// 6   Gender class
                SetMemoryCellpCellIsSingular(GetWordsLC(x),GetPluralWordFlag(x));                          /// 7   plural word flag
                SetMemoryCellpCellSingularForm(GetWordsLC(x),GetSingularForm(x));                          /// 8   singular form
                SetMemoryCellpIsSingularPossessive(GetWordsLC(x),GetisSingularPossessive(x));              /// 9   singular possessive-bool
                SetMemorypCellPurpose(GetWordsLC(x),'w');                                                  /// 10  cell purpose
                SetMemoryCellpIsPluralPossessive(GetWordsLC(x),GetisPluralPossessive(x));                  /// 11  plural possessive-bool
                SetMemoryCellPossessiveRoot(GetWordsLC(x),GetPossessiveRoot(x));                           /// 12  possessive root
                SetMemoryCellPossessiveRootType(GetWordsLC(x),GetPossessiveRootType(x));                   /// 13  possessive root type
                SetMemorypWordTense(GetWordsLC(x),GetWordTense(x));                                        /// 14  word tense
                SetMemorypSecondaryType(GetWordsLC(x),GetSecondaryType(x));                                /// 15  secondary type
                SetMemorypAlternateType(GetWordsLC(x),GetAlternateType(x));                                /// 16  alternate type
                if((x == GetFromSentenceSubjectLocation()) && (!GetFromSentenceIsQuestion()) ){
                    SetMemorypCellMiniDefinition(GetWordsLC(x),GetFromSentenceGistOfSentence());}                      //use gist if subject & not a question sentence
                                                                                                           /// 17  mini def
                GetMemoryCellpDaysOld(GetWordsLC(x),Result);
                if(Result){
                    SetMemoryCellpDaysOld(GetWordsLC(x),GetDaysSinceDate());}                              /// 18  pDaysOld




            }


        }

        void LTMSaveSentencesInFile(){
            ofstream SentenceDataFile ("SentenceDataFile.dat", ios::out);
            if (SentenceDataFile.is_open()){
                SentenceDataFile << "VERSION " << Version << Deliminator;
                for (csIT = CopySentenceMap.begin(); csIT != CopySentenceMap.end(); csIT++){
                      if(!csIT->second.GetFromSentenceIsQuestion()){
                        SentenceDataFile << "Word Count,";
                        SentenceDataFile << csIT->second.GetFromSentenceWordCount() << Deliminator;
                        SentenceDataFile << "Subject Location,";
                        SentenceDataFile << csIT->second.GetFromSentenceSubjectLocation() << Deliminator;
                        SentenceDataFile << "Original string,";
                        SentenceDataFile << csIT->second.GetFromSentenceOriginalString() << Deliminator;
                        SentenceDataFile << "Final pattern,";
                        SentenceDataFile << csIT->second.GetFromSentencePattern() << Deliminator;
                        SentenceDataFile << "First pattern,";
                        SentenceDataFile << csIT->second.GetFromSentencePreProcessedPattern()<< Deliminator;
                        SentenceDataFile << "bool Has plural pronoun,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasPluralPronoun() << Deliminator;
                        SentenceDataFile << "bool Has punctuation,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasPunctuation() << Deliminator;
                        SentenceDataFile << "Punctuation character,";
                        SentenceDataFile << csIT->second.GetFromSentencePunctuation() << Deliminator;
                        SentenceDataFile << "bool Is question,";
                        SentenceDataFile << csIT->second.GetFromSentenceIsQuestion() << Deliminator;
                        SentenceDataFile << "bool Has contraction,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasContraction() << Deliminator;
                        SentenceDataFile << "bool Has greeting word,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasGreetingsWord() << Deliminator;
                        SentenceDataFile << "bool Has gender reference,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasGenderReference() << Deliminator;
                        SentenceDataFile << "bool Has been understood,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasBeenUnderstood() << Deliminator;
                        SentenceDataFile << "bool Has dual subjects,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasDualSubjects() << Deliminator;
                        SentenceDataFile << "bool Has Pronoun reference,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasPronoun() << Deliminator;
                        SentenceDataFile << "Second subject string,";
                        SentenceDataFile << csIT->second.GetFromSentenceSecondSubject() << Deliminator;
                        SentenceDataFile << "Second subject location,";
                        SentenceDataFile << csIT->second.GetFromSentenceSecondSubjectLocation() << Deliminator;
                        SentenceDataFile << "Adverb location,";
                        SentenceDataFile << csIT->second.GetAdverbLocation() << Deliminator;
                        SentenceDataFile << "Noun count,";
                        SentenceDataFile << csIT->second.GetFromSentenceNounCount() << Deliminator;
                        SentenceDataFile << "Verb location,";
                        SentenceDataFile << csIT->second.GetFromSentenceVerbLocation() << Deliminator;
                        SentenceDataFile << "Adjective location,";
                        SentenceDataFile << csIT->second.GetFromSentenceAdjectiveLocation() << Deliminator;
                        SentenceDataFile << "Name pointer,";
                        SentenceDataFile << csIT->second.GetFromSentenceNamePointer() << Deliminator;
                        SentenceDataFile << "Indirect object location,";
                        SentenceDataFile << csIT->second.GetFromSentenceIndirectObjectLocation() << Deliminator;
                        SentenceDataFile << "bool Has Gender determiner,";
                        SentenceDataFile << csIT->second.GetFromSentenceHasGenderDeterminer() << Deliminator;
                        SentenceDataFile << "Gist of sentence,";
                        SentenceDataFile << csIT->second.GetFromSentenceGistOfSentence() << Deliminator;
                        SentenceDataFile << "subGist of sentence,";
                        SentenceDataFile << csIT->second.GetFromSentenceSubGistOfSentence() << Deliminator;
                        SentenceDataFile << "Supportive phrase,";
                        SentenceDataFile << csIT->second.GetFromSentenceSupportivePhrase() << Deliminator;
                        SentenceDataFile << "Conjunction location,";
                        SentenceDataFile << csIT->second.GetFromSentenceConjunctionLocation() << Deliminator;
                        SentenceDataFile << "Sentence direction,";
                        SentenceDataFile << csIT->second.GetFromSentenceSentenceDirection() << Deliminator;
                        SentenceDataFile << "Days since 2019,";
                        SentenceDataFile << csIT->second.GetFromSentencesDaysOld() << Deliminator;
                        SentenceDataFile << "Understanding level,";
                        SentenceDataFile << csIT->second.GetFromSentencesUnderstandingLevel() << Deliminator;


                        for(int x = 0; x <= csIT->second.GetFromSentenceWordCount()-1; x++){
                            SentenceDataFile << "Word data,";
                            SentenceDataFile << csIT->second.GetWords(x) << Deliminator;
                            SentenceDataFile << "Word token,";
                            SentenceDataFile << csIT->second.GetWordTokens(x) << Deliminator;
                            SentenceDataFile << "Quote Location,";
                            SentenceDataFile << csIT->second.GetQuoteLocation(x) << Deliminator;
                            SentenceDataFile << "bool is contraction,";
                            SentenceDataFile << csIT->second.GetisContraction(x) << Deliminator;
                            SentenceDataFile << "Word data LC,";
                            SentenceDataFile << csIT->second.GetWordsLC(x) << Deliminator;
                            SentenceDataFile << "Subsitute word,";
                            SentenceDataFile << csIT->second.GetSubWords(x) << Deliminator;
                            SentenceDataFile << "Word type,";
                            SentenceDataFile << csIT->second.GetWordType(x) << Deliminator;
                            SentenceDataFile << "Secondary word type,";
                            SentenceDataFile << csIT->second.GetSecondaryType(x) << Deliminator;
                            SentenceDataFile << "Alternate word type,";
                            SentenceDataFile << csIT->second.GetAlternateType(x) << Deliminator;
                            SentenceDataFile << "Gender class,";
                            SentenceDataFile << csIT->second.GetGenderClassInSentence(x) << Deliminator;
                            SentenceDataFile << "Contraction root 1st,";
                            SentenceDataFile << csIT->second.GetContractionLongFormFirst(x) << Deliminator;
                            SentenceDataFile << "Contraction root 2nd,";
                            SentenceDataFile << csIT->second.GetContractionLongFormSecond(x) << Deliminator;
                            SentenceDataFile << "bool is plural,";
                            SentenceDataFile << csIT->second.GetIsPluralWord(x) << Deliminator;
                            SentenceDataFile << "Plural root,";
                            SentenceDataFile << csIT->second.GetPluralRoot(x) << Deliminator;
                            SentenceDataFile << "Plural word flag,";
                            SentenceDataFile << csIT->second.GetPluralWordFlag(x) << Deliminator;
                            SentenceDataFile << "Word tense,";
                            SentenceDataFile << csIT->second.GetWordTense(x) << Deliminator;
                            SentenceDataFile << "bool Is SingularPossessive,";
                            SentenceDataFile << csIT->second.GetisSingularPossessive(x) << Deliminator;
                            SentenceDataFile << "bool Is Plural Possive,";
                            SentenceDataFile << csIT->second.GetisPluralPossessive(x) << Deliminator;
                            SentenceDataFile << "Possessive Root,";
                            SentenceDataFile << csIT->second.GetPossessiveRoot(x) << Deliminator;
                            SentenceDataFile << "Possessive Root Type,";
                            SentenceDataFile << csIT->second.GetPossessiveRootType(x) << Deliminator;

                        }

                      }//end if not question sentence

                }//end for count
            }
            else {
                cout << "file didn't open" << endl;
            }
            SentenceDataFile.close();

            ofstream SentenceDataOrderFile ("SentenceDataOrderFile.dat", ios::out);
            if (SentenceDataOrderFile.is_open()){
               SentenceDataOrderFile << "VERSION " << Version << Deliminator;
               if(SentenceOrder.size()>=1){
                 soIT = SentenceOrder.end();
                 soIT--;

                 while(soIT != SentenceOrder.begin()){
                    SentenceDataOrderFile << *soIT << Deliminator;
                    soIT--;
                 }
               SentenceDataOrderFile << *soIT << Deliminator;
               SentenceDataOrderFile.close();

            }
            }
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
                CopySentence.SetInSentenceWordCount(stoi(strLineData,&decType));          //set WordCount
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceSubjectLocation(stoi(strLineData,&decType));    //set SubjectLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceOriginalString(strLineData);                    //set OriginalString
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
                CopySentence.SetInSentenceIndirectObjectLocation(stoi(strLineData,&decType)); //set int IndirectObjectLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetInSentenceHasGenderDeterminer(stoi(strLineData,&decType));//set bool HasGenderDeterminer
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
                    CopySentence.SetWords(x,strLineData);                       //set string Words[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetWordTokens(x,stoi(strLineData,&decType));    //set int WordTokens[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetQuoteLocation(x,stoi(strLineData,&decType)); //set int QuoteLocation[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetisContraction(x,stoi(strLineData,&decType)); //set bool isContraction[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetWordsLC(x,strLineData);             //set string WordsLC[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetSubWords(x,strLineData);            //set string SubWords[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetWordType(strLineData[0],x);         //set char WordType[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetSecondaryType(strLineData[0],x);    //set char SecondaryType[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetSecondaryType(strLineData[0],x);    //set char AlternateType[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetGenderClassInSentence(x,strLineData[0]); //set char GenderClassInSentence[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetContractionLongFormFirst(x,strLineData); //set string ContractionLongFormFirst[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetContractionLongFormSecond(x,strLineData);//set string ContractionLongFormSecond[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetIsPluralWord(x,stoi(strLineData,&decType));  //set bool IsPluralWord[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetPluralRoot(x,strLineData);          //set string PluralRoot[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetPluralWordFlag(x,strLineData[0]);   //set char PluralWordFlag[x]
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetWordTense(x,strLineData[0]);        //set char word tense
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetisSingularPossessive(x,stoi(strLineData,&decType));//set bool IsSingularPossessive
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetisPluralPossessive(x,stoi(strLineData,&decType)); //set bool IsPluralPossessive
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetPossessiveRoot(x,strLineData);                        // set string possessive root
                    getline (SentenceDataFile,strLineData,',');
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetPossessiveRootType(x,strLineData[0]);               // set char possessive root type
                    getline (SentenceDataFile,strLineData,',');

                }//end for loop
                    CopySentenceMap.emplace(Tokenize(CopySentence.GetFromSentenceOriginalString()),CopySentence);  //store in map
                    getline (SentenceDataFile,strLineData);
                }//end while loop
                }//end if file open

                SentenceDataFile.close();
            cout << "...";
            ifstream SentenceDataOrderFile ("SentenceDataOrderFile.dat");
            if (SentenceDataOrderFile.is_open()){
                    getline (SentenceDataOrderFile,strLineData);
                    //if(strLineData != "VERSION " + Version){
                    if(!VerifyFileVersion(strLineData)){
                        SentenceDataOrderFile.close();
                        remove("SentenceDataOrderFile.dat");
                        strLineData = "";
                    }
                    else{
                        getline (SentenceDataOrderFile,strLineData);
                    }
                while(strLineData != ""){
                    soIT = SentenceOrder.begin();
                    SentenceOrder.emplace(soIT,stoi(strLineData,&decType));
                    getline (SentenceDataOrderFile,strLineData);
                 }
            }
            SentenceDataOrderFile.close();
        }
};

#endif // C_LONGTERMMEMORY_H
