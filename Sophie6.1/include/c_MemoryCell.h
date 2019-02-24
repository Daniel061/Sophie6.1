#ifndef C_MEMORYCELL_H
#define C_MEMORYCELL_H
#include <string>
#include <map>
#include <iostream>
#include <unordered_set>

using namespace std;
class c_MemoryCell
{
    public:
        c_MemoryCell();
        virtual ~c_MemoryCell();

    protected:

    private:
        string pCellData;                          // the raw data
        string pCellDataLC;                        // the data in lower case
        string pGivenName;                         // if this noun or proper noun has a given name
        string pCellContractionLongFormFirst;      // i.e. he's to he
        string pCellContractionLongFormSecond;     // i.e. he's to is
        string pPossessiveRoot;                    // i.e. cat's = cat
        string pSingularForm;                      // i.e. cats  = cat
        string pResolvedPattern;                   // if used as pattern storage, contains constructed pattern or to self if final construction form
        char   pPossessiveRootType;                // usually a 'n' noun type but not always
        char   pCellPurpose;                       // s-sentence w-word r-response m-memory
        char   pWordType;                          // n-noun v-verb p-pronoun a-adjective d-determiner(the) r-subject representative(it that) u-unknown c-connecting word(and)  C(cap) Contraction word
                                                   // n-noun p-pronoun v-verb q-question word a-adjective r-subject replacement P(cap) ProperNoun i.e. name A(cap) Adverb D(cap) Direct Object I(LC) Indirect object
                                                   // s - plural possessive  X(cap) Directive j-joining word
                                                   // initialize to 'u'
        char   pWordTense;                         // p-past c-present f-future s-plural
                                                   // the decision on this word type is made elsewhere
        char   pSecondaryType;                     // Could be used as another type i.e. light-n light red - A box is light -a
        char   pAlternateType;                     // some words without modification could have a third type (All type references conform to pWordType definitions)
        char   pGenderClass;                       // n - neutral e- either m - male only f - female only u - undefined
        bool   pIsRoot;                            // the root of a word
        bool   pIsLocked;                          // this data is locked
        bool   pIsPluralPossessive;                // flag
        bool   pIsSingularPossessive;              // flag
        char   pCellIsSingular;                    // p = plural s = singular u = undefined
        int    pSingularLocation;                  // if CellIsSingular = p, this points to the memorycell containing the singular version
        int    pNextVerb;                          // pointer to next verb
        int    pNextNoun;                          // pointer to next noun
        int    pToken;                             // the token value of this data
        int    pDaysOld;                           // day stamp

        unordered_set <string> pCellMiniDefinition;// from GistOfSentence if this word was a subject
                                                   // can use list count as number of times used as subject

        unordered_set <string> adjectiveList;      // Adjective List for this word
        unordered_set <string> verbList;           // Verbs used with this word
        unordered_set <string> adverbList;         // Adverbs used with this word
        unordered_set <string> relatedNounList;    // Nouns related to this word
        unordered_set <string>::iterator SetIT;    // iterator for this set




    public:
        string GetpSingularForm(){return pSingularForm;}
        void   SetpSingularForm(string newVal){pSingularForm = newVal;}

        bool   GetpIsPluralPossessive(){return pIsPluralPossessive;}
        void   SetpIsPluralPossessive(bool newVal){pIsPluralPossessive = newVal;}

        bool   GetpIsSingularPossessive(){return pIsSingularPossessive;}
        void   SetpIsSingularPossessive(bool newVal){pIsSingularPossessive = newVal;}

        string GetpPossessiveRoot(){return pPossessiveRoot;}
        void   SetpPossessiveRoot(string newVal){pPossessiveRoot = newVal;}

        char   GetpPossessiveRootType(){return pPossessiveRootType;}
        void   SetpPossessiveRootType(char newVal){pPossessiveRootType = newVal;}

        string GetpCellContractionLongFormFirst(){return pCellContractionLongFormFirst;}
        string GetpCellContractionLongFormSecond(){return pCellContractionLongFormSecond;}
        void   SetpCellContractionLongFormFirst(string newVal){pCellContractionLongFormFirst = newVal;}
        void   SetpCellContractionLongFormSecond(string newVal){pCellContractionLongFormSecond = newVal;}

        void   SetpCellMiniDefinition(string newData){pCellMiniDefinition.emplace(newData);}
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

        int    GetpDaysOld(){return pDaysOld;}
        void   SetpDaysOld(int newVal){pDaysOld = newVal;}



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
                pPossessiveRootType             = 'u';
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
        }


       void AssociateAdjectiveInMap(string AdjectiveToAssociate){
           ///new set usage  Store ADJECTIVE
            adjectiveList.emplace(AdjectiveToAssociate);  //will not duplicate
       }


       void AssociateNounInMap(string NounToAssociate){
           ///new set usage Store NOUN
            relatedNounList.emplace(NounToAssociate);   //will not duplicate
       }


       void AssociateVerbToAdjectiveInMap(string AdjectiveToAssociate, string VerbToAssociate){
           ///new set usage Store VERB
           verbList.emplace(VerbToAssociate);           //will not duplicate
       }

       void AssociateAdverbToVerbInMap(string AdverbToAssociate,string VerbToAssociate){
           ///new set usage Store ADVERB
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

       string GetAdjectiveFromList(int Location){
            SetIT = adjectiveList.begin();
            for(int x = 0; x < Location; x++) ++SetIT;
            if(SetIT == adjectiveList.end())
                return "";
            else
                return *SetIT;}


       string GetVerbFromList(int Location){
            SetIT = verbList.begin();
            for(int x = 0; x < Location; x++) ++SetIT;
            if(SetIT == verbList.end())
                return "";
            else
                return *SetIT;}


       string GetAdverbFromList(int Location){
            SetIT = adverbList.begin();
            for(int x = 0; x < Location; x++) ++SetIT;
            if(SetIT == adverbList.end())
                return "";
            else
                return *SetIT;}


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
