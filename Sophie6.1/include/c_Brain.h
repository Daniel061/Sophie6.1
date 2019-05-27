#ifndef C_BRAIN_H
#define C_BRAIN_H

#include <c_PTLControl.h>
extern string Version;
extern bool   StoryMode;
extern bool   TrainingMode;

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

class c_Brain : public c_PTLControl
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



        void ControlProcessingUserInput(string &strData, bool ProcessCommands){
            if(Verbose)cout << "[c_Brain.h::ControlProcessingUserInput]" << endl;
            int    CommandFound   = -1;
            string tmpInputData   = strData;
            bool   OwnerShip,Plural;
            string Root,LongFormFirst,LongFormSecond;

            if(ProcessCommands){
               CommandCheckSentence.InitializeVars();
               CommandCheckSentence.Parse(strData);
               CommandFound     = CommandTrap();}
               else{
                CommandFound = 0;}


            if(CommandFound == 0){

              Parse(strData);                                                                                        // c_Sentence parse this data
              SaveSentenceInLongTermMemory(strData);                                                                 // update Long term memory
              GatherAndSetAllSentenceData();                                                                         // pull all data into c_sentence and c_words
                                                                                                                     //  from memory and language helper
              //DeconstructContractions(OwnerShip,Plural,Root,LongFormFirst,LongFormSecond,tmpInputData);
              //DecipherCurrentSentence(strData);                  // Work with what is known at this point
              RebuildPattern();                                                                                      // Updated corrected pattern
              ReVerseBuildPattern();                                                                                 // push pattern data to word type
              FindDirectAndIndirectObject();                                                                         // See if Direct and indirect object can be set now
              LinkRelatedWords();                                                                                    // link related words together in word class
              SaveAllSentenceWordDataToMemory();                                                                     // push sentence and word data to memory cells
              SaveCurrentSentenceInMap();                                                                            // push sentence class to map
              SavePreAndPostPatternConstruction(GetFromSentencePreProcessedPattern(),GetFromSentencePattern());
//              if(TrainingMode){
//              ProcessPTLData(strData,GetFromSentenceWordCount(),GetFromSentencePattern(),GetFromSentenceWordMap());} // give sentence data to PTLControl
//              PTLProcessSentenceIneWFT();                                                                            // create extended word frequency map
//              if(!TrainingMode){
//                CreateSoftCompareMap(GetFromSentenceWordMap(),GetFromSentenceWordCount());
//              }

            }
            else{
              if(CommandFound == -1)strData = "end";}
        } //End of ControlProcessingUserInput




//---------------------------------------------------------------------------------------------------------------------------------------------------




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
                            cout << "Cell String     :" << GetMemoryCellRawData(strWorkingWord,Result)<< endl;
                            cout << "Cell String (LC):" << GetMemoryCellDataLC(strWorkingWord,Result) << endl;
                            cout << "Cell Word Type  :" << GetMemoryCellcharWordType(strWorkingWord,Result) << endl;
                            cout << "Cell Extended Word type   :" << GetMemoryCellpExtendedWordType(strWorkingWord,Result) << endl;
                            if(GetMemoryCellcharWordType(strWorkingWord,Result)==typeContraction){
                                cout << "  Contraction Word Long Form First:" << GetMemoryCellContractionFirst(strWorkingWord,Result) << endl;
                                cout << "  Contraction Word Long Form Second:" << GetMemoryCellContractionSecond(strWorkingWord,Result) << endl;
                            }
                            cout << "Cell Secondary Word Type  :" << GetMemoryCellcharSecondaryWordType(strWorkingWord,Result) << endl;
                            cout << "Cell Alternate Word Type  :" << GetMemoryCellcharAlternateWordType(strWorkingWord,Result) << endl;
                            cout << "Cell Data Tense           :" << GetMemoryCellcharWordTense(strWorkingWord,Result) << endl;

                            cout << "Cell Gender               :" << GetMemoryCellcharGenderClass(strWorkingWord,Result) << endl;
                            cout << "Cell Primary Usage        :" << GetMemoryCellcharPurpose(strWorkingWord,Result) << endl;
                            cout << "Cell Data is Set          :" << boolalpha << GetMemoryCellIsSet(strWorkingWord,Result) << endl;
                            cout << "Cell Plural flag          :" << GetMemoryCellcharIsSingular(strWorkingWord,Result) << endl;
                            cout << "Plural Root               :" << GetMemoryCellpSingularForm(strWorkingWord,Result) << endl;
//                            cout << "Cell used as subject count:" << GetMemoryCellpTimesUsedAsSubject(strWorkingWord,Result) << endl;
//                            cout << "Cell adjectives stored in map:" << GetMemoryCellNumberOfAdjectives(strWorkingWord,Result) << endl;
//                            cout << "Cell verbs stored in map     :" << GetMemoryCellNumberOfVerbs(strWorkingWord,Result) << endl;
//                            cout << "Cell adverbs stored in map   :" << GetMemoryCellNumberOfAdVerbs(strWorkingWord,Result) << endl;
//                            cout << "Cell Adjectives, Verbs, Adverbs:\n";
//                              for(int x = 0; x< GetMemoryCellNumberOfAdjectives(strWorkingWord,Result); x++){
//                                 cout  << "   " << GetMemoryCellAdjectiveFromList(strWorkingWord,x,Result) << " " << GetMemoryCellVerbFromList(strWorkingWord,x,Result)
//                                       << " " << GetMemoryCellAdverbFromList(strWorkingWord,x,Result) << endl;
//                               }
//                            cout << endl;
//                            y = GetMemoryCellNumberOfRelatedNouns(strWorkingWord,Result);
//                            cout << "Cell related Nouns("  << y << "):\n";
//
//                               for(int x = 0; x< y;x++){
//                                 cout << "   " << GetMemoryCellNounFromList(strWorkingWord,x,Result) << endl;
//                               }

                    }//end if result
                    else
                        cout << strWorkingWord << " not in memory!\n";

                    Control = 2;
                    break;
                }

            case 21244631:   // map summary
                {
                    int NounCount,VerbCount,AdjectiveCount,AdverbCount,PronounCount,PropernounCount,WordCount,UnknownCount,KnownCount;
                    float Ratio;
                    WordCount = GetRightLobeCellMapSummary(VerbCount,NounCount,AdjectiveCount,AdverbCount,PronounCount,PropernounCount,UnknownCount,KnownCount,Ratio);
                    cout << "Total Words in memory cells:" << WordCount <<  "  Total in Left Lobes:" << GetLeftLobeCellMapCount() <<  " Sentences saved:" << GetNumberOfSentencesSaved() << endl;
                    cout << " Nouns        :" << NounCount << endl;
                    cout << " Verbs        :" << VerbCount << endl;
                    cout << " Adjectives   :" << AdjectiveCount << endl;
                    cout << " Adverbs      :" << AdverbCount << endl;
                    cout << " Pronouns     :" << PronounCount << endl;
                    cout << " Proper Nouns :" << PropernounCount << endl;
                    cout << " Unknown Words:" << UnknownCount << endl;
                    cout << " Known Words  :" << KnownCount << endl;
                    cout << " Memory Ratio :" << Ratio << endl;
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
                    Control = 2; int z = 0;
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
