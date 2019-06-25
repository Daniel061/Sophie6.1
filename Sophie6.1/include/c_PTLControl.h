#ifndef C_PTLCONTROL_H
#define C_PTLCONTROL_H
#include <string>
#include <vector>
#include <map>
#include <c_PTL.h>
#include <c_WordFreqTracker.h>
#include <c_Cerebellum.h>


class c_PTLControl : public c_Cerebellum
{
    public:
        c_PTLControl();
        virtual ~c_PTLControl();

    protected:

    private:
        c_Sentence                                PTLSentence;
        c_WordFreqTracker                         PTLeWFT;
        map<string,c_WordFreqTracker>             PTLeWFTMap;
        map<string,c_WordFreqTracker>::iterator   PTLeWFTMapIT;
        multimap<int,c_WordFreqTracker>           PTLeWFTOrderedMap;
        multimap<int,c_WordFreqTracker>::iterator PTLeWFTOrderedMapIT;
        vector   <string>                         PTLVectorData;
        vector   <string>::iterator               PTLVectorIT;
        map      <string,c_PTL>                   PTLMapData;
        map      <string,c_PTL>::iterator         PTLMapIT;
        multimap <int,c_PTL>                      PTLmmData;
        multimap <int,c_PTL>::iterator            PTLmmIT;
        multimap <float,c_PTL>                    PTLSoftCompareMap;
        multimap <float,c_PTL>::iterator          PTLSoftCmpIT;



    public:
        void ProcessPTLData(string NewSentence,int newWordCount, string thisPattern, map <int,c_Word> WordMapCopy){

            c_PTL PTLNode(NewSentence,thisPattern,newWordCount,WordMapCopy);
            PTLmmData.emplace(newWordCount,PTLNode);
            PTLVectorIT = PTLVectorData.end();
            PTLVectorData.insert(PTLVectorIT,NewSentence);

        }

        void CreateSoftCompareMap(map <int,c_Word> WordMapCopy, int WordCount){
            PTLSoftCompareMap.clear();

            float  R = 0.0;
            int    x = 0;
            pair<multimap<int,c_PTL>::iterator,multimap<int,c_PTL>::iterator> range;
            string Matched ="";
            range = PTLmmData.equal_range(WordCount);
            for(PTLmmIT = range.first; PTLmmIT != range.second; PTLmmIT++){
                R = PTLmmIT->second.PTLSoftCompare(WordMapCopy);
                PTLSoftCompareMap.emplace(R,PTLmmIT->second);
                x++;
            }
            ofstream PTLmmDataFile ("PTLSoftCompareMap.dat", ios::out);
            if (PTLmmDataFile.is_open()){
                for(PTLSoftCmpIT = PTLSoftCompareMap.begin(); PTLSoftCmpIT != PTLSoftCompareMap.end(); PTLSoftCmpIT++){
                    PTLmmDataFile << PTLSoftCmpIT->first << " " << PTLSoftCmpIT->second.GetPTLOriginalSentence() << " " << PTLSoftCmpIT->second.GetPTLBeginningPattern() << endl;
                }
            }
            PTLmmDataFile.close();
            PTLSoftCmpIT--;
//            x = PTLSoftCmpIT->second;
//            PTLVectorIT = PTLVectorData.begin();
//            for(int y = 0; y<= x; y++) PTLVectorIT++;
            cout <<  "<<" << PTLSoftCmpIT->second.GetPTLOriginalSentence() << "  " << PTLSoftCmpIT->first <<endl;


        }

        void FilePTLmmData(){

            ofstream PTLmmDataFile ("PTLmmData.dat", ios::out);
            if (PTLmmDataFile.is_open()){
               for(PTLmmIT = PTLmmData.begin(); PTLmmIT != PTLmmData.end(); PTLmmIT++){
                PTLmmDataFile << PTLmmIT->first << "," << PTLmmIT->second.GetPTLOriginalSentence() << "\t" << PTLmmIT->second.GetPTLBeginningPattern() << endl;
               }
            PTLmmDataFile.close();
        }
        }

        void PTLProcessSentenceIneWFT(){
            int tmpWordCount = GetFromSentenceWordCount();
            for(int x =0; x < tmpWordCount; x++){
                PTLeWFTMapIT = PTLeWFTMap.find(GetswWordsLC(x));
                if(PTLeWFTMapIT == PTLeWFTMap.end()){
                    PTLeWFT.WFTInitialize(GetswWordsLC(x));
                    PTLeWFTMap.emplace(GetswWordsLC(x),PTLeWFT);                                               //store new word
                    PTLeWFTMapIT = PTLeWFTMap.find(GetswWordsLC(x));
                }
                if(x !=0){
                    PTLeWFTMapIT->second.WFTAddBeforeWord(GetswWordsLC(x-1));                                  //add before word
                    if(x < tmpWordCount){
                        PTLeWFTMapIT->second.WFTAddAfterWord(GetswWordsLC(x+1));}                              //add after word if not last
                }
                else{
                    if(x < tmpWordCount){
                        PTLeWFTMapIT->second.WFTAddAfterWord(GetswWordsLC(x+1));                               //this was the first word so only add after word if not last
                    }
                }
            }

        }

        void PTLCreateWFTFile(){
            PTLeWFTOrderedMap.clear();

            for(PTLeWFTMapIT = PTLeWFTMap.begin(); PTLeWFTMapIT != PTLeWFTMap.end(); PTLeWFTMapIT++){
                    PTLeWFTOrderedMap.emplace(PTLeWFTMapIT->second.WFTGetNumberOfBeforeWords(),PTLeWFTMapIT->second);
            }

            ofstream PTLeWFTDataFile ("PTLeWFTData.dat", ios::out);
            if (PTLeWFTDataFile.is_open()){
//                for(PTLeWFTMapIT = PTLeWFTMap.begin(); PTLeWFTMapIT != PTLeWFTMap.end(); PTLeWFTMapIT++){
//                    PTLeWFTDataFile << PTLeWFTMapIT->first << " Words Before:" << PTLeWFTMapIT->second.WFTGetNumberOfBeforeWords() << " Words After:" << PTLeWFTMapIT->second.WFTGetNumberOfAfterWords() << endl;
//                }

                for(PTLeWFTOrderedMapIT = PTLeWFTOrderedMap.begin(); PTLeWFTOrderedMapIT != PTLeWFTOrderedMap.end(); PTLeWFTOrderedMapIT++){
                    PTLeWFTDataFile << "Words Before:" << PTLeWFTOrderedMapIT->first << " [" << PTLeWFTOrderedMapIT->second.WTFGetThisWord() << "] Words After:" << PTLeWFTOrderedMapIT->second.WFTGetNumberOfAfterWords() << endl;
                }
            }
            PTLeWFTDataFile.close();
        }
};

#endif // C_PTLCONTROL_H
