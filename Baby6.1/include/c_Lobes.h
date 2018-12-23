#ifndef C_LOBES_H
#define C_LOBES_H

#include <c_MemoryCell.h>
#include <iostream>
extern bool Verbose;
using namespace std;
class c_Lobes
{
    public:
        c_Lobes();
        virtual ~c_Lobes();

    protected:

        c_MemoryCell LeftLobeMemory[30000];
        c_MemoryCell RightLobeMemory[30000];

    private:
        int LeftLobeUsageCount;
        int RightLobeUsageCount;
        int MAXCELLCOUNT;


    public:
        int GetLeftLobeUsageCount(){return LeftLobeUsageCount;}
        int GetRightLobeUsageCount(){return RightLobeUsageCount;}
        int GetBrainCellCount(){return LeftLobeUsageCount+RightLobeUsageCount;}

        void SetMemoryCellStringData(char LR, string strData, bool& Result){
            int TokenizedstrData;
            Result = false;
            TokenizedstrData = Tokenize(strData);
            if(TokenizedstrData <= (MAXCELLCOUNT-1)){
                if(LR == 'r'){
                    RightLobeMemory[TokenizedstrData].SetpCellDataString(strData);}}}

        bool GetBrainCellIsSet(char LR, int Location){
            if(LR == 'r'){
                return RightLobeMemory[Location].GetpIsSet();}
                else
                    return LeftLobeMemory[Location].GetpIsSet();}


        char GetBrainWordType(string strData, char Brainside)
           {
            char tmpWordType;
            int tmpToken;
            tmpToken = Tokenize(strData);
            if (Brainside == 'l'){
               tmpWordType = LeftLobeMemory[tmpToken].GetpWordType();}
            if (Brainside == 'r'){
               tmpWordType = RightLobeMemory[tmpToken].GetpWordType();
            }
            return tmpWordType;}


        void BrainSetWordType(string strData, char Brainside, char tmpWordType){
            int tmpToken;
            tmpToken = Tokenize(strData);
            if (Brainside == 'l'){
               LeftLobeMemory[tmpToken].SetpWordType(tmpWordType);
               }
            if (Brainside == 'r'){
               RightLobeMemory[tmpToken].SetpWordType(tmpWordType);
               } }


        bool CheckForKnownWord (string strData){                                                //currently right side only
            int tmpToken; tmpToken = Tokenize(strData);
            if(RightLobeMemory[tmpToken].GetpCellDataString() == strData){
                return true;}
                else{
                    return false;}}


        void InstallNewWord(string NewWord, char WordType, char Purpose, string NewWordLC){     //currently right side only
            if(Verbose)cout << "[c_Lobes.h::InstallNewWord]\n";
            int tmpToken;
            tmpToken = Tokenize(NewWord);
            if (tmpToken){
            RightLobeMemory[tmpToken].SetpCellDataString(NewWord);
            RightLobeMemory[tmpToken].SetpWordType(WordType);
            RightLobeMemory[tmpToken].SetpCellPurpose(Purpose);
            RightLobeMemory[tmpToken].SetpCellDataLC(NewWordLC);
            if(Verbose)
                cout << "Storing -->" << NewWord << " at " << tmpToken << endl;

            RightLobeUsageCount++;
            }
        }



        int Tokenize (string str_Data)
        {
            int z;
            int y;
            int PlaceValue;
            int tmpToken;

                z = str_Data.size();
                PlaceValue = 1;
                tmpToken = 0;
                for( y = z; y > 0; y--)
                {
                    tmpToken = tmpToken + (int(tolower(str_Data[y-1])))*PlaceValue;

                    PlaceValue ++;
                }
            return tmpToken;

        }

    bool CheckLinkOfTwoNounsWithAdjectives(string FirstNoun,string SecondNoun, string& VerbUsage, string& MatchedAdjective){
       /** TODO **
         Check for multi Matching and report back if so.
         Current logic returns last matching Adjective.
       */

       VerbUsage           = "";
       MatchedAdjective    = "";
       bool Result; Result = false;
       int FirstNounAdjectiveCount,SecondNounAdjectiveCount;
       int TokenFirstNoun,TokenSecondNoun,intVerbUsage,intMatchedAdjective;

       TokenFirstNoun           = Tokenize(FirstNoun);
       TokenSecondNoun          = Tokenize(SecondNoun);
       FirstNounAdjectiveCount  = RightLobeMemory[TokenFirstNoun].GetAdjectiveCount();
       SecondNounAdjectiveCount = RightLobeMemory[TokenSecondNoun].GetAdjectiveCount();

       if((FirstNounAdjectiveCount == 0) | (SecondNounAdjectiveCount == 0)){
          //can't match, no adjectives to compare
          //returns empty strings and false.
          }
       else{
          for(int x = 0; x < FirstNounAdjectiveCount; x++){
            for(int y = 0; y < SecondNounAdjectiveCount; y++){
                if(RightLobeMemory[TokenFirstNoun].GetAdjective(x) == RightLobeMemory[TokenSecondNoun].GetAdjective(y)){
                    Result              = true;
                    intMatchedAdjective = RightLobeMemory[TokenFirstNoun].GetAdjective(x);
                    MatchedAdjective    = RightLobeMemory[intMatchedAdjective].GetpCellDataString();
                    intVerbUsage        = RightLobeMemory[TokenFirstNoun].GetVerbWithAdjective(x,1);
                    VerbUsage           = RightLobeMemory[intVerbUsage].GetpCellDataString();}
            } } }

          return Result;
    }

};

#endif // C_LOBES_H
