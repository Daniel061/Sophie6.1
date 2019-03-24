#ifndef C_MEMORYCELL_H
#define C_MEMORYCELL_H
#include <string>
#include <map>
#include <iostream>
#include <unordered_set>

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

extern bool Verbose;
using namespace std;
class c_MemoryCell
{
    public:
        c_MemoryCell();
        virtual ~c_MemoryCell();

    protected:

    private:
        string pCellData;                          // 1)  the raw data
        string pCellDataLC;                        // 2)  the data in lower case
        string pGivenName;                         // 3)  if this noun or proper noun has a given name
        string pCellContractionLongFormFirst;      // 4)  i.e. he's to he
        string pCellContractionLongFormSecond;     // 5)  i.e. he's to is
        string pPossessiveRoot;                    // 6)  i.e. cat's = cat
        string pSingularForm;                      // 7)  i.e. cats  = cat
        string pResolvedPattern;                   // 8)  if used as pattern storage, contains constructed pattern or to self if final construction form
        string pVowelPattern;                      // 9)  C- constant  V- vowel
        string pPresentTenseForm;                  // 10) threw = throw
        char   pPossessiveRootType;                // 11) usually a 'n' noun type but not always
        char   pCellPurpose;                       // 12) s-sentence w-word r-response m-memory
        char   pWordType;                          //     n-noun v-verb p-pronoun a-adjective d-determiner(the) r-subject representative(it that) u-unknown c-connecting word(and)  C(cap) Contraction word
                                                   //     n-noun p-pronoun v-verb q-question word a-adjective r-subject replacement P(cap) ProperNoun i.e. name A(cap) Adverb D(cap) Direct Object I(LC) Indirect object
                                                   //     s - plural possessive  X(cap) Directive j-joining word
                                                   //     initialize to 'u'
        char   pWordTense;                         // 13) p-past c-present f-future s-plural
                                                   //      the decision on this word type is made elsewhere
        char   pSecondaryType;                     // 14) Could be used as another type i.e. light-n light red - A box is light -a
        char   pAlternateType;                     // 15) some words without modification could have a third type (All type references conform to pWordType definitions)
        char   pGenderClass;                       // 16) n - neutral e- either m - male only f - female only u - undefined
        char   pPolarity;                          // 17) Positive/Negative
        bool   pIsRoot;                            // 18) the root of a word
        bool   pIsLocked;                          // 19) this data is locked
        bool   pIsPluralPossessive;                // 20) flag
        bool   pIsSingularPossessive;              // 21) flag
        char   pCellIsSingular;                    // 22) p = plural s = singular u = undefined
        int    pSingularLocation;                  // 23) if CellIsSingular = p, this points to the memorycell containing the singular version
        int    pNextVerb;                          // 24) pointer to next verb
        int    pNextNoun;                          // 25) pointer to next noun
        int    pToken;                             // 26) the token value of this data
        int    pDaysOld;                           // 27) day stamp
        int    pTimesUsedAsSubject;                // 28) Subject usage count, int to 0
        int    pTimesUsedAsIndirectObject;         // 29) Indirect object usage count, int to 0
        int    pTimesUsedAsDirectObject;           // 30) Direct Object usage count, int to 0
        int    pTimesUsedAsNoun;                   // 31) Noun usage count, int to 0
        int    pTimesUsedAsVerb;                   // 32) Verb usage count, int to 0
        int    pTimesUsedAsAdjective;              // 33) Adjective usage count, int to 0
        int    pTimesUsedAsAdverb;                 // 34) Adverb usage count, int to 0
        int    pTimesUsedAsPronoun;                // 35) Pronoun usage count, int to 0
        int    pTimesUsedAsPropernoun;             // 36) Propernoun usage count, int to 0



        unordered_set <string> pCellMiniDefinition;// 37) from GistOfSentence if this word was a subject
                                                   //      can use list count as number of times used as subject

        unordered_set <string> adjectiveList;      // 38) Adjective List for this word
        unordered_set <string> verbList;           // 39) Verbs used with this word
        unordered_set <string> adverbList;         // 40) Adverbs used with this word
        unordered_set <string> relatedNounList;    // 41) Nouns related to this word
        unordered_set <string>::iterator SetIT;    // Local iterator for these sets




    public:
        int    GetpTimesUsedAsSubject(){return pTimesUsedAsSubject;}
        void   IncrementpTimesUsedAsSubject(){pTimesUsedAsSubject++;}
        void   SetpTimesUsedAsSubject(int newVal){pTimesUsedAsSubject = newVal;}

        int    GetpTimesUsedAsIndirectObject(){return pTimesUsedAsIndirectObject;}
        void   IncrementpTimesUsedAsIndirectObject(){pTimesUsedAsIndirectObject++;}
        void   SetpTimesUsedAsIndirectObject(int newVal){pTimesUsedAsIndirectObject = newVal;}

        int    GetpTimesUsedAsDirectObject(){return pTimesUsedAsDirectObject;}
        void   IncrementpTimesUsedAsDirectObject(){pTimesUsedAsDirectObject++;}
        void   SetpTimesUsedAsDirectObject(int newVal){pTimesUsedAsDirectObject = newVal;}

        int    GetpTimesUsedAsNoun(){return pTimesUsedAsNoun;}
        void   IncrementpTimesUsedAsNoun(){pTimesUsedAsNoun++;}
        void   SetpTimesUsedAsNoun(int newVal){pTimesUsedAsNoun = newVal;}

        int    GetpTimesUsedAsVerb(){return pTimesUsedAsVerb;}
        void   IncrementpTimesUsedAsVerb(){pTimesUsedAsVerb++;}
        void   SetpTimesUsedAsVerb(int newVal){pTimesUsedAsVerb = newVal;}

        int    GetpTimesUsedAsAdjective(){return pTimesUsedAsAdjective;}
        void   IncrementpTimesUsedAsAdjective(){pTimesUsedAsAdjective++;}
        void   SetpTimesUsedAsAdjective(int newVal){pTimesUsedAsAdjective = newVal;}

        int    GetpTimesUsedAsAdverb(){return pTimesUsedAsAdverb;}
        void   IncrementpTimesUsedAsAdverb(){pTimesUsedAsAdverb++;}
        void   SetpTimesUsedAsAdverb(int newVal){pTimesUsedAsAdverb = newVal;}


        int    GetpTimesUsedAsPronoun(){return pTimesUsedAsPronoun;}
        void   IncrementpTimesUsedAsPronoun(){pTimesUsedAsPronoun++;}
        void   SetpTimesUsedAsPronoun(int newVal){pTimesUsedAsPronoun = newVal;}


        int    GetpTimesUsedAsPropernoun(){return pTimesUsedAsPropernoun;}
        void   IncrementpTimesUsedAsPropernoun(){pTimesUsedAsPropernoun++;}
        void   SetpTimesUsedAsPropernoun(int newVal){pTimesUsedAsPropernoun = newVal;}

        string GetpCellVowelPattern(){return pVowelPattern;}
        void   SetpCellVowelPattern(string newVal){pVowelPattern = newVal;}

        char   GetpCellPolarity(){return pPolarity;}
        void   SetpCellPolarity(char newVal){pPolarity = newVal;}

        string GetpCellSingularForm(){return pSingularForm;}
        void   SetpCellSingularForm(string newVal){pSingularForm = newVal;}

        bool   GetpCellIsPluralPossessive(){return pIsPluralPossessive;}
        void   SetpCellIsPluralPossessive(bool newVal){pIsPluralPossessive = newVal;}

        bool   GetpCellIsSingularPossessive(){return pIsSingularPossessive;}
        void   SetpCellIsSingularPossessive(bool newVal){pIsSingularPossessive = newVal;}

        string GetpCellPossessiveRoot(){return pPossessiveRoot;}
        void   SetpCellPossessiveRoot(string newVal){pPossessiveRoot = newVal;}

        char   GetpCellPossessiveRootType(){return pPossessiveRootType;}
        void   SetpCellPossessiveRootType(char newVal){pPossessiveRootType = newVal;}

        string GetpCellContractionLongFormFirst(){return pCellContractionLongFormFirst;}
        string GetpCellContractionLongFormSecond(){return pCellContractionLongFormSecond;}
        void   SetpCellContractionLongFormFirst(string newVal){pCellContractionLongFormFirst = newVal;}
        void   SetpCellContractionLongFormSecond(string newVal){pCellContractionLongFormSecond = newVal;}

        void   SetpCellMiniDefinition(string newData){if(newData != "") pCellMiniDefinition.emplace(newData);}
        string GetpCellMiniDefinition(int Which){
               SetIT = pCellMiniDefinition.begin();
               for(int x = 0; x<Which; x++) ++SetIT;
               if(SetIT != pCellMiniDefinition.end())
                return *SetIT;
               else
                return "";}
        int    GetpCellMiniDefinitionCount(){return pCellMiniDefinition.size(); }

        char   GetpCellIsSingular(){return pCellIsSingular;}
        void   SetpCellIsSingular(char newData){pCellIsSingular = newData;}

        int    GetpCellSingularLocation(){return pSingularLocation;}
        void   SetpCellSingularLocation(int newLocation){pSingularLocation = newLocation;}

        string GetpCellResolvedPattern(){return pResolvedPattern;}
        void   SetpCellResolvedPattern(string strPattern){pResolvedPattern = strPattern;}

        char   GetpCellWordTense() {return pWordTense;}
        void   SetpCellWordTense(char newTense){pWordTense = newTense;}

        char   GetpCellSecondaryType(){return pSecondaryType;}
        void   SetpCellSecondaryType(char Type){pSecondaryType = Type;}

        char   GetpCellAlternateType(){return pAlternateType;}
        void   SetpCellAlternateType(char Type){pAlternateType = Type;}

        string GetpCellDataString(){return pCellData;}
        void   SetpCellDataString(string NewData){pCellData = NewData; pIsLocked = true;}

        string GetpCellDataLC(){return pCellDataLC;}
        void   SetpCellDataLC(string newData){pCellDataLC=newData;}

        char   GetpCellPurpose(){return pCellPurpose;}
        void   SetpCellPurpose (char NewData){pCellPurpose = NewData;}

        char   GetpCellWordType(){return pWordType;}
        void   SetpCellWordType(char NewData){pWordType = NewData;}

        bool   GetpCellIsRoot(){return pIsRoot;}
        void   SetpCellIsRoot(bool NewVal){pIsRoot = NewVal;}

        int    GetpCellNextVerb(){return pNextVerb;}
        void   SetpCellNextVerb(int NewVal){pNextVerb = NewVal;}

        int    GetpCellNextNoun(){return pNextNoun;}
        void   SetpCellNextNoun(int loc){pNextNoun = loc;}

        void   SetpCellToken(int NewVal){pToken=NewVal;}
        int    GetpCellToken(){return pToken;}

        bool   GetpCellIsLocked() {return pIsLocked;}
        void   SetpCellIsLocked(bool newVal){pIsLocked = newVal;}

        void   SetpCellGenderClass(char NewClass){pGenderClass = NewClass;}
        char   GetpCellGenderClass(){return pGenderClass;}

        string GetpCellGivenName(){return pGivenName;}
        void   SetpCellGivenName(string NewName){pGivenName = NewName;}

        int    GetpCellDaysOld(){return pDaysOld;}
        void   SetpCellDaysOld(int newVal){pDaysOld = newVal;}

        string GetpCellPresentTenseForm(){return pPresentTenseForm;}
        void   SetpCellPresentTenseForm(string newVal){pPresentTenseForm = newVal;}



        void InitializeAll(){
                pCellIsSingular                 = 'u';
                pWordTense                      = 'u';
                pCellData                       = "";
                pCellDataLC                     = "";
                pGivenName                      = "";
                pCellContractionLongFormFirst   = "";
                pCellContractionLongFormSecond  = "";
                pPossessiveRoot                 = "";
                pSingularForm                   = "";
                pPresentTenseForm               = "";
                pPossessiveRootType             = 'u';
                pPolarity                       = 'u';
                pCellPurpose                    = 'u'; //undefined
                pWordType                       = 'u';
                pIsRoot                         = false;
                pNextVerb                       = 0;
                pNextNoun                       = 0;
                pToken                          = 0;
                pDaysOld                        = 0;
                pIsLocked                       = false;
                pIsPluralPossessive             = false;
                pIsSingularPossessive           = false;
                pGenderClass                    = 'u';
                pSecondaryType                  = 'u';
                pAlternateType                  = 'u';
                adjectiveList.clear();
                adverbList.clear();
                verbList.clear();
                relatedNounList.clear();
                pCellMiniDefinition.clear();
                pResolvedPattern                = "";
                pSingularLocation               = 0;
                pTimesUsedAsSubject             = 0;
                pTimesUsedAsIndirectObject      = 0;
                pTimesUsedAsDirectObject        = 0;
                pTimesUsedAsNoun                = 0;
                pTimesUsedAsVerb                = 0;
                pTimesUsedAsAdjective           = 0;
                pTimesUsedAsAdverb              = 0;
                pTimesUsedAsPronoun             = 0;
                pTimesUsedAsPropernoun          = 0;
        }


       void AssociateAdjectiveInMap(string AdjectiveToAssociate){
           ///new set usage  Store ADJECTIVE
            if(Verbose){
                cout << "[c_MemoryCell::AssociateAdjectiveInMap]\n";
                cout << "Associating " << pCellDataLC << " with " << AdjectiveToAssociate << " if not empty\n";}
            if(AdjectiveToAssociate != "")
                adjectiveList.emplace(AdjectiveToAssociate);  //will not duplicate
       }


       void AssociateNounInMap(string NounToAssociate){
           ///new set usage Store NOUN
           if(Verbose){
            cout << "[c_MemoryCell::AssociateNounInMap]\n";
            cout << "Associating " << pCellData << " with " << NounToAssociate << " if not empty\n";}
            if(NounToAssociate != "")
               relatedNounList.emplace(NounToAssociate);   //will not duplicate
       }


       void AssociateVerbInMap(string VerbToAssociate){
           ///new set usage Store VERB
           if(VerbToAssociate != "")
              verbList.emplace(VerbToAssociate);           //will not duplicate
       }

       void AssociateAdverbToVerbInMap(string AdverbToAssociate,string VerbToAssociate){
           ///new set usage Store ADVERB
           if(AdverbToAssociate != "")
              adverbList.emplace(AdverbToAssociate);      // will not duplicate
       }

       ///NEXT 4 FUNCTIONS USING NEW SET LIST
       int GetNumberOfAdjectivesInList(){
           return adjectiveList.size();}

       int GetNumberOfVerbsInList(){
           return verbList.size();}

       int GetNumberOfAdverbsInList(){
           return adverbList.size();}

       int GetNumberOfRelatedNounsInList(){
           return relatedNounList.size();}

       ///________________________________///
       /// USING NEW SET LIST
       string GetAdjectiveFromList(int Location){
            SetIT = adjectiveList.begin();
            for(int x = 0; x < Location; x++) ++SetIT;
            if(SetIT == adjectiveList.end())
                return "";
            else{
                if(Verbose)
                    cout << "[c_MemoryCell::GetAdjectiveFromList] Returned adjective:" << *SetIT << endl;
                return *SetIT;}}

       /// USING NEW SET LIST
       string GetVerbFromList(int Location){
            SetIT = verbList.begin();
            for(int x = 0; x < Location; x++) ++SetIT;
            if(SetIT == verbList.end())
                return "";
            else
                return *SetIT;}

       /// USING NEW SET LIST
       string GetAdverbFromList(int Location){
            SetIT = adverbList.begin();
            for(int x = 0; x < Location; x++) ++SetIT;
            if(SetIT == adverbList.end())
                return "";
            else
                return *SetIT;}

        /// USING NEW SET LIST
        string GetNounFromList(int Location){
            SetIT = relatedNounList.begin();
            for(int x = 0; x < Location; x++) ++SetIT;
            if(SetIT == relatedNounList.end())
                return "";
            else
                return *SetIT;}


       /// USING NEW SET LIST
       bool IsNounRelatedToMe(string NounToCheck){
           SetIT = relatedNounList.find(NounToCheck);
           if(SetIT == relatedNounList.end())
            return false;
           else
            return true;}


       /// USING NEW SET LIST
       bool IsAdjectiveAssociatedToMe(string AdjectiveToCheck){
           if(SetIT == adjectiveList.end())
            return false;
           else
            return true;}



        ///depreciated
        int Tokenize (string str_Data,bool ForceUpperCase = true)
        {
            int z          = str_Data.size();
            int y;
            int PlaceValue = 1;
            int tmpToken   = 0;
            int tmpHolder  = 0;

                if(ForceUpperCase){
                for( y = z; y > 0; y--){
                    tmpHolder  = int(toupper(str_Data[y-1]))-64; //'A' to 'Z'
                    if(tmpHolder <= 0) tmpHolder = str_Data[y-1];
                    tmpToken   = tmpToken + (tmpHolder*PlaceValue);
                    PlaceValue = PlaceValue * 10;}}
                  else {
                    for( y = z; y > 0; y--){
                    tmpHolder  = str_Data[y-1] - 64;
                    if(tmpHolder <= 0) tmpHolder = str_Data[y-1];
                    tmpToken   = tmpToken + (tmpHolder*PlaceValue);
                    PlaceValue = PlaceValue * 10;}
                  }

            return tmpToken;

        }
};

#endif // C_MEMORYCELL_H
