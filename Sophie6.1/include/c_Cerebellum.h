#ifndef C_CEREBELLUM_H
#define C_CEREBELLUM_H

#include <c_Cortex.h>

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
         int    LocalPastTenseWords      = -1;
         float  LocalUnderstandingRatio  = 0.0;
         string LocalPattern             = "";
         string LocalExtendedPattern     = "";
         string LocalWordCopy            = "";
         char   LocalAlternateType       = 'u';
         char   LocalGenderClass         = 'u';
         char   LocalWordType            = 'u';
         char   MemoryWordType           = 'u';
         char   SentenceWordType         = 'u';
         char   SelectedWordType         = 'u';
         bool   LocalBoolFlag            = false;
         bool   LocalHasAlternateType    = false;
         bool   LocalSentenceTense       = false;
         bool   Result                   = false;

         void InitializeAll(){
                 LocalGenderClass         = 'u';
                 LocalAdjectiveLocation   = -1;
                 LocalAdverbLocation      = -1;
                 LocalNamePointer         = -1;
                 LocalVerbLocation        = -1;
                 LocalAltLocation         = -1;
                 LocalPastTenseWords      = -1;
                 LocalNounCount           = 0;
                 LocalWordCount           = -1;
                 LocalUnknownCount        = 0;
                 LocalUnderstandingLevel  = 0;
                 LocalUnderstandingRatio  = 0.0;
                 LocalUnderstandingDegree = 0;
                 LocalPattern             = "";
                 LocalWordCopy            = "";
                 LocalExtendedPattern     = "";
                 SentenceWordType         = 'u';
                 LocalWordType            = 'u';
                 MemoryWordType           = 'u';
                 SelectedWordType         = 'u';
                 LocalAlternateType       = 'u';
                 LocalBoolFlag            = false;
                 LocalHasAlternateType    = false;
                 Result                   = false;
                 LocalSentenceTense       = false;}

public:

        //*********call this after c_sentence.h::parse() has been run***********************

    int GatherAndSetAllSentenceData(){
        if(Verbose)
            cout << "[c_Cerebellum.h::GatherAndSetAllSentenceData()]\n";

        InitializeAll();
        LocalWordCount               = GetFromSentenceWordCount();
        string LocalOriginalString   = GetFromSentenceOriginalString();
        string LocalExtendedWordType = "";
        string MemoryExtWordType     = "";
        //check for empty sentence
        if(LocalWordCount == 0) return -1;

        //*******NOTE: c_Language.h::FindWordType() sets the following in c_Sentence.h private variables
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

        for(int x = 0; x  <= LocalWordCount-1; x++){                                  //***First try to set wordtype

            LocalWordType     = FindWordType(GetswWordsLC(x),LocalExtendedWordType,x); //Get Wordtype from language helper, receives 'u' if can't determine
            MemoryWordType    = GetMemoryCellcharWordType(GetswWordsLC(x),Result);     //Get Wordtype from memory cell, receives NULL if doesn't exist, else returns CellWordType
            SentenceWordType  = GetswWordType(x);                                      //Get Wordtype from c_sentence
            MemoryExtWordType = GetMemoryCellpExtendedWordType(GetswWordsLC(x),Result);//Get memory cell extended word type
            LocalWordCopy     = GetswWords(x);                                         //Get a copy of the word

            //if(MemoryWordType == '\0') MemoryWordType = 'u';                      //removed due to redundancy

            if(MemoryWordType == typeUnknownWord){                                    //Nothing in memory cell
                SelectedWordType = LocalWordType;}                                    //  -use type from language helper, could still be 'u'
            else
                if(MemoryWordType == LocalWordType){
                    SelectedWordType = LocalWordType;
                    }
                    else
                        if((MemoryWordType == typeUnknownWord) && ( LocalWordType != typeUnknownWord)){     //Use LocalWordType
                            SelectedWordType = LocalWordType;
                            }
                            else
                                if((MemoryWordType != typeUnknownWord) &&
                                (LocalWordType != typeUnknownWord) &&
                                (MemoryWordType != LocalWordType)){
                                  if(Verbose){
                                   cout << "Disagreement!\n";
                                   cout << "MemmoryWordType=" << MemoryWordType << " LocalWordType=" << LocalWordType << " Working Word:" << GetswWords(x) << "\n";
                                   cout << "Sentence:" << GetFromSentenceOriginalString() << endl;}
                                  //disagreement here!!!                            //We have a disagreement here between memory cell wordtype and language helper
                                   LocalHasAlternateType = true;
                                   SelectedWordType      = MemoryWordType;          //MemoryWordType wins
                                   LocalExtendedWordType = MemoryExtWordType;       //Use Memory cell extended word type
                                   LocalAlternateType    = LocalWordType;           //Save for alternate type storage
                                   LocalAltLocation      = x;                       //save x for storage function   ***Possible double disagreement******
                                   }         // using FindWordType
                                    else
                                        if(SentenceWordType != typeUnknownWord){
                                            SelectedWordType = SentenceWordType;}   //use c_Sentence wordtype
                                                else
                                                {
                                                 SelectedWordType = MemoryWordType; //Use MemoryWordType because language helper did not help
                                                }

         if(SelectedWordType == typeProperNoun){
            if((GetswWords(x)[0] >= 'A') && (GetswWords(x)[0] <= 'Z')){
                //Proper Noun usage ok
            }
            else{
                SelectedWordType = typeNoun;
                //Proper Noun form not used this time
            }

         }

         LocalPattern += SelectedWordType;                                          //build the pattern as we go
         LocalExtendedPattern += LocalExtendedWordType + " ";                       //build the extended pattern
         SetswWordType(SelectedWordType,x);                                         //set the selected word type in the sentence
         SetswExtendedWordType(x,LocalExtendedWordType);                            //Set the extended word type in the sentence
         if(SelectedWordType == typeNoun) LocalNounCount++;                         //count the nouns
         if(SelectedWordType == typeVerb) LocalVerbLocation = x;                    //save the verb location
         if(SelectedWordType == typeAssociativeWord) LocalNamePointer = x;          //save the name pointer
         if(SelectedWordType == typeAdverb) LocalAdverbLocation = x;                //save the Adverb location
         if(SelectedWordType == typeAdjective) LocalAdjectiveLocation = x;          //save the adjective location
         if(SelectedWordType == typeConjunction) SetInSentenceConjunctionLocation(x);//save the conjunction location
         if(SelectedWordType == typePreposition) SetInSentenceHasPreposition(true); //flag preposition in sentence

         LocalGenderClass = GetMemoryCellcharGenderClass(GetswWordsLC(x),Result);   //take care of GenderClass in sentence
         if(LocalGenderClass != typeUnknownWord)
            SetswGenderClassInSentence(x,LocalGenderClass);

        SetswWordType(SelectedWordType,x);                                          //update word type in sentence class
        } //END of for loop to scan sentence
        if(Verbose)
            cout << "[GatherAndSet]:LocalPattern " << LocalPattern << endl;;

        SetInSentencePreProcessedPattern(LocalPattern);                             //store  first version of pattern if empty
        SetInSentencePattern(LocalPattern);                                         //store  pattern first time
        //TODO: Give this pattern version to c_PTL
        SetInSentenceAdjectiveLocation(LocalAdjectiveLocation);                     //store  ADJECTIVE LOCATION in c_Sentence
        SetInSentenceAdverbLocation(LocalAdverbLocation);                           //store  ADVERB LOCATION in c_Sentence
        SetInSentenceNamePointer(LocalNamePointer);                                 //store  NAME POINTER in c_Sentence
        SetInSentenceVerbLocation(LocalVerbLocation);                               //store  VERB LOCATION in c_Sentence
        SetInSentenceNounCount(LocalNounCount);                                     //store  NOUN COUNT in c_Sentence
        if(LocalHasAlternateType){
            SetswAlternateType(LocalAlternateType,LocalAltLocation);                //store in c_Sentence
        }
        SetInSentenceSentenceDirection(DetermineDirectionOfPhrase());               //Store phrase/question direction in sentence data
        SetInSentencesDaysOld(GetDaysSinceDate());                                  //day stamp this sentence
        //LocalPattern = PatternJoinerCheck(LocalPattern);
        //LocalPattern = PatternReview();                                             //Check for corrections
        //SetInSentencePattern(LocalPattern);                                         //store in c_Sentence
        //LocalPattern = PatternReview();                                             //Check for corrections   do this twice
        //SetInSentencePattern(LocalPattern);                                         //store in c_Sentence
        //ImplyUnknowns();                                                            //let language try to set some unknowns
        ReVerseBuildPattern();                                                      //push from pattern to word types
        FindAndSetGistOfSentence();                                                 //store gist,subgist and supportive phrase in sentence

        for (int x = 0; x < int(LocalPattern.size()); x++ ){                        //for calc in understanding level
            if(LocalPattern[x] == typeUnknownWord)
              LocalUnknownCount ++;
            else
              LocalUnderstandingLevel ++;

            if(GetswWordTense(x)=='p'){                                             //set sentence tense to past if one word tense is past
                LocalPastTenseWords++;}
        }//end for loop to scan pattern

            if(LocalPastTenseWords != -1){
                if(Verbose)
                   cout << "Setting sentence tense to past.\n";
                SetInSentencesSentenceTense('p');}
            else{
                if(Verbose)
                   cout << "Setting sentence tense to current.\n";
                SetInSentencesSentenceTense('c');}


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


         for(int x =0; x < LocalWordCount; x++){

          for(int y = 0; y < GetMemoryCellNumberOfAdjectives(GetswWordsLC(x),Result); y++){
            if (Verbose)
                cout << "Setting adjective " << GetMemoryCellAdjectiveFromList(GetswWordsLC(x),y,Result) << " to " << GetswWordsLC(x) << endl;
            SetswAdjectiveToWord(x,GetMemoryCellAdjectiveFromList(GetswWordsLC(x),y,Result));
            if (Verbose)
                cout << "Completed " << boolalpha << Result << endl;
          }

          for(int y = 0; y < GetMemoryCellNumberOfAdVerbs(GetswWordsLC(x),Result); y++){
            SetswAdverbToWord(x,GetMemoryCellAdverbFromList(GetswWordsLC(x),y,Result));}

          for(int y = 0; y < GetMemoryCellNumberOfVerbs(GetswWordsLC(x),Result); y++){
            SetswVerbToWord(x,GetMemoryCellVerbFromList(GetswWordsLC(x),y,Result));}

          for(int y = 0; y < GetMemoryCellNumberOfRelatedNouns(GetswWordsLC(x),Result); y++){
            SetswNounToWord(x,GetMemoryCellNounFromList(GetswWordsLC(x),y,Result));}

          for(int y = 0; y < GetMemoryCellMiniDefinitionCount(GetswWordsLC(x),Result); y++){
            SetswMiniDefinition(x,GetMemoryCellMiniDef(GetswWordsLC(x),Result,y));}

          //SetswSingularForm  Already taken care of in SetWordTypes
          SetswPossessiveRootType(x,GetMemoryCellPossessiveRootType(GetswWordsLC(x),Result));
          SetswPossessiveRoot(x,GetMemoryCellPossessiveRoot(GetswWordsLC(x),Result));
          SetswisSingularPossessive(x,GetMemoryCellIsSingularPossessive(GetswWordsLC(x),Result));
          SetswisPluralPossessive(x,GetMemoryCellIsPluralPossessive(GetswWordsLC(x),Result));
          SetswContractionLongFormFirst(x,GetMemoryCellContractionFirst(GetswWordsLC(x),Result));
          SetswContractionLongFormSecond(x,GetMemoryCellContractionSecond(GetswWordsLC(x),Result));
          //SetswSubWords(x,Getmemorycellsubwords)
          //SetPluralWordFlag(x,Getmemorycell)   correct this all the way to memory cell
          SetswPluralRoot(x,GetMemoryCellpSingularForm(GetswWordsLC(x),Result));
          //SetIsPluralWord(x,Getmemorycell)   memory cell doesn't agree with this type
          //SetswisContraction(x,getmemorycellisContraction)

          if(GetMemoryCellcharWordTense(GetswWordsLC(x),Result)!=typeUnknownWord)            //set swWordTense if not unknown
                SetswWordTense(x,GetMemoryCellcharWordTense(GetswWordsLC(x),Result));


          //Finished all word data transfer
         }//end of all words for loop


         //FindAndSetGistOfSentence();
         FindSubject();
         SetInSentenceExtendedPattern(LocalExtendedPattern);
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
            if((GetswWordType(x)== typeProNounsInward)&&(DirectionDetected == -1)){ DirectionDetected = 0;}        //mentioned me, so to me
             else
                if((GetswWordType(x)==typeProNounsOutward)&&(DirectionDetected == -1)) DirectionDetected = 1;       //user mentioned self, so to user
                  else
                    if((GetswWordType(x)==typeGenderDeterminer)&&(DirectionDetected == -1)) DirectionDetected = 2;}  //user used a pronoun

        if(GetswWordType(0) == typeVerb){
            if( (GetswWordsLC(0)=="is") || (GetswWordsLC(0)=="can") || (GetswWordsLC(0)== "will") || (GetswWordsLC(0)=="are") || (GetswWordsLC(0)== "do") || (GetswWordsLC(0)=="would") ){
                DirectionDetected = 3;}}                                                          //most likely a question

        PatternMatch = WorkingPattern.find(typeAssociativeWord);
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
