#ifndef C_SUBJECTSTACK_H
#define C_SUBJECTSTACK_H

#include <vector>
#include<map>
#include <c_Sentence.h>
#include <c_SubjectData.h>

class c_SubjectStack :  public c_Sentence
{
    public:
        c_SubjectStack();
        virtual ~c_SubjectStack();
    private:

        int                                  Subjects[15];                           //These Subjects are tokenized words
        string                               strSubjects[15];
        string                               strTmpSubject;
        int                                  SubjectCount;
        int                                  tmpSubject;
        vector <int>                         SubjectStack;
        vector <string>                      strSubjectStack;
        vector <int>::iterator               stackIT;
        vector <string>::iterator            strStackIT;
        vector <string>                      strSentenceStack;
        map<int,c_SubjectData>               SubjectDataMap;                //<Tokenized string strSubject,c_SubjectData>
        map<int,c_SubjectData>::iterator     sbjDataIT;
        vector<int>::iterator                sbjOrderIT;
        vector<int>                          SubjectOrder;
        c_SubjectData                        WorkingsbjData;

    public:


        void SetSubjectInStack(int NewSubject,string strSubject,string OriginalString){
            stackIT = SubjectStack.begin();
            int FirstSubject = -1;
            if(SubjectStack.size()!= 0){
               FirstSubject = SubjectStack[0];}
            if(FirstSubject != NewSubject){
                SubjectStack.emplace(stackIT,NewSubject);
                strStackIT = strSubjectStack.begin();
                strSubjectStack.emplace(strStackIT,strSubject);
                strStackIT = strSentenceStack.begin();
                strSentenceStack.emplace(strStackIT,OriginalString);}
            //new version of SetSubjectInStack
            sbjDataIT = SubjectDataMap.find(Tokenize(strSubject));
            int Adjectives[30];
            int RelatedNouns[30];
            int adjCount,nounCount;
            //bool Result = false;
             if(sbjDataIT == SubjectDataMap.end()){
                WorkingsbjData.InitializeAllSubjectVariables();
                WorkingsbjData.SetsbjSubjectPhrase(GetFromSentenceOriginalString());
                WorkingsbjData.SetsbjSubjectStringOriginal(GetswWords(GetFromSentenceSubjectLocation()));
                WorkingsbjData.SetsbjSubjectStringLC(GetswWordsLC(GetFromSentenceSubjectLocation()));
                WorkingsbjData.SetsbjSubjectContractionLongFormFirst(GetswContractionLongFormFirst(GetFromSentenceSubjectLocation()));
                WorkingsbjData.SetsbjSubjectContractionLongFormSecond(GetswContractionLongFormSecond(GetFromSentenceSubjectLocation()));
                WorkingsbjData.SetsbjSubjectPatternResolved(GetFromSentencePattern());
                //WorkingsbjData.SetsbjSubjectPatternBeforeResolution(); //need this sent to me
                WorkingsbjData.SetsbjGenderClass(GetswGenderClassInSentence(GetFromSentenceSubjectLocation()));
                WorkingsbjData.SetsbjWordType(GetswWordType(GetFromSentenceSubjectLocation()));
                //WorkingsbjData.SetsbjWordTense(getWordTense); // needs to be added to c_Sentence and data storage
                WorkingsbjData.SetsbjIsSingular(GetswIsPluralWord(GetFromSentenceSubjectLocation()));
                WorkingsbjData.SetsbjIsContraction(GetswisContraction(GetFromSentenceSubjectLocation()));
                WorkingsbjData.SetsbjSingularLocation(Tokenize(GetswPluralRoot(GetFromSentenceSubjectLocation())));
                WorkingsbjData.SetsbjPhraseToken(Tokenize(GetFromSentenceOriginalString(),false));
                WorkingsbjData.SetsbjSubjectLocation(GetFromSentenceSubjectLocation());
                WorkingsbjData.SetsbjIndirectObjectLocation(GetFromSentenceIndirectObjectLocation());
                WorkingsbjData.SetsbjWordToken(GetswWordTokens(GetFromSentenceSubjectLocation()));
                adjCount  = GetMemoryCellAdjectives(GetswWordTokens(GetFromSentenceSubjectLocation()),Adjectives);
                nounCount = GetMemoryCellRelatedNouns(GetswWordTokens(GetFromSentenceSubjectLocation()),RelatedNouns);
                for(int x = 0; x< adjCount; x++){
                        ///***********************NEEDS FIXED************************************* remove tokens!!
                  //  WorkingsbjData.SetsbjAdjectiveInMap(GetMemoryCellRawStringData(Result,"",Adjectives[x]),Adjectives[x]);
                }
                for(int x = 0; x< nounCount; x++){
                  //  WorkingsbjData.SetsbjRelatedNounInMap(GetMemoryCellRawStringData(Result,"",RelatedNouns[x]),RelatedNouns[x]);
                }
                sbjDataIT = SubjectDataMap.begin();
                SubjectDataMap.emplace_hint(sbjDataIT,WorkingsbjData.GetsbjWordToken(),WorkingsbjData);
                sbjOrderIT = SubjectOrder.begin();
                SubjectOrder.insert(sbjOrderIT,GetswWordTokens(GetFromSentenceSubjectLocation()));
            }
            else{
                sbjDataIT->second.SetsbjSubjectPhrase(GetFromSentenceOriginalString());
                sbjDataIT->second.SetsbjSubjectStringOriginal(GetswWords(GetFromSentenceSubjectLocation()));
                sbjDataIT->second.SetsbjSubjectStringLC(GetswWordsLC(GetFromSentenceSubjectLocation()));
                sbjDataIT->second.SetsbjSubjectContractionLongFormFirst(GetswContractionLongFormFirst(GetFromSentenceSubjectLocation()));
                sbjDataIT->second.SetsbjSubjectContractionLongFormSecond(GetswContractionLongFormSecond(GetFromSentenceSubjectLocation()));
                sbjDataIT->second.SetsbjSubjectPatternResolved(GetFromSentencePattern());
                //sbjDataIT->second.SetsbjSubjectPatternBeforeResolution(); //need this sent to me
                sbjDataIT->second.SetsbjGenderClass(GetswGenderClassInSentence(GetFromSentenceSubjectLocation()));
                sbjDataIT->second.SetsbjWordType(GetswWordType(GetFromSentenceSubjectLocation()));
                // sbjDataIT->second.SetsbjWordTense(getWordTense); // needs to be added to c_Sentence and data storage
                sbjDataIT->second.SetsbjIsSingular(GetswIsPluralWord(GetFromSentenceSubjectLocation()));
                sbjDataIT->second.SetsbjIsContraction(GetswisContraction(GetFromSentenceSubjectLocation()));
                sbjDataIT->second.SetsbjSingularLocation(Tokenize(GetswPluralRoot(GetFromSentenceSubjectLocation())));
                sbjDataIT->second.SetsbjPhraseToken(Tokenize(GetFromSentenceOriginalString(),false));
                sbjDataIT->second.SetsbjSubjectLocation(GetFromSentenceSubjectLocation());
                sbjDataIT->second.SetsbjIndirectObjectLocation(GetFromSentenceIndirectObjectLocation());
                sbjDataIT->second.SetsbjWordToken(GetswWordTokens(GetFromSentenceSubjectLocation()));
                sbjDataIT->second.SetsbjSubjectCountPlusOne();
                adjCount  = GetMemoryCellAdjectives(GetswWordTokens(GetFromSentenceSubjectLocation()),Adjectives);
                nounCount = GetMemoryCellRelatedNouns(GetswWordTokens(GetFromSentenceSubjectLocation()),RelatedNouns);
                ///************************NEEDS FIXED  remove token based search*************************************
                for(int x = 0; x< adjCount; x++){
                  //  sbjDataIT->second.SetsbjAdjectiveInMap(GetMemoryCellRawStringData(Result,"",Adjectives[x]),Adjectives[x]);
                }
                for(int x = 0; x< nounCount; x++){
                  //  sbjDataIT->second.SetsbjRelatedNounInMap(GetMemoryCellRawStringData(Result,"",RelatedNouns[x]),RelatedNouns[x]);
                }
                sbjOrderIT = SubjectOrder.begin();
                if(*sbjOrderIT != GetswWordTokens(GetFromSentenceSubjectLocation())) //not already at the top
                   SubjectOrder.insert(sbjOrderIT,GetswWordTokens(GetFromSentenceSubjectLocation()));

            }


        }


        //Returns the tokenized subject string from the map
        //latest subject location = 0
        //returns -1 if nothing at 0 or the requested location
        int GetSubjectTokenInMap(int Location = 0){ // 0 = first
            if(int(SubjectOrder.size()) < Location){
                return -1;
            }
            else{
            sbjOrderIT = SubjectOrder.begin();
            sbjOrderIT += Location;
            if(sbjOrderIT != SubjectOrder.end()){
                return *sbjOrderIT;}
            else{
                return -1;
            }
            }
        }


        //Returns the subject string from the map
        //latest subject location = 0
        //returns empty string if nothing at 0 or the requested location
        string GetSubjectStringInMap(int Location = 0){ // 0 = first
            if (int(SubjectOrder.size()) < Location) {
                return "";
            }
            else {
            sbjOrderIT    = SubjectOrder.begin();
            for(int x = 0; x < Location; x++){
                    ++sbjOrderIT;}
            sbjDataIT     = SubjectDataMap.find(*sbjOrderIT);
            if(sbjDataIT != SubjectDataMap.end()){
                return sbjDataIT->second.GetsbjSubjectStringOriginal();
            }
            else{
                return "";
            }
            }
        }


        char GetSubjectWordType(int Location = 0){ // 0 = first
            if (int(SubjectOrder.size()) < Location) {
                return '\0';
            }
            else {
            sbjOrderIT    = SubjectOrder.begin();
            for(int x = 0; x < Location; x++){
                    ++sbjOrderIT;}
            sbjDataIT     = SubjectDataMap.find(*sbjOrderIT);
            if(sbjDataIT != SubjectDataMap.end()){
                return sbjDataIT->second.GetsbjWordType();
            }
            else{
                return '\0';
            }
            }
        }


        char GetSubjectGender(int Location = 0){ // 0 = first
            if (int(SubjectOrder.size()) < Location) {
                return '\0';
            }
            else {
            sbjOrderIT    = SubjectOrder.begin();
            for(int x = 0; x < Location; x++){
                    ++sbjOrderIT;}
            sbjDataIT     = SubjectDataMap.find(*sbjOrderIT);
            if(sbjDataIT != SubjectDataMap.end()){
                return sbjDataIT->second.GetsbjGenderClass();
            }
            else{
                return '\0';
            }
            }
        }


        //returns number of subjects in map
        int GetSubjectMapSize(){
            return SubjectOrder.size();
        }


        //returns number of adjectives for subject located at Location
        int GetSubjectAdjectiveCount(int Location = 0){
            if(int(SubjectOrder.size()) < Location) {
                return -1;
            }
            else {
                sbjOrderIT  = SubjectOrder.begin() + Location;
                sbjDataIT   = SubjectDataMap.find(*sbjOrderIT);
                if(sbjDataIT != SubjectDataMap.end()){
                    return sbjDataIT->second.GetsbjAdjectiveMapCount();
                }
                else{
                    return -1;
                }
            }
        }


        //returns number of nouns for subject located at Location
        int GetSubjectNounCount(int Location = 0){
            if(int(SubjectOrder.size()) < Location) {
                return -1;
            }
            else {
                sbjOrderIT  = SubjectOrder.begin() + Location;
                sbjDataIT   = SubjectDataMap.find(*sbjOrderIT);
                if(sbjDataIT != SubjectDataMap.end()){
                    return sbjDataIT->second.GetsbjRelatedNounsMapCount();
                }
                else{
                    return -1;
                }
            }
        }


        //Get adjectives for subject located at Location
        int GetSubjectAdjectives(string Adjectives[], int Location = 0){
            if(int(SubjectOrder.size()) < Location) {
                return -1;
            }
            else {
                sbjOrderIT  = SubjectOrder.begin() + Location;
                sbjDataIT   = SubjectDataMap.find(*sbjOrderIT);
                if(sbjDataIT != SubjectDataMap.end()){
                    return sbjDataIT->second.GetsbjAdjectivesFromMap(Adjectives);
                }
                else{
                    return -1;
                }
            }
        }


        //Get related nouns for subject located at Location
        int GetSubjectRelatedNouns(string Nouns[], int Location = 0){
            if(int(SubjectOrder.size()) < Location) {
                return -1;
            }
            else {
                sbjOrderIT  = SubjectOrder.begin() + Location;
                sbjDataIT   = SubjectDataMap.find(*sbjOrderIT);
                if(sbjDataIT != SubjectDataMap.end()){
                    return sbjDataIT->second.GetsbjRelatedNounsFromMap(Nouns);
                }
                else{
                    return -1;
                }
            }
        }


        //Get the subject count
        //returns -1 if subject not found
        int GetsbjSubjectCountInMap(int Location = 0){
            if(int(SubjectOrder.size()) < Location) {
                return -1;
            }
            else {
                sbjOrderIT  = SubjectOrder.begin() + Location;
                sbjDataIT   = SubjectDataMap.find(*sbjOrderIT);
                if(sbjDataIT != SubjectDataMap.end()){
                    return sbjDataIT->second.GetsbjSubjectCount();
                }
                else{
                    return -1;
                }
            }
        }
//------------------------------------old subject processing---------------------------------
        int GetSubjectInStack(int Location = 0){
            if(int(SubjectDataMap.size()) < Location){
                return -1;
            }
            else{
            stackIT = SubjectStack.begin()+Location;
            return *stackIT;}
        }



        string GetstrSubjectInStack(int Location){
            strStackIT = strSubjectStack.begin()+Location;
            return *strStackIT;
        }

        string GetOriginalStringInStack(int Location){
            return strSentenceStack[Location];
        }

        int GetSubjectStackCount(){
            return SubjectStack.size();
        }
};

#endif // C_SUBJECTSTACK_H
