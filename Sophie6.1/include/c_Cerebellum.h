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
         int    LocalAdjectiveLocation = 0;
         int    LocalAdverbLocation    = 0;
         int    LocalNamePointer       = 0;
         int    LocalVerbLocation      = 0;
         int    LocalNounCount         = 0;
         int    LocalWordCount         = -1;
         int    QuoteMarker            = -1;
         string LocalPattern           = "";
         string LocalWordCopy          = "";
         char   LocalGenderClass       = '\0';
         char   LocalWordType          = '\0';
         char   MemoryWordType         = '\0';
         char   SentenceWordType       = '\0';
         char   SelectedWordType       = '\0';
         bool   LocalBoolFlag          = false;
         bool   LocalContractionFlag   = false;

         void InitializeAll(){
                 LocalGenderClass       = '\0';
                 LocalAdjectiveLocation = 0;
                 LocalAdverbLocation    = 0;
                 LocalNamePointer       = 0;
                 LocalVerbLocation      = 0;
                 LocalNounCount         = 0;
                 LocalWordCount         = -1;
                 QuoteMarker            = -1;
                 LocalPattern           = "";
                 LocalWordCopy          = "";
                 SentenceWordType       = '\0';
                 LocalWordType          = '\0';
                 MemoryWordType         = '\0';
                 SelectedWordType       = '\0';
                 LocalBoolFlag          = false;
                 LocalContractionFlag   = false;}

public:

        //*********call this after c_sentence.h::parse() has been run***********************
        //*****TODO******
        //   Code for handling disagreement at line 90
    int GatherAndSetAllSentenceData(){
        if(Verbose)
            cout << "[c_Cerebellum.h::GatherAndSetAllSentenceData()]\n";
        InitializeAll();
        LocalWordCount = GetWordCount();
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

        for(int x = 0; x  <= LocalWordCount-1; x++){                                //***First try to set wordtype
            LocalWordType    = FindWordType(GetWordsLC(x),x);                       //Get Wordtype from language helper, receives 'u' if can't determine
            MemoryWordType   = GetMemoryCellWordType(GetWordTokens(x));             //Get Wordtype from memory cell, receives NULL if doesn't exist, else returns CellWordType
            SentenceWordType = GetWordType(x);                                      //Get Wordtype from c_sentence
            LocalWordCopy    = GetWords(x);                                         //Get a copy of the word

            if(MemoryWordType == '\0'){                                             //Nothing in memory cell
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
                                (MemoryWordType != LocalWordType))
                                   cout << "Disagreement!\n";
                                  //disagreement here!!!                            //We have a disagreement here between memory cell wordtype and language helper
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

         LocalGenderClass = GetMemoryCellGenderClass(GetWordTokens(x));             //take care of GenderClass in sentence
         if(LocalGenderClass != '\0')
            SetGenderClassInSentence(x,LocalGenderClass);
        }                                                                           //END of for loop to scan sentence
        SetAdjectiveLocation(LocalAdjectiveLocation);                               //store in c_Sentence
        SetAdverbLocation(LocalAdverbLocation);                                     //store in c_Sentence
        SetNamePointer(LocalNamePointer);                                           //store in c_Sentence
        SetVerbLocation(LocalVerbLocation);                                         //store in c_Sentence
        SetNounCount(LocalNounCount);                                               //store in c_Sentence
        SetPattern(LocalPattern);                                                   //store in c_Sentence
        SetHasContraction(LocalContractionFlag);                                    //Store contraction flag

        return LocalWordCount;                                                      //finished

    }

};

#endif // C_CEREBELLUM_H
