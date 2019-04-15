#ifndef C_PTLCONTROL_H
#define C_PTLCONTROL_H
#include <string>
#include <vector>
#include <map>
#include <c_PTL.h>
#include <c_Cerebellum.h>


class c_PTLControl : public c_Cerebellum
{
    public:
        c_PTLControl();
        virtual ~c_PTLControl();

    protected:

    private:
        c_Sentence                        PTLSentence;
        vector   <string>                 PTLVectorData;
        vector   <string>::iterator       PTLVectorIT;
        map      <string,c_PTL>           PTLMapData;
        map      <string,c_PTL>::iterator PTLMapIT;
        multimap <int,c_PTL>              PTLmmData;
        multimap <int,c_PTL>::iterator    PTLmmIT;
        multimap <float,c_PTL>            PTLSoftCompareMap;
        multimap <float,c_PTL>::iterator  PTLSoftCmpIT;



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
                    PTLmmDataFile << PTLSoftCmpIT->first << " " << PTLSoftCmpIT->second.GetPTLOriginalSentence() << " " << PTLSoftCmpIT->second.GetPTLComparisonResult() << endl;
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
};

#endif // C_PTLCONTROL_H
