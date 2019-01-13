#ifndef C_BRAIN_H
#define C_BRAIN_H

#include <c_Cerebellum.h>


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

        void ProcessUserInput(string& strData){
            if(Verbose)cout << "[c_Brain.h::ProcessUserInput]" << endl;
            int a, ConfidenceLevel;
            string CheckedPattern;
            int SubjectLocation;
            string FirstPattern = "";
            bool Greeting;
            a = 0;


            CommandCheckSentence.Parse(strData);
            a = CommandTrap();
            Parse(strData);                                                              //break sentence down
            CheckForGreetings(Greeting);
           if(Greeting == false){


            if(a == 0){                                                                   //check for command
             SaveReceivedInput(strData,true);                                             //update short term memory
             SetWordTypes();                                                              //try to set all word types
             SubjectLocation = FindSubject();                                             //try to located subject
             SetSubjectLocation(SubjectLocation);                                         //set the suggestion
             RebuildPattern();
             FirstPattern = GetPattern();
             CheckedPattern = PatternReview(GetPattern(),ConfidenceLevel);                //see if language class can enhance pattern
             if(Verbose){
                    cout << "Processed Pattern:" << CheckedPattern << ":" << GetPattern() << "Confidence level: " << ConfidenceLevel << endl;}
             if(CheckedPattern != GetPattern()){
                SetPattern(CheckedPattern);
                for(int x = 0; x < GetWordCount(); x++){
                    SetWordType(CheckedPattern[x],x);
                }
                SubjectLocation = FindSubject();
                SetSubjectLocation(SubjectLocation);
             }
             DecipherCurrentSentence();                                                             //work with sentence
             SubjectLocation = FindSubject();                                                       // need to run this again to see if any indirect objects
             SetSubjectLocation(SubjectLocation);                                                  //store the location or -1
             a = StoreNewWords();                                                                  //save any new words in rBrainCells
             RebuildPattern();
             SaveProcessedPattern(GetPattern());                                                   //update short term memory
             if(SubjectLocation >=0)
                SetSubject(GetWordTokens(SubjectLocation),GetWords(SubjectLocation));
                SavePreAndPostPatternConstruction(FirstPattern,GetPattern());                      //save learned pattern for future// language helper to use this
             }
            else
                if(a == -1)
            {
                strData = "end";
            }
           }//end Greeting check

            }
//-----------------------------------------------END FIRST PROCESSING---------------------------------------------------------------------------------



        void Report(){
        int WC; int sbj;
        WC = GetWordCount();
        cout << "Punctuation Flag:" << boolalpha << GetHasPunctuation() << "  Punctuation Character:" << GetPunctuation() << endl;
        cout << "Word Count:" << WC << " Pattern:" << GetPattern() << endl;
        cout << "Subject location:" << GetSubjectLocation() << " Indirect Object Location:" << GetIndirectObjectLocation() << endl;
        for (int x = 0; x < WC; x++){
            cout << x << " " << GetWords(x) << ":" << GetWordTokens(x) <<  " Type:"
            << GetWordType(x) << " isContraction:" << GetisContraction(x) << " Quote Location:" << GetQuoteLocation(x) << endl;
        }
            cout << "Cell Usage(r):" << GetRightLobeCellCount() <<  " Cell Usage(l):" << GetLeftLobeCellCount() << endl;
        }







        int CommandTrap()
        {
            int Command;
            int Count;
            Command = 0;
            int Control; Control =0;
            Count = CommandCheckSentence.GetWordCount();
            Command = CommandCheckSentence.GetWordTokens(0);
            if(Count >1)
             Command = Command + CommandCheckSentence.GetWordTokens(1);



            switch (Command)
            {

            case 623: //end
                {
                    Control = -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 1090: // exit
                {
                    Control =  -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 2699: // mood level
                {
                    cout << "MoodLevel = " << GetMoodLevel() << endl;
                    Control = 2;
                    break;
                }
            case 2979: // goodbye
                {
                    Control =  -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 3337:    // cell report
                {
                    int WorkingWord = CommandCheckSentence.GetWordTokens(2);
                    int AdjectivesInMap[20];
                    int AdverbsInMap[20];
                    int VerbsInMap[20];
                    int RelatedNounsInMap[20];
                    int y = 0;
                    bool Result = false;
                    cout << "Cell Report:Right Brain" << endl << endl;
                    cout << "Cell String:" << GetMemoryCellRawStringData(Result,"",WorkingWord)<< endl;
                    cout << "Cell String (LC):" << GetMemoryCellWordLC("",WorkingWord) << endl;
                    cout << "Cell Word Type:" << GetMemoryCellWordType(WorkingWord) << endl;
                    //cout << "Cell Secondary Word Type:" << RightLobeMemory[WorkingWord].GetSecondaryType() << endl;
                    //cout << "Cell Alternate Word Type:" << RightLobeMemory[WorkingWord].GetAlternateType() << endl;
                    cout << "Cell Gender:" << GetMemoryCellGenderClass(WorkingWord) << endl;
                    cout << "Cell Primary Usage:" << GetMemoryCellPurpose(WorkingWord) << endl;
                   // cout << "Cell Root Pointer:" << RightLobeMemory[WorkingWord].GetpNextNoun() << endl;
                    cout << "Cell Data is Set:" << boolalpha << GetMemoryCellIsSet(WorkingWord) << endl;
                    cout << "Cell Location by token:" << WorkingWord << endl;
                    cout << "Cell adjectives stored in map:" << GetMemoryCellAdjectives(WorkingWord,AdjectivesInMap) << endl;
                    cout << "Cell verbs stored in map:" << GetMemoryCellVerbs(WorkingWord,VerbsInMap) << endl;
                    cout << "Cell adverbs stored in map:" << GetMemoryCellAdverbs(WorkingWord,AdverbsInMap) << endl;
                    cout << "Cell Adjectives, Verbs, Adverbs:\n";
                       for(int x = 0; x< GetMemoryCellAdjectiveCount(WorkingWord); x++){
                         cout  << "   " << GetMemoryCellWordLC("",AdjectivesInMap[x]) << " " << GetMemoryCellWordLC("",VerbsInMap[x]) << " " << GetMemoryCellWordLC("",AdverbsInMap[x]) << endl;
                       }
                    cout << endl;
                    y = GetMemoryCellRelatedNouns(WorkingWord,RelatedNounsInMap);
                    cout << "Cell related Nouns("  << y << "):\n";

                       for(int x = 0; x< y;x++){
                         cout << "   " << GetMemoryCellWordLC("",RelatedNounsInMap[x]) << endl;
                       }

                    Control = 2;
                    break;
                }
            case 3058:   //verbose
                {
                    if(Verbose)
                        Verbose = false;
                    else
                        Verbose = true;

                    Control = 2;
                    break;
                }
            case 3387:  //report flow
                {
                    ReportStorageFlow();
                    Control = 2;
                    break;
                }

            case 3383:  //report last
                {
                    Report();
                    Control = 2;
                    break;
                }
            case 4854:  //moodlevel
                {
                    cout << "MoodLevel = " << GetMoodLevel() << endl;
                    Control = 2;
                    break;
                }
            case 5352:  //subject report
                {
                    Control = 2;
                    cout << "no. Token Memory Subject string\n";
                    for(int x =0; x<15; x++){
                        if(GetSubject(x)>0)
                            cout << x << ":   " << GetSubject(x) << "    " << GetMemoryCellWordLC("",GetSubject(x)) << " " << GetstrSubject(x) << endl;}
                    break;
                }
            case 5365:   // pattern report 'duvu'
                {
                    Control = 2;
                    cout << GetMemoryCellWordLC("",CommandCheckSentence.GetWordTokens(2)) << " points to "
                         << GetMemoryCellWordLC("",GetMemoryCellPointerToNextPattern(CommandCheckSentence.GetWordTokens(2))) << endl;
                    //cout << LeftLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetpCellDataString() << " points to "
                    //     << LeftLobeMemory[LeftLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetPointerToNextPattern()].GetpCellDataString() << endl;

                    break;

                }



            }
            if((Control != 0)&(Verbose))
                cout << "[c_Brain.h::CommandTrap]-successful\n";
            else
                if(Verbose) cout << "[c_Brain.h::CommandTrap]-no command found\n";
            return Control;
        }



        int Respond(){    //can delete this

        //if(lBrainCellCount == 0){
        //    cout << "Hello. My name is " << MyPersonality.GetMyName() << endl;
        //    return 1;                                                         //ask user for more input

         return CommandTrap() ;

        return 0;
        }










      //scan sentence words and set their types
      //   Check memory storage first (search only lowercase storage)
      //     if already stored set the sentence word type to the memory value
      //     if not, has already been initialized to 'u' unless sentence parser has set something other than 'u'
      //    doCorrection is control to not override wordtype stored in brain  true = change it to whatever is set by others

       void SetWordTypes(bool doCorrection = false)
        {
            if(Verbose){cout << "[c_Brain.h::SetWordTypes]" << endl;}
            char tmpTypeInSentence, tmpTypeInMemoryCell, tmpTypeFromLanguageHelper;
            bool isSetInMemory;
            for(int x = 0; x < GetWordCount(); x++){
                    tmpTypeInSentence         = GetWordType(x);
                    tmpTypeInMemoryCell       = GetMemoryCellWordType(GetWordTokens(x));//  GetBrainWordType(GetWordsLC(x),'r');
                    tmpTypeFromLanguageHelper = FindWordType(GetWordsLC(x));
                    isSetInMemory             = GetMemoryCellIsSet(GetWordTokens(x)); //  GetBrainCellIsSet('r',Tokenize(GetWordsLC(x)));
                    if(Verbose){
                        cout << "WordLC:  " << GetWordsLC(x) << endl;
                        cout << "  Sentence Set:" << tmpTypeInSentence << endl;
                        cout << "  MemoryCell Set:" << tmpTypeInMemoryCell << endl;
                        cout << "  Language helper Set:" << tmpTypeFromLanguageHelper << endl;
                        cout << "  Memory Cell Previously set?" << boolalpha << isSetInMemory << endl;}

                    if(isSetInMemory && doCorrection) isSetInMemory = false;

                    if(isSetInMemory == false){
                        if(tmpTypeInSentence == 'u')
                            SetWordType(tmpTypeFromLanguageHelper,x);}
                    else{
                        SetWordType(tmpTypeInMemoryCell,x);}

                     if( GetWordType(x) == 'q') SetIsQuestion(true);

            }
        }//------END SET WORD TYPES---------------------------------------------------------------

///------------------------------------------------------------------------------------------------



        void TrySubject()
        {
          int SubjectLoc;
          int Complexity;
          int Response;
          SubjectLoc = GetSubjectLocation();
          Complexity = GetWordCount();
          //cout << "Subject Location:" << SubjectLoc << endl;

           switch(Complexity)
           {


             case 4:
               {
                   DecipherCurrentSentence();

                   SlowSpeak(GetWords(0)+ " " + GetWords(3)+ " " + GetWords(SubjectLoc)+ ".");
                   SlowSpeak("Is this right?");
                   Response = RequestUserResponse();
                   if(Response == 1){
                    cout << "Yeah!" << endl;
                    //tell user to describe subject or suggest the subject we're understanding
                    //set assumptions
                    //set/adjust subject stack
                   }
                   else{
                    SlowSpeak("Oh. Let me try again.");   //subject is wrong
                    SlowSpeak("Is " + GetWords(3) + " " + GetWords(1) + " " + GetWords(2)+ "?");
                    Response = RequestUserResponse();
                     if(Response == 1){
                        //reset subject location
                        //tell user to describe subject or suggest the subject we're understanding
                       //set assumptions
                       //set/adjust subject stack
                     }

                   }
                   break;
               }

           }

            //if(SubjectLoc){
            //cout << "Tech me about " << Sentence.GetWords(SubjectLoc) << ",please." << endl;
            //}
        }
//------------------------------STORE NEW WORDS-----------------------------------------------------------------
        int StoreNewWords()
        {
         if(Verbose)cout << "[c_Brain.h::StoreNewWords]" << endl;
         int NewWords; NewWords = 0;
         int Noun1 = -1;
         int Noun2 = -1;

         for (int x = 0; x < GetWordCount(); x++)
         {
             if((GetWordType(x)=='n') && (Noun1 == -1) ) Noun1 = x; else if((GetWordType(x) == 'n') && (Noun2 == -1))  Noun2 =x;
             if( !( GetMemoryCellIsSet(GetWordTokens(x)) )) //   CheckForKnownWord(GetWords(x))))
                {NewWords++;}
                InstallNewWord(GetWords(x),GetWordType(x),'w',true);
                if(GetWordType(x)=='a'){
                        if(GetSubjectLocation() >=0 )
                            if(!AssociateMemoryCellAdjective(GetWordTokens(GetSubjectLocation()),GetWordsLC(x))){
                                InstallNewWord(GetWords(GetSubjectLocation()),GetWordType(GetSubjectLocation()),'w',true);
                                AssociateMemoryCellAdjective(GetWordTokens(GetSubjectLocation()),GetWordsLC(x));
                                if(Verbose)
                                    cout << "Associating " << GetWords(x) << " with " << GetWords(GetSubjectLocation()) << endl;
                            }
                            if(GetIndirectObjectLocation() >=0)
                                if(!AssociateMemoryCellAdjective(GetWordTokens(GetIndirectObjectLocation()),GetWordsLC(x))){
                                    InstallNewWord(GetWords(GetIndirectObjectLocation()),GetWordType(GetIndirectObjectLocation()),'w',true);
                                    AssociateMemoryCellAdjective(GetWordTokens(GetIndirectObjectLocation()),GetWordsLC(x));
                                    if(Verbose)
                                       cout << "Associating " << GetWords(x) << " with " << GetWords(GetIndirectObjectLocation()) << endl;
                                }
                                //RightLobeMemory[GetWordTokens(GetIndirectObjectLocation())].AccociateAdjective(GetWordTokens(x));
                    int z; z = GetVerbPointingToAdjective();
                    if(z >=0)
                        AssociateMemoryCellVerbToAdjective(GetWordTokens(GetSubjectLocation()),GetWordsLC(z),GetWordsLC(x));
                        //RightLobeMemory[GetWordTokens(GetSubjectLocation())].AccociateAdjectiveWithVerb(GetWordTokens(z),GetWordTokens(x));
                        if(GetIndirectObjectLocation()>=0)
                            AssociateMemoryCellVerbToAdjective(GetWordTokens(GetIndirectObjectLocation()),GetWordsLC(z),GetWordsLC(x));
                            //RightLobeMemory[GetWordTokens(GetIndirectObjectLocation())].AccociateAdjectiveWithVerb(GetWordTokens(z),GetWordTokens(x));
                }
                if(GetWordType(x) == 'A')
                    AssociateMemoryCellAdverbToVerb(GetWordTokens(GetSubjectLocation()),GetWordsLC(GetWordTokens(GetVerbPointingToAdjective())),GetWordsLC(x));
                    //L_AssociateAdverbToVerbInMap(GetWordsLC(x),GetWordsLC(GetVerbPointingToAdjective()),GetWordTokens(GetSubjectLocation()));
         }
         if((GetNounCount() >=2)&& (!GetIsQuestion())){
                if(Verbose)
                   cout << "Associating " << GetWords(Noun1) << " with " << GetWords(Noun2) << endl;
                AssociateMemoryCellNoun(GetWordTokens(Noun1),GetWordsLC(Noun2));
                AssociateMemoryCellNoun(GetWordTokens(Noun2),GetWordsLC(Noun1));

         }

            return NewWords;

        }
};

#endif // C_BRAIN_H
