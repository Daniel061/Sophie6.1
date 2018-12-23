#ifndef C_CORTEX_H
#define C_CORTEX_H

//#include <c_Sentence.h>
#include <c_Language.h>

class c_Cortex : public c_Language             //c_Sentence
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
            int ProNounLocation;
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
            int AdverbLocation;
            float UnderstandingRatio;
            bool ISQ;


    public:
        void DecipherCurrentSentence(){
            //***TODO add D(direct object) and I(indirect object) s(plural possessive                                      // objects and variables are passed by reference
            //CurrentSentence = Data;                                                                                      // Data is referenced to Sentence in calling program, CurrentSentence is a LOCAL copy!!
            //CurrectSubject = sbjData;                                                                                    // changes to Data are seen in calling program, not in CurrentSentence
            //Personality = PData;                                                                                         // Remember to destroy CurrentSentence ~ Automatic

            if(Verbose){cout << "[c_Cortex.h::DeciperCurrentSentence]" << endl;}
            SubjectLoc = GetSubjectLocation();
            AdjectiveLocation  = -1; FirstUnknown = -1; ContractionLocation = -1;
            DeterminerLocation = -1; ProNounLocation = -1; ISQ = false;
            Pattern = ""; NounLocation = -1; Control = -1; UnderstandingLevel = 0;
            UnderstandingRatio = 0.0; UnknownCount = 0; QuestionLocation = 0;
            AdverbLocation = -1;
            for(int x =0; x < GetWordCount(); x++){                                                                  // Build pattern string i.e. duvu  4 word sentence
                    Pattern += GetWordType(x);
                    tmpWordType = GetWordType(x);
                    if (tmpWordType == 'n') {NounLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'd') {DeterminerLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'p') {ProNounLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'v') {VerbLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'a') {AdjectiveLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'r') {ReplacementLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'q') {QuestionLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'C') {ContractionLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'A') {AdverbLocation = x; UnderstandingLevel++;}
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
            if(ISQ == true)UnderstandingDegree= 1; //question trap
            switch (UnderstandingDegree)
            {
               case 0:{  ///All new words, lots of work to do
                   if (Verbose)
                    cout << "Case 0" << endl;


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
                   HandleQuestion();
                   break;

               }
                case 10:{  ///Only 1 known but could have a ratio of 100%
                   if (Verbose)
                    cout << "Case 10" << endl;

                 SlowSpeak("I'm going to have to work on this.");
                 break;
                }
                case 25:{  ///Some understanding but depends on ratio
                   if (Verbose)
                    cout << "Case 25" << endl;

                 SlowSpeak("I don't know "  + GetWords(FirstUnknown)+"?");
                 break;
                }
                case 50:{  ///stronger understanding but also depends on ratio
                   if (Verbose)
                    cout << "Case 50" << endl;


                 WorkWithHalfLevel(Pattern,DeterminerLocation);
                 break;
                }
                case 75:{  ///Much stronger
                   if (Verbose)
                    cout << "Case 75" << endl;
                 Handle75LevelUnderstanding();
                 //todo******
                 //see if a noun already exist
                 //see if it matches the tracked subject

//                 SlowSpeak("Hmmm.");
//                 string tmpUnknown; string tmpSubject; int a,b; int tmpLocation;
//                 tmpSubject = CurrentSentence.GetWords(SubjectLoc);
//                 for(int x =0; x < CurrentSentence.GetWordCount(); x++)
//                    if(CurrentSentence.GetWordType(x)=='u'){
//                            tmpUnknown = CurrentSentence.GetWords(x);
//                            tmpLocation = x;}
//                 if(AdjectiveLocation == -1)a = tmpLocation; else a = AdjectiveLocation;
//                 SlowSpeak("I think " + CurrentSentence.GetWords(a) + " is describing the " + tmpSubject + ".");
//                 SlowSpeak(" Am I right?");
//                 b = RequestUserResponse();
//                 if(b==1){
//                    CurrentSentence.SetWordType('a',a);
//
//                    CurrentSentence.SetWordType('n',SubjectLoc);
//                    SlowSpeak("Got it!"); SlowSpeak("Thanks!");
//                    SlowSpeak("So a " + CurrentSentence.GetWords(a) + " " + tmpSubject + ".");
//                    SlowSpeak("What else can a " + tmpSubject + " be or do?");
//                    CurrectSubject.SetSubject(CurrentSentence.GetWordTokens(SubjectLoc),tmpSubject);
//                    Personality.IncreaseMoodLevel();
//                 }
//                 else
//                 {
//                     SlowSpeak("Hmmm. I'll get it eventually.");
//                     SlowSpeak(":(");
//                     Personality.DecreaseMoodLevel();
//
//                 }
                 break;
                }
                case 100:{  ///very strong
                   if (Verbose)
                    cout << "Case 100" << endl;
                    string tmpSubject;
                    tmpSubject = GetWords(SubjectLoc);
                    SetSubject(GetWordTokens(SubjectLoc),tmpSubject);
                 SlowSpeak("Okay.");
                 IncreaseMoodLevel();
                 SlowSpeak(":)");
                 break;
                }

            }

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

    }


    return -1;
}
//---------------------------------------end greetings-------------------------------------------------------------------------------

//-------------------------------------PROCESS MIDLEVEL UNDERSTANDING----------------------------------------------------------------

int WorkWithHalfLevel(string Pattern, int Determiner){
    if(Verbose){cout << "[c_Cortex.h::WorkWithHalfLevel]" << endl;}
       int Response;
       string tmpAdjective;
       int tmpAdjectiveLoc;
       if(Verbose)
            cout << "Noun Loc:" << NounLocation << "Unknown Loc:" << UnKnownLocation << "Pattern:" << Pattern << endl;
         SlowSpeak("  Are we talking about a " + GetWords(Determiner + 1) + "?");
         Response = RequestUserResponse();
         if(Response == 1){  //yes answer
            //set subject to this
            //set wordtype to noun if it isn't
            //see if this is a known word
            IncreaseMoodLevel();
            SetWordType('n',Determiner+1);
            SetSubject(Tokenize(GetWords(Determiner+1)),GetWords(Determiner+1));
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
                    SetWordType('a',tmpAdjectiveLoc);
                    SetWordType('n',Determiner+1);
                    RebuildPattern();

            }
            else{
                SlowSpeak(":(");
                DecreaseMoodLevel();

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
                    //set subject
                }
                else{
                    SlowSpeak("I'm lost.");
                    SlowSpeak("I need to learn more before I understand this.");
                    SlowSpeak(":(");
                    DecreaseMoodLevel();
                }
            }
            else{
                SlowSpeak("Ok");
                SlowSpeak("You'll have to tell me more about a " + GetWords(Determiner+2)+ ".");
                SetWordType('n',Determiner+2);
                SetSubject(Tokenize(GetWords(Determiner+2)),GetWords(Determiner+2));
                IncreaseMoodLevel();
                //set subject
            }
         }

      return 0;

}//end work with half level
//---------------------------------------------------------------------------------------------------------------
int HandleQuestion(){
    if(Verbose){cout << "[c_Cortex.h::HandleQuestion]" << endl;}
    int Control;    Control = -1;
    string VerbUsed, MatchedAdjective;
    bool Matched;
    if(Verbose)
        cout << "qLoc:" << QuestionLocation << " Pattern:" << Pattern << " SubjectLoc:" << GetSubjectLocation() << endl;

   // Matched = CheckLinkOfTwoNounsWithAdjectives("dog","color",VerbUsed,MatchedAdjective);

    Matched = CheckLinkOfTwoNounsWithAdjectives(RightLobeMemory[GetWordTokens(GetSubjectLocation())].GetpCellDataString(),
                                                RightLobeMemory[GetWordTokens(QuestionLocation+1)].GetpCellDataString(),
                                                VerbUsed,MatchedAdjective);
    if (Matched){
        SlowSpeak("The " + GetWords(GetSubjectLocation())+ " " + VerbUsed + " " + MatchedAdjective + ".");}
        else
        SlowSpeak("You haven't told me yet.");
    if(Verbose)
        cout << "Matched:" << Matched << " Verb:" << VerbUsed << " Adjective: " << MatchedAdjective << endl;

  return Control;
}
//End HandleQuestion-----------------------------------------------------------------------------------------------

//--------------------------------HANDLE75LEVELUNDERSTANDING-------------------------------------------------------
void Handle75LevelUnderstanding(){
    bool Testing; Testing = true;
    if(Verbose){
        cout << "c_Cortex.h::Handle75LevelUnderstanding\n";
        cout << "  Pattern:" << Pattern << endl;
        cout << "  Subject Location:" << GetSubjectLocation() << endl;
        cout << "  Noun Location:" << NounLocation << endl;
        cout << "  Adjective Location:" << AdjectiveLocation << endl;
        cout << "  Verb Location:" << VerbLocation << endl;}


   while(Testing & (NounLocation >=0)){   //no noun! How to handle this Kenzie??  she says if pronoun use it as noun and subject

    //----------Missing Noun Test------
    if((NounLocation == -1) & (VerbLocation >=0) & (DeterminerLocation >=0) & (AdjectiveLocation >=0)){ //no noun but has verb, determiner and adjective
        SlowSpeak("So " + GetWords(DeterminerLocation+1)+ " can be " + GetWords(AdjectiveLocation) + "?");
        UserResponse = RequestUserResponse();
        if(UserResponse == 1){
            SetWordType('n',DeterminerLocation+1);    //set the noun
            SetSubjectLocation(DeterminerLocation+1); //be sure subject location is newly found noun
            SlowSpeak(":)"); IncreaseMoodLevel();
            Testing = false;
            break;}
    }

    //------End Missing noun test------

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
                  }
                  else{
                    SlowSpeak(":("); DecreaseMoodLevel();
                  }


       Testing = false;
       break;
    }




    //-------End Modifier test---------

    //----------Adjective Test---------

    SlowSpeak( "A " + GetWords(UnKnownLocation) + " " + GetWords(NounLocation) + "?");
    UserResponse = RequestUserResponse();
    if(UserResponse == 1){
        SetWordType('a',UnKnownLocation);  //set word type to adjective
        SlowSpeak(":)"); IncreaseMoodLevel();
        Testing = false;
        break;}
        else{
            SlowSpeak(":("); DecreaseMoodLevel();
            Testing = false;
        }
    //---end Adjective Testing ----------


    //-- DNVUA -- Test for u = Adverb -----
    // the dog is very fast.
    SlowSpeak("A " + GetWords(UnKnownLocation) + " " + GetWords(AdjectiveLocation) + " " + GetWords(GetSubjectLocation()) + "?");
    UserResponse = RequestUserResponse();

    //-- END TESTING FOR ADVERB -----------





   }//---end testing control loop
}





};

#endif // C_CORTEX_H
