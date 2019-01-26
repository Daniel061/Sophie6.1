#ifndef C_LONGTERMMEMORY_H
#define C_LONGTERMMEMORY_H
#include <c_Sentence.h>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>

class c_LongTermMemory : public c_Sentence
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
                }
              CopySentence.WordCount                      =GetWordCount();
              CopySentence.SubjectLocation                =GetSubjectLocation();
              CopySentence.OriginalString                 =GetOriginalString();
              CopySentence.Pattern                        =GetPattern();
              CopySentence.HasPluralPronoun               =GetHasPluralPronoun();
              CopySentence.HasPunctuation                 =GetHasPunctuation();
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



};

#endif // C_LONGTERMMEMORY_H
