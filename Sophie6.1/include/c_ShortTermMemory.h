#ifndef C_SHORTTERMMEMORY_H
#define C_SHORTTERMMEMORY_H

#include <c_Medulla.h>

/** SOPHIE 6.1
     author - Daniel W. Ankrom ©2019

     GNU General Public License v3.0
     Permissions of this strong copyleft license are conditioned
      on making available complete source code of licensed works
       and modifications, which include larger works using a licensed
       work, under the same license.
       Copyright and license notices must be preserved.
       Contributors provide an express grant of patent rights.

     see - https://github.com/Daniel061/Sophie6.1/blob/master/LICENSE
*/

class c_ShortTermMemory : public c_Medulla
{
    public:
        c_ShortTermMemory();
        virtual ~c_ShortTermMemory();

    protected:

    private:
        string ReceivedInputs[300];
        string ProcessedPatterns[300];
        string ResponsesSent[300];

        int StoragePlacement;
        void IncrementStoragePlacement(){
            StoragePlacement++;
            if(StoragePlacement>=300) StoragePlacement =299;}


    public:
        void SaveReceivedInput(string NewData,bool NewLine=false){
            if(NewLine) IncrementStoragePlacement();
            ReceivedInputs[StoragePlacement] += " " + NewData;}

        void SaveProcessedPattern(string NewData,bool NewLine=false){
            if(NewLine) IncrementStoragePlacement();
            ProcessedPatterns[StoragePlacement] += " " + NewData;}

        void SaveResponsesSent(string NewData,bool NewLine=false){
            if(NewLine) IncrementStoragePlacement();
            ResponsesSent[StoragePlacement] += " " + NewData;}

        void ReportStorageFlow(){

            for(int x =0; x<=StoragePlacement; x++)
                cout << ReceivedInputs[x] << "---" << ProcessedPatterns[x] << "---" << ResponsesSent[x] << endl;
            }
};

#endif // C_SHORTTERMMEMORY_H
