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
        LocalWordCount     = GetWordCount();
        //check for empty sentence
        if(LocalWordCount == 0) return -1;

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
            LocalWordType    = FindWordType(GetWordsLC(x),x);                       //Get Wordtype from language helper, receives 'u' if can't determine
            MemoryWordType   = GetMemoryCellcharWordType(GetWordsLC(x),Result);     //Get Wordtype from memory cell, receives NULL if doesn't exist, else returns CellWordType
            SentenceWordType = GetWordType(x);                                      //Get Wordtype from c_sentence
            LocalWordCopy    = GetWords(x);                                         //Get a copy of the word

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
         SetWordType(SelectedWordType,x);                                           //set the selected word type in the sentence
         if(SelectedWordType == 'n') LocalNounCount++;                              //count the nouns
         if(SelectedWordType == 'v') LocalVerbLocation = x;                         //save the verb location
         if(SelectedWordType == 'g') LocalNamePointer = x;                          //save the name pointer
         if(SelectedWordType == 'A') LocalAdverbLocation = x;                       //save the Adverb location
         if(SelectedWordType == 'a') LocalAdjectiveLocation = x;                    //save the adjective location
         if(SelectedWordType == 'C') LocalContractionFlag = true;                   //mark has contraction
         if(SelectedWordType == 'c') SetConjunctionLocation(x);                     //save the conjunction location

         LocalGenderClass = GetMemoryCellcharGenderClass(GetWordsLC(x),Result);     //take care of GenderClass in sentence
         if(LocalGenderClass != 'u')
            SetGenderClassInSentence(x,LocalGenderClass);

        SetWordType(SelectedWordType,x);                                            //update word type in sentence class
        } //END of for loop to scan sentence

        SetAdjectiveLocation(LocalAdjectiveLocation);                               //store in c_Sentence
        SetAdverbLocation(LocalAdverbLocation);                                     //store in c_Sentence
        SetNamePointer(LocalNamePointer);                                           //store in c_Sentence
        SetVerbLocation(LocalVerbLocation);                                         //store in c_Sentence
        SetNounCount(LocalNounCount);                                               //store in c_Sentence
        if(LocalHasAlternateType){
            SetAlternateType(LocalAlternateType,LocalAltLocation);                  //store in c_Sentence
        }
        SetHasContraction(LocalContractionFlag);                                    //Store contraction flag
        SetSentenceDirection(DetermineDirectionOfPhrase());                         //Store phrase/question direction in sentence data
        SetsDaysOld(GetDaysSinceDate());                                            //day stamp this sentence
        LocalPattern = PatternReview(LocalPattern,LocalConfidenceLevel);            //Check for corrections
        SetPattern(LocalPattern);                                                   //store in c_Sentence

        for (int x = 0; x < int(LocalPattern.size()); x++ ){                       //for calc in understanding level
            if(LocalPattern[x] == 'u')
              LocalUnknownCount ++;
            else
              LocalUnderstandingLevel ++;
        }

            if(LocalUnderstandingLevel > 0)
                LocalUnderstandingRatio = float(LocalUnderstandingLevel) / float(GetWordCount());

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

         SetsUnderstandingLevel(LocalUnderstandingDegree);                          //store the understanding degree for c_Cortex to use

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
        string WorkingPattern       = GetPattern();
        string cSentenceDirection   = "muYPMGx";

        for(int x =0; x<= GetWordCount(); x++){
            if((GetWordType(x)== 'm')&&(DirectionDetected == -1)){ DirectionDetected = 0;}        //mentioned me, so to me
             else
                if((GetWordType(x)=='y')&&(DirectionDetected == -1)) DirectionDetected = 1;       //user mentioned self, so to user
                  else
                    if((GetWordType(x)=='B')&&(DirectionDetected == -1)) DirectionDetected = 2;}  //user used a pronoun

        if(GetWordType(0) == 'v'){
            if( (GetWordsLC(0)=="is") || (GetWordsLC(0)=="can") || (GetWordsLC(0)== "will") || (GetWordsLC(0)=="are") || (GetWordsLC(0)== "do") || (GetWordsLC(0)=="would") ){
                DirectionDetected = 3;}}                                                          //most likely a question

        PatternMatch = WorkingPattern.find('g');
        if(PatternMatch >=0) DirectionDetected = 4;                                               //user mentioned 'name' in statement

        PatternMatch = WorkingPattern.find("vmv");      //i.e. do you know
        if (PatternMatch >=0){
            DirectionDetected = 0;}
        PatternMatch = WorkingPattern.find("qdnv") + WorkingPattern.find("qvdn") + 1;
        if (PatternMatch >= 0){
            DirectionDetected = 2;}
        if(GetWordsLC(0) == "who"){
            DirectionDetected = 5;}                                                               //data miner, i.e. who fell down

        if(Verbose)
            cout << "   Direction of Phrase Detected:" << DirectionDetected << endl;
        return DirectionDetected;
    }

//-------------------------------END DETERMINE DIRECTION OF PHRASE------------------------------------------
};

#endif // C_CEREBELLUM_H
