#ifndef C_MEMORYCELL_H
#define C_MEMORYCELL_H
#include <string>
#include <map>

using namespace std;
class c_MemoryCell
{
    public:
        c_MemoryCell();
        virtual ~c_MemoryCell();

    protected:

    private:
        string pCellData;                    // the raw data
        string pCellDataLC;                  // raw data in lower case
        string pGivenName;                   // if this noun or proper noun has a given name
        string pCellMiniDefinition;          // a short string defining this data
        char pCellPurpose;                   // s-sentence w-word r-response m-memory
        char pWordType;                      // n-noun v-verb p-pronoun a-adjective d-determiner(the) r-subject representative(it that) u-unknown c-connecting word(and)  C(cap) Contraction word
                                             // n-noun p-pronoun v-verb q-question word a-adjective r-subject replacement P(cap) ProperNoun i.e. name A(cap) Adverb D(cap) Direct Object I(LC) Indirect object
                                             // s - plural possessive  X(cap) Directive j-joining word
                                             // initialize to 'u'
        char pWordTense;                     // p-past c-present f-future s-plural
                                             // the decision on this word type is made elsewhere
        char pSecondaryType;                 // Could be used as another type i.e. light-n light red - A box is light -a
        char pAlternateType;                 // some words without modification could have a third type (All type references conform to pWordType definitions)
        char pGenderClass;                   // n - neutral e- either m - male only f - female only u - undefined
        bool pIsRoot;                        // the root of a word
        bool pIsSet;                         // Has been set with data before
        char pCellIsSingular;                // p = plural s = singular u = undefined
        int  pSingularLocation;              // if CellIsSingular = p, this points to the memorycell containing the singular version
        int  pNextVerb;                      // pointer to next verb
        int  pNextNoun;                      // pointer to next noun
        int  pToken;                         // the token value of this data
        int  pPointerToNextPattern;          // if used as pattern storage, points to constructed pattern or to self if final construction form
        multimap<int,int> adjDescriptors;    // storage of adjectives                        (Adjective,token)
        multimap<int,int> verbDescriptors;   // storage of verbs associated with adjectives  (Verb,Adjective)
        multimap<int,int> advDescriptors;    // storage of adverbs associated with verbs     (Adverb,Adjective)
        multimap<int,int> RelatedNouns;      // storage of related nouns   i.e. dog,animal   (Noun(this cell),related noun)
        multimap<int,int>::iterator mapIT;   // pointer for maps



    public:
        void   SetpCellMiniDefinition(string newData){pCellMiniDefinition=newData;}
        string GetpCellMiniDefinition(){return pCellMiniDefinition;}
        char   GetpCellIsSingular(){return pCellIsSingular;}
        void   SetpCellIsSingular(char newData){pCellIsSingular = newData;}
        int    GetpSingularLocation(){return pSingularLocation;}
        void   SetpSingularLocation(int newLocation){pSingularLocation = newLocation;}
        int    GetpPointerToNextPattern(){return pPointerToNextPattern;}
        void   SetpPointerToNextPattern(int NextPattern){pPointerToNextPattern = NextPattern;}
        char   GetpWordTense() {return pWordTense;}
        void   SetpWordTense(char newTense){pWordTense = newTense;}
        char   GetpSecondaryType(){return pSecondaryType;}
        void   SetpSecondaryType(char Type){pSecondaryType = Type;}
        char   GetpAlternateType(){return pAlternateType;}
        void   SetpAlternateType(char Type){pAlternateType = Type;}
        string GetpCellDataString(){return pCellData;}
        string GetpCellDataLC(){return pCellDataLC;}
        void   SetpCellDataLC(string newData){pCellDataLC=newData;}
        char   GetpCellPurpose(){return pCellPurpose;}
        void   SetpCellPurpose (char NewData){pCellPurpose = NewData;}
        char   GetpWordType(){return pWordType;}
        void   SetpWordType(char NewData){pWordType = NewData;}
        bool   GetpIsRoot(){return pIsRoot;}
        void   SetpIsRoot(bool NewVal){pIsRoot = NewVal;}
        int    GetpNextVerb(){return pNextVerb;}
        void   SetpNextVerb(int NewVal){pNextVerb = NewVal;}
        int    GetpNextNoun(){return pNextNoun;}
        void   SetpToken(int NewVal){pToken=NewVal;}
        int    GetpToken(){return pToken;}
        bool   GetpIsSet() {return pIsSet;}
        void   SetpGenderClass(char NewClass){pGenderClass = NewClass;}
        char   GetpGenderClass(){return pGenderClass;}
        string GetpGivenName(){return pGivenName;}
        void   SetpGivenName(string NewName){pGivenName = NewName;}
        void   SetpCellDataString(string NewData){pCellData = NewData; pIsSet = true;}

        void InitializeAll(){
                pCellIsSingular     = 'u';
                pWordTense          = 'u';
                pCellData           = "";
                pCellDataLC         = "";
                pGivenName          = "";
                pCellMiniDefinition = "";
                pCellPurpose        = 'u'; //undefined
                pWordType           = 'u';
                pIsRoot             = false;
                pNextVerb           = 0;
                pNextNoun           = 0;
                pToken              = 0;
                pIsSet              = false;
                pGenderClass        = 'u';
                pSecondaryType      = 'u';
                pAlternateType      = 'u';
                advDescriptors.clear();
                verbDescriptors.clear();
                adjDescriptors.clear();
                pPointerToNextPattern= 0;
                pSingularLocation    = 0;
        }


       void AssociateAdjectiveInMap(string AdjectiveToAssociate){
           if(adjDescriptors.find(Tokenize(AdjectiveToAssociate)) == adjDescriptors.end())
            adjDescriptors.emplace(Tokenize(AdjectiveToAssociate),pToken);
       }

       void AssociateNounInMap(string NounToAssociate){
           if(RelatedNouns.find(Tokenize(NounToAssociate)) == RelatedNouns.end())
            RelatedNouns.emplace(Tokenize(NounToAssociate),pToken);
       }

       void AssociateVerbToAdjectiveInMap(string AdjectiveToAssociate, string VerbToAssociate){
           if(verbDescriptors.find(Tokenize(AdjectiveToAssociate)) == verbDescriptors.end())
            verbDescriptors.emplace(Tokenize(AdjectiveToAssociate),Tokenize(VerbToAssociate));
       }

       void AssociateAdverbToVerbInMap(string AdverbToAssociate,string VerbToAssociate){
           if(advDescriptors.find(Tokenize(AdverbToAssociate)) == advDescriptors.end())
            advDescriptors.emplace(Tokenize(AdverbToAssociate),Tokenize(VerbToAssociate));
       }

       int GetNumberOfAdjectivesInMap(){
           return adjDescriptors.size();}

       int GetNumberOfVerbsInMap(){
           return verbDescriptors.size();}

       int GetNumberOfAdverbsInMap(){
           return advDescriptors.size();}

       int GetNumberOfRelatedNounsInMap(){
           return RelatedNouns.size();}

       int GetAdjectiveFromMap(int Location){
            mapIT = adjDescriptors.begin();
            for(int x = 0; x < Location; x++) ++mapIT;

            if(mapIT == adjDescriptors.end()){
                return -1;}
                else
                    return mapIT->first;
       }

       int GetVerbFromMap(int Location){
            mapIT = verbDescriptors.begin();
            for(int x = 0; x < Location; x++) ++mapIT;

            if(mapIT == verbDescriptors.end()){
                return -1;}
                else
                    return mapIT->first;
       }

        int GetAdverbFromMap(int Location){
            mapIT = advDescriptors.begin();
            for(int x = 0; x < Location; x++) ++mapIT;

            if(mapIT == advDescriptors.end()){
                return -1;}
                else
                    return mapIT->first;
       }

        int GetNounFromMap(int Location){
            mapIT = RelatedNouns.begin();
            for(int x = 0; x < Location; x++) ++mapIT;

            if(mapIT == RelatedNouns.end()){
                return -1;}
                else
                    return mapIT->first;
       }


       bool IsNounRelatedToMe(string NounToCheck){
           mapIT = RelatedNouns.find(Tokenize(NounToCheck));
           if(mapIT == RelatedNouns.end()) return false;
           else return true;}






        int Tokenize (string str_Data, bool ForceLowerCase=true)
        {
            int z;
            int y;
            int PlaceValue;
            int tmpToken;

                z = str_Data.size();
                PlaceValue = 1;
                tmpToken = 0;
                if(ForceLowerCase){
                    for( y = z; y > 0; y--){
                    tmpToken = tmpToken + (int(tolower(str_Data[y-1])))*PlaceValue;
                    PlaceValue ++;}
                }
                else{
                for( y = z; y > 0; y--){
                    tmpToken = tmpToken + (int(str_Data[y-1]))*PlaceValue;
                    PlaceValue ++;}}
            return tmpToken;

        }
};

#endif // C_MEMORYCELL_H
