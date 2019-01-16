#ifndef C_LONGTERMMEMORY_H
#define C_LONGTERMMEMORY_H
#include <c_Sentence.h>
#include <unordered_map>
#include <string>

class c_LongTermMemory : public c_Sentence
{
    public:
        c_LongTermMemory();
        virtual ~c_LongTermMemory();
        c_LongTermMemory(const c_LongTermMemory& other);

    protected:

    private:
        unordered_map <int,string> SentenceStorage;
        unordered_map <int,string>::iterator ssIT;


    public:


        void SaveSentenceInLongTermMemory(string strData){
             SentenceStorage.emplace(Tokenize(strData),strData);
        }

        int  GetNumberOfSentencesSaved(){
             return SentenceStorage.size();
        }
};

#endif // C_LONGTERMMEMORY_H
