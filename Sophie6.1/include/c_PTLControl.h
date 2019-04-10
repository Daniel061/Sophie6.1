#ifndef C_PTLCONTROL_H
#define C_PTLCONTROL_H
#include <string>
#include <vector>
#include <map>
#include <c_PTL.h>
#include <c_Sentence.h>


class c_PTLControl : public c_PTL
{
    public:
        c_PTLControl();
        virtual ~c_PTLControl();

    protected:

    private:
        c_Sentence                      PTLSentence;
        vector <string>                 PTLVectorData;
        vector <string>::iterator       PTLVectorIT;
        map    <string,c_PTL>           PTLMapData;
        map    <string,c_PTL>::iterator PTLMapIT;



    public:
        void ProcessPTLData(string NewSentence){


            PTLVectorIT = PTLVectorData.emplace(PTLVectorData.begin(),NewSentence);




        }
};

#endif // C_PTLCONTROL_H
