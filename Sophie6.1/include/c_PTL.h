#ifndef C_PTL_H
#define C_PTL_H
#include <string>
using namespace std;
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

//[P] Pattern [T] Tracking and [L] Learning class
class c_PTL
{
    public:
        c_PTL();
        virtual ~c_PTL();

    protected:

    private:
        string    OriginalSentence;             // raw data
        string    BeginningPattern;             // starting point for pattern work
        string    NextPattern;                  // next step in processing
        string    RelatedPattern;               // a similar pattern path
        string    RelatedSentence;              // a similar sentence
        string    ComparisonResult;             // the product of the compare routine
        bool      FinalPattern;                 // this is the end of a dendrite




    public:
        void  InitializeAll(){
                  BeginningPattern    =  "";    // (1)
                  NextPattern         =  "";    // (2)
                  RelatedPattern      =  "";    // (3)
                  FinalPattern        =  false; // (4)

        }

        //Standard Sets/Gets

        string GetPTLComparisonResult(){return ComparisonResult;}
        void   SetPTLComparisonResult(string newVal){ComparisonResult = newVal;}

        string GetPTLRelatedSentence(){return RelatedSentence;}
        void   SetPTLRelatedSentence(string newVal){RelatedSentence = newVal;}

        string GetPTLOriginalSentence(){return OriginalSentence;}
        void   SetPTLOriginalSentence(string newVal){OriginalSentence = newVal;}

        string GetPTLBeginningPattern(){return BeginningPattern;}
        void   SetPTLBeginningPattern(string newVal){BeginningPattern = newVal;}

        string GetPTLNextPattern(){return NextPattern;}
        void   SetPTLNextPattern(string newVal){NextPattern = newVal;}

        string GetPTLRelatedPattern(){return RelatedPattern;}
        void   SetPTLRelatedPattern(string newVal){RelatedPattern = newVal;}

        bool   GetPTLFinalPattern(){return FinalPattern;}
        void   SetPTLFinalPAtterm(bool newVal){FinalPattern = newVal;}

};

#endif // C_PTL_H
