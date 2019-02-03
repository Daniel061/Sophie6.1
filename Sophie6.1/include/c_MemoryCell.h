#ifndef C_MEMORYCELL_H
#define C_MEMORYCELL_H
#include <string>
#include <map>
#include <iostream>

using namespace std;
class c_MemoryCell
{
    public:
        c_MemoryCell();
        virtual ~c_MemoryCell();

    protected:

    private:
        string pCellData;                        // the raw data
        string pCellDataLC;                      // raw data in lower case
        string pGivenName;                       // if this noun or proper noun has a given name
        string pCellMiniDefinition;              // a short string defining this data
        string pCellContractionLongFormFirst;    // i.e. he's to he
        string pCellContractionLongFormSecond;   // i.e. he's to is
        char pCellPurpose;                       // s-sentence w-word r-response m-memory
        char pWordType;                          // n-noun v-verb p-pronoun a-adjective d-determiner(the) r-subject representative(it that) u-unknown c-connecting word(and)  C(cap) Contraction word
                                                 // n-noun p-pronoun v-verb q-question word a-adjective r-subject replacement P(cap) ProperNoun i.e. name A(cap) Adverb D(cap) Direct Object I(LC) Indirect object
                                                 // s - plural possessive  X(cap) Directive j-joining word
                                                 // initialize to 'u'
        char pWordTense;                         // p-past c-present f-future s-plural
                                                 // the decision on this word type is made elsewhere
        char pSecondaryType;                     // Could be used as another type i.e. light-n light red - A box is light -a
        char pAlternateType;                     // some words without modification could have a third type (All type references conform to pWordType definitions)
        char pGenderClass;                       // n - neutral e- either m - male only f - female only u - undefined
        bool pIsRoot;                            // the root of a word
        bool pIsSet;                             // Has been set with data before
        char pCellIsSingular;                    // p = plural s = singular u = undefined
        int  pSingularLocation;                  // if CellIsSingular = p, this points to the memorycell containing the singular version
        int  pNextVerb;                          // pointer to next verb
        int  pNextNoun;                          // pointer to next noun
        int  pToken;                             // the token value of this data
        int  pPointerToNextPattern;              // if used as pattern storage, points to constructed pattern or to self if final construction form
        multimap<int,int> adjDescriptors;        // storage of adjectives                        (Adjective,token)
        multimap<int,int> verbDescriptors;       // storage of verbs associated with adjectives  (Verb,Adjective)
        multimap<int,int> advDescriptors;        // storage of adverbs associated with verbs     (Adverb,Adjective)
        map<int,string> RelatedNouns;            // storage of related nouns   i.e. dog,animal   (tokenized related noun,related noun)
        multimap<int,int>::iterator mapIT;       // pointer for  int maps
        multimap<int,string>::iterator strIT;    // pointer for string maps



    public:
        string GetpCellContractionLongFormFirst(){return pCellContractionLongFormFirst;}
        string GetpCellContractionLongFormSecond(){return pCellContractionLongFormSecond;}
        void   SetpCellContractionLongFormFirst(string newVal){pCellContractionLongFormFirst = newVal;}
        void   SetpCellContractionLongFormSecond(string newVal){pCellContractionLongFormSecond = newVal;}
        void   SetpCellMiniDefinition(string newData){pCellMiniDefinition=newData;}
        string GetpCellMiniDefinition(){return pCellMiniDefinition;}
        char   GetpCellIsSingular(){return pCellIsSingular;}
        void   SetpCellIsSingular(char newData){pCellIsSingular = newData;}
        int    GetpCellSingularLocation(){return pSingularLocation;}
        void   SetpCellSingularLocation(int newLocation){pSingularLocation = newLocation;}
        int    GetpCellPointerToNextPattern(){return pPointerToNextPattern;}
        void   SetpCellPointerToNextPattern(int NextPattern){pPointerToNextPattern = NextPattern;}
        char   GetpCellWordTense() {return pWordTense;}
        void   SetpCellWordTense(char newTense){pWordTense = newTense;}
        char   GetpCellSecondaryType(){return pSecondaryType;}
        void   SetpCellSecondaryType(char Type){pSecondaryType = Type;}
        char   GetpCellAlternateType(){return pAlternateType;}
        void   SetpCellAlternateType(char Type){pAlternateType = Type;}
        string GetpCellDataString(){return pCellData;}
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
        bool   GetpCellIsSet() {return pIsSet;}
        void   SetpCellIsSet(bool newVal){pIsSet = newVal;}
        void   SetpCellGenderClass(char NewClass){pGenderClass = NewClass;}
        char   GetpCellGenderClass(){return pGenderClass;}
        string GetpCellGivenName(){return pGivenName;}
        void   SetpCellGivenName(string NewName){pGivenName = NewName;}
        void   SetpCellDataString(string NewData){pCellData = NewData; pIsSet = true;}

        void InitializeAll(){
                pCellIsSingular                 = 'u';
                pWordTense                      = 'u';
                pCellData                       = "";
                pCellDataLC                     = "";
                pGivenName                      = "";
                pCellMiniDefinition             = "";
                pCellContractionLongFormFirst   = "";
                pCellContractionLongFormSecond  = "";

                pCellPurpose                    = 'u'; //undefined
                pWordType                       = 'u';
                pIsRoot                         = false;
                pNextVerb                       = 0;
                pNextNoun                       = 0;
                pToken                          = 0;
                pIsSet                          = false;
                pGenderClass                    = 'u';
                pSecondaryType                  = 'u';
                pAlternateType                  = 'u';
                advDescriptors.clear();
                verbDescriptors.clear();
                adjDescriptors.clear();
                RelatedNouns.clear();
                pPointerToNextPattern           = 0;
                pSingularLocation               = 0;
        }


       void AssociateAdjectiveInMap(string AdjectiveToAssociate){
           if(adjDescriptors.find(Tokenize(AdjectiveToAssociate)) == adjDescriptors.end())
            adjDescriptors.emplace(Tokenize(AdjectiveToAssociate),pToken);
       }

//       void AssociateNounInMap(string NounToAssociate){
//           if(RelatedNouns.find(Tokenize(NounToAssociate)) == RelatedNouns.end())
//            RelatedNouns.emplace(Tokenize(NounToAssociate),pToken);
//       }
       void AssociateNounInMap(string NounToAssociate){
           //cout << "Storing " << NounToAssociate << " to " << pCellData << endl;
            RelatedNouns.emplace(Tokenize(NounToAssociate),NounToAssociate);
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
            strIT = RelatedNouns.begin();
            for(int x = 0; x < Location; x++) ++strIT;

            if(strIT == RelatedNouns.end()){
                return -1;}
                else
                    return Tokenize(strIT->second);
       }


       bool IsNounRelatedToMe(string NounToCheck){
           strIT = RelatedNouns.find(Tokenize(NounToCheck));
           if(strIT == RelatedNouns.end()) return false;
           else return true;}

       bool IsAdjectiveAssociatedToMe(string AdjectiveToCheck){
           mapIT = adjDescriptors.find(Tokenize(AdjectiveToCheck));
           if(mapIT == adjDescriptors.end()) return false;
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
