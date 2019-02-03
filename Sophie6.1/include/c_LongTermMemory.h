#ifndef C_LONGTERMMEMORY_H
#define C_LONGTERMMEMORY_H
#include <c_Sentence.h>
#include <c_SubjectStack.h>
#include <unordered_map>
#include <fstream>
#include <map>
#include <vector>
#include <string>

class c_LongTermMemory : public c_SubjectStack
{

    public:
        c_LongTermMemory();
        virtual ~c_LongTermMemory();
        c_LongTermMemory(const c_LongTermMemory& other);

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

        c_Sentence  CopySentence;

        void CopyCurrentSentence(){
            CopySentence.InitializeVars();
            for (int x =0; x<=GetWordCount(); x++){
                CopySentence.Words[x]                     = GetWords(x);
                CopySentence.WordTokens[x]                = GetWordTokens(x);
                CopySentence.QuoteLocation[x]             = GetQuoteLocation(x);
                CopySentence.isContraction[x]             = GetisContraction(x);
                CopySentence.WordsLC[x]                   = GetWordsLC(x);
                CopySentence.SubWords[x]                  = GetSubWords(x);
                CopySentence.WordType[x]                  = GetWordType(x);
                CopySentence.SecondaryType[x]             = GetSecondaryType(x);
                CopySentence.AlternateType[x]             = GetAlternateType(x);
                CopySentence.GenderClassInSentence[x]     = GetGenderClassInSentence(x);
                CopySentence.ContractionLongFormFirst[x]  = GetContractionLongFormFirst(x);
                CopySentence.ContractionLongFormSecond[x] = GetContractionLongFormSecond(x);
                CopySentence.IsPluralWord[x]              = GetIsPluralWord(x);
                CopySentence.PluralRoot[x]                = GetPluralRoot(x);
                CopySentence.PluralWordFlag[x]            = GetPluralWordFlag(x);
                }
              CopySentence.WordCount                      =GetWordCount();
              CopySentence.SubjectLocation                =GetSubjectLocation();
              CopySentence.OriginalString                 =GetOriginalString();
              CopySentence.ConjunctionLocation            =GetConjunctionLocation();
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

            CopyCurrentSentence();
            SentenceToken = Tokenize(CopySentence.OriginalString);
            CopySentenceMap.emplace(SentenceToken,CopySentence);
            soIT = SentenceOrder.begin();
            SentenceOrder.emplace(soIT,SentenceToken);
        }

        bool FindPhraseInSentenceMap(string PhraseToFind){
            PhraseToFind = " " + PhraseToFind + " ";
            int MatchedLocation = -1;
            csIT = CopySentenceMap.begin();
            for(int x = 0; x<= int(CopySentenceMap.size()); x++){
                MatchedLocation = csIT->second.GetOriginalString().find(PhraseToFind);
                if(MatchedLocation >=0){
                  return true;
                  break;}
                csIT++;
            }
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

                for (csIT = CopySentenceMap.begin(); csIT != CopySentenceMap.end(); csIT++){

                        SentenceDataFile << csIT->second.GetWordCount() << Deliminator;
                        SentenceDataFile << csIT->second.GetSubjectLocation() << Deliminator;
                        SentenceDataFile << csIT->second.GetOriginalString() << Deliminator;
                        SentenceDataFile << csIT->second.GetPattern() << Deliminator;
                        SentenceDataFile << csIT->second.GetPreProcessedPattern()<< Deliminator;
                        SentenceDataFile << csIT->second.GetHasPluralPronoun() << Deliminator;
                        SentenceDataFile << csIT->second.GetHasPunctuation() << Deliminator;
                        SentenceDataFile << csIT->second.GetPunctuation() << Deliminator;
                        SentenceDataFile << csIT->second.GetIsQuestion() << Deliminator;
                        SentenceDataFile << csIT->second.GetHasContraction() << Deliminator;
                        SentenceDataFile << csIT->second.GetHasGreetingsWord() << Deliminator;
                        SentenceDataFile << csIT->second.GetHasGenderReference() << Deliminator;
                        SentenceDataFile << csIT->second.GetHasBeenUnderstood() << Deliminator;
                        SentenceDataFile << csIT->second.GetAdverbLocation() << Deliminator;
                        SentenceDataFile << csIT->second.GetNounCount() << Deliminator;
                        SentenceDataFile << csIT->second.GetVerbLocation() << Deliminator;
                        SentenceDataFile << csIT->second.GetAdjectiveLocation() << Deliminator;
                        SentenceDataFile << csIT->second.GetNamePointer() << Deliminator;
                        SentenceDataFile << csIT->second.GetIndirectObjectLocation() << Deliminator;
                        SentenceDataFile << csIT->second.GetHasGenderDeterminer() << Deliminator;
                        SentenceDataFile << csIT->second.GetGistOfSentence() << Deliminator;
                        SentenceDataFile << csIT->second.GetConjunctionLocation() << Deliminator;

                        for(int x = 0; x <= csIT->second.GetWordCount()-1; x++){
                            SentenceDataFile << csIT->second.GetWords(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetWordTokens(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetQuoteLocation(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetisContraction(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetWordsLC(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetSubWords(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetWordType(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetSecondaryType(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetAlternateType(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetGenderClassInSentence(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetContractionLongFormFirst(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetContractionLongFormSecond(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetIsPluralWord(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetPluralRoot(x) << Deliminator;
                            SentenceDataFile << csIT->second.GetPluralWordFlag(x) << Deliminator;

                        }



                }
            }
            else {
                cout << "file didn't open" << endl;
            }
            SentenceDataFile.close();

            ofstream SentenceDataOrderFile ("SentenceDataOrderFile.dat", ios::out);
            if (SentenceDataOrderFile.is_open()){
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

              while(strLineData !=""){

                CopySentence.InitializeVars();
                CopySentence.SetWordCount(stoi(strLineData,&decType));          //set WordCount
                getline (SentenceDataFile,strLineData);
                CopySentence.SetSubjectLocation(stoi(strLineData,&decType));    //set SubjectLocation
                getline (SentenceDataFile,strLineData);
                CopySentence.SetOriginalString(strLineData);                    //set OriginalString
                getline (SentenceDataFile,strLineData);
                CopySentence.SetPattern(strLineData);                           //set Pattern
                getline (SentenceDataFile,strLineData);
                CopySentence.SetPreProcessedPattern(strLineData);               //set PreProcessedPattern
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasPluralPronoun(stoi(strLineData,&decType));   //set bool HasPluralPronoun
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasPunctuation(stoi(strLineData,&decType));     //set bool HasPunctuation
                getline (SentenceDataFile,strLineData);
                CopySentence.SetPunctuation(strLineData[0]);                    //set char Punctuation character
                getline (SentenceDataFile,strLineData);
                CopySentence.SetIsQuestion(stoi(strLineData,&decType));         //set bool isQuestion
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasContraction(stoi(strLineData,&decType));     //set bool HasContraction
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasGreetingsWord(stoi(strLineData,&decType));   //set bool HasGreetingsWord
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasGenderReference(stoi(strLineData,&decType)); //set bool HasGenderReference
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasBeenUnderstood(stoi(strLineData,&decType));  //set bool HasBeenUnderstood
                getline (SentenceDataFile,strLineData);
                CopySentence.SetAdverbLocation(stoi(strLineData,&decType));     //set int AdverbLocation
                getline (SentenceDataFile,strLineData);
                CopySentence.SetNounCount(stoi(strLineData,&decType));          //set int NounCount
                getline (SentenceDataFile,strLineData);
                CopySentence.SetVerbLocation(stoi(strLineData,&decType));       //set int VerbLocation
                getline (SentenceDataFile,strLineData);
                CopySentence.SetAdjectiveLocation(stoi(strLineData,&decType));  //set int AdjectiveLocation
                getline (SentenceDataFile,strLineData);
                CopySentence.SetNamePointer(stoi(strLineData,&decType));        //set int NamePointer
                getline (SentenceDataFile,strLineData);
                CopySentence.SetIndirectObjectLocation(stoi(strLineData,&decType)); //set int IndirectObjectLocation
                getline (SentenceDataFile,strLineData);
                CopySentence.SetHasGenderDeterminer(stoi(strLineData,&decType));//set bool HasGenderDeterminer
                getline (SentenceDataFile,strLineData);
                CopySentence.SetGistOfSentence(strLineData);                    //set Gist data
                getline (SentenceDataFile,strLineData);
                CopySentence.SetConjunctionLocation(stoi(strLineData,&decType));//set Conjunction Location

                for(int x = 0; x<=CopySentence.GetWordCount()-1; x++){
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetWords(strLineData,x);                       //set string Words[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetWordTokens(x,stoi(strLineData,&decType));    //set int WordTokens[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetQuoteLocation(x,stoi(strLineData,&decType)); //set int QuoteLocation[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetisContraction(x,stoi(strLineData,&decType)); //set bool isContraction[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetWordsLC(x,strLineData);             //set string WordsLC[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetSubWords(x,strLineData);            //set string SubWords[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetWordType(strLineData[0],x);         //set char WordType[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetSecondaryType(strLineData[0],x);    //set char SecondaryType[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetSecondaryType(strLineData[0],x);    //set char AlternateType[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetGenderClassInSentence(x,strLineData[0]); //set char GenderClassInSentence[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetContractionLongFormFirst(x,strLineData); //set string ContractionLongFormFirst[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetContractionLongFormSecond(x,strLineData);//set string ContractionLongFormSecond[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetIsPluralWord(x,stoi(strLineData,&decType));  //set bool IsPluralWord[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetPluralRoot(x,strLineData);          //set string PluralRoot[x]
                    getline (SentenceDataFile,strLineData);
                    CopySentence.SetPluralWordFlag(x,strLineData[0]);   //set char PluralWordFlag[x]

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
