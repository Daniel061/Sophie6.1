#ifndef C_CORTEX_H
#define C_CORTEX_H
#include <c_Language.h>

class c_Cortex : public c_Language
{
    public:
        c_Cortex();
        virtual ~c_Cortex();

   private:

            int Control;
            string Pattern;
            char tmpWordType;
            int NounLocation;
            int DeterminerLocation;
            int ProNounOtherLocation;
            int ProNounInwardLocation;
            int ProNounOutwardLocation;
            int AssociativeWordLocation;
            int VerbLocation;
            int AdjectiveLocation;
            int SubjectLoc;
            int ReplacementLocation;
            int UnderstandingLevel;
            int UnderstandingDegree;
            int UnknownCount;
            int UnKnownLocation;
            int FirstUnknown;
            int QuestionLocation;
            int UserResponse;
            int ContractionLocation;
            int ConjunctionLocation;
            int AdverbLocation;
            int DirectiveLocation;
            int JoinerLocation;
            int DirectObjectLocation;
            int IndirectObjectLocation;
            int PluralPossessiveLocation;
            int PluralPronounLocation;
            int ProperNounLocation;
            int GenderIndicatorLocation;
            bool isGenderIndicator;
            float UnderstandingRatio;
            bool ISQ;
            bool Rerundecipher = false;
            bool ForcedSubjectChange = false;


    public:
        bool DecipherCurrentSentence(string &strData){
            if(Verbose){cout << "[c_Cortex.h::DeciperCurrentSentence]" << endl;}

            SubjectLoc               = GetSubjectLocation();
            AdjectiveLocation        = -1;
            FirstUnknown             = -1;
            ContractionLocation      = -1;
            ConjunctionLocation      = -1;
            DeterminerLocation       = -1;
            ProNounOtherLocation     = -1;
            ISQ                      = false;
            ForcedSubjectChange      = false;
            Pattern                  = "";
            NounLocation             = -1;
            Control                  = -1;
            UnderstandingLevel       = 0;
            UnderstandingRatio       = 0.0;
            UnknownCount             = 0;
            QuestionLocation         = 0;
            AdverbLocation           = -1;
            DirectiveLocation        = -1;
            JoinerLocation           = -1;
            DirectObjectLocation     = -1;
            IndirectObjectLocation   = -1;
            PluralPossessiveLocation = -1;
            ProNounInwardLocation    = -1;
            ProNounOutwardLocation   = -1;
            AssociativeWordLocation  = -1;
            PluralPronounLocation    = -1;
            ProperNounLocation       = -1;
            UnKnownLocation          = -1;
            bool Greetings           = false;
            GenderIndicatorLocation  = -1;
            isGenderIndicator        = false;

            for(int x =0; x < GetWordCount(); x++){                                                                  // Build pattern string i.e. duvu  4 word sentence
                    Pattern += GetWordType(x);
                    tmpWordType = GetWordType(x);
                    if (tmpWordType == 't') {UnderstandingLevel++;}
                    if (tmpWordType == 'c') {UnderstandingLevel++; ConjunctionLocation = x;}
                    if (tmpWordType == 'n') {NounLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'd') {DeterminerLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'p') {ProNounOtherLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'y') {ProNounOutwardLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'm') {ProNounInwardLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'g') {AssociativeWordLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'v') {VerbLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'a') {AdjectiveLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'r') {ReplacementLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'q') {QuestionLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'C') {ContractionLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'A') {AdverbLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'X') {DirectiveLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'P') {ProperNounLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'j') {JoinerLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 's') {PluralPossessiveLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'N') {PluralPronounLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'G') {GenderIndicatorLocation = x; UnderstandingLevel++; isGenderIndicator = true;}
                    if (tmpWordType == 'W') {UnderstandingLevel++;}
                    if (tmpWordType == 'B') {UnderstandingLevel++;}
                    if (tmpWordType == 'I') {UnderstandingLevel++;}
                    if (tmpWordType == 'u') {
                            UnknownCount++; UnKnownLocation = x;
                            if(FirstUnknown == -1) FirstUnknown = x;
                            }
            }


            SetPattern(Pattern);
            ISQ = GetIsQuestion();
            if(UnderstandingLevel > 0)
                UnderstandingRatio = float(UnderstandingLevel) / float(GetWordCount());

            ///Set the understanding degree weighted with the ratio
            if(UnderstandingRatio == 1) UnderstandingDegree = 100;
             else
                if(UnderstandingRatio >= .75) UnderstandingDegree = 75;
             else
                if(UnderstandingRatio >= .50) UnderstandingDegree = 50;
             else
                if(UnderstandingRatio >= .25) UnderstandingDegree = 25;
             else
                if(UnderstandingRatio >= .10) UnderstandingDegree = 10;
             else
                UnderstandingDegree = 0;
            if(Verbose)
             cout << "Pattern: " + Pattern + " Understanding Level:" << UnderstandingLevel << " Ratio:" << UnderstandingRatio<< " Is Question:" << ISQ << " Degree:" << UnderstandingDegree << " Unknown Count:" << UnknownCount << "\n";

            if(ISQ == true)UnderstandingDegree = 1;               //question trap
            if(DirectiveLocation >=0)UnderstandingDegree = 2;     //directive trap
            if(PluralPronounLocation >=0)UnderstandingDegree = 3; //plural pronoun trap
            if(GetHasGreetingsWord())UnderstandingDegree = 4;     //greetings trap

        ofstream PatternDataFile ("PatternData.dat", ios::out | ios::app);
        if (PatternDataFile.is_open()){ PatternDataFile << Pattern << "," << GetOriginalString() << ",from before Switch(UnderstandingDegree)" << endl; PatternDataFile.close();}

            switch (UnderstandingDegree)
            {
               case 0:{  ///All new words, lots of work to do
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 0" << endl;


                 switch(GetMoodLevel()){
                    case  0:{
                      SlowSpeak(":x");
                      DecreaseMoodLevel();
                      break;
                   }
                    case 1:{
                      SlowSpeak("I'm sorry."); SlowSpeak("I don't understand this yet.");
                      SlowSpeak("Can you reword it somehow?");
                      SlowSpeak(":(");
                      DecreaseMoodLevel();
                      break;
                   }
                    case 2:{
                      SlowSpeak("I'll try harder next time.");
                      SlowSpeak(":o");
                      DecreaseMoodLevel();
                      break;
                     case 3:{
                       SlowSpeak("I don't know what " + GetWords(0)+ " is.");
                       SlowSpeak(":{");
                       DecreaseMoodLevel();
                       break;
                     }
                    }

                 }



                 break;
               }
               case 1:{ //question trap
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 1 - Question trap" << endl;
                   if(!QuestionSentenceBreakDown())
                   HandleQuestion(strData);
                   break;}

               case 2:{ //directive trap
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 2 - directive trap" << endl;
                    HandleDirective();
                    break;}

               case 3:{ //plural pronoun trap
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 3 - Plural pronoun trap" << endl;
                    HandlePluralPronoun(PluralPronounLocation);
                    break;}

                case 4:{ //Greetings trap
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 4 - Greetings trap" << endl;
                    CheckForGreetings(Greetings);
                    break;}

                case 10:{  ///Only 1 known but could have a ratio of 100%
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 10 - no code here" << endl;

                     SlowSpeak("I'm going to have to work on this.");
                     break;}

                case 25:{  ///Some understanding but depends on ratio
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 25 - Maybe Missing determiner - add in the help" << endl;
                    if(GetWordType(0) == 'u'){
                     strData = "the " + strData;
                     return true;}
                     else
                      SlowSpeak("I don't know "  + GetWords(FirstUnknown)+"?");
                    break;}

                case 50:{  ///stronger understanding but also depends on ratio
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 50 -send to WorkWithHalfLevel()" << endl;
                     WorkWithHalfLevel(Pattern,DeterminerLocation);
                     break;}

                case 75:{  ///Much stronger
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 75 - send to Handle75LevelUnderstanding" << endl;
                     Handle75LevelUnderstanding(strData);
                     break;}

                case 100:{  ///very strong
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 100 - inside logic" << endl;
                    string tmpSubject;
                    if(GetSubjectLocation() != -1){
                         tmpSubject = GetWords(SubjectLoc);
                         SetSubjectInStack(GetWordTokens(SubjectLoc),tmpSubject,GetOriginalString());
                         if(GetWordType(GetSubjectLocation())=='p'){
                            CheckForImpliedGender();}}
                     if((GetHasGenderReference()) && (GetSubjectLocation()!=-1)){
                        //assign Gender to subject
                        if(GenderIndicatorLocation != -1){
                            SetGenderClassInSentence(GetSubjectLocation(),GetGenderClassInSentence(GenderIndicatorLocation));
                        }
                     }
                     if((JoinerLocation != -1) && (Pattern[JoinerLocation+1]=='a') ){ //associate first adjective to subject, wasn't picked up before
                        AssociateMemoryCellAdjective(GetWordTokens(GetSubjectLocation()),GetWordsLC(JoinerLocation-1)); }
                     SlowSpeak("Okay.");
                     IncreaseMoodLevel();
                     SetHasBeenUnderstood(true);
                     SlowSpeak(":)");
                     break;}

            }
             return false;
            }
//--------------------------------------END DECIPHER SENTENCE------------------------------------------------------------------------

//-------------------------------------Check for greetings---------------------------------------------------------------------------
int CheckForGreetings(bool& Greeting){
    string FirstWord;
    FirstWord = GetWordsLC(0);
    Greeting = false;
    if((FirstWord == "hello") | (FirstWord == "hi")){
        SlowSpeak("Hi!");
        IncreaseMoodLevel();
        SlowSpeak("How are you?");
        Greeting = true;
        SetHasBeenUnderstood(true);

    }
    return -1;
}
//---------------------------------------end greetings-------------------------------------------------------------------------------

//-------------------------------------PROCESS MIDLEVEL UNDERSTANDING----------------------------------------------------------------

int WorkWithHalfLevel(string Pattern, int Determiner){
    if(Verbose){cout << "[c_Cortex.h::WorkWithHalfLevel]" << endl;}
       int Response;
       string tmpAdjective;
       int StatementDirection = -1;
       int tmpAdjectiveLoc;
       bool Testing = true;
       if(Verbose)
            cout << "Noun Loc:" << NounLocation << "Unknown Loc:" << UnKnownLocation << "Pattern:" << Pattern << endl;

        ofstream HalfLevelDataFile ("HalfLevelPatternData.dat", ios::out | ios::app);
        if (HalfLevelDataFile.is_open()){ HalfLevelDataFile << Pattern << "," << GetOriginalString() << endl; HalfLevelDataFile.close();}
       for(int x = 0; x < GetWordCount(); x++){
        if((GetWordType(x) == 'y') || (GetWordType(x) == 'm') || (GetWordType(x) == 'p')){
            if(GetWordType(x)== 'y') StatementDirection = 0; //Statement towards user
            if(GetWordType(x)== 'm') StatementDirection = 1; //Statement towards program
            if(GetWordType(x)== 'p') StatementDirection = 2; //Statement towards other
        }
       }

//cout << "Pattern 1/2 level:" << Pattern << endl;
       while(Testing){

         switch (StatementDirection){

            case 0: //Statement towards user
                {
                  if((GetWords(UnKnownLocation)[0]>='A') && (GetWords(UnKnownLocation)[0]<='Z')) {
                    //Proper noun is unknown word - user might be naming self
                    SetWordType('P',UnKnownLocation);
                    SlowSpeak("Hello " + GetWords(UnKnownLocation) + "!");
                    SlowSpeak("Nice to meet you.");
                    SlowSpeak(":)");
                    IncreaseMoodLevel();
                    SetHasBeenUnderstood(true);
                    SetUserName(GetWords(UnKnownLocation));

                  }
                  else
                  {
                      //user may be using an adjective
                  }


                  if(Verbose){cout << "[c_Cortex.h::WorkWithHalfLevel]:Case 0" << endl;}
                  Testing = false;
                  break;
                }

            case 1: //Statement towards program
                {

                  if(Verbose){cout << "[c_Cortex.h::WorkWithHalfLevel]:Case 1" << endl;}
                  Testing = false;
                  break;
                }
            case 2: //Statement towards other
                {

                  if(Verbose){cout << "[c_Cortex.h::WorkWithHalfLevel]:Case 2" << endl;}
                  Testing = false;
                  break;
                }
            default:
                {
                  Testing = false;
                }


         SlowSpeak("  Are we talking about a " + GetWords(Determiner + 1) + "?");
         Response = RequestUserResponse();
         if(Response == 1){  //yes answer
            //set subject to this
            //set wordtype to noun if it isn't
            //see if this is a known word
            IncreaseMoodLevel();
            SetWordType('n',Determiner+1);
            SetSubjectInStack(Tokenize(GetWords(Determiner+1)),GetWords(Determiner+1),GetOriginalString());
            for(int x =0; x < GetWordCount(); x++){
                if (GetWordType(x)=='u'){
                    tmpAdjective = GetWords(x);
                    tmpAdjectiveLoc = x;
                }
            }
            SlowSpeak("Great!");
            SlowSpeak("But I don't know much about a " + GetWords(Determiner +1)+ " yet.");
            SlowSpeak("And, is " + tmpAdjective + " describing " + GetWords(Determiner +1)+ "?");
            Response = RequestUserResponse();
            if(Response == 1){
                    SlowSpeak("Perfect!");
                    IncreaseMoodLevel();
                    SlowSpeak("So a " + tmpAdjective + " " + GetWords(Determiner+1) + ". Ha!");
                    SlowSpeak("Can you tell me more about " + GetWords(Determiner +1)+ "?");
                    SlowSpeak("I want to learn more!");
                    SlowSpeak(":)");
                    IncreaseMoodLevel();
                    SetHasBeenUnderstood(true);
                    SetWordType('a',tmpAdjectiveLoc);
                    SetWordType('n',Determiner+1);
                    RebuildPattern();
                    Testing = false;

            }
            else{
                SlowSpeak(":(");
                DecreaseMoodLevel();
                Testing = false;

            }
            //release control back for more user input
         }
         else{
            SlowSpeak("  Are we talking about a " + GetWords(Determiner + 2) + "?");
            Response = RequestUserResponse();
            if(Response == -1){
                SlowSpeak("  Are we talking about a " + GetWords(Determiner + 3) + "?");
                DecreaseMoodLevel();
                Response = RequestUserResponse();
                if(Response == 1){
                    SlowSpeak("I will need to learn about " + GetWords(Determiner + 3)+".");
                    SlowSpeak("Please tell me more.");
                    IncreaseMoodLevel();
                    SetHasBeenUnderstood(true);
                    Testing = false;
                    //set subject
                }
                else{
                    SlowSpeak("I'm lost.");
                    SlowSpeak("I need to learn more before I understand this.");
                    SlowSpeak(":(");
                    DecreaseMoodLevel();
                    Testing = false;
                }
            }
            else{
                SlowSpeak("Ok");
                SlowSpeak("You'll have to tell me more about a " + GetWords(Determiner+2)+ ".");
                SetWordType('n',Determiner+2);
                SetSubjectInStack(Tokenize(GetWords(Determiner+2)),GetWords(Determiner+2),GetOriginalString());
                IncreaseMoodLevel();
                SetHasBeenUnderstood(true);
                Testing = false;
                //set subject
            }
         }
         }//end switch statement

     }//end control Loop
     return 0;
}//end work with half level
//---------------------------------------------------------------------------------------------------------------
int HandleQuestion(string &strData){
    //***TODO**
    //check for multi match and handle

    if(Verbose){cout << "[c_Cortex.h::HandleQuestion]" << endl;}
    int Control;    Control = -1;
    int MatchedCount;
    string VerbUsed, MatchedAdjective[15];
    string AnswerString;
    bool Matched = false;
    if(Verbose)
        cout << "qLoc:" << QuestionLocation << " Pattern:" << Pattern << " SubjectLoc:" << GetSubjectLocation() << endl;
    if(UnKnownLocation >=0){
            Handle75LevelUnderstanding(strData,true); //try to find the unknown but run silent.
            FindSubject();}

   // check for correct form
   //actually need to compare indirect object to subject
    if(GetIndirectObjectLocation() != -1)
    Matched = CheckLinkOfTwoNounsWithAdjectives(GetWords(GetIndirectObjectLocation()),GetWords(GetSubjectLocation()),VerbUsed,MatchedAdjective,MatchedCount);
    if (Matched){
            if(MatchedCount > 1){
                AnswerString = "The " +  GetWordsLC(GetSubjectLocation()) + " of ";
                if(!(GetWordType(GetIndirectObjectLocation())== 'P') || (GetWordType(GetIndirectObjectLocation())== 'p')) AnswerString += "the ";
                AnswerString +=  GetWords(GetIndirectObjectLocation()) + " can be ";
                for(int x = 0; x < MatchedCount; x++){
                        AnswerString = AnswerString + MatchedAdjective[x];
                        if(!(x+1==MatchedCount)) AnswerString += " or ";}
                AnswerString += ".";
                SlowSpeak(AnswerString);
                SetHasBeenUnderstood(true);
            }
            else{
               AnswerString = "The " +  GetWordsLC(GetSubjectLocation()) + " of ";
               if(!(GetWordType(GetIndirectObjectLocation())== 'P') || (GetWordType(GetIndirectObjectLocation())== 'p')) AnswerString += "the ";
               AnswerString +=  GetWords(GetIndirectObjectLocation())+ " is " + MatchedAdjective[0] + ".";
               SlowSpeak(AnswerString);
               SetHasBeenUnderstood(true);
            }
        }
        else
        SlowSpeak("You haven't told me yet.");
    if(Verbose)
        cout << "Matched:" << Matched << " Verb:" << VerbUsed << " Adjective: " << MatchedAdjective[0] << endl;

  return Control;
}
//End HandleQuestion-----------------------------------------------------------------------------------------------

//--------------------------------HANDLE75LEVELUNDERSTANDING-------------------------------------------------------
void Handle75LevelUnderstanding(string &strData, bool RunSilent = false){
    bool Testing                = true;
    bool NeedNameHandling       = false;
    bool VerbFollowsNamePtr     = false;
    int LocalNamePtrLocation    = GetNamePointer();
    int localVerbLocation       = -1;
    int SubjectLocationInCortex = -1;
    //in case of recursive entry, scan for unknown location again
//cout << "at 757Levelunderstanding with pattern of:" << Pattern << endl;
    if(Verbose){
        cout << "[c_Cortex.h::Handle75LevelUnderstanding]\n";
        cout << "  Pattern:" << Pattern << endl;
        cout << "  Run Silent:" << boolalpha << RunSilent << endl;
        cout << "  Subject Location:" << GetSubjectLocation() << endl;
        cout << "  Noun Location:" << NounLocation << endl;
        cout << "  Adjective Location:" << AdjectiveLocation << endl;
        cout << "  Verb Location:" << VerbLocation << endl;}

    if(GetNamePointer() >=0){
        NeedNameHandling = true;
        if(GetWordType(LocalNamePtrLocation+1)=='v')
            VerbFollowsNamePtr = true;
    }


//   if(NounLocation == -1){
//            NounLocation = GetSubjectLocation(); //no noun! How to handle this Kenzie??  she says if pronoun(or Proper noun) use it as noun and subject
//            ForcedSubjectChange = true;
//   }

                                                                                 //check for name handling work first
   if( NeedNameHandling ){                                                       // i.e. my name is ...   or the dog's name is ...
        Testing = false;                                                         // this is the only work required because of name reference
        if(VerbFollowsNamePtr){                                                  // try to prevent out of bounds error
        if(GetWordType(LocalNamePtrLocation-1) == 'y'){                          // the name data refers the the user, REMEMBER - this is a statement, not a question ~ questions trapped elsewhere
                if(IsThisAPropernoun(GetWords(LocalNamePtrLocation+2))){         // enforce Capital letter usage
                    SetUserName(GetWords(LocalNamePtrLocation+2));               // Store the user name
                    SlowSpeak("Hello " + GetWords(LocalNamePtrLocation+2)+"!");  // greet the user
                    SlowSpeak("Nice to meet you!");
                    SetWordType('P',LocalNamePtrLocation+2);                     // Make sure word type is set
                    }
        }//end outward direction
        }//end ensure verb follows name
   }//end name handling




   while(Testing && (NounLocation >=0)){

    //----------Missing Noun Test------
    if((NounLocation == -1) && (VerbLocation >=0) && (DeterminerLocation >=0) && (AdjectiveLocation >=0)){ //no noun but has verb, determiner and adjective
        SlowSpeak("So " + GetWords(DeterminerLocation+1)+ " can be " + GetWords(AdjectiveLocation) + "?");
        UserResponse = RequestUserResponse();
        if(UserResponse == 1){
            SetWordType('n',DeterminerLocation+1);    //set the noun
            SetSubjectLocation(DeterminerLocation+1); //be sure subject location is newly found noun
            SlowSpeak(":)"); IncreaseMoodLevel();
            SetHasBeenUnderstood(true);
            Testing = false;
            break;}
    }
    else{
        if( (NounLocation == -1) && (VerbLocation >=0) && (DeterminerLocation >=0) ){    // no noun but has verb and determiner
            SlowSpeak(" Are we talking about a" + GetWords(DeterminerLocation+1) + "?");
            UserResponse = RequestUserResponse();
            if(UserResponse == 1){
                SetWordType('n',DeterminerLocation+1);
                SetSubjectLocation(DeterminerLocation+1);
                SlowSpeak(":)");
                IncreaseMoodLevel();
                SetHasBeenUnderstood(true);
                Testing = false;
                break;}
            }
         else{
             if( (NounLocation == -1) && (VerbLocation >=0) && (GetHasGenderReference()) ){  // no noun but has verb and gender reference
                if(IsThisAPropernoun(GetWords(UnKnownLocation))){
                    SetWordType('P',UnKnownLocation);
                    SubjectLocationInCortex = FindSubject();
                    SetSubjectLocation(SubjectLocationInCortex);
                    RebuildPattern();
                    DecipherCurrentSentence(strData);
                    Testing = false;
                    break;}
                 else  {
                    SetWordType('n',UnKnownLocation);
                    SubjectLocationInCortex = FindSubject();
                    SetSubjectLocation(SubjectLocationInCortex);
                    RebuildPattern();
                    DecipherCurrentSentence(strData);
                    Testing = false;
                    break;

                 }
             }

            }
    } //------End Missing noun test------


    // --TEST FOR MISSING VERB--------------
    for(int x= 0; x < GetWordCount(); x++){
        if(GetWordType(x)=='v') localVerbLocation = x;}


    if(localVerbLocation == -1 ){
        if(UnKnownLocation != -1){
            SetWordType('v',UnKnownLocation);
            Testing = false;
            SlowSpeak("Okay.");
            SetHasBeenUnderstood(true);
            break;
        }
    }



    //--END TEST FOR MISSING VERB ----------

    //-------Modifier Test-------------
    int tmpLocation; tmpLocation = Pattern.find("uav");
    if(tmpLocation >= 0){


        SlowSpeak("So " + GetWords(NounLocation)+" can be " +
                  GetWords(tmpLocation)+ " "+
                  GetWords(AdjectiveLocation)+ "?");
                  UserResponse = RequestUserResponse();
                  if(UserResponse == 1){ //tmpLocation has to be adverb(A)
                        SetWordType('A',tmpLocation);
                        SlowSpeak(":)"); IncreaseMoodLevel();
                        SetHasBeenUnderstood(true);
                  }
                  else{
                    SlowSpeak(":("); DecreaseMoodLevel();
                  }


       Testing = false;
       break;
    }




    //-------End Modifier test---------



    //-------Noun to Noun test---------
    //i.e. the dog is an animal

    tmpLocation = Pattern.find("dnvdu") + Pattern.find("duvdn") + 1;  //if one .find returns -1 it is removed with the +1, if both return -1, the +1 results in -1
    if (tmpLocation>=0){
        if(!RunSilent)
            SlowSpeak("Okay. Tell me more about " + GetWordsLC(UnKnownLocation-1) + " " + GetWordsLC(UnKnownLocation) + ".");
            SetHasBeenUnderstood(true);
        if(Pattern[tmpLocation+1]== 'u'){
           AssociateMemoryCellNoun(GetWordTokens(tmpLocation),GetWordsLC(tmpLocation+1));                                 //associate first noun to second noun
           AssociateMemoryCellNoun(GetWordTokens(tmpLocation+3),GetWordsLC(tmpLocation+4));                               //associate second noun to first noun
           SetWordType('n',tmpLocation+1);}
         else{
           AssociateMemoryCellNoun(GetWordTokens(tmpLocation),GetWordsLC(tmpLocation+4));                                 //associate first noun to second noun
           AssociateMemoryCellNoun(GetWordTokens(tmpLocation+3),GetWordsLC(tmpLocation+1));                               //associate second noun to first noun
           SetWordType('n',tmpLocation+4);}
        FindSubject();                                                                                                    //Update subject
        SetSubjectInStack(GetWordTokens(GetSubjectLocation()),GetWords(GetSubjectLocation()),GetOriginalString());        //update subject stack
        CheckForImpliedName();
        Testing = false;
        break;
    }
    //---------End Noun to noun test----------



    //----------Adjective Test---------
    if(UnKnownLocation >=0){
       if(GetPluralWordFlag(NounLocation) == 'p'){
           SlowSpeak(GetWords(UnKnownLocation) + " " + GetWords(NounLocation) + "?");}
           else{
                SlowSpeak( "A " + GetWords(UnKnownLocation) + " " + GetWords(NounLocation) + "?");}
        UserResponse = RequestUserResponse();
        if(UserResponse == 1){
            SetWordType('a',UnKnownLocation);  //set word type to adjective
            SlowSpeak(":)"); IncreaseMoodLevel();
            SetHasBeenUnderstood(true);
            Testing = false;
            break;}
            else{
                SlowSpeak(":("); DecreaseMoodLevel();
                Testing = false;
                break;
            }}
    //---end Adjective Testing ----------


    //-- DNVUA -- Test for u = Adverb -----
    // the dog is very fast.
    SlowSpeak("A " + GetWords(UnKnownLocation) + " " + GetWords(AdjectiveLocation) + " " + GetWords(GetSubjectLocation()) + "?");
    UserResponse = RequestUserResponse();


    Testing = false;
    break;
    //-- END TESTING FOR ADVERB ------------





   }//---end testing control loop
   if(Verbose)
    cout << "  New Pattern:" << GetPattern() << endl;
}
//-----------------------------END HANDLE75LEVELUNDERSTANDING -------------------------------

//----------------------ISTHISAPROPERNOUN----------------------------------------------------
    bool IsThisAPropernoun(string strDataToTest){
        if((strDataToTest[0] >= 'A') && (strDataToTest[0] <= 'Z') )
            return true;
        else
            return false;

    }
//-----------------END ISTHISAPROPERNOUN------------------------------------------------------




//------------------------DIRECTIVE TRAP-----------------------------------------------------

    void HandleDirective(){
        int CompareMode, dLoc; CompareMode = 0;
        int MatchedCount;
        string Noun1,Noun2,VerbUsage,MatchedAdjective[15],WorkingPattern, ResponseString;
        Noun1 = ""; Noun2 = "";
        if(Verbose)cout << "[c_Cortex.h::Directive Trap] Pattern:" << Pattern << " ";



        if((GetWordTokens(DirectiveLocation) == 2972) || (GetWordTokens(DirectiveLocation)==1070)){
            if(Verbose) cout << "compare/same directive ";
            //extract determiners 'd' from pattern
            WorkingPattern = Pattern;
            dLoc = WorkingPattern.find('d');
            while((dLoc >=0) & (dLoc <= int(WorkingPattern.size()))){
                WorkingPattern = WorkingPattern.substr(0,dLoc) + WorkingPattern.substr(dLoc+1);
                dLoc = WorkingPattern.find('d');}

            if( (WorkingPattern.find("njn") >= 0) && (WorkingPattern.find("njn")<=WorkingPattern.size()) ) CompareMode = 3;
            if( (WorkingPattern.find("nun") >= 0) && (WorkingPattern.find("nun")<=WorkingPattern.size()) ) CompareMode = 3;
            if( (WorkingPattern.find("aua") >= 0) && (WorkingPattern.find("aua")<=WorkingPattern.size()) ) CompareMode = 1;
            if( (WorkingPattern.find("aja") >= 0) && (WorkingPattern.find("aja")<=WorkingPattern.size()) ) CompareMode = 1;
            if( (WorkingPattern.find("aun") >= 0) && (WorkingPattern.find("aun")<=WorkingPattern.size()) ) CompareMode = 2;
            if( (WorkingPattern.find("ajn") >= 0) && (WorkingPattern.find("ajn")<=WorkingPattern.size()) ) CompareMode = 2;
            if( (WorkingPattern.find("Aua") >= 0) && (WorkingPattern.find("Aua")<=WorkingPattern.size()) ) CompareMode = 4;
            if( (WorkingPattern.find("Aja") >= 0) && (WorkingPattern.find("Aja")<=WorkingPattern.size()) ) CompareMode = 4;
            if( (WorkingPattern.find("AuA") >= 0) && (WorkingPattern.find("AuA")<=WorkingPattern.size()) ) CompareMode = 5;
            if( (WorkingPattern.find("AjA") >= 0) && (WorkingPattern.find("AjA")<=WorkingPattern.size()) ) CompareMode = 5;
            if( (WorkingPattern.find("Aun") >= 0) && (WorkingPattern.find("Aun")<=WorkingPattern.size()) ) CompareMode = 6;
            if( (WorkingPattern.find("Ajn") >= 0) && (WorkingPattern.find("Ajn")<=WorkingPattern.size()) ) CompareMode = 6;

                switch(CompareMode){

                    case 3: //noun to noun
                        {
                            for(int x =0; x < GetWordCount(); x++){
                                if((GetWordType(x)=='n')&&(Noun1 == "")) Noun1 = GetWordsLC(x);
                                else
                                    if(GetWordType(x)=='n') Noun2 = GetWordsLC(x);}

                             if(Verbose) cout << "Noun to Noun :" << Noun1 << " " << Noun2 << endl;

                             if (CheckLinkOfTwoNounsWithAdjectives(Noun1,Noun2,VerbUsage,MatchedAdjective,MatchedCount)){
                                    if(MatchedCount > 1){
                                        ResponseString = "They both can be " + MatchedAdjective[0] + " or ";
                                        for(int x = 1; x< MatchedCount; x++)ResponseString += MatchedAdjective[x];
                                        ResponseString += ".";}
                                     else
                                        ResponseString = "They both can be " + MatchedAdjective[0] + ".";

                                 SlowSpeak(ResponseString);
                                 SetHasBeenUnderstood(true);
                                 SlowSpeak(":)");}
                              else{


                                  if(GetIsNounRelatedToThisMemoryCell(Tokenize(Noun1),Noun2)){
                                    SlowSpeak("A " + Noun1 + " is a " + Noun2 + ".");
                                    SetHasBeenUnderstood(true);}
                                 else{
                                 SlowSpeak("I don't know anything alike between " + Noun2 + " and " + Noun1 + ".");
                                 SlowSpeak(":(");}}
                        }

                    default:
                        if(Verbose) cout << "\n";
                }



        }
        else{  //not compare/same directive
          if(Verbose) cout << "\n";}

        if(ISQ) QuestionSentenceBreakDown();

    }


//---------------------DECONSTRUCTCONTRACTIONS()--------------------------------------------
    bool DeconstructContractions(bool &OwnerShip, bool &Plural, string &Root, string &LongFormFirst, string &LongFormSecond, string &strData){

         string TrailingCharacters   = "";    //i.e  cat's = s   baby's = s
         string PreceedingCharacters = "";    //i.e  cat's = cat  baby's = baby
         int    ContractionPointer   = 0;
         int    ContractionCount     = 0;
         string WorkingWord          = "";
         string NewSentence          = "";
                OwnerShip            = false;
                Plural               = false;
                Root                 = "";
                LongFormFirst        = "";
                LongFormSecond       = "";
                ContractionLocation  = -1;

         //error check - ensure a contraction exists
         for(int x = 0; x<= GetWordCount(); x++){
                if(GetWordType(x) == 'C'){
                   if(ContractionLocation == -1)     //process first contraction only  ***TODO*** work with the others if exists
                      ContractionLocation = x;
                   ContractionCount++;}}
         if(ContractionLocation == -1) return false;


         char   FollowingWordType    = GetWordType(ContractionLocation+1);
         //char   PreceedingWordType   = GetWordType(ContractionLocation-1);   future use
         bool   Split                = false;
         bool   NeedRerun            = false;

         WorkingWord           = GetWordsLC(ContractionLocation);
         ContractionPointer    = GetQuoteLocation(ContractionLocation);
         PreceedingCharacters  = WorkingWord.substr(0,ContractionPointer);
         TrailingCharacters    = WorkingWord.substr(ContractionPointer+1);
         Root                  = PreceedingCharacters;

         if(FollowingWordType == 'g'){ // i.e cat's name
            OwnerShip = true;
            LongFormFirst = Root;}
            else{
                 Split = true;}

         if(Split){
            LongFormFirst   = Root;
            if(TrailingCharacters == "s"){LongFormSecond = "is";}
            if(TrailingCharacters == "ll"){LongFormSecond = "will";}
            if(TrailingCharacters == "ve"){LongFormSecond = "have";}
            if(TrailingCharacters == "m"){LongFormSecond = "am";}
            if(TrailingCharacters == "d"){LongFormSecond = "would";}
            if(TrailingCharacters == "re"){LongFormSecond = "are";}

         for(int x =0; x<ContractionLocation; x++){
            NewSentence += GetWords(x) + " ";}
            NewSentence += LongFormFirst + " ";
            NewSentence += LongFormSecond + " ";

         for(int x = ContractionLocation+1; x<= GetWordCount(); x++){
            NewSentence += GetWords(x)+ " ";}
            strData = NewSentence;
            NeedRerun    = true;}

         if(Verbose){
            cout << "c_Cortex.h::DeconstructContraction\n";
            cout << "  " << boolalpha << "OwnerShip:" << OwnerShip << endl;
            cout << "  " << boolalpha << "Plural:" << Plural << endl;
            cout << "  " << boolalpha << "Request Rerun:" << NeedRerun << endl;
            cout << "  " << "Root:" << Root << endl;
            cout << "  " << "Long Form first:" << LongFormFirst << endl;
            cout << "  " << "Long Form second:" << LongFormSecond << endl;
            cout << "   New Sentence:" << NewSentence << endl;}

         SetContractionLongFormFirst(ContractionLocation,LongFormFirst);
         SetContractionLongFormSecond(ContractionLocation,LongFormSecond);

          return NeedRerun;
    }

//-----------------------END DECONSTRUCTCONTRACTIONS()---------------------------------------



    void HandlePluralPronoun(int PluralPronounLocation){     // i.e. both

        //**TODO**
        //Check the word type after PluralPronounLocation
        // could be adverb

        string Noun1       = "";
        string Noun2       = "";
        int NounCount      = 0;
        int JoinerLocation = 0;

        for(int x = 0; x < GetWordCount(); x++){
           if(GetWordType(x)=='n'){
                NounCount++;
                if(Noun1 =="")Noun1 = GetWordsLC(x); else Noun2 = GetWordsLC(x);}
            if(GetWordType(x)=='j') JoinerLocation = x;}


         if((JoinerLocation >0)&(NounCount==2)){ //two nouns with joiner
                AssociateMemoryCellAdjective(Tokenize(Noun1),GetWordsLC(PluralPronounLocation+1));
                AssociateMemoryCellAdjective(Tokenize(Noun2),GetWordsLC(PluralPronounLocation+1));
                SetWordType('a',PluralPronounLocation+1);
                SlowSpeak("Alright.");
                SlowSpeak(":)");
                SetHasBeenUnderstood(true);
                IncreaseMoodLevel();}
          else{
                SlowSpeak(":{");
                DecreaseMoodLevel();}
    }

//--------------------Question Sentence Break Down----------------------------------------------------------
    bool QuestionSentenceBreakDown(){

        //int PatternMatch        = 0;
        int DirectionOfQuestion = -1;
        int MatchedAdjective    = -1;
        int Adjectives[20];
        int LinkedNouns[20];
        int LinkedNounCount     = -1;
        int IndirectObjectLoc   = GetIndirectObjectLocation();
        int SubjectLocation     = GetSubjectLocation();
        int AdjectiveCount      = GetMemoryCellAdjectives(GetWordTokens(SubjectLocation),Adjectives)-1;
        bool ToMe               = false;
        bool Result             = false;
        int Response            = -1;
        char GenderChar         = '\0';
        string WorkingPattern   = GetPattern();



        DirectionOfQuestion = GetSentenceDirection();
        switch (DirectionOfQuestion){

            case 0: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction toMe\n";


                if((GetHasGenderDeterminer()) || (GetHasGenderReference())){
                    GenderChar = GetMyGender();
                    if(GenderChar == 'f'){SlowSpeak("I'm a girl."); Result = true; SetHasBeenUnderstood(true);}
                       else
                          if(GenderChar == 'm') {SlowSpeak("I'm a boy.");Result = true; SetHasBeenUnderstood(true);}
                             else
                                {SlowSpeak("You haven't said yet.");Result = true; SetHasBeenUnderstood(true);}
                    break;
                }

                if((GetWordsLC(0)=="how")&& (GetWordsLC(GetVerbLocation()) == "are") && (GetSubjectLocation() == -1)){
                    SlowSpeak("I'm fine thanks!");
                    SlowSpeak("But I want to learn all that I can. Will you teach me something please?");
                    Response = RequestUserResponse();
                    if (Response == 1){
                        SlowSpeak("Thank you!");
                        SlowSpeak(":)");
                        SetHasBeenUnderstood(true);
                        Result = true;} //using this as a control here
                        else{
                            SlowSpeak(":(");
                            Result = true;
                            break;}}
                   if((GetWordsLC(0)=="how")&& (GetWordsLC(GetVerbLocation()) == "are") && (GetSubjectLocation() != -1)) {
                      if(GetWordType(GetSubjectLocation())=='r'){ //this
                        SlowSpeak("I'm learning, just like you do.");
                        SlowSpeak("I hope that I am doing a good job.");
                        SlowSpeak(":)");
                        SetHasBeenUnderstood(true);
                        Result = true;
                        break;}}
                   if((GetWordsLC(0)=="how")&& (GetWordsLC(GetVerbLocation()) == "do") && (GetSubjectLocation() != -1)) {
                      if(GetWordType(GetSubjectLocation())=='r'){ //this
                        SlowSpeak("I try.");
                        SlowSpeak(":)");
                        SetHasBeenUnderstood(true);
                        Result = true;
                        break;}}

                    if(GetHasGenderReference()){
                        if(GetMyGender() == GetGenderClassInSentence(GetSubjectLocation())){
                            SlowSpeak("Yes.");
                            Result = true;
                            SetHasBeenUnderstood(true);
                            break;}
                            else{
                                SlowSpeak("No.");
                                Result = true;
                                break;}
                    }



                break;}
            case 1: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction toUser\n";
                break;}
            case 2: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction to Report\n";

                if(GetHasGenderDeterminer()){
                    GenderChar = GetMemoryCellGenderClass(GetWordTokens(GetSubjectLocation()));
                    if(GenderChar == 'f'){SlowSpeak("Girl."); Result = true; SetHasBeenUnderstood(true);}
                       else
                          if(GenderChar == 'm') {SlowSpeak("Boy.");Result = true; SetHasBeenUnderstood(true);}
                             else
                                {SlowSpeak("You haven't said yet.");Result = true; SetHasBeenUnderstood(true);}
                 break;
                }

                break;}
            case 3: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction Yes/No\n";
                bool   LeftOfConjunctionMatch   = false;
                bool   RightOfConjunctionMatch  = false;
                int    LocalConjunctionLocation = GetConjunctionLocation();
                string ResponseString           = "";
                //checks for direct comparison i.e. the dog is black.   is the dog black
                //compares adjective list with the adjective in the sentence
                //sets MatchedAdjective to the location in the array if matched
                //First check for Conjunction
                if(LocalConjunctionLocation >=0){
                    LeftOfConjunctionMatch = GetIsAdjectiveAssociatedToThisMemoryCell(GetWordTokens(GetSubjectLocation()),GetWords(LocalConjunctionLocation-1));
                    RightOfConjunctionMatch = GetIsAdjectiveAssociatedToThisMemoryCell(GetWordTokens(GetSubjectLocation()),GetWords(LocalConjunctionLocation+1));
                    ResponseString = "The " + GetWords(GetSubjectLocation()) + " ";
                    if(LeftOfConjunctionMatch && RightOfConjunctionMatch){
                        ResponseString += "is " + GetWords(LocalConjunctionLocation-1) + " and " + GetWords(LocalConjunctionLocation+1) + ".";
                    }
                    else{
                        if(LeftOfConjunctionMatch){
                            ResponseString += "is " + GetWords(LocalConjunctionLocation-1) + ".";
                        }
                        else{
                            if(RightOfConjunctionMatch){
                                ResponseString += "is " + GetWords(LocalConjunctionLocation+1) + ".";
                            }
                        }
                    }
                    if(LeftOfConjunctionMatch || RightOfConjunctionMatch){
                        SlowSpeak(ResponseString);
                        Result = true;
                        break;
                    }
                    else{
                        ResponseString += "is neither " + GetWords(LocalConjunctionLocation-1) + " or " + GetWords(LocalConjunctionLocation+1) + ".";
                        SlowSpeak(ResponseString);
                        Result = true;
                        break;
                    }
                }

                for(int x = 0; x <= AdjectiveCount; x++){
                    if(Adjectives[x] == GetWordTokens(GetAdjectiveLocation())) MatchedAdjective = x; }
                //Checks for direct comparison of linked nouns between the subject and the indirect object
                //sets MatchedAdjective is found
                if(IndirectObjectLoc >=0){
                    if(GetIsNounRelatedToThisMemoryCell(GetWordTokens(SubjectLocation),GetWordsLC(IndirectObjectLoc))==true) MatchedAdjective = 1;
                }
                //checks for an indirect comparison between the subjects linked nouns and the indirect object linked nouns
                //sets MatchedAdjective if found
                LinkedNounCount = GetMemoryCellRelatedNouns(GetWordTokens(GetSubjectLocation()),LinkedNouns);
                for(int x =0; x < LinkedNounCount; x++){
                    if(GetIsNounRelatedToThisMemoryCell(GetWordTokens(GetIndirectObjectLocation()),GetMemoryCellWordLC("",LinkedNouns[x]))){
                        MatchedAdjective = x;
                    }
                }

                //Checks for gender class request
                if(isGenderIndicator){
                    string FemaleIndicators = " girl female woman women ";
                    int    LocatorPlace     = FemaleIndicators.find(GetWordsLC(GenderIndicatorLocation));
                    char   SubjectsGender   = GetGenderClassInSentence(GetSubjectLocation());

                    if( (SubjectsGender == 'f') && (LocatorPlace >=0) ){
                        MatchedAdjective = 3;  //just using the variable as a control here
                    }

                    if( SubjectsGender == GetGenderClassInSentence(GenderIndicatorLocation)){
                        MatchedAdjective = 3;  //just using the variable as a control here
                    }

                }

                if(MatchedAdjective >=0) {SlowSpeak("Yes."); Result = true;} else {SlowSpeak("No."); Result = true;}

                break;}
             case 4: {//Proper noun reference
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction Proper noun reference\n";
                 string  ReferenceWord = GetWordsLC(GetSubjectLocation());
                 bool    OwnerShip,Plural;
                 string  Root,LongFormFirst,LongFormSecond;
                 string  strData = "";
                 int     RelatedNouns[20];
                 int     RelatedNounCount = -1;

                 if(GetWordType(GetSubjectLocation())=='C'){
                     DeconstructContractions(OwnerShip,Plural,ReferenceWord,LongFormFirst,LongFormSecond,strData);}

                 RelatedNounCount = GetMemoryCellRelatedNouns(Tokenize(ReferenceWord),RelatedNouns);

                 for(int x = 0; x < RelatedNounCount; x++){
                    if(GetMemoryCellWordType(RelatedNouns[x])== 'P')
                        SlowSpeak(GetMemoryCellRawStringData(Result,"",RelatedNouns[x]));
                        Result = true;
                 }

                   if((GetWordsLC(0)=="what")&&
                      (GetWordsLC(GetVerbLocation()) == "is")&&
                      (GetNamePointer() != -1) && (ToMe) ) {
                        SlowSpeak(GetMyName());
                        SlowSpeak(":)");
                        SetHasBeenUnderstood(true);
                        Result = true;
                        break;}


                 if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction Name handler\n";

                 break;
             }
             case 5:{ //data miner, i.e. Who fell down
                 if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Case 5 Data Miner\n";
                  bool   DualSubs      = false;
                  string SecSub        = "";
                  string FrstSub       = "";
                  string strResponse   = "";
                  if(FindPhraseInSentenceMap(GetGistOfSentence())){
                    //phrase exists, pull subject for response
                    FrstSub = GetSubjectWithMatchingPhraseInSentenceMap(GetGistOfSentence(),SecSub,DualSubs);
                    if(DualSubs){
                        strResponse = FrstSub + " and " + SecSub + " " + GetGistOfSentence() + ".";
                    }
                    else{
                        strResponse = FrstSub + " " +GetGistOfSentence() + ".";
                    }

                    SlowSpeak(strResponse);
                  }
                  else{
                    SlowSpeak("I don't know.");
                    SlowSpeak(":(");
                  }



                 Result = true;
                 break;
             }

            default: if(Verbose) cout << "[c_Cortex::QuestionSentenceBreakDown()] No direction detected.\n";
        }


       return Result;



    }

//--------------------------CHECK FOR IMPLIED NAME------------------------------------------------------------
 void CheckForImpliedName(){

    if(Verbose)
        cout << "[c_Cortex.h::CheckForImpliedName]\n";
    // Subject must be noun
    // must also start with capital letter

    int Response = -1;
    char FirstWordFirstLetter = GetWords(GetSubjectLocation())[0];
    if ((FirstWordFirstLetter >='A' && FirstWordFirstLetter <= 'Z' && GetWordType(GetSubjectLocation()) == 'n') || (GetWordType(GetSubjectLocation())=='P')){
        SlowSpeak("Is " + GetWords(GetSubjectLocation())+ " the " + GetWords(GetIndirectObjectLocation()) + "'s name?");
        Response = RequestUserResponse();
        if(Response == 1){ // yes
            //set subject to Proper Noun
            SetWordType('P',GetSubjectLocation());
            SetSubjectInStack(GetWordTokens(GetSubjectLocation()),GetWords(GetSubjectLocation()),GetOriginalString());
            IncreaseMoodLevel();
            SetHasBeenUnderstood(true);
            QuizForGenderInformation();
        }
        else
            SlowSpeak(":(");
    }



 }
 //-------------------------------------END OF CHECK FOR IMPLIED NAME------------------------------------------------

 //-----------------------------QUIZFORGENDERINFORMATION------------------------------------------------------------
    void QuizForGenderInformation(){
        if(Verbose)
            cout << "[c_Cortex.h::QuizForGenderInformation]\n";

        string PositiveString   = " boy Boy m male b ";
        string NegativeString   = " girl Girl f female g ";
        string OtherString      = " neither none not no ";
        int    Response         = -4;

        if(GetGenderClassInSentence(GetSubjectLocation())=='u'){
            SlowSpeak("Is " + GetWords(GetSubjectLocation()) + " a boy or girl?");
            Response = RequestUserResponse(PositiveString,NegativeString,OtherString);
            if(Response == 1){ // boy
                SetGenderClassInSentence(GetSubjectLocation(),'m');
                SlowSpeak("Ok");
                SetHasBeenUnderstood(true);}
                else
                if(Response == -1){ // girl
                    SetGenderClassInSentence(GetSubjectLocation(),'f');
                    SlowSpeak("Like me!");
                    SlowSpeak(":)");
                    SetHasBeenUnderstood(true);}
                    else
                    if(Response == -2){ //neither
                        SetGenderClassInSentence(GetSubjectLocation(),'n');}
        }
    }

 //-----------------------------END OF QUIZFORGENDERINFORMATION------------------------------------------------------

 //--------------------------CHECK FOR IMPLIED GENDER----------------------------------------------------------------
 void CheckForImpliedGender(){
        if(Verbose)
            cout << "[c_Cortex.h::CheckForImpliedGender\n]";
        //qualification;
        // subject must be pronoun   he,she,her, him
        //***TODO***    Check to be sure gender isn't already set

        string MaleProNouns      = " he him his ";
        string FemaleProNouns    = " she her hers ";
        string SubjectText       = GetMemoryCellWordLC("",GetSubjectInStack(1)); //pronoun has already been set as subject so get next
        string ProNounResolution = "";
        char GenderClass         = '\0';
        int MatchedM             = MaleProNouns.find(" " + GetWordsLC(GetSubjectLocation())+" ");
        int MatchedF             = FemaleProNouns.find(" " + GetWordsLC(GetSubjectLocation())+" ");
        int Response             = -1;

        if(MatchedF >=0){
            ProNounResolution = "girl";
            GenderClass       = 'G';}
        else
            if(MatchedM >=0){
                ProNounResolution = "boy";
                GenderClass       = 'M';}

        if( (GetWordType(GetSubjectLocation()) == 'p') && ((MatchedF + MatchedM +1) >=0) ){
            SlowSpeak("So " + SubjectText + " is a " + ProNounResolution + "?");
            Response = RequestUserResponse();
            if(Response == 1){
                SetMemoryCellGenderClass(GetSubjectInStack(1),GenderClass);
                SlowSpeak("Okay."); SlowSpeak(":)"); IncreaseMoodLevel();SetHasBeenUnderstood(true);
            }
        }

 }
 //-----------------------------------END OF CHECK FOR IMPLIED GENDER-------------------------------------------------



};

#endif // C_CORTEX_H
