#ifndef C_LOBES_H
#define C_LOBES_H

#include <c_MemoryCell.h>
#include <iostream>
extern bool Verbose;
using namespace std;
class c_Lobes //: public c_MemoryCell
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
            if(LR = 'r'){
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


        bool CheckForKnownWord (string strData){                                         //currently right side only
            int tmpToken; tmpToken = Tokenize(strData);
            if(RightLobeMemory[tmpToken].GetpCellDataString() == strData){
                return true;}
                else{
                    return false;}}


        void InstallNewWord(string NewWord, char WordType, char Purpose, string NewWordLC){
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
                    tmpToken = tmpToken + (int(str_Data[y-1]))*PlaceValue;

                    PlaceValue ++;
                }
            return tmpToken;

        }



};

#endif // C_LOBES_H
