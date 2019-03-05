#ifndef C_BRAIN_H
#define C_BRAIN_H

#include <c_Cerebellum.h>
extern string Version;
extern bool   StoryMode;

class c_Brain : public c_Cerebellum
{
    public:
        c_Brain();
        virtual ~c_Brain();





        c_Personality UserPersonality;
        c_ShortTermMemory ShortTermMemory;

        c_Sentence SlowSpeakSentence;
        c_Sentence LastSentence;
        c_Sentence CommandCheckSentence;


        int rBrainCellCount;
        int lBrainCellCount;
        char GenClass;


    public:
        void SetMyName (string NewVal){SetName(NewVal);}
        void SetUserName (string NewVal){UserPersonality.SetName(NewVal);}
        void SetMyGender (char NewVal){SetGender(NewVal);}
        void SetUserGender (char NewVal){UserPersonality.SetGender(NewVal);}








//---------------------------------------------------------------------------------------------------------------------------------------------------
//********************************************* First Processing Point / Cortex is Main Processor****************************************************
//*****************************************THIS IS A PROCESS CONTROL AREA****************************************************************************

        void ProcessUserInput(string& strData){
            if(Verbose)cout << "[c_Brain.h::ProcessUserInput]" << endl;
            int CommandFound, ConfidenceLevel;
            string CheckedPattern,Root,LongFormFirst,LongFormSecond;
            int SubjectLocation;
            string FirstPattern = "";
            CommandFound = 0;
            bool OwnerShip,Plural,NeedRerun;
            NeedRerun = false;

           do{
            CommandCheckSentence.Parse(strData);
            CommandFound = CommandTrap();


            if(CommandFound == 0){                                                                      //check for command  0 = no command
                 Parse(strData);                                                                        //break sentence down
                 SaveReceivedInput(strData,true);                                                       //update short term memory
                 SaveSentenceInLongTermMemory(strData);                                                 //update Long Term Memory
                 GatherAndSetAllSentenceData();                                                         //check language helper, memory and pattern review for data
                 SetInSentencePreProcessedPattern(GetFromSentencePattern());                            //save for later review
                 //FindAndSetGistOfSentence();                                                          //save phrases of the sentence
                 if(IsThisSentenceDuplicated(strData))
                    SlowSpeak("You said that before.");
                 if(GetFromSentenceHasContraction()){                                                   //break contraction apart and rewrite sentence if so, rerun the process
                   NeedRerun = DeconstructContractions(OwnerShip,Plural,Root,LongFormFirst,LongFormSecond,strData);
                   if(NeedRerun){
                    StoreNewWords();
                    Parse(strData);
                    GatherAndSetAllSentenceData();
                    SetInSentencePreProcessedPattern(GetFromSentencePattern());
                    FindAndSetGistOfSentence();
                    SaveReceivedInput(strData,true);
                    SaveSentenceInLongTermMemory(strData);
                    NeedRerun = false;
                   }
                 }
                 SubjectLocation = FindSubject();                                                           //try to located subject
                 SetInSentenceSubjectLocation(SubjectLocation);                                             //set the suggestion
                 RebuildPattern();
                 FirstPattern = GetFromSentencePreProcessedPattern();
                 CheckedPattern = PatternReview(GetFromSentencePattern(),ConfidenceLevel);                  //see if language class can enhance pattern
                 if(Verbose){
                        cout << "Processed Pattern:" << CheckedPattern << ":" << GetFromSentencePattern() << "Confidence level: " << ConfidenceLevel << endl;}
                 if(CheckedPattern != GetFromSentencePattern()){
                    SetInSentencePattern(CheckedPattern);
                    for(int x = 0; x < GetFromSentenceWordCount(); x++){
                        SetswWordType(CheckedPattern[x],x);
                    }
                    SubjectLocation = FindSubject();
                    SetInSentenceSubjectLocation(SubjectLocation);
                 }
                 NeedRerun = DecipherCurrentSentence(strData);                                             //work with sentence
                 if(!NeedRerun){
                     SubjectLocation = FindSubject();                                                      // need to run this again to see if any indirect objects
                     SetInSentenceSubjectLocation(SubjectLocation);                                        //store the location or -1
                     StoreNewWords();                                                                      //save any new words in rBrainCells
                     SaveAllSentenceWordDataToMemory();                                                    //new function to save all to memory
                     RebuildPattern();
                     SaveProcessedPattern(GetFromSentencePattern());                                       //update short term memory
                     if(SubjectLocation >=0)
                        SetSubjectInStack(GetswWordTokens(SubjectLocation),GetswWords(SubjectLocation),GetFromSentenceOriginalString());
                     SavePreAndPostPatternConstruction(FirstPattern,GetFromSentencePattern());             //save learned pattern for future// language helper to use this
                     SaveCurrentSentenceInMap();
                     SaveAllSentenceWordDataToMemory();
                     }
                   }
                   else
                    if(CommandFound == -1){  //exit commands
                    strData = "end";}//stop the loop


             } while (NeedRerun);
            }
//-----------------------------------------------END FIRST PROCESSING---------------------------------------------------------------------------------



        void Report(){
        int WC = GetFromSentenceWordCount();
        cout << "Punctuation Flag:" << boolalpha << GetFromSentenceHasPunctuation() << "  Punctuation Character:" << GetFromSentencePunctuation() << endl;
        cout << "Word Count:" << WC << " Pattern:" << GetFromSentencePattern() << " Dual Subject Flag:" << boolalpha << GetFromSentenceHasDualSubjects() <<endl;
        cout << "Subject location:" << GetFromSentenceSubjectLocation() << "\nIndirect Object Location:" << GetFromSentenceIndirectObjectLocation() << " Second Subject:" << GetFromSentenceSecondSubject() << endl;
        cout << "Gist of sentence:" << GetFromSentenceGistOfSentence() << "\nSubGist of sentence:" << GetFromSentenceSubGistOfSentence() << endl;
        cout << "Supportive phrase:" << GetFromSentenceSupportivePhrase() << endl;
        cout << "Sentence is question flag:" << boolalpha << GetFromSentenceIsQuestion() << endl;
        cout << "Sentence has preposition flag:" << boolalpha << GetFromSentenceHasPreposition() << endl;
        cout << "Sentence was understood:" << boolalpha << GetFromSentenceHasBeenUnderstood() << endl;
        for (int x = 0; x < WC; x++){
            cout << x << " " << GetswWords(x) << ":" << GetswWordTokens(x) <<  " Type:"
            << GetswWordType(x) << " isContraction: " << GetswisContraction(x) << "\n     Quote Location:" << GetswQuoteLocation(x) << "  Plural flag: " <<
               boolalpha << GetswIsPluralWord(x) << " Plural root word:" << GetswPluralRoot(x) << endl;
        }
            cout << "Cell Usage(r):" << GetRightLobeCellCount() <<  " Cell Usage(l):" << GetLeftLobeCellCount() << "\n"
                 << " Number of Sentences in LTM:" << GetNumberOfSentencesSaved() << " Sentence Map Count:" << GetSentenceStorageCountInMap() << endl;
        }







        int CommandTrap()
        {
            int Command;
            int Count;
            Command = 0;
            int Control; Control =0;
            Count   = CommandCheckSentence.GetFromSentenceWordCount();
            Command = CommandCheckSentence.GetswWordTokens(0);
            if(Count >1)
             Command = Command + CommandCheckSentence.GetswWordTokens(1);



            switch (Command)
            {

            case 644: //end
                {
                    Control = -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 2729: // the end
                {
                    if(StoryMode){
                        StoryMode = false;
                        SlowSpeak("Thank you for that story. I loved it!");
                        SlowSpeak(":)");
                        IncreaseMoodLevel();
                    }
                    Control = 2;
                    break;
                }
            case 7510: // exit 1090
                {
                    Control =  -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 141916: // mood level
                {
                    cout << "MoodLevel = " << GetMoodLevel() << endl;
                    Control = 2;
                    break;
                }
            case 8654455: // goodbye
                {
                    Control =  -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 1871332:    // cell report
                {
                    int WorkingWord = CommandCheckSentence.GetswWordTokens(2);
                    string strWorkingWord = CommandCheckSentence.GetswWordsLC(2);
                    int AdjectivesInMap[20];
                    int AdverbsInMap[20];
                    int VerbsInMap[20];
                    int RelatedNounsInMap[20];
                    int y = 0;
                    bool Result = false;

                    GetMemoryCellRawData(strWorkingWord,Result);
                    if(Result){
                            cout << "Cell Report:Right Brain" << endl << endl;
                            cout << "Cell String:" << GetMemoryCellRawData(strWorkingWord,Result)<< endl;
                            cout << "Cell String (LC):" << GetMemoryCellDataLC(strWorkingWord,Result) << endl;
                            cout << "Cell Word Type:" << GetMemoryCellcharWordType(strWorkingWord,Result) << endl;
                            if(GetMemoryCellcharWordType(strWorkingWord,Result)=='C'){
                                cout << "  Contraction Word Long Form First:" << GetMemoryCellContractionFirst(strWorkingWord,Result) << endl;
                                cout << "  Contraction Word Long Form Second:" << GetMemoryCellContractionSecond(strWorkingWord,Result) << endl;
                            }
                            //cout << "Cell Secondary Word Type:" << RightLobeMemory[WorkingWord].GetSecondaryType() << endl;
                            //cout << "Cell Alternate Word Type:" << RightLobeMemory[WorkingWord].GetAlternateType() << endl;
                            cout << "Cell Gender:" << GetMemoryCellcharGenderClass(strWorkingWord,Result) << endl;
                            cout << "Cell Primary Usage:" << GetMemoryCellcharPurpose(strWorkingWord,Result) << endl;
                           // cout << "Cell Root Pointer:" << RightLobeMemory[WorkingWord].GetpNextNoun() << endl;
                            cout << "Cell Data is Set:" << boolalpha << GetMemoryCellIsSet(strWorkingWord,Result) << endl;
                           // cout << "Cell Plural flag:" << GetMemoryCellpCellIsSingular("",WorkingWord) << "  Plural Root:" << GetMemoryCellpSingularLocation("",WorkingWord) << endl;
                            cout << "Cell Location by token:" << WorkingWord << endl;
                            cout << "Cell adjectives stored in map:" << GetMemoryCellAdjectives(WorkingWord,AdjectivesInMap) << endl;
                            cout << "Cell verbs stored in map:" << GetMemoryCellVerbs(WorkingWord,VerbsInMap) << endl;
                            cout << "Cell adverbs stored in map:" << GetMemoryCellAdverbs(WorkingWord,AdverbsInMap) << endl;
                            cout << "Cell Adjectives, Verbs, Adverbs:\n";
        //                       for(int x = 0; x< GetMemoryCellAdjectiveCount(WorkingWord); x++){
        //                         cout  << "   " << GetMemoryCellDataLC(AdjectivesInMap[x],Result) << " " << GetMemoryCellDataLC(VerbsInMap[x],Result) << " " << GetMemoryCellDataLC(AdverbsInMap[x],Result) << endl;
        //                       }
                            cout << endl;
                            y = GetMemoryCellRelatedNouns(WorkingWord,RelatedNounsInMap);
                            cout << "Cell related Nouns("  << y << "):\n";

        //                       for(int x = 0; x< y;x++){
        //                         cout << "   " << GetMemoryCellWordLC("",RelatedNounsInMap[x]) << endl;
        //                       }

                    }//end if result
                    else
                        cout << strWorkingWord << " not in memory!\n";

                    Control = 2;
                    break;
                }
            case 22683695:   //verbose
                {
                    if(Verbose)
                        Verbose = false;
                    else
                        Verbose = true;

                    Control = 2;
                    break;
                }
            case 22700064:  //version
                {
                    cout << "Version:" << Version << endl;
                    Control = 2;
                    break;
                }
            case 3387:  //report flow
                {
                    ReportStorageFlow();
                    Control = 2;
                    break;
                }

            case 1880010:  //report last
                {
                    Report();
                    Control = 2;
                    break;
                }
            case 1465527262:  //moodlevel
                {
                    cout << "MoodLevel = " << GetMoodLevel() << endl;
                    Control = 2;
                    break;
                }
            case 196612681:  //dump sentence
                {
                    DumpSentencesInMap();
                    Control = 2;
                    break;
                }
            case 22998250:  //subject report
                //Add a check for three words in CommandCheckSentence, if a third, report all data about it only
                // otherwise dump the list of subject names and adjective + related noun counts
                {
                    string sbjAdjectives[35];
                    string sbjRelatedNouns[35];
                    Control = 2; int z;
                    cout << "Subjects in map:" << GetSubjectMapSize() << endl;
                    for(int x = 0; x < GetSubjectMapSize(); x++){
                        if(x == 0){
                            cout << " Current subject: Token:" << GetSubjectTokenInMap(x) << "  String:" << GetSubjectStringInMap(x) << endl;}
                        else {
                            cout << " Subject Token:" << GetSubjectTokenInMap(x) << "  String:" << GetSubjectStringInMap(x) << endl;}
                        GetSubjectAdjectives(sbjAdjectives,x);
                        GetSubjectRelatedNouns(sbjRelatedNouns,x);
                        int adjCount = GetSubjectAdjectiveCount(x);
                        int nounCount = GetSubjectNounCount(x);
                        cout << "  Subject Adjective(s):" << GetSubjectAdjectiveCount(x) << "  Related Noun(s):" << nounCount
                             << "  Word Type:" << GetSubjectWordType(x) << "  Gender:" << GetSubjectGender(x) << " Times used:" << GetsbjSubjectCountInMap(x) << endl;
                        cout << "   Adjectives\tNouns" << endl;

                        for(int t =0; t<= adjCount-1; t++){
                            cout << t+1 << "      " << sbjAdjectives[t] << "\t";
                            if (t <= nounCount){
                                cout << sbjRelatedNouns[t] << endl;
                            }
                            else{
                                cout << endl;
                            }
                            z = t; //save the place
                            }
                            z++;
                            if( z<= nounCount){
                                cout << z+1 << "      \t\t" << sbjRelatedNouns[z] << endl;
                                z++;
                            }
                    }
                    break;
                }

            case 18188394:   // pattern report 'duvu'
                {
                    Control = 2;
//                    cout << GetMemoryCellWordLC("",CommandCheckSentence.GetWordTokens(2)) << " points to "
//                         << GetMemoryCellWordLC("",GetMemoryCellPointerToNextPattern(CommandCheckSentence.GetWordTokens(2))) << endl;

                    break;

                }



            }//end switch command
            if((Control != 0)&(Verbose))
                cout << "[c_Brain.h::CommandTrap]-successful\n";
            else
                if(Verbose) cout << "[c_Brain.h::CommandTrap]-no command found\n";
            return Control;
        }//end command trap


      //------------------------SETWORDTYPES---------------------------------------------------------------------------
      //     scan sentence words and set their types
      //     Check memory storage first (search only lowercase storage)
      //     if already stored set the sentence word type to the memory value
      //     if not, has already been initialized to 'u' unless sentence parser has set something other than 'u'
      //     doCorrection is control to not override wordtype stored in brain  true = change it to whatever is set by others

       void SetWordTypes(bool doCorrection = false)
        {
            if(Verbose){cout << "[c_Brain.h::SetWordTypes]" << endl;}
            char tmpTypeInSentence, tmpTypeInMemoryCell, tmpTypeFromLanguageHelper;
            char tmpGenderClassFromMemoryCell;
            bool isSetInMemory;
            bool Result = false;
            for(int x = 0; x < GetFromSentenceWordCount(); x++){
                    tmpTypeInSentence            = GetswWordType(x);
                    tmpTypeInMemoryCell          = GetMemoryCellcharWordType(GetswWordsLC(x),Result);
                    tmpTypeFromLanguageHelper    = FindWordType(GetswWordsLC(x),x);
                    isSetInMemory                = GetMemoryCellIsSet(GetswWordsLC(x),Result);
                    tmpGenderClassFromMemoryCell = GetMemoryCellcharGenderClass(GetswWordsLC(x),Result);
                    if(tmpGenderClassFromMemoryCell != '\0')
                        SetswGenderClassInSentence(x,tmpGenderClassFromMemoryCell);
                    if(Verbose){
                        cout << "WordLC:  " << GetswWordsLC(x) << endl;
                        cout << "  Sentence Set:" << tmpTypeInSentence << endl;
                        cout << "  MemoryCell Set:" << tmpTypeInMemoryCell << endl;
                        cout << "  Language helper Set:" << tmpTypeFromLanguageHelper << endl;
                        cout << "  Memory Cell Previously set?" << boolalpha << isSetInMemory << endl;}

                    if(isSetInMemory && doCorrection) isSetInMemory = false;

                    if(isSetInMemory == false){
                        if(tmpTypeInSentence == 'u')
                            SetswWordType(tmpTypeFromLanguageHelper,x);}
                    else{
                        SetswWordType(tmpTypeInMemoryCell,x);}

                     if( GetswWordType(x) == 'q') SetInSentenceIsQuestion(true);
                     if( GetswWordType(x) == 'g') SetInSentenceNamePointer(x);
                     if( GetswWordType(x) == 'C') SetInSentenceHasContraction(true);

            }
        }//------END SET WORD TYPES---------------------------------------------------------------

///------------------------------------------------------------------------------------------------


//------------------------------STORE NEW WORDS-----------------------------------------------------------------
        int StoreNewWords()
        {
         if(Verbose)cout << "[c_Brain.h::StoreNewWords]" << endl;
         int  NewWords; NewWords = 0;
         int  Noun1 = -1;
         int  Noun2 = -1;
         bool Result = false;

         for (int x = 0; x < GetFromSentenceWordCount(); x++)
         {
             if((GetswWordType(x)=='n') && (Noun1 == -1) ) Noun1 = x; else if((GetswWordType(x) == 'n') && (Noun2 == -1))  Noun2 =x;
             if( !( GetMemoryCellIsSet(GetswWordsLC(x),Result) )) //   CheckForKnownWord(GetWords(x))))
                {NewWords++;}
                InstallNewWord(GetswWords(x),GetswWordType(x),'w',true,GetswGenderClassInSentence(x),
                               GetswContractionLongFormFirst(x),GetswContractionLongFormSecond(x),GetswPluralWordFlag(x),Tokenize(GetswPluralRoot(x)));
                if(GetswIsPluralWord(x)){ //store the singular root
                    InstallNewWord(GetswPluralRoot(x),GetswWordType(x),'w',true,GetswGenderClassInSentence(x),
                                   "","",'s');}
                //Associate Adjective if not a question sentence
                if((GetswWordType(x)=='a')&&(!GetFromSentenceIsQuestion()) ){
                        if(GetFromSentenceSubjectLocation() >=0 ){
                            if(!SetMemoryCellAdjectiveInList(GetswWordsLC(GetFromSentenceSubjectLocation()),GetswWordsLC(x))){ //NOTE: Adjective Storage to Memory
                                InstallNewWord(GetswWords(GetFromSentenceSubjectLocation()),GetswWordType(GetFromSentenceSubjectLocation()),'w',true,GetswGenderClassInSentence(GetFromSentenceSubjectLocation()));}
                                SetMemoryCellAdjectiveInList(GetswWordsLC(GetFromSentenceSubjectLocation()),GetswWordsLC(x));  //NOTE: Adjective Storage to Memory
                                if(GetswIsPluralWord(GetFromSentenceSubjectLocation())){
                                    SetMemoryCellAdjectiveInList(GetswPluralRoot(GetFromSentenceSubjectLocation()),GetswWordsLC(x)); //NOTE Adjective Storage to Memory
                                }
                                if(Verbose)
                                    cout << "Associating " << GetswWords(x) << " with " << GetswWords(GetFromSentenceSubjectLocation()) << endl;
                            }
                            if((GetFromSentenceIndirectObjectLocation() >=0) && (!GetFromSentenceIsQuestion()) ){ //Associate Indirect object if not a question sentence
                                if(!SetMemoryCellAdjectiveInList(GetswWordsLC(GetFromSentenceIndirectObjectLocation()),GetswWordsLC(x))){  //NOTE: Adjective Storage to Memory
                                    InstallNewWord(GetswWords(GetFromSentenceIndirectObjectLocation()),GetswWordType(GetFromSentenceIndirectObjectLocation()),'w',true,GetswGenderClassInSentence(GetFromSentenceIndirectObjectLocation()));}
                                    SetMemoryCellAdjectiveInList(GetswWordsLC(GetFromSentenceIndirectObjectLocation()),GetswWordsLC(x));   //NOTE: Adjective Storage to Memory
                                    if(GetswIsPluralWord(GetFromSentenceSubjectLocation())){
                                        SetMemoryCellAdjectiveInList(GetswPluralRoot(GetFromSentenceSubjectLocation()),GetswWordsLC(x));   //NOTE: Adjective Storage to Memory
                                    }
                                    if(Verbose)
                                       cout << "Associating " << GetswWords(x) << " with " << GetswWords(GetFromSentenceIndirectObjectLocation()) << endl;
                                }
                    int z; z = GetVerbPointingToAdjective();
                    if((z >=0) && (!GetFromSentenceIsQuestion()))
                        AssociateMemoryCellVerbToAdjective(GetswWordTokens(GetFromSentenceSubjectLocation()),GetswWordsLC(z),GetswWordsLC(x));
                        if(GetFromSentenceIndirectObjectLocation()>=0)
                            AssociateMemoryCellVerbToAdjective(GetswWordTokens(GetFromSentenceIndirectObjectLocation()),GetswWordsLC(z),GetswWordsLC(x));
                }
                //Associate Adverb if not a question sentence
                if((GetswWordType(x) == 'A') && (!GetFromSentenceIsQuestion()))
                    AssociateMemoryCellAdverbToVerb(GetswWordTokens(GetFromSentenceSubjectLocation()),GetswWordsLC(GetswWordTokens(GetVerbPointingToAdjective())),GetswWordsLC(x));
         }//nd for loop
         //Associate two nouns if not a question sentence
         if((GetFromSentenceNounCount() >=2)&& (!GetFromSentenceIsQuestion())){
                if(Verbose)
                   cout << "Associating " << GetswWords(Noun1) << " with " << GetswWords(Noun2) << endl;
                SetMemoryCellNounInList(GetswWordsLC(Noun1),GetswWordsLC(Noun2));
                SetMemoryCellNounInList(GetswWordsLC(Noun2),GetswWordsLC(Noun1));

         }
          //Associate Proper Noun to noun and vice versa
          if((GetswWordType(GetFromSentenceIndirectObjectLocation())=='P') && (!GetFromSentenceIsQuestion()) ){
                AssociateMemoryCellNoun(GetswWordTokens(GetFromSentenceSubjectLocation()),GetswWordsLC(GetFromSentenceIndirectObjectLocation()));
                AssociateMemoryCellNoun(GetswWordTokens(GetFromSentenceIndirectObjectLocation()),GetswWordsLC(GetFromSentenceSubjectLocation()));
          }

          //Associate Noun to gender word and vice versa
          if((GetswWordType(GetFromSentenceIndirectObjectLocation())=='P') && (!GetFromSentenceIsQuestion()) ){
                AssociateMemoryCellNoun(GetswWordTokens(GetFromSentenceSubjectLocation()),GetswWordsLC(GetFromSentenceIndirectObjectLocation()));
                AssociateMemoryCellNoun(GetswWordTokens(GetFromSentenceIndirectObjectLocation()),GetswWordsLC(GetFromSentenceSubjectLocation()));
          }

            return NewWords;

        }






 //----------------------------------FIRST RUN WELCOME MESSAGE--------------------------------------------------------

    void FirstRunWelcomeMessage(){
           //Recording turned off for this
            cout << "[Version:" << Version << "]\n";
            SlowSpeak("Hello there!",false);
            SlowSpeak("I'm Sohpie and I'm a girl.",false);
            SlowSpeak("Thanks for helping me learn new things.",false);
            SlowSpeak("Right now I don't know much about anything. I need for you to teach me.",false);
            SlowSpeak("I will do my best to understand you but if I don't I may ask you a question about what you said.",false);
            SlowSpeak("If I do need to ask a question, you will see >? prompt. Please respond with a yes or no answer unless I ask something more specific.",false);
            SlowSpeak("This will help me to understand.",false);
            SlowSpeak("Thank you!",false);
            SlowSpeak(":)",false);








    }
//--------------------------------END FIRST RUN WELCOME MESSAGE-------------------------------------------------------------
};

#endif // C_BRAIN_H
