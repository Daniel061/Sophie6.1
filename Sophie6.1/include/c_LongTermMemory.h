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
            for (int x =0; x<=GetWordCount(); x++){
                CopySentence.SetWords(x,GetWords(x));                                       //1
                CopySentence.SetWordTokens(x,GetWordTokens(x));                             //2
                CopySentence.SetQuoteLocation(x,GetQuoteLocation(x));                       //3
                CopySentence.SetisContraction(x,GetisContraction(x));                       //4
                CopySentence.SetWordsLC(x,GetWordsLC(x));                                   //5
                CopySentence.SetSubWords(x,GetSubWords(x));                                 //6
                CopySentence.SetWordType(x,GetWordType(x));                                 //7
                CopySentence.SetSecondaryType(x,GetSecondaryType(x));                       //8
                CopySentence.SetAlternateType(x,GetAlternateType(x));                       //9
                CopySentence.SetGenderClassInSentence(x,GetGenderClassInSentence(x));       //10
                CopySentence.SetContractionLongFormFirst(x,GetContractionLongFormFirst(x)); //11
                CopySentence.SetContractionLongFormSecond(x,GetContractionLongFormSecond(x));//12
                CopySentence.SetIsPluralWord(x,GetIsPluralWord(x));                         //13
                CopySentence.SetPluralRoot(x,GetPluralRoot(x));                             //14
                CopySentence.SetPluralWordFlag(x,GetPluralWordFlag(x));                     //15
                CopySentence.SetWordTense(x,GetWordTense(x));                               //16
                }
              CopySentence.WordCount                      =GetWordCount();
              CopySentence.SubjectLocation                =GetSubjectLocation();
              CopySentence.OriginalString                 =GetOriginalString();
              CopySentence.ConjunctionLocation            =GetConjunctionLocation();
              CopySentence.SentenceDirection              =GetSentenceDirection();
              CopySentence.Pattern                        =GetPattern();
              CopySentence.PreProcessedPattern            =GetPreProcessedPattern();
              CopySentence.HasPluralPronoun               =GetHasPluralPronoun();
              CopySentence.HasPunctuation                 =GetHasPunctuation();
              CopySentence.Punctuation                    =GetPunctuation();
              CopySentence.IsQuestion                     =GetIsQuestion();
              CopySentence.HasContraction                 =GetHasContraction();
              CopySentence.HasGreetingsWord               =GetHasGreetingsWord();
              CopySentence.HasGenderReference             =GetHasGenderReference();
              CopySentence.HasBeenUnderstood              =GetHasBeenUnderstood();
              CopySentence.AdverbLocation                 =GetAdverbLocation();
              CopySentence.NounCount                      =GetNounCount();
              CopySentence.VerbLocation                   =GetVerbLocation();
              CopySentence.AdjectiveLocation              =GetAdjectiveLocation();
              CopySentence.NamePointer                    =GetNamePointer();
              CopySentence.IndirectObjectLocation         =GetIndirectObjectLocation();
              CopySentence.HasGenderDeterminer            =GetHasGenderDeterminer();
              CopySentence.GistOfSentence                 =GetGistOfSentence();
              CopySentence.subGistOfSentence              =GetSubGistOfSentence();
              CopySentence.HasDualSubjects                =GetHasDualSubjects();
              CopySentence.SecondSubject                  =GetSecondSubject();
              CopySentence.SecondSubjectLocation          =GetSecondSubjectLocation();


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
            if(!GetIsQuestion()){
                CopyCurrentSentence();
                SentenceToken = Tokenize(CopySentence.OriginalString);
                CopySentenceMap.emplace(SentenceToken,CopySentence);
                soIT = SentenceOrder.begin();
                SentenceOrder.emplace(soIT,SentenceToken);
            }
        }

        bool FindPhraseInSentenceMap(string PhraseToFind){
            PhraseToFind = " " + PhraseToFind;
            //if(PhraseToFind[int(PhraseToFind.size()-1)] != ' '){
            //    PhraseToFind += " ";
            //}
            int    MatchedLocation = -1;
            bool   ResultOfSearch  = false;
            string strOrigString   = "";
            csIT = CopySentenceMap.begin();
            for(int x = 0; x< int(CopySentenceMap.size()); x++){
                strOrigString = csIT->second.GetOriginalString();
                MatchedLocation = strOrigString.find(PhraseToFind);
                if(MatchedLocation >=0){
                  ResultOfSearch = true;
                  break;}
                csIT++;
            }
            return ResultOfSearch;
        }


        string GetSubjectWithMatchingPhraseInSentenceMap(string PhraseToFind,string &strSecondSubject, bool &HasDualSubs){
            PhraseToFind = " " + PhraseToFind ;
            //if(PhraseToFind[int(PhraseToFind.size()-1)] != ' '){
            //    PhraseToFind += " ";
            //}
            int    MatchedLocation = -1;
            int    SubLoc          = -1;
            string strOrigString   = "";
            csIT = CopySentenceMap.begin();
            for(int x = 0; x< int(CopySentenceMap.size()); x++){
                strOrigString = csIT->second.GetOriginalString();
                MatchedLocation = strOrigString.find(PhraseToFind);
                if(MatchedLocation >=0){
                  SubLoc = csIT->second.GetSubjectLocation();
                  strSecondSubject = csIT->second.GetSecondSubject();
                  HasDualSubs      = csIT->second.GetHasDualSubjects();
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
                cout << x << ": " << *soIT << " " << csIT->second.GetOriginalString() << endl;
                x++;
            }
        }

        void LTMSaveSentencesInFile(){
            ofstream SentenceDataFile ("SentenceDataFile.dat", ios::out);
            if (SentenceDataFile.is_open()){
                SentenceDataFile << "VERSION " << Version << Deliminator;
                for (csIT = CopySentenceMap.begin(); csIT != CopySentenceMap.end(); csIT++){
                      if(!csIT->second.GetIsQuestion()){
                        SentenceDataFile << "Word Count,";
                        SentenceDataFile << csIT->second.GetWordCount() << Deliminator;
                        SentenceDataFile << "Subject Location,";
                        SentenceDataFile << csIT->second.GetSubjectLocation() << Deliminator;
                        SentenceDataFile << "Original string,";
                        SentenceDataFile << csIT->second.GetOriginalString() << Deliminator;
                        SentenceDataFile << "Final pattern,";
                        SentenceDataFile << csIT->second.GetPattern() << Deliminator;
                        SentenceDataFile << "First pattern,";
                        SentenceDataFile << csIT->second.GetPreProcessedPattern()<< Deliminator;
                        SentenceDataFile << "bool Has plural pronoun,";
                        SentenceDataFile << csIT->second.GetHasPluralPronoun() << Deliminator;
                        SentenceDataFile << "bool Has punctuation,";
                        SentenceDataFile << csIT->second.GetHasPunctuation() << Deliminator;
                        SentenceDataFile << "Punctuation character,";
                        SentenceDataFile << csIT->second.GetPunctuation() << Deliminator;
                        SentenceDataFile << "bool Is question,";
                        SentenceDataFile << csIT->second.GetIsQuestion() << Deliminator;
                        SentenceDataFile << "bool Has contraction,";
                        SentenceDataFile << csIT->second.GetHasContraction() << Deliminator;
                        SentenceDataFile << "bool Has greeting word,";
                        SentenceDataFile << csIT->second.GetHasGreetingsWord() << Deliminator;
                        SentenceDataFile << "bool Has gender reference,";
                        SentenceDataFile << csIT->second.GetHasGenderReference() << Deliminator;
                        SentenceDataFile << "bool Has been understood,";
                        SentenceDataFile << csIT->second.GetHasBeenUnderstood() << Deliminator;
                        SentenceDataFile << "bool Has dual subjects,";
                        SentenceDataFile << csIT->second.GetHasDualSubjects() << Deliminator;
                        SentenceDataFile << "Second subject string,";
                        SentenceDataFile << csIT->second.GetSecondSubject() << Deliminator;
                        SentenceDataFile << "Second subject location,";
                        SentenceDataFile << csIT->second.GetSecondSubjectLocation() << Deliminator;
                        SentenceDataFile << "Adverb location,";
                        SentenceDataFile << csIT->second.GetAdverbLocation() << Deliminator;
                        SentenceDataFile << "Noun count,";
                        SentenceDataFile << csIT->second.GetNounCount() << Deliminator;
                        SentenceDataFile << "Verb location,";
                        SentenceDataFile << csIT->second.GetVerbLocation() << Deliminator;
                        SentenceDataFile << "Adjective location,";
                        SentenceDataFile << csIT->second.GetAdjectiveLocation() << Deliminator;
                        SentenceDataFile << "Name pointer,";
                        SentenceDataFile << csIT->second.GetNamePointer() << Deliminator;
                        SentenceDataFile << "Indirect object location,";
                        SentenceDataFile << csIT->second.GetIndirectObjectLocation() << Deliminator;
                        SentenceDataFile << "bool Has Gender determiner,";
                        SentenceDataFile << csIT->second.GetHasGenderDeterminer() << Deliminator;
                        SentenceDataFile << "Gist of sentence,";
                        SentenceDataFile << csIT->second.GetGistOfSentence() << Deliminator;
                        SentenceDataFile << "subGist of sentence,";
                        SentenceDataFile << csIT->second.GetSubGistOfSentence() << Deliminator;
                        SentenceDataFile << "Conjunction location,";
                        SentenceDataFile << csIT->second.GetConjunctionLocation() << Deliminator;
                        SentenceDataFile << "Sentence direction,";
                        SentenceDataFile << csIT->second.GetSentenceDirection() << Deliminator;

                        for(int x = 0; x <= csIT->second.GetWordCount()-1; x++){
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
               if(strLineData != "VERSION " + Version){
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
                CopySentence.SetWordCount(stoi(strLineData,&decType));          //set WordCount
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetSubjectLocation(stoi(strLineData,&decType));    //set SubjectLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetOriginalString(strLineData);                    //set OriginalString
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetPattern(strLineData);                           //set Pattern
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetPreProcessedPattern(strLineData);               //set PreProcessedPattern
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasPluralPronoun(stoi(strLineData,&decType));   //set bool HasPluralPronoun
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasPunctuation(stoi(strLineData,&decType));     //set bool HasPunctuation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetPunctuation(strLineData[0]);                    //set char Punctuation character
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetIsQuestion(stoi(strLineData,&decType));         //set bool isQuestion
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasContraction(stoi(strLineData,&decType));     //set bool HasContraction
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasGreetingsWord(stoi(strLineData,&decType));   //set bool HasGreetingsWord
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasGenderReference(stoi(strLineData,&decType)); //set bool HasGenderReference
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasBeenUnderstood(stoi(strLineData,&decType));  //set bool HasBeenUnderstood
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasDualSubjects(stoi(strLineData,&decType));    //set bool HasDualSubjects
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetSecondSubject(strLineData);                     //set second Subject
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetSecondSubjectLocation(stoi(strLineData,&decType));//set Second Subject location
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetAdverbLocation(stoi(strLineData,&decType));     //set int AdverbLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetNounCount(stoi(strLineData,&decType));          //set int NounCount
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetVerbLocation(stoi(strLineData,&decType));       //set int VerbLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetAdjectiveLocation(stoi(strLineData,&decType));  //set int AdjectiveLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetNamePointer(stoi(strLineData,&decType));        //set int NamePointer
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetIndirectObjectLocation(stoi(strLineData,&decType)); //set int IndirectObjectLocation
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasGenderDeterminer(stoi(strLineData,&decType));//set bool HasGenderDeterminer
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetGistOfSentence(strLineData);                    //set Gist data
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetSubGistOfSentence(strLineData);                 //set subGist data
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetConjunctionLocation(stoi(strLineData,&decType));//set Conjunction Location
                getline (SentenceDataFile,strLineData,',');
                getline (SentenceDataFile,strLineData);
                CopySentence.SetSentenceDirection(strLineData[0]);              //set Sentence Direction
                getline (SentenceDataFile,strLineData,',');

                for(int x = 0; x<=CopySentence.GetWordCount()-1; x++){
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

                }//end for loop
                    CopySentenceMap.emplace(Tokenize(CopySentence.GetOriginalString()),CopySentence);  //store in map
                    getline (SentenceDataFile,strLineData);
                }//end while loop
                }//end if file open

                SentenceDataFile.close();
            cout << "...";
            ifstream SentenceDataOrderFile ("SentenceDataOrderFile.dat");
            if (SentenceDataOrderFile.is_open()){
                    getline (SentenceDataOrderFile,strLineData);
                    if(strLineData != "VERSION " + Version){
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
