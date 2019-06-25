#include "c_PTL.h"

c_PTL::c_PTL(string newData,string FirstPattern, int newWordCount, map <int,c_Word> WordMapCopy)
{
    OriginalSentence = newData;
    BeginningPattern = FirstPattern;
    WordCount        = newWordCount;
    LocalWordMap     = WordMapCopy;
    //ctor
}

c_PTL::~c_PTL()
{
    //dtor
}
