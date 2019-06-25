#ifndef C_WORDFREQTRACKER_H
#define C_WORDFREQTRACKER_H

#include <map>
#include <string>
using namespace std;

//Extended Word Frequency Tracker (eWFT)
class c_WordFreqTracker
{
    public:
        c_WordFreqTracker();
//        c_WordFreqTracker(string newVal){
//            ThisWord   = newVal;
//            BeforeWord.clear();
//            AfterWord.clear();
//        }

        virtual ~c_WordFreqTracker();

    private:
        int                       Counter    = 0;
        string                    ThisWord   = "";
        map<string,int>           BeforeWord;
        map<string,int>           AfterWord;
        map<string,int>::iterator MapIT;

    public:
        void WFTInitialize(string newVal){
            ThisWord   = newVal;
            BeforeWord.clear();
            AfterWord.clear();
        }

        void WFTAddBeforeWord(string newVal){
            MapIT = BeforeWord.find(newVal);
            if(MapIT != BeforeWord.end()){
                Counter = MapIT->second;
                Counter++;
                MapIT->second = Counter;
            }
            else{
                BeforeWord.emplace(newVal,1);
            }
        }

        void WFTAddAfterWord(string newVal){
            MapIT = AfterWord.find(newVal);
            if(MapIT != AfterWord.end()){
                Counter = MapIT->second;
                Counter++;
                MapIT->second = Counter;
            }
            else{
                AfterWord.emplace(newVal,1);
            }
        }

        int WFTGetNumberOfBeforeWords(){
            return BeforeWord.size();
        }

        int WFTGetNumberOfAfterWords(){
            return AfterWord.size();
        }

        string WTFGetThisWord(){
            return ThisWord;
        }
};

#endif // C_WORDFREQTRACKER_H
