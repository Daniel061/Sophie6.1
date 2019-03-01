#ifndef C_CEREBELLUM_H
#define C_CEREBELLUM_H

#include <c_Cortex.h>


class c_Cerebellum : public c_Cortex
{
    public:
        c_Cerebellum();
        virtual ~c_Cerebellum();

    protected:

    private:
         int    LocalAdjectiveLocation   = 0;
         int    LocalAdverbLocation      = 0;
         int    LocalNamePointer         = 0;
         int    LocalVerbLocation        = 0;
         int    LocalNounCount           = 0;
         int    LocalUnknownCount        = 0;
         int    LocalUnderstandingLevel  = 0;
         int    LocalWordCount           = -1;
         int    LocalConfidenceLevel     = 0;
         int    LocalUnderstandingDegree = 0;
         int    LocalAltLocation         = -1;
         int    QuoteMarker              = -1;
         float  LocalUnderstandingRatio  = 0.0;
         string LocalPattern             = "";
         string LocalWordCopy            = "";
         char   LocalAlternateType       = 'u';
         char   LocalGenderClass         = 'u';
         char   LocalWordType            = 'u';
         char   MemoryWordType           = 'u';
         char   SentenceWordType         = 'u';
         char   SelectedWordType         = 'u';
         bool   LocalBoolFlag            = false;
         bool   LocalContractionFlag     = false;
         bool   LocalHasAlternateType    = false;
         bool   Result                   = false;

         void InitializeAll(){
                 LocalGenderClass         = 'u';
                 LocalAdjectiveLocation   = -1;
                 LocalAdverbLocation      = -1;
                 LocalNamePointer         = -1;
                 LocalVerbLocation        = -1;
                 LocalAltLocation         = -1;
                 LocalNounCount           = 0;
                 LocalWordCount           = -1;
                 LocalUnknownCount        = 0;
                 LocalUnderstandingLevel  = 0;
                 LocalUnderstandingRatio  = 0.0;
                 LocalUnderstandingDegree = 0;
                 QuoteMarker              = -1;
                 LocalPattern             = "";
                 LocalWordCopy            = "";
                 SentenceWordType         = 'u';
                 LocalWordType            = 'u';
                 MemoryWordType           = 'u';
                 SelectedWordType         = 'u';
                 LocalAlternateType       = 'u';
                 LocalBoolFlag            = false;
                 LocalHasAlternateType    = false;
                 Result                   = false;
                 LocalContractionFlag     = false;}

public:

        //*********call this after c_sentence.h::parse() has been run***********************

    int GatherAndSetAllSentenceData(){
        if(Verbose)
            cout << "[c_Cerebellum.h::GatherAndSetAllSentenceData()]\n";
        InitializeAll();
        LocalWordCount     = GetFromSentenceWordCount();
        //check for empty sentence
        if(LocalWordCount == 0) return -1;

        for (int x = 0; x <= LocalWordCount; x++) FindWordType(GetswWordsLC(x),x);
        FindSubject();
        FindAndSetGistOfSentence();


        //*******NOTE: c_Language.h::FindWordType() sets the follow in c_Sentence.h private variables
        //     bool   IsQuestion
        //     bool   HasPluralPronoun
        //     bool   HasGenderReference
        //     bool   HasGreetingsWord
        // ::FindSubject() sets the following in c_Sentence.h private variables
        //     int    SubjectLocation
        // c_Sentence.h sets the rest of the private variables except
        //     int    IndirectObjectLocation (Set by FindSubject())
        //     int    AdverbLocation (SET HERE)
        //     int    AdjectiveLocation (SET HERE)
        //     int    NounCount  (SET HERE)
        //     int    VerbLocation (SET HERE)
        //     int    NamePointer  (SET HERE)
        //     string Pattern   (SET HERE) c_Sentence.h can rebuild Pattern
        //     char   WordType[]  (SET HERE) / checked against Memorycell and Sentence
        //     char   GenderClassInSentence[] (SET HERE)
        //     bool   HasContraction (SET HERE)
        //     int    sDaysOld (SET HERE)
        //     int    sUnderstandingLevel (SET HERE)

        for(int x = 0; x  <= LocalWordCount-1; x++){                                //***First try to set wordtype
            LocalWordType    = FindWordType(GetswWordsLC(x),x);                       //Get Wordtype from language helper, receives 'u' if can't determine
            MemoryWordType   = GetMemoryCellcharWordType(GetswWordsLC(x),Result);     //Get Wordtype from memory cell, receives NULL if doesn't exist, else returns CellWordType
            SentenceWordType = GetswWordType(x);                                      //Get Wordtype from c_sentence
            LocalWordCopy    = GetswWords(x);                                         //Get a copy of the word

            if(MemoryWordType == '\0') MemoryWordType = 'u';

            if(MemoryWordType == 'u'){                                              //Nothing in memory cell
                SelectedWordType = LocalWordType;}                                  //  -use type from language helper, could still be 'u'
            else
                if(MemoryWordType == LocalWordType){
                    SelectedWordType = LocalWordType;
                    }
                    else
                        if((MemoryWordType == 'u') && ( LocalWordType != 'u')){     //Use LocalWordType
                            SelectedWordType = LocalWordType;
                            }
                            else
                                if((MemoryWordType != 'u') &&
                                (LocalWordType != 'u') &&
                                (MemoryWordType != LocalWordType)){
                                   //cout << "Disagreement!\n";
                                  //disagreement here!!!                            //We have a disagreement here between memory cell wordtype and language helper
                                   LocalHasAlternateType = true;
                                   LocalAlternateType    = LocalWordType;           //Save for alternate type storage
                                   LocalAltLocation      = x;                       //save x for storage function   ***Possible double disagreement******
                                   SelectedWordType      = MemoryWordType;}         // use memory type for now ****NEEDS REVIEW*****
                                    else
                                        if(SentenceWordType != 'u'){
                                            SelectedWordType = SentenceWordType;}   //use c_Sentence wordtype
                                                else
                                                {
                                                 SelectedWordType = MemoryWordType; //Use MemoryWordType because language helper did not help
                                                }

         QuoteMarker = LocalWordCopy.find('\'');                                    //check for contraction
         if(QuoteMarker >=0) SelectedWordType = 'C';                                //Mark the word type

         LocalPattern += SelectedWordType;                                          //build the pattern as we go
         SetswWordType(SelectedWordType,x);                                         //set the selected word type in the sentence
         if(SelectedWordType == 'n') LocalNounCount++;                              //count the nouns
         if(SelectedWordType == 'v') LocalVerbLocation = x;                         //save the verb location
         if(SelectedWordType == 'g') LocalNamePointer = x;                          //save the name pointer
         if(SelectedWordType == 'A') LocalAdverbLocation = x;                       //save the Adverb location
         if(SelectedWordType == 'a') LocalAdjectiveLocation = x;                    //save the adjective location
         if(SelectedWordType == 'C') LocalContractionFlag = true;                   //mark has contraction
         if(SelectedWordType == 'c') SetInSentenceConjunctionLocation(x);           //save the conjunction location

         LocalGenderClass = GetMemoryCellcharGenderClass(GetswWordsLC(x),Result);     //take care of GenderClass in sentence
         if(LocalGenderClass != 'u')
            SetswGenderClassInSentence(x,LocalGenderClass);

        SetswWordType(SelectedWordType,x);                                            //update word type in sentence class
        } //END of for loop to scan sentence

        SetInSentenceAdjectiveLocation(LocalAdjectiveLocation);                               //store  ADJECTIVE LOCATION in c_Sentence
        SetInSentenceAdverbLocation(LocalAdverbLocation);                                     //store  ADVERB LOCATION in c_Sentence
        SetInSentenceNamePointer(LocalNamePointer);                                           //store  NAME POINTER in c_Sentence
        SetInSentenceVerbLocation(LocalVerbLocation);                                         //store  VERB LOCATION in c_Sentence
        SetInSentenceNounCount(LocalNounCount);                                               //store  NOUN COUNT in c_Sentence
        if(LocalHasAlternateType){
            SetswAlternateType(LocalAlternateType,LocalAltLocation);                          //store in c_Sentence
        }
        SetInSentenceHasContraction(LocalContractionFlag);                                    //Store contraction flag
        SetInSentenceSentenceDirection(DetermineDirectionOfPhrase());                         //Store phrase/question direction in sentence data
        SetInSentencesDaysOld(GetDaysSinceDate());                                            //day stamp this sentence
        LocalPattern = PatternReview(LocalPattern,LocalConfidenceLevel);                      //Check for corrections
        SetInSentencePattern(LocalPattern);                                                   //store in c_Sentence

        for (int x = 0; x < int(LocalPattern.size()); x++ ){                                  //for calc in understanding level
            if(LocalPattern[x] == 'u')
              LocalUnknownCount ++;
            else
              LocalUnderstandingLevel ++;
        }

            if(LocalUnderstandingLevel > 0)
                LocalUnderstandingRatio = float(LocalUnderstandingLevel) / float(GetFromSentenceWordCount());

            ///Set the understanding degree weighted with the ratio
            if(LocalUnderstandingRatio == 1) LocalUnderstandingDegree = 100;
             else
                if(LocalUnderstandingRatio >= .75) LocalUnderstandingDegree = 75;
             else
                if(LocalUnderstandingRatio >= .50) LocalUnderstandingDegree = 50;
             else
                if(LocalUnderstandingRatio >= .25) LocalUnderstandingDegree = 25;
             else
                if(LocalUnderstandingRatio >= .10) LocalUnderstandingDegree = 10;
             else
                LocalUnderstandingDegree = 0;

         SetInSentencesUnderstandingLevel(LocalUnderstandingDegree);                          //store the understanding degree for c_Cortex to use

         //Pull from memory cells and set all word data


         for(int x =0; x <= LocalWordCount; x++){
          for(int y = 0; y < GetMemoryCellNumberOfAdjectives(GetswWordsLC(x),Result); y++){
            SetswAdjectiveToWord(x,GetMemoryCellAdjectiveFromList(GetswWordsLC(x),y,Result));}
          for(int y = 0; y < GetMemoryCellNumberOfAdVerbs(GetswWordsLC(x),Result); y++){
            SetswAdverbToWord(x,GetMemoryCellAdverbFromList(GetswWordsLC(x),y,Result));}
          for(int y = 0; y < GetMemoryCellNumberOfVerbs(GetswWordsLC(x),Result); y++){
            SetswVerbToWord(x,GetMemoryCellVerbFromList(GetswWordsLC(x),y,Result));}
          for(int y = 0; y < GetMemoryCellNumberOfRelatedNouns(GetswWordsLC(x),Result); y++){
            SetswNounToWord(x,GetMemoryCellNounFromList(GetswWordsLC(x),y,Result));}
          for(int y = 0; y < GetMemoryCellMiniDefinitionCount(GetswWordsLC(x),Result); y++){
            SetswMiniDefinition(x,GetMemoryCellMiniDef(GetswWordsLC(x),Result,y));}

          SetswSingularForm(x,GetMemoryCellpSingularForm(GetswWordsLC(x)));
          SetswPossessiveRootType(x,GetMemoryCellPossessiveRootType(GetswWordsLC(x),Result));
          SetswPossessiveRoot(x,GetMemoryCellPossessiveRoot(GetswWordsLC(x),Result));
          SetswisSingularPossessive(x,GetMemoryCellIsSingularPossessive(GetswWordsLC(x),Result));
          SetswisPluralPossessive(x,GetMemoryCellIsPluralPossessive(GetswWordsLC(x),Result));
          SetswContractionLongFormFirst(x,GetMemoryCellContractionFirst(GetswWordsLC(x),Result));
          SetswContractionLongFormSecond(x,GetMemoryCellContractionSecond(GetswWordsLC(x),Result));
          //SetswSubWords(x,Getmemorycellsubwords)
          //SetPluralWordFlag(x,Getmemorycell)   correct this all the way to memory cell
          SetswPluralRoot(x,GetMemoryCellpSingularForm(GetswWordsLC(x)));
          //SetIsPluralWord(x,Getmemorycell)   memory cell doesn't agree with this type
          //Finish all word data transfer
         }//end of all words for loop

         ImplyUnknowns();                                                           //let language try to set some unknowns

        return LocalWordCount;                                                      //finished

    }
//----------------------------------END GATHER AND SET ALL SENTENCE DATA--------------------------------

 //---------------------------------Determine Direction of Phrase---------------------------------------------

    int DetermineDirectionOfPhrase(){
        if(Verbose)
            cout << "[c_Cerebellum.h::DetermineDirectionOfPhrase()]\n";

        //Direction ID
        //  0  - To the Program
        //  1  - To the User
        //  2  - To another pronoun, i.e they them he him she her it we
        //  3  - First word Question
        //  4  - name word used in phrase i.e. name set or request
        //  5  - data miner, i.e. who is
        //  6  - general statement
        // -1  - Direction not determined

        int    DirectionDetected    = -1;
        int    PatternMatch         = -1;
        string WorkingPattern       = GetFromSentencePattern();
        string cSentenceDirection   = "muYPMGx";

        for(int x =0; x<= GetFromSentenceWordCount(); x++){
            if((GetswWordType(x)== 'm')&&(DirectionDetected == -1)){ DirectionDetected = 0;}        //mentioned me, so to me
             else
                if((GetswWordType(x)=='y')&&(DirectionDetected == -1)) DirectionDetected = 1;       //user mentioned self, so to user
                  else
                    if((GetswWordType(x)=='B')&&(DirectionDetected == -1)) DirectionDetected = 2;}  //user used a pronoun

        if(GetswWordType(0) == 'v'){
            if( (GetswWordsLC(0)=="is") || (GetswWordsLC(0)=="can") || (GetswWordsLC(0)== "will") || (GetswWordsLC(0)=="are") || (GetswWordsLC(0)== "do") || (GetswWordsLC(0)=="would") ){
                DirectionDetected = 3;}}                                                          //most likely a question

        PatternMatch = WorkingPattern.find('g');
        if(PatternMatch >=0) DirectionDetected = 4;                                               //user mentioned 'name' in statement

        PatternMatch = WorkingPattern.find("vmv");      //i.e. do you know
        if (PatternMatch >=0){
            DirectionDetected = 0;}
        PatternMatch = WorkingPattern.find("qdnv") + WorkingPattern.find("qvdn") + 1;
        if (PatternMatch >= 0){
            DirectionDetected = 2;}
        if(GetswWordsLC(0) == "who"){
            DirectionDetected = 5;}                                                               //data miner, i.e. who fell down

        if(Verbose)
            cout << "   Direction of Phrase Detected:" << DirectionDetected << endl;
        return DirectionDetected;
    }

//-------------------------------END DETERMINE DIRECTION OF PHRASE------------------------------------------
};

#endif // C_CEREBELLUM_H
