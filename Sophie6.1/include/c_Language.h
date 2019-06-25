#ifndef C_LANGUAGE_H
#define C_LANGUAGE_H
#include <c_Sentence.h>
#include <c2_Sentence.h>
#include <c_LongTermMemory.h>
#include <string>
#include <iostream>
#include <stack>
#include <queue>

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

     This is the ENGLISH version os language helper.
*/

extern bool Verbose;
extern int  ThisSpeed;
extern bool StoryMode;

using namespace std;

/**    Language Helper Class

      This class is responsible for the first setting  of word types
         (based on a small set of standards, finalizing word type setting is done elsewhere)
       deconstruction of  plurals,
       comparing patterns for proper form and/or stored patterns,
       Finding the subject and/or indirect object of a sentence,
       Sending responses to the console, delayed to appear as typing,
       Receiving user responses,
       and, finding the 'Gist' of the sentence and store that.

*/

class c_Language : public c_LongTermMemory
{
    public:
        c_Language();
        virtual ~c_Language();


    protected:

    private:
       c2_Sentence SlowSentence;
       c2_Sentence tmpSentence;

    public:
//-------------------------Pattern Review  ------------------------
 string PatternJoinerCheck(string LocPattern){
   if(Verbose)cout << "[c_Language::PatternReview]: " ;
   string CorrectedPattern, LeftOfJoiner, RightOfJoiner;
   CorrectedPattern        = LocPattern;
   string WorkingWord      = "";
   int ConfidenceLevel     = -1;  // no suggestion
   int LeftOfJoinerLocation,RightOfJoinerLocation;
   LeftOfJoinerLocation    = -1; RightOfJoinerLocation = 1;
   int  JoinerLocation     = -1;
   bool Result             = false;
   bool VerifyPattern      = false;
   int  PatternPointer     = 0;


   /*Check for a joiner word and assist if possible
      Possible combinations are;
        unknown-type joiner known-type              can assume unknown-type = known-type
        unknown-type joiner unknown-type            cannot help here
        known-type joiner unknown-type              can assume unknown-type = known-type
        known-type joiner known-type                no help needed here
        unknown-type joiner determiner known-type   can assume unknown-type = known-type after skipping determiner

        Working principle~ you cannot join unlike word types i.e. dog and cat ~ ok     dirty and dog ~ improper form
        Possible exception~ The cat is fast and the dog is too.  The joining word 'and' would trigger this routine to match dog and fast as the same word types

    */
    //CorrectedPattern = GetFromSentencePattern();
    JoinerLocation = LocPattern.find("+");
    if((JoinerLocation >=1) & (JoinerLocation < int(LocPattern.size()))){  //not the first word and not the last word
        LeftOfJoiner = LocPattern.substr(JoinerLocation + LeftOfJoinerLocation,1);
        RightOfJoiner = LocPattern.substr(JoinerLocation + RightOfJoinerLocation,1);
        if(RightOfJoiner == "d"){
            RightOfJoinerLocation++; //move past determiner
            RightOfJoiner[0] = LocPattern[JoinerLocation + RightOfJoinerLocation];} //get new character

        if(LeftOfJoiner == RightOfJoiner){ // if both known-type or unknown-type  cannot help

        }
        else
            if(LeftOfJoiner == "u") LeftOfJoiner = RightOfJoiner;                             //assume left is same as right
                else
                    if(RightOfJoiner == "u" )  RightOfJoiner = LeftOfJoiner;                  //assume right is same as left. the tests for unknowns prevents matching dissimilar types


    CorrectedPattern[JoinerLocation + LeftOfJoinerLocation]  = LeftOfJoiner[0];
    CorrectedPattern[JoinerLocation + RightOfJoinerLocation] = RightOfJoiner[0];
    }
   return CorrectedPattern;
 }
//--------------------------End Pattern Review------------------------------------------------
//------------------------------NEW PATTERN REVIEW--------------------------------------------
string PatternReview(){
    if(Verbose)
        cout << "[c_Language::PatternReview()\n";
    string   CorrectedPattern    = GetFromSentencePattern(); //pattern is preset in FindWordTypes
    bool     Correcting          = true;
    bool     Corrected           = false;
    int      PatternPointer      = -1;
    int      SecondMatch         = -1;

    //large pattern corrections first
    //one change at a time with loop-break control

    while(Correcting){
//        PatternPointer = CorrectedPattern.find("dG+dGvvu>du");    //change to dG+dGvvA>dn
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+7]  = typeAdverb;
//            CorrectedPattern[PatternPointer+10] = typeNoun;
//            Correcting = false;
//            break;}
//
//        PatternPointer = CorrectedPattern.find("dG+dGvvA>du");    //change to dG+dGvvA>dn
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+7]  = typeAdverb;
//            CorrectedPattern[PatternPointer+10] = typeNoun;
//            Correcting = false;
//            break;}
//
//        PatternPointer = CorrectedPattern.find("dG>duvv>du+vdu");    //change to dG>dnvv>dn+vdn
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+4]  = typeNoun;
//            CorrectedPattern[PatternPointer+9]  = typeNoun;
//            CorrectedPattern[PatternPointer+13] = typeNoun;
//            Correcting = false;
//            break;}

//        PatternPointer = CorrectedPattern.find("dGvvdu");    //change to dGvvdn
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+5] = typeNoun;
//            Correcting = false;
//            break;}
//
//
//        PatternPointer = CorrectedPattern.find(">avvuu+v");    //change to >avvan+v
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+4] = typeAdjective;
//            CorrectedPattern[PatternPointer+5] = typeNoun;
//            Correcting = false;
//            break;}



//        PatternPointer = CorrectedPattern.find(">dGv>nvvan");    //change to >dGv>avvan
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+4] = typeAdjective;
//            Correcting = false;
//            break;}
//
//        PatternPointer = CorrectedPattern.find("duvvdn");    //change to dnvvdn
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+1] = typeNoun;
//            Correcting = false;
//            break;}


//        PatternPointer = CorrectedPattern.find("dnvv>du");    //change to dnvv>dn
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+6] = typeNoun;
//            Correcting = false;
//            break;}
//
//
//        PatternPointer = CorrectedPattern.find("dGvvvu");
//        if(PatternPointer >= 0){
//            CorrectedPattern[PatternPointer+4] = typeAdjective;
//            CorrectedPattern[PatternPointer+5] = typeNoun;
//            Correcting = false;
//            break;}
//
//        PatternPointer = CorrectedPattern.find("ntu");      //change to ntn
//        if(PatternPointer >= 0){
//            CorrectedPattern[PatternPointer+2] = typeNoun;
//            Correcting = false;
//            break;}


//        PatternPointer = CorrectedPattern.find("dGvvdu");
//        if(PatternPointer >= 0){
//            CorrectedPattern[PatternPointer+5] = typeNoun;
//            Correcting = false;
//            break;}
//
//
//
//        PatternPointer = CorrectedPattern.find("vdu");
//        if(PatternPointer >= 0){
//            CorrectedPattern[PatternPointer+2] = typeNoun;
//            Correcting = false;
//            break;}
//
//
//        PatternPointer = CorrectedPattern.find("Aun");
//        if(PatternPointer >= 0){
//            CorrectedPattern[PatternPointer+1] = typeAdjective;
//            Correcting = false;
//            break;}
//
//        PatternPointer = CorrectedPattern.find("Gu");
//        if(PatternPointer >= 0){
//            CorrectedPattern[PatternPointer+1] = typeVerb;
//            Correcting = false;
//            break;}

//        PatternPointer = CorrectedPattern.find(">dau");
//        if(PatternPointer >= 0){
//            CorrectedPattern[PatternPointer+3] = typeNoun;
//            Correcting = false;
//            break;}
//
//        PatternPointer = CorrectedPattern.find(">dvu");
//        if(PatternPointer >= 0){
//            CorrectedPattern[PatternPointer+3] = typeNoun;
//            Correcting = false;
//            break;}
//
//        PatternPointer = CorrectedPattern.find("vv>da");
//        if(PatternPointer >= 0){
//            CorrectedPattern[PatternPointer+4] = typeNoun;
//            Correcting = false;
//            break;}


//        PatternPointer = CorrectedPattern.find(">u");
//        if(PatternPointer >= 0){
//            CorrectedPattern[PatternPointer+1] = typeNoun;
//            Correcting = false;
//            break;}

        PatternPointer = CorrectedPattern.find("dnvvu");
        if(PatternPointer >=0){
            CorrectedPattern[PatternPointer+4] = typeNoun;
            Correcting = false;
            break;}

       PatternPointer = CorrectedPattern.find("muvv");
        if(PatternPointer >=0){
            CorrectedPattern[PatternPointer+1] = typeNoun;
            Correcting = false;
            break;}


       PatternPointer = CorrectedPattern.find("du>uv");
        if(PatternPointer >=0){
            CorrectedPattern[PatternPointer+1] = typeNoun;
            CorrectedPattern[PatternPointer+3] = typeNoun;
            Correcting = false;
            break;}


        PatternPointer = CorrectedPattern.find("vvduu");
        if(PatternPointer >=0){
            CorrectedPattern[PatternPointer+3] = typeAdjective;
            CorrectedPattern[PatternPointer+4] = typeNoun;
            Correcting = false;
            break;}


        PatternPointer = CorrectedPattern.find("vvu");
        if(PatternPointer >=0){
            CorrectedPattern[PatternPointer+2] = typeNoun;
            Correcting = false;
            break;}


        PatternPointer = CorrectedPattern.find(">udu>");
        if(PatternPointer >=0 ){
                CorrectedPattern[PatternPointer+1] = typeVerb;
                CorrectedPattern[PatternPointer+3] = typeNoun;
                Correcting = false;
                break;}

        PatternPointer = CorrectedPattern.find(">uu+");
        if(PatternPointer >=0 ){
                CorrectedPattern[PatternPointer+1] = typeAdjective;
                CorrectedPattern[PatternPointer+2] = typeNoun;
                Correcting = false;
                break;}



        PatternPointer = CorrectedPattern.find(">du>");
        if(PatternPointer >=0 ){
                CorrectedPattern[PatternPointer+2] = typeNoun;
                Correcting = false;
                break;}



        PatternPointer = CorrectedPattern.find(">duvv");
        if(PatternPointer >=0 ){
                CorrectedPattern[PatternPointer+2] = typeNoun;
                Correcting = false;
                break;}


        PatternPointer = CorrectedPattern.find("dauvv"); //change to danvv
        if(PatternPointer >=0){
            CorrectedPattern[PatternPointer+2] = typeNoun;
            Correcting = false;
            break;}


//        PatternPointer = CorrectedPattern.find("ddu"); //change to "dan"
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+1] = typeAdjective;
//            CorrectedPattern[PatternPointer+2] = typeNoun;
//            Correcting = false;
//            break;}
//
//
//        PatternPointer = CorrectedPattern.find("dnn"); //change to dan
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+1] = typeAdjective;
//            CorrectedPattern[PatternPointer+2] = typeNoun;
//            Correcting = false;
//            break;}


//        PatternPointer = CorrectedPattern.find("davv"); //change to dnvv
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+1] = typeNoun;
//            Correcting = false;
//            break;}
//
//
//        PatternPointer = CorrectedPattern.find("duG"); //change to daG
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+1] = typeAdjective;
//            Correcting = false;
//            break;}
//
//
//        PatternPointer = CorrectedPattern.find("vnu>"); //change to van>
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+1] = typeAdjective;
//            CorrectedPattern[PatternPointer+2] = typeNoun;
//            Correcting = false;
//            break;}


//        PatternPointer = CorrectedPattern.find("dAvv"); //change to dnvv
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+1] = typeNoun;
//            Correcting = false;
//            break;}
//
//
//        PatternPointer = CorrectedPattern.find("avvuu"); //change to avvan
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+3] = typeAdjective;
//            CorrectedPattern[PatternPointer+4] = typeNoun;
//            Correcting = false;
//            break;}
//
//
//        PatternPointer = CorrectedPattern.find("duvv"); //change to dnvv
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+1] = typeNoun;
//            Correcting = false;
//            break;}
//
//
//        PatternPointer = CorrectedPattern.find("aGvvu"); //change to aGvvn
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+4] = typeNoun;
//            Correcting = false;
//            break;}

//        PatternPointer = CorrectedPattern.find("vvda"); //change to vvdn
//        if(PatternPointer >=0){
//            CorrectedPattern[PatternPointer+3] = typeNoun;
//            Correcting = false;
//            break;}

        PatternPointer = CorrectedPattern.find("Pvu+vpu");
        if(PatternPointer == 0){ //begining of sentence
            CorrectedPattern[PatternPointer+2] = typeNoun;
            CorrectedPattern[PatternPointer+6] = typeNoun;
            Corrected  = true;
            Correcting = false;
            break;
        }


        PatternPointer = CorrectedPattern.find("duvv");
        if(PatternPointer == 0){ //begining of sentence
            CorrectedPattern[PatternPointer+1] = typeNoun;
            Corrected  = true;
            Correcting = false;
            break;
        }



        if(IsThisPatternAtEndOfSentence("du",PatternPointer)==true){
            CorrectedPattern[PatternPointer+1] = typeNoun;
            Corrected  = true;
            Correcting = false;
            break;
        }


        PatternPointer = CorrectedPattern.find("vvdau");
        if(PatternPointer >= 0){
            CorrectedPattern[PatternPointer+4] = typeNoun;
            Corrected  = true;
            Correcting = false;
            break;
        }

        PatternPointer = CorrectedPattern.find("dnu>d");
        if(PatternPointer == 0){ //begining of sentence
            CorrectedPattern[PatternPointer+1] = typeAdjective;
            CorrectedPattern[PatternPointer+2] = typeNoun;
            Corrected  = true;
            Correcting = false;
            break;
        }


        if(IsThisPatternAtEndOfSentence("nnvv",PatternPointer)==true){
            CorrectedPattern[PatternPointer] = typeAdjective;
            Corrected  = true;
            Correcting = false;
            break;
        }


        if(IsThisPatternAtEndOfSentence("dun",PatternPointer)==true){
            CorrectedPattern[PatternPointer+1] = typeAdjective;
            Corrected  = true;
            Correcting = false;
            break;
        }

        if(IsThisPatternAtEndOfSentence("vv>duu",PatternPointer)==true){
            CorrectedPattern[PatternPointer+4] = typeAdjective;
            CorrectedPattern[PatternPointer+5] = typeNoun;
            Corrected  = true;
            Correcting = false;
            break;
        }


        if(IsThisPatternAtEndOfSentence("vvun",PatternPointer)==true){
            CorrectedPattern[PatternPointer+2] = typeAdjective;
            Corrected  = true;
            Correcting = false;
            break;
        }


        PatternPointer = CorrectedPattern.find("danvvun");
        if(PatternPointer == 0){
            CorrectedPattern[PatternPointer+5] = typeAdjective;
            Corrected  = true;
            Correcting = false;
            break;
        }


        if(IsThisPatternAtEndOfSentence("dau>dau",PatternPointer)==true){
            CorrectedPattern[PatternPointer+2] = typeNoun;
            CorrectedPattern[PatternPointer+6] = typeNoun;
            Corrected  = true;
            Correcting = false;
            break;
        }

        if(IsThisPatternAtEndOfSentence("dau",PatternPointer)==true){
            CorrectedPattern[PatternPointer+2] = typeNoun;
            Corrected  = true;
            Correcting = false;
            break;
        }

        PatternPointer    = CorrectedPattern.find("n");
        if(PatternPointer == -1){             //no noun
           PatternPointer = CorrectedPattern.find("u");
           if(PatternPointer >= 0){
               SecondMatch    = CorrectedPattern.find("u",PatternPointer+1);
               if(SecondMatch >= 0){                          //more than 1 unknown, cannot help
               }
               else{
                CorrectedPattern[PatternPointer]  = typeNoun;
                Corrected  = true;
                Correcting = false;
                break;
               }
           }
        }

        PatternPointer = CorrectedPattern.find("duvvduu"); //change to dnvvdan
        if(PatternPointer >=0){
            CorrectedPattern[PatternPointer+5] = typeAdjective;
            CorrectedPattern[PatternPointer+6] = typeNoun;
            CorrectedPattern[PatternPointer+1] = typeNoun;
            Correcting = false;
            Corrected  = true;
            break;}


        PatternPointer = CorrectedPattern.find("duvvdu"); //change to dnvvdn
        if(PatternPointer >=0){
            CorrectedPattern[PatternPointer+5] = typeNoun;
            CorrectedPattern[PatternPointer+1] = typeNoun;
            Correcting = false;
            Corrected  = true;
            break;}


//            if(CorrectedPattern == "duvu"){
//                CorrectedPattern = "dnvu";}
//            if(CorrectedPattern == "dun"){
//                CorrectedPattern = "dan";}
//            if(CorrectedPattern == "duva"){
//                CorrectedPattern = "dnva";}
//            if(CorrectedPattern == "uuv"){
//                CorrectedPattern = "dnv";}
//            if(CorrectedPattern == "dvdun"){
//                CorrectedPattern = "dvdan";}
//            if(CorrectedPattern == "dvdu"){
//                CorrectedPattern = "dvdn";}
//            if(CorrectedPattern == "dnup"){
//                CorrectedPattern = "dnvp";}
//            if(CorrectedPattern == "avdu"){
//                CorrectedPattern = "avdn";}
//            if (CorrectedPattern == "dntua"){
//                CorrectedPattern = "dntva";}

            if (CorrectedPattern == "dnvvdu"){
                CorrectedPattern = "dnvvdn";}

        Correcting = false;
    }//end While correcting loop

    if((Corrected)&& (Verbose)){
        cout << "Original Sentence:" << GetFromSentenceOriginalString() << endl;
        cout << "Corrected pattern " << GetFromSentencePattern() << " to " << CorrectedPattern << endl;}

    return CorrectedPattern;
}
//------------------------------END of NEW PATTERN REVIEW-------------------------------------

//-------------------------Bool EndOfSentencePatternCheck-------------------------------------
 bool IsThisPatternAtEndOfSentence(string PatternToSearch, int &PositionFound){

        int    PatternPointer = -1;
        string WorkingPattern = GetFromSentencePattern();
        bool   Result         = false;

        PatternPointer        = WorkingPattern.find(PatternToSearch);
        if(PatternPointer    >=0){
            if( (PatternToSearch.size()+PatternPointer ) == WorkingPattern.size()){
                PositionFound = PatternPointer;
                Result        = true;}
        }
        return Result;
    }
//--------------------------END of EndOfSentencePatternCheck----------------------------------

//-------------------------Find Word Type------------------------------------------------------
 char FindWordTypeOLD(string tmpWord, int LocationInSentence = -1){

           if(Verbose)cout << "[c_Language::FindWordType] :";


           string OrigWord;
           string OrigWordUC;


           char tmpWordType = typeUnknownWord;

           string ProNounsInward      = " you your yours ";
           string ProNounsOther       = " they them he him his she her we which someone ";
           string ProNounsOutward     = " me mine my I i ";
           string Determiners         = " the a an each every certain this that these those any all each some much no ";
           string Questions           = " what where how when who ";
           string Verbs               = " go went can will be have do say get make go know take is see come fell ran think look want give use find tell ask work seem feel try leave call am been ";
           string PastTenseVerbs      = " came went gone threw broke ran sold fell ";
           string BaseNouns           = " dog cat ball tree person horse car cow front ";
           string PluralVerbs         = " are ";
           string SubjectReplacements = " it that this its ";
           string Adverbs             = " very again ";
           string Adjectives          = " black white blue brown red green clear tan purple hazel blond yellow gray grey pink orange little few many ";
           string Directives          = " compare same about ";
           string JoiningWords        = " and ";
           string AssociativeWord     = " name name's ";
           string PluralPronoun       = " both ";
           string ThrowAwayWords      = " also ";
           string GenderIndicator     = " boy male man men girl female woman women ";
           string MaleGenderClass     = " boy male man men ";
           string FemaleGenderClass   = " girl female woman women ";
           string GenderDeterminer    = " gender ";
           string GreetingsWord       = " hello hi ";
           string ExclamationWord     = " there ";
           string ConjunctionWords    = " or either ";
           string PrepositionWords    = " in into up after to on with under within of at near until over across among while from throughout through during towards by upon across ";
           string VerbTenseCombos     = " threw throw broke break ran run sold sell gone go fell fall came come was is went go ";
           string NumericWords        = " zero one two three four five six seven eight nine ten eleven twelve thirteen fourteen fifteen sixteen seventeen eighteen nineteen twenty ";
           string Vowels              = "aeiou";
           string SentenceBreak       = " , ; ";
           string SingularWord        = "";
           string PresentTenseVerb    = "";
           string VowelPattern        = "";  //for creation
           string UCWord              = GetswWords(LocationInSentence);



           int  isBaseNoun          = -1;
           int  isExclamationWord   = -1;
           int  isAdjective         = -1;
           int  isNumericWord       = -1;
           int  isPastTenseVerb     = -1;
           int  isPreposition       = -1;
           int  isThrowAwayWord     = -1;
           int  isPluralPronoun     = -1;
           int  isPluralVerb        = -1;
           int  isDirective         = -1;
           int  isDeterminer        = -1;
           int  isQuestion          = -1;
           int  isVerb              = -1;
           int  isSubRep            = -1;
           int  isAdverb            = -1;
           int  isJoiner            = -1;
           int  isProNounsOther     = -1;
           int  isProNounsInward    = -1;
           int  isProNounsOutward   = -1;
           int  isAssociativeWord   = -1;
           int  isGenderIndicator   = -1;
           int  isGreetingsWord     = -1;
           int  isConjunction       = -1;
           int  isMaleGenderClass   = -1;
           int  isFemaleGenderClass = -1;
           int  isGenderDeterminer  = -1;
           int  isCommaDetected     = -1;
           int  QuoteMarker         = -1;
           int  PatternMarker       = -1;
           bool RuleTesting         = true;
           bool IsPlural            = false;
           bool Result              = false;
           bool VerbTenseSet        = false;
           bool WordTypeIsSet       = false;




              for(int t = 0; t < int(tmpWord.size()); t++){
                tmpWord[t] = tolower(tmpWord[t]);}
              OrigWord     = tmpWord;
              OrigWordUC   = GetswWords(LocationInSentence);
              tmpWord = " " + tmpWord + " ";

                isBaseNoun          = BaseNouns.find(tmpWord);
                isExclamationWord   = ExclamationWord.find(tmpWord);
                isAdjective         = Adjectives.find(tmpWord);
                isNumericWord       = NumericWords.find(tmpWord);
                isCommaDetected     = SentenceBreak.find(tmpWord);
                isPastTenseVerb     = PastTenseVerbs.find(tmpWord);
                isPreposition       = PrepositionWords.find(tmpWord);
                isConjunction       = ConjunctionWords.find(tmpWord);
                isPluralVerb        = PluralVerbs.find(tmpWord);
                isGenderDeterminer  = GenderDeterminer.find(tmpWord);
                isMaleGenderClass   = MaleGenderClass.find(tmpWord);
                isFemaleGenderClass = FemaleGenderClass.find(tmpWord);
                isGreetingsWord     = GreetingsWord.find(tmpWord);
                isGenderIndicator   = GenderIndicator.find(tmpWord);
                isThrowAwayWord     = ThrowAwayWords.find(tmpWord);
                isPluralPronoun     = PluralPronoun.find(tmpWord);
                isJoiner            = JoiningWords.find(tmpWord);
                isDirective         = Directives.find(tmpWord);
                isDeterminer        = Determiners.find(tmpWord);
                isProNounsOther     = ProNounsOther.find(tmpWord);
                isProNounsInward    = ProNounsInward.find(tmpWord);
                isProNounsOutward   = ProNounsOutward.find(tmpWord);
                isQuestion          = Questions.find(tmpWord);
                isVerb              = Verbs.find(tmpWord);
                isSubRep            = SubjectReplacements.find(tmpWord);
                isAdverb            = Adverbs.find(tmpWord);
                isAssociativeWord   = AssociativeWord.find(tmpWord);
                QuoteMarker         = tmpWord.find("'");

                while(!WordTypeIsSet){

                  if(isBaseNoun >= 0) {      //Set noun type 'n'
                    tmpWordType   = typeNoun;
                    WordTypeIsSet = true;
                    break;}

                  if(isExclamationWord >=0){ //Set exclamation type 'E'
                    tmpWordType   = typeExclamation;
                    WordTypeIsSet = true;
                    break;
                  }

                  if(isAdjective >=0){      //Set Adjective type 'a'
                      tmpWordType = typeAdjective;
                      WordTypeIsSet = true;
                      break;}

                  if(isNumericWord >=0){    //Set NumericWord type '#'
                      tmpWordType = typeNumericWord;
                      WordTypeIsSet = true;
                      break;}

                  if(isCommaDetected >= 0){ //Set Comma Type '_'
                      tmpWordType = typeSentenceBreak;
                      WordTypeIsSet = true;
                      break;}

                  if (isPastTenseVerb >= 0){ //Set PastTenseVerb 'v'
                      tmpWordType = typeVerb;
                      SetswWordTense(LocationInSentence,'p');
                      VerbTenseSet = true;
                      WordTypeIsSet = true;
                      break;}

                  if (QuoteMarker >= 0){     //Set Contraction Type 'C'
                      tmpWordType   = typeContraction;
                      WordTypeIsSet = true;
                      break;}

                  if (isConjunction >= 0){  //Set Conjunction Type 'c'
                      tmpWordType  = typeConjunction;
                      WordTypeIsSet = true;
                      break;}

                  if (isVerb >= 0){         //Set Verb Type 'v'
                      tmpWordType = typeVerb;
                      WordTypeIsSet = true;
                      break;}

                  if (isDeterminer >= 0){   //Set Determiner Type 'd'
                       tmpWordType = typeDeterminer;
                       WordTypeIsSet = true;
                       break;}

                  if (isProNounsOther >= 0){//Set ProNounsOther Type 'p'
                       tmpWordType = typePronoun;
                       WordTypeIsSet = true;
                       break;}

                  if (isProNounsInward >=0){//Set ProNounsInward Type 'm'
                       tmpWordType = typeProNounsInward;
                       WordTypeIsSet = true;
                       break;}

                  if (isProNounsOutward >=0){//Set ProNounsOutward Type 'y'
                       tmpWordType = typeProNounsOutward;
                       WordTypeIsSet = true;
                       break;}

                  if (isQuestion >= 0){     //Set Question type 'q'
                       tmpWordType = typeQuestion;
                       SetInSentenceIsQuestion(true);
                       WordTypeIsSet = true;
                       break;}

                  if (isSubRep >=0){        //Set Replacement Word Type 'r'
                      tmpWordType = typeReplacementWord;
                      WordTypeIsSet = true;
                      break;}

                  if (isAdverb >=0){        //Set Adverb Type 'A'
                      tmpWordType = typeAdverb;
                      WordTypeIsSet = true;
                      break;}

                  if (isDirective >=0){     //Set Directive Type 'X'
                      tmpWordType = typeDirective;
                      WordTypeIsSet = true;
                      break;}

                  if (isJoiner >=0){        //Set Joiner Type '+'
                      tmpWordType = typeJoinerWord;
                      WordTypeIsSet = true;
                      break;}

                  if (isAssociativeWord >=0){//Set Associative Word Type 'g'
                      tmpWordType = typeAssociativeWord;
                      WordTypeIsSet = true;
                      break;}

                  if (isPluralPronoun >=0){ //Set Plural Pronoun Type 'N'
                      tmpWordType = typePluralPronoun;
                      SetInSentenceHasPluralPronoun(true);
                      WordTypeIsSet = true;
                      break;}

                  if (isThrowAwayWord >=0){ //Set Throwaway Word Type 't'
                      tmpWordType = typeThrowAwayWord;
                      WordTypeIsSet = true;
                      break;}

                  if (isGenderIndicator >=0){//Set Gender Indicator 'G'
                      tmpWordType = typeGenderIndicator;
                      SetInSentenceHasGenderReference(true);
                      WordTypeIsSet = true;
                      break;}

                  if (isGreetingsWord >=0){  //Set Greeting Word Type 'W'
                      tmpWordType = typeGreetingsWord;
                      SetInSentenceHasGreetingsWord(true);
                      WordTypeIsSet = true;
                      break;}

                  if (isGenderDeterminer >=0){//Set Gender Determiner Type 'B'
                      tmpWordType = typeGenderDeterminer;
                      SetInSentenceHasGenderDeterminer(true);
                      WordTypeIsSet = true;
                      break;}

                  if ((isFemaleGenderClass >=0) && (LocationInSentence != -1)){ //Set Female Gender Type 'f'
                      SetswGenderClassInSentence(LocationInSentence,typeFemaleClass);
                      WordTypeIsSet = true;
                      break;}

                  if ((isMaleGenderClass >=0) && (LocationInSentence != -1)){  //Set Male Gender Type 'm'
                      SetswGenderClassInSentence(LocationInSentence,typeMaleClass);
                      WordTypeIsSet = true;
                      break;}

                  if(isPluralVerb >=0){     //Set Plural Verb Type 'v'  ~same as verb but marks plural
                      tmpWordType = typeVerb;
                      SetswIsPluralWord(LocationInSentence,true);
                      SetswPluralWordFlag(LocationInSentence,'p'); //set plural flag
                      WordTypeIsSet = true;
                      break;}

                  if(isPreposition >=0){    //Set Preposition Type '>'
                      tmpWordType = typePreposition;
                      SetInSentenceHasPreposition(true);
                      SetInSentencePrepositionPosition(LocationInSentence);

                      break;}

                  if((UCWord[0] >='A') && (UCWord[0] <='Z') &&(tmpWordType == 'u') ) {  //Set Proper Noun Type 'P'
                        tmpWordType = typeProperNoun;}

                      WordTypeIsSet = true;
                }//end while loop

                  /// **TODO**  Check for plural verbs, i.e. are->is
                  ///           Try to set tense flag
                  //***check for plural word and set if so*****
                  //*rules:
                  //   1) Must not be a verb
                  //   2) Words ending in -ch, -s, -sh, -x, -z  get -es added
                  //           i.e. wash - washes, box - boxes,
                  //   3) Some words ending in f or fe change to ves:
                  //           knife - knives, life - lives, wife - wives, shelf - shelves
                  //   4) Words ending in ff add s:
                  //            cliffs, sniffs, scoffs, toffs stiffs, tiffs
                  //   5) Change y to ies or s
                  //        a. If the word ends in a vowel (a,e,i,o,u) + y then just add s:
                  //             boy - boys, journey - journeys, key - keys, tray - trays
                  //        b. If the word ends in a consonant + y change y to ies:
                  //             country - countries, baby - babies, body - bodies, memory - memories
                  //      ***Exceptions: add s: roof - roofs, proof - proofs, chief - chiefs
                  //    6) Adding s or es to words ending in O:
                  //        a. If a word ends in a vowel (a,e,i,o,u) + 'o' then we sometimes add s.
                  //            radio - radios, stereo - stereos, video - videos
                  //        b. If a words ends in a consonant + 'o', we sometimes add s, sometimes es. No rules for this
                  //            kilo - kilos, zero - zeros, piano - pianos, photo - photos
                  //            ****but hero - heroes, potato - potatoes, volcano - volcanoes, tomato - tomatoes.
                  //    7) Irregular plurals
                  //            woman - women, man - men, child - children, person - people, tooth - teeth, foot - feet, mouse - mice, penny - pence
                  //    8) Regular plurals end in -s
                  //            i.e. dog-dogs
                  //    9) Plural proper nouns end in ' if the proper noun ends in s
                  //            i.e. Jones - Jones' Texas - Texas'


                  //FIXME: PluralForm data not making it to file storage

                  //Rule #3 comes before Rule #2 because pattern matching finds es before ves
                  while (RuleTesting){

                        //Rule #1 Must Not be verb, must not be preset as pronoun
                        if(tmpWordType == typeVerb) {RuleTesting = false; break;}
                        if((tmpWordType == typePronoun) || (tmpWordType == typeProNounsInward) || (tmpWordType == typeProNounsOutward)) {SetInSentenceHasPronoun(true); RuleTesting = false; break;}

                        //Rule #9 Plural Proper Noun Check
                        PatternMarker = OrigWord.find("s'");
                        if ((PatternMarker >=0)&&((PatternMarker+2)==int(OrigWord.size())) && ((OrigWordUC[0]>='A') && (OrigWordUC[0] <= 'Z')) ){
                            SingularWord = OrigWord.substr(0,PatternMarker+1);
                            SetswIsPluralWord(LocationInSentence,true);
                            SetswPluralRoot(LocationInSentence,SingularWord);
                            SetswPluralWordFlag(LocationInSentence,'p');
                            SetswSingularForm(LocationInSentence,SingularWord);
                            tmpWordType = typeProperNoun;
                            RuleTesting = false;
                            IsPlural    = true;
                            break; }

                        //Rule #3 Some words ending in f or fe change to ves: knife - knives, life - lives, wife - wives, shelf - shelves
                        PatternMarker = OrigWord.find("ves");
                        //Location must be the ending
                        if((PatternMarker >=0)&&((PatternMarker+3)==int(OrigWord.size()))){
                            SingularWord = OrigWord.substr(0,PatternMarker-3);
                            //exceptions
                            if(SingularWord == "shel")
                                SingularWord += "f";
                                else
                                    SingularWord +="fe";
                            SetswIsPluralWord(LocationInSentence,true);
                            SetswPluralRoot(LocationInSentence,SingularWord);
                            SetswPluralWordFlag(LocationInSentence,'p');
                            SetswWordType(GetMemoryCellcharWordType(SingularWord,Result),LocationInSentence);
                            tmpWordType = GetMemoryCellcharWordType(SingularWord,Result);
                            SetswSingularForm(LocationInSentence,SingularWord);
                            RuleTesting = false;
                            IsPlural    = true;
                            break;
                        }

                        //"ses" Rule Some words ending in s  change to ses: house - houses
                        PatternMarker = OrigWord.find("ses");
                        //Location must be the ending
                        if((PatternMarker >=0)&&((PatternMarker+3)==int(OrigWord.size()))){
                            SingularWord = OrigWord.substr(0,PatternMarker-3);
                            SingularWord +="se";
                            SetswIsPluralWord(LocationInSentence,true);
                            SetswPluralRoot(LocationInSentence,SingularWord);
                            SetswPluralWordFlag(LocationInSentence,'p');
                            tmpWordType = GetMemoryCellcharWordType(SingularWord,Result);
                            SetswWordType(GetMemoryCellcharWordType(SingularWord,Result),LocationInSentence);
                            SetswSingularForm(LocationInSentence,SingularWord);
                            RuleTesting = false;
                            IsPlural    = true;
                            break;
                        }


                        //Rule #4 Words ending in ff add s: cliffs, sniffs, scoffs, toffs stiffs, tiffs
                        PatternMarker = OrigWord.find("ffs");
                        //Location must be the ending
                        if((PatternMarker >=0)&&((PatternMarker+3)==int(OrigWord.size()))){
                            SingularWord = OrigWord.substr(0,PatternMarker-3);
                            SingularWord +="ff";
                            SetswIsPluralWord(LocationInSentence,true);
                            SetswPluralRoot(LocationInSentence,SingularWord);
                            SetswPluralWordFlag(LocationInSentence,'p');
                            SetswWordType(GetMemoryCellcharWordType(SingularWord,Result),LocationInSentence);
                            tmpWordType = GetMemoryCellcharWordType(SingularWord,Result);
                            SetswSingularForm(LocationInSentence,SingularWord);
                            RuleTesting = false;
                            IsPlural    = true;
                            break;
                        }



                        //Rule #5 Words ending in y add ies: puppies, kitties
                        PatternMarker = OrigWord.find("ies");
                        //Location must be the ending
                        if((PatternMarker >=0)&&((PatternMarker+3)==int(OrigWord.size()))){
                            SingularWord = OrigWord.substr(0,PatternMarker);
                            SingularWord +="y";
                            SetswIsPluralWord(LocationInSentence,true);
                            SetswPluralRoot(LocationInSentence,SingularWord);
                            SetswPluralWordFlag(LocationInSentence,'p');
                            SetswWordType(GetMemoryCellcharWordType(SingularWord,Result),LocationInSentence);
                            if(Result == false)//singular form didn't exist - assume noun
                                SetswWordType(typeNoun,LocationInSentence);
                            tmpWordType = typeNoun;
                            SetswSingularForm(LocationInSentence,SingularWord);
                            RuleTesting = false;
                            IsPlural    = true;
                            break;
                        }


                        //Rule #2 Words ending in -ch, -s, -sh, -x, -z  get -es added  i.e. wash - washes, box - boxes
                        //      NOTE - houses needs fixed
                        PatternMarker = OrigWord.find("es");
                        //Location must be the ending
                        if((PatternMarker >=0)&&((PatternMarker+2)==int(OrigWord.size()))){
                            SingularWord = OrigWord.substr(0,PatternMarker-2);
                            SetswIsPluralWord(LocationInSentence,true);
                            SetswPluralRoot(LocationInSentence,SingularWord);
                            SetswPluralWordFlag(LocationInSentence,'p');
                            SetswWordType(GetMemoryCellcharWordType(SingularWord,Result),LocationInSentence);
                            tmpWordType = GetMemoryCellcharWordType(SingularWord,Result);
                            SetswSingularForm(LocationInSentence,SingularWord);
                            RuleTesting = false;
                            IsPlural    = true;
                            break;
                        }


                        //Rule #8 Regular Plurals: dogs, cats, cars
                        //   Last letter = 's' must not be 'ss'
                        PatternMarker = OrigWord.size()-1;
                        if(OrigWord[PatternMarker] == 's'){
                            PatternMarker = OrigWord.find("ss");
                            if((PatternMarker >=0)&&((PatternMarker+2)==int(OrigWord.size()))){
                              // end in ss don't proceed
                            }
                            else{
                                SingularWord = OrigWord.substr(0,OrigWord.size()-1);
                                SetswIsPluralWord(LocationInSentence,true);
                                SetswPluralRoot(LocationInSentence,SingularWord);
                                SetswPluralWordFlag(LocationInSentence,'p');
                                SetswWordType(GetMemoryCellcharWordType(SingularWord,Result),LocationInSentence);
                                tmpWordType = GetMemoryCellcharWordType(SingularWord,Result);
                                SetswSingularForm(LocationInSentence,SingularWord);
                                RuleTesting = false;
                                IsPlural    = true;
                                break;}
                        }






                        RuleTesting = false;
                  }
                  if(!IsPlural){
                      SetswPluralWordFlag(LocationInSentence,'s');  //set as singular
                  }

                  //Check for verb tense and try to set root
                  if(VerbTenseSet){
                    PatternMarker = VerbTenseCombos.find(tmpWord); // tmpWord has " " + OrigWord + " "
                    if(PatternMarker >= 0){
                        PresentTenseVerb = VerbTenseCombos.substr(PatternMarker+1);
                        PatternMarker = PresentTenseVerb.find(" ");
                        PresentTenseVerb = PresentTenseVerb.substr(PatternMarker+1,PresentTenseVerb.find(" "));
                        SetswPresentTenseForm(LocationInSentence,PresentTenseVerb);}
                  }

//*******************GRAMMER RULE TESTING*****************************************************
                  string  TrimSegment = "";
                  //Rule testing for past tense verbs
                  // ends in 'ed
                  // is not already set by previous operations, prevents proper nouns changing
                  // longer than three letters
                  if( (tmpWordType == typeUnknownWord) && (OrigWord.size()>3)){
                    TrimSegment = OrigWord.substr(OrigWord.size()-2,2);
                    if(TrimSegment == "ed" ){
                        tmpWordType = typeVerb;
                        SetswWordTense(LocationInSentence,'p');
                        PresentTenseVerb = OrigWord.substr(0,OrigWord.size()-2);
                        //PresentTenseVerb += "e";
                        SetswPresentTenseForm(LocationInSentence,PresentTenseVerb);
                        //TODO: test this extraction
                    }
                  }


                  //Rule testing for present tense verbs
                  // ends in 'ing
                  // is not already set by previous operations, prevents proper nouns changing
                  // longer than five letters
                  if( (tmpWordType == typeUnknownWord) && (OrigWord.size()>=5)){
                    TrimSegment = OrigWord.substr(OrigWord.size()-3,3);
                    if(TrimSegment == "ing" ){
                        tmpWordType = typeVerb;
                        SetswWordTense(LocationInSentence,'c');
                        PresentTenseVerb = OrigWord.substr(0,OrigWord.size()-3);
                        //TODO: Rules for adding 'e'
                        // 1) for words that end in a silent 'e',
                        //     drop the 'e' and add 'ing'
                        //    example: smile -> smiling
                        // 2) for one syllable words that end in consonant-vowel-consonant (except x and w)
                        //    double the last letter and add 'ing'
                        //    example: sit -> sitting
                        // 3) for most other words (including words that end in 'y')
                        //    add 'ing' with no changes
                        //  ref) https://www.elsonjunior.co.uk/year-6-homework/english-2/496-week-beginning-25th-september-spelling-homework/file
                        //PresentTenseVerb += "e";
                        SetswPresentTenseForm(LocationInSentence,PresentTenseVerb);
                    }
                  }

 //TODO:      Create present tense form storage i.e. remembered - past tense verb / present tense form is remember

                  //Rule testing for adverbs
                  // ends in 'ly
                  // is not already set by previous operations, prevents proper nouns changing
                  // longer than five letters
                  if( (tmpWordType == typeUnknownWord) && (OrigWord.size()>=4)){
                    TrimSegment = OrigWord.substr(OrigWord.size()-2,2);
                    if(TrimSegment == "ly" ){
                        tmpWordType = typeAdverb;
                        SetswWordTense(LocationInSentence,'c');
                        //extract root verb, i.e. quick from quickly
                        // -exceptions:[tepidly] root tepid is adjective
                        //             [extendedly] subroot [extended] root extend is verb
                        //TODO: Finish extraction
                    }
                  }


//TODO: Find and set nouns that end in 'er  like lawyer, teacher, worker


                  //create vowel pattern and store it in sw_VowelPattern
                  VowelPattern = "";
                  int VowelMarker = -1;
                  int Ymarker     = -1;
                  int Cmarker     = -1;
                  for(int x = 0; x < int(OrigWord.size()); x++){
                    VowelMarker = Vowels.find(OrigWord[x]);
                    if(VowelMarker >=0)
                        VowelPattern += "V";
                    else
                        VowelPattern += "C";
                  }
                  //rule sometimes "y" is a vowel
                  //  1) The word has no other vowel: gym, my.
                  //  2) The letter is at the end of a word or syllable: candy, deny, bicycle, acrylic.
                  //  3) The letter is in the middle of a syllable: system, borborygmus.
                  //  4) Typically, the letter “y” is a consonant when it is at the beginning of a word, e.g., yes, you, yard and young.
                  //  5) Ending y is not a vowel when preceded by a vowel
                  Ymarker = OrigWord.find("y");
                  if(Ymarker >= 0){
                    if(Ymarker == int(OrigWord.size())-1){ //2) y at end of word check
                        if(VowelPattern[Ymarker-1]== 'C'){ //5) ending y not preceded by vowel
                           VowelPattern[Ymarker] = 'V';}}

                  Cmarker = VowelPattern.find("V");
                  if(!(Cmarker >=0)){                      //1) no other vowel in word
                    VowelPattern[Ymarker] = 'V';}

                  if(VowelPattern[Ymarker-1]== 'C'){       //3) y not preceded by vowel
                     VowelPattern[Ymarker] = 'V';}

                  if(Ymarker == 0){                        //4) beginning y is a consonant
                     VowelPattern[Ymarker] = 'C';}



                  }

                  SetswVowelPattern(LocationInSentence,VowelPattern);


//-------------------------------------------check Propernoun rule-----------------------------------------
                    if(tmpWordType == typeUnknownWord){
                       if(GetMemoryCellcharWordType(tmpWord,Result) == typeProperNoun){ //was used as a proper noun before but here a noun
                        tmpWordType = typeNoun;
                       }
                    }

            if(Verbose)
                cout << "tmpWord " << tmpWord <<" type:" << tmpWordType << endl;
            return tmpWordType;

 }
//--------------------------------end Find Word Type--------------------------------------


//--------------------------------New Find Word Type(Extended)----------------------------

char  FindWordType(string LocalWord, string &ExtendedType, int LocationInSentence = -1){

           char   LocalWordType             = typeUnknownWord;  //char
           ExtendedType                     = typeExUnknownWord;//string
           string SearchWord                = " " + LocalWord + " ";
           string RawWord                   = GetswWords(LocationInSentence);   //mostly for proper noun checking, hence the raw word instead of LC word
           //----PRONOUNS-----------------------
           string Pronouns                  = " I you he she it they me him her my mine your ";
                  Pronouns                 += " yours our his hers its who those whom whose ";
                  Pronouns                 += " what which another each everything nobody ";
                  Pronouns                 += " either someone myself yourself himself their ";
                  Pronouns                 += " herself itself this that these those them ";
                  Pronouns                 += " somebody someone ";
           string PossessivePronouns        = " my your his her its our their mine yours hers ";
           string SubjectPronouns           = " I you he she it they somebody someone ";
           string ObjectPronouns            = " me you him her ";
           string InterrogativePronouns     = " who whom whose what which ";
           string IndefinatePronouns        = " another each everything nobody either someone them ";
           string DemonstrativePronouns     = " this that these those ";
           //----CONJUNCTIONS-------------------
           string Conjunctions              = " and but for nor or so yet as ";
           //----Cardinal Numbers---------------
           string CardinalNumbers           = " one two three four five six seven eight nine ten ";
           //----DETERMINERS--------------------
           string Determiners               = " the a an each every certain any all few many ";
                  Determiners              += " each some much no lot most enough both half neither ";
                  Determiners              += " there several ";
           string DefiniteArticles          = " the ";
           string IndefiniteArticles        = " a an there ";
           string DeterminerQuantifiers     = " few many much lot most some any enough several ";
           string Distributives             = " all both half either neither each every ";
           //----VERBS--------------------------
           string Verbs                     = " came are go gone went threw broke can will be ";
                  Verbs                    += " have do say get make go know take is see come ";
                  Verbs                    += " fell ran run think look want give use find tell ";
                  Verbs                    += " ask work seem feel try leave call am been sold ";
                  Verbs                    += " has made attach attached runs swims goes gather ";
                  Verbs                    += " sit sits build built cover covered bend bent ";
                  Verbs                    += " stretched stretch lets does says climbs placed ";
                  Verbs                    += " looks ";
           string LinkingVerbs              = " is are ";
           string ActionVerbs               = " sits lets does says climbs ";
           string PastTenseVerbs            = " came went gone threw broke ran sold fell has made ";
                  PastTenseVerbs           += " attached sat seen built covered bent stretched ";
                  PastTenseVerbs           += " stitched placed ";
           //----PREPOSITIONS-------------------
           string PrepositionWords          = " in into up after to on with under within ";
                  PrepositionWords         += " of at near until over across among while ";
                  PrepositionWords         += " from throughout through during towards by upon ";
                  PrepositionWords         += " across beside along onto between toward ";
                  PrepositionWords         += " behind like against amid ";
           //----SPECIFIC NOUNS-----------------
           string SpecificNouns             = " man woman girl boy men women girls boys lady ";
                  SpecificNouns            += " ladies sunday monday tuesday wednesday ";
                  SpecificNouns            += " thursday friday saturday clothing building ";
                  SpecificNouns            += " bikinis railing people children dress string ";
           string GenderNounsSingular       = " man woman lady girl boy ";
           string GenderNounsPlural         = " men women girls boys ladies ";
           string WeekDayNames              = " sunday monday tuesday wednesday ";
                  WeekDayNames             += " thursday friday saturday ";
           //----SPECIFIC ADJECTIVES------------
           string SpecificAdjectives        = " brown blue red white black green yellow pink ";
                  SpecificAdjectives       += " grey gray clear purple dyed dressed other ";
                  SpecificAdjectives       += " tan long young little interesting large no ";
                  SpecificAdjectives       += " dangerous serious ";
           //----SPECIFIC ADVERBS---------------
           string SpecificAdverbs           = " very where ahead just away together ";
           //----SENTENCE STOP/PAUSE------------
           string SentencePause             = " , ";
           //----CONTRACTIONS-------------------
           string Contractions              = " isn't can't won't didn't aren't ";

           //----ALL CONSTRUCTION WORDS---------
           string AllConstructionWords      = Pronouns + PossessivePronouns + SubjectPronouns +
                                              ObjectPronouns + InterrogativePronouns +
                                              IndefinatePronouns + DemonstrativePronouns +
                                              CardinalNumbers + Determiners + DefiniteArticles +
                                              DeterminerQuantifiers + Distributives +
                                              Verbs + LinkingVerbs + PastTenseVerbs +
                                              PrepositionWords + Conjunctions + SpecificNouns +
                                              SentencePause + SpecificAdjectives + SpecificAdverbs
                                              + Contractions;

           //----ALL CONSTRUCTION WORDS POINTER-
           int    isInBaseWords             = -1;
           //----CONJUNCTION POINTERS-----------
           int    isConjunction             = -1;
           //----CONTRACTION POINTERS-----------
           int    isContraction             = -1;
           //----PREPOSITION POINTERS-----------
           int    isPreposition             = -1;
           //----DETERMINER POINTERS------------
           int    isDeterminer              = -1;
           int    isDefiniteArticle         = -1;
           int    isIndefiniteArticle       = -1;
           int    isDeterminerQuantifier    = -1;
           int    isDistributive            = -1;
           //----VERB POINTERS------------------
           int    isVerb                    = -1;
           int    isPastTenseVerb           = -1;
           int    isLinkingVerb             = -1;
           int    isActionVerb              = -1;
           //----NOUN POINTERS------------------
           int    isSpecificNoun            = -1;
           int    isGenderNounSingular      = -1;
           int    isGenderNounPlural        = -1;
           int    isWeekDayName             = -1;
           //----Cardinal Pointers--------------
           int    isCardinalNumber          = -1;
           //----PRONOUN POINTERS---------------
           int    isDemonstrativePronoun    = -1;
           int    isPossessivePronoun       = -1;
           int    isPronoun                 = -1;
           int    isSubjectPronoun          = -1;
           int    isObjectPronoun           = -1;
           int    isInterrogativePronoun    = -1;
           int    isIndefinatePronoun       = -1;
           //----SPECIFIC ADJECTIVE POINTER-----
           int    isSpecificAdjective       = -1;
           //----SPECIFIC ADVERB POINTER--------
           int    isSpecificAdverb          = -1;
           //----SENTENCE STOP/PAUSE POINTER----
           int    isSentenceStop            = -1;
           //----LOCAL WORK VARIABLES-----------
           int    MatchPos                  = -1;   //pointer for substring searches

           isInBaseWords                    = AllConstructionWords.find(SearchWord);        //screen word
           if(isInBaseWords){

           isConjunction                    = Conjunctions.find(SearchWord);                ///base type
           isSentenceStop                   = SentencePause.find(SearchWord);               //Extended type
           isSpecificAdjective              = SpecificAdjectives.find(SearchWord);          //Extended type
           isSpecificAdverb                 = SpecificAdverbs.find(SearchWord);             //Extended type
           isContraction                    = Contractions.find(SearchWord);                //Extended type

           isPronoun                        = Pronouns.find(SearchWord);                    ///base type
            isDemonstrativePronoun          = DemonstrativePronouns.find(SearchWord);       //extended type
            isPossessivePronoun             = PossessivePronouns.find(SearchWord);          //extended type
            isSubjectPronoun                = SubjectPronouns.find(SearchWord);             //extended type
            isObjectPronoun                 = ObjectPronouns.find(SearchWord);              //extended type
            isInterrogativePronoun          = InterrogativePronouns.find(SearchWord);       //extended type
            isIndefinatePronoun             = IndefinatePronouns.find(SearchWord);          //extended type

           isDeterminer                     = Determiners.find(SearchWord);                  ///base type
            isDefiniteArticle               = DefiniteArticles.find(SearchWord);             //extended types
            isDeterminerQuantifier          = DeterminerQuantifiers.find(SearchWord);        //extended types
            isDistributive                  = Distributives.find(SearchWord);                //extended types
            isIndefiniteArticle             = IndefiniteArticles.find(SearchWord);           //extended type

           isVerb                           = Verbs.find(SearchWord);                        ///base type
            isPastTenseVerb                 = PastTenseVerbs.find(SearchWord);               //extended types
            isLinkingVerb                   = LinkingVerbs.find(SearchWord);                 //extended types
            isActionVerb                    = ActionVerbs.find(SearchWord);                  //extended type

           isCardinalNumber                 = CardinalNumbers.find(SearchWord);              ///base type '#'
           isPreposition                    = PrepositionWords.find(SearchWord);             ///base type 'I'

           isSpecificNoun                   = SpecificNouns.find(SearchWord);                ///base
           isGenderNounSingular             = GenderNounsSingular.find(SearchWord);          //extended type
           isGenderNounPlural               = GenderNounsPlural.find(SearchWord);            //extended type
           isWeekDayName                    = WeekDayNames.find(SearchWord);                 //extended type


          // Process Conjunctions
          if(isConjunction >=0){
             LocalWordType = typeConjunction;                                               ///base type
             ExtendedType  = typeCoordinatingConjunction;                                   // extended type "CC"
             return LocalWordType;}

          // Process Contractions
          if(isContraction >=0){
             LocalWordType = typeContraction;                                               ///base type
             ExtendedType  = typeExContraction;                                             // extended type "CONT"
             return LocalWordType;}

          // Process Adjectives
          if(isSpecificAdjective >=0){
             LocalWordType = typeAdjective;                                                 ///base type
             ExtendedType  = typeExAdjective;                                               // extended type
             return LocalWordType;}

          // Process Adverbs
          if(isSpecificAdverb >=0){
             LocalWordType = typeAdverb;                                                    ///base type
             ExtendedType  = typeExAdverb;                                                  // extended type
             return LocalWordType;}

          // Process Comma
          if(isSentenceStop >=0){
            LocalWordType  = typeSentenceBreak;                                             ///Base type
            ExtendedType   = typeExSentenceBreak;                                           // Extended type
            return LocalWordType;}

          // Process Pronouns
          if(isPronoun >= 0){
             LocalWordType = typePronoun;                                                   ///base type 'p'
             if(isSubjectPronoun >= 0){
                ExtendedType = typeSubjectPronoun;}                                         // extended type "PS"
             else
             if(isObjectPronoun >=0 ){
                ExtendedType = typeObjectPronoun;}                                          // extended type "PJ"
                else
                if(isInterrogativePronoun >=0){
                   ExtendedType = typeInterrogativePronoun;}                                // extended type "PQ"
                   else
                   if(isIndefinatePronoun >= 0){
                      ExtendedType = typeIndefinatePronoun;}                                // extended type "PI"
                      else
                      if(isPossessivePronoun >=0){
                         ExtendedType = typePossessivePronoun;}                             // extended type "PO"
                         else
                         if(isDemonstrativePronoun >=0){
                            ExtendedType = typeDemonstrativePronoun;}                       // extended type "PD"
                            else
                                ExtendedType = typePronounBase;                             // extended type "PB"
              return LocalWordType;
          }


          // Process Preposition
          if(isPreposition >= 0){
             LocalWordType = typePreposition;                                                ///base type 'I'
             ExtendedType  = typePrepositionWord;                                            // extended type "PR"
             return LocalWordType;}


          // Process Cardinal
          if(isCardinalNumber >= 0){
             LocalWordType = typeNumericWord;                                               ///base type '#'
             ExtendedType  = typeCardinalNumber;                                            //extended type "cn"
             return LocalWordType;}

          // Process Determiners and their extended types
           if(isDeterminer >=0){
              LocalWordType = typeDeterminer;                                                //  'd'
              if(isDefiniteArticle >= 0){
               ExtendedType = typeDefiniteArticle;}                                          /// "da"
                else
                    if(isDeterminerQuantifier >= 0){
                        ExtendedType = typeDeterminerQuantifier;}                            /// "dq"
                    else
                        if(isDistributive >=0){
                            ExtendedType = typeDistributive;}                                /// "dv"
                        else
                           if(isIndefiniteArticle >=0){
                              ExtendedType = typeIndefiniteArticle;}
                            else
                            ExtendedType = typeDeterminerBase;                               /// "dd"
                            return LocalWordType;
           }

          // Process Verbs and their extended types
           if(isVerb >= 0){                                                                  // 'v'
               LocalWordType = typeVerb;
               if(isPastTenseVerb >= 0){
                ExtendedType = typePastTenseVerb;}                                            /// "vp"
                else
                    if(isLinkingVerb >=0){
                        ExtendedType = typeLinkingVerb;}                                      /// "vL"
                    else
                        if(isActionVerb >=0){
                            ExtendedType = typeActionVerb;}                                   /// "VACT"
                        else
                            ExtendedType = typeVerbBase;                                      /// "vv"
                            return LocalWordType;}

           // Process Specific Nouns
            if(isSpecificNoun >=0){
                LocalWordType = typeNoun;                                                     // 'n'
                if(isGenderNounPlural >=0){
                    ExtendedType = typeGenderNounPlural;}
                else
                    if(isGenderNounSingular >=0){
                       ExtendedType = typeGenderNounSingular;}
                else
                    if(isWeekDayName >=0){
                       ExtendedType = typeNounWeekDay;}
                else
                       ExtendedType = typeNounBase;

                return LocalWordType;}

           }//end of screened word


           // Check for action verb
           // word type will still be unknown at this point
           MatchPos = LocalWord.find("ing");
           if((MatchPos >=0) && ((MatchPos + 3) == LocalWord.size())){      //must be at end of sentence
                LocalWordType = typeVerb;                                                     //  'v'
                ExtendedType  = typeActionVerb;                                               /// "va"
                return LocalWordType;}
             else{
                MatchPos = LocalWord.find("inging");
                if((MatchPos >=0) && ((MatchPos + 6) == LocalWord.size())){
                    LocalWordType = typeVerb;
                    ExtendedType  = typeActionVerb;
                    return LocalWordType;
                }
             }

           // Check for proper noun
           // Word type is still unknown here
           if( (RawWord[0] >='A' && RawWord[0] <= 'Z') && (LocationInSentence > 0) ){
                LocalWordType = typeProperNoun;
                ExtendedType  = typeExProperNoun;
                return LocalWordType;}


           // Check for 'ly' endings for adverb
           // word type still unknown at this point
           MatchPos = LocalWord.find("ly");
           if((MatchPos >=0) && ((MatchPos + 2) == LocalWord.size()) ) {
               LocalWordType = typeAdverb;
               ExtendedType  = typeExAdverb;
               return LocalWordType;}


           // Check for 'ous' endings for adjective
           // word type still unknown at this point
           MatchPos = LocalWord.find("ous");
           if((MatchPos >=0) && ((MatchPos + 3) == LocalWord.size()) ) {
               LocalWordType = typeAdjective;
               ExtendedType  = typeExAdjective;
               return LocalWordType;}

           return LocalWordType;

}
//---------------------------------END NEW FIND WORD TYPE (EXTENDED)----------------------

//----------------------------------APPLY GRAMMAR RULES TO DISCOVER NEW WORDS-------------
bool ApplyGrammarRules(){
       stack <int>    DefiniteArticleLocs;
       queue <string> FollowingWords;
       queue <int>    intFollowingWords;
       int            NextWord;
       bool           Correction = false;

        //store all definite article locations
        for(int x= 0; x<GetFromSentenceWordCount(); x++){
            if(GetswExtendedWordType(x) == typeDefiniteArticle){
                DefiniteArticleLocs.push(x);
            }
        }

        while(DefiniteArticleLocs.size()>0){
            NextWord = 1;
            while (!FollowingWords.empty()) FollowingWords.pop();       //empty the queue
            while (!intFollowingWords.empty()) intFollowingWords.pop(); //empty the queue

            //store words that follow the definite article up to the end of sentence, or verb or preposition
            while(((DefiniteArticleLocs.top() + NextWord) != GetFromSentenceWordCount()) &&
            (GetswWordType(DefiniteArticleLocs.top()+NextWord) != typeVerb) && (GetswWordType(DefiniteArticleLocs.top()+NextWord) != typePreposition) ) {
            FollowingWords.push(GetswExtendedWordType(DefiniteArticleLocs.top()+NextWord));
            intFollowingWords.push(DefiniteArticleLocs.top()+NextWord);
            NextWord++;
            }
                if(FollowingWords.size() >0){
                    if( (FollowingWords.size() == 1) && (GetswExtendedWordType(intFollowingWords.front()) == typeExUnknownWord) ){
                        //only 1 unknown between definite article and verb, end of sentence or preposition
                        SetswExtendedWordType(intFollowingWords.front(),typeNounBase); //set extended type
                        SetswWordType(typeNoun,intFollowingWords.front());             //set char type
                        FollowingWords.pop();
                        intFollowingWords.pop();
                        Correction = true;
                    }
                    else
                        if( (FollowingWords.size() == 2) && (GetswExtendedWordType(intFollowingWords.front()) == typeExUnknownWord) ) {
                            //2 words between with the first being unknown
                            SetswExtendedWordType(intFollowingWords.front(),typeExAdjective);   //set extended type
                            SetswWordType(typeAdjective,intFollowingWords.front());             //set char type
                            FollowingWords.pop();
                            intFollowingWords.pop();
                            if(GetswExtendedWordType(intFollowingWords.front()) == typeExUnknownWord){
                                SetswExtendedWordType(intFollowingWords.front(),typeNounBase); //set extended type
                                SetswWordType(typeNoun,intFollowingWords.front());             //set char type
                                FollowingWords.pop();
                                intFollowingWords.pop();
                                Correction = true;}
                        }

                    else{
                        FollowingWords.pop();
                        intFollowingWords.pop();}


                }
            DefiniteArticleLocs.pop();
        }


    return Correction;

}
//--------------------------------END APPLY GRAMMAR RULES---------------------------------

//--------------------------------ENHANCE PATTERN-----------------------------------------
bool EnhancePattern(){
    int    PatternMatchPointer     = -1;
    int    ShortPatternPointer     = -1;
    extern int PatternCount;
    extern string Patterns [][4];         //defined in library.cpp
    string tmptype                 = "";
    string  LocalExtendedPattern   = GetFromSentenceExtendedPattern();
    string  LocalShortPattern      = GetFromSentencePattern();
    bool    Corrected              = false;


    for( int x =0; x < PatternCount; x++){
      if(Patterns[x][3] == "y"){
          PatternMatchPointer = LocalExtendedPattern.find(Patterns[x][0]);
            if(PatternMatchPointer >=0){
               LocalExtendedPattern.replace(PatternMatchPointer,Patterns[x][0].size(),Patterns[x][1]);
               ShortPatternPointer = Patterns[x][0].find(typeExUnknownWord);
               ShortPatternPointer = ShortPatternPointer / ExtendedTypeSize;
               tmptype = Patterns[x][2];
               LocalShortPattern[(PatternMatchPointer/ExtendedTypeSize)+ShortPatternPointer] = tmptype[0];
               SetInSentenceExtendedPattern(LocalExtendedPattern);
               SetInSentencePattern(LocalShortPattern);
               Corrected = true;
               return Corrected;}
      }
    }

    return Corrected;
}
//--------------------------------END ENHANCE PATTERN-------------------------------------


//--------------------------------GRAMMER PATTERN CHECK-----------------------------------------
bool GrammerPatternCheck(){
    int    PatternMatchPointer     = -1;
    int    ShortPatternPointer     = -1;
    extern int GrammerPatternCount;
    extern string GrammerPatterns [][7];         //defined in library.cpp
    string tmptype                 = "";
    string::size_type decType;

    string  LocalExtendedPattern   = GetFromSentenceExtendedPattern();
    string  LocalShortPattern      = GetFromSentencePattern();
    bool    Corrected              = false;


    for( int x =0; x < GrammerPatternCount; x++){
      if(GrammerPatterns[x][3] == "y"){
          PatternMatchPointer = LocalExtendedPattern.find(GrammerPatterns[x][0]);
            if(PatternMatchPointer >=0){
               LocalExtendedPattern.replace(PatternMatchPointer,GrammerPatterns[x][0].size(),GrammerPatterns[x][1]);
               ShortPatternPointer  = stoi(GrammerPatterns[x][4],&decType);
               tmptype = GrammerPatterns[x][2];
               LocalShortPattern[(PatternMatchPointer/ExtendedTypeSize)+ShortPatternPointer] = tmptype[0];
               if(stoi(GrammerPatterns[x][6])>=0){  //second correction
                  ShortPatternPointer  = stoi(GrammerPatterns[x][6],&decType);
                  tmptype = GrammerPatterns[x][5];
                  LocalShortPattern[(PatternMatchPointer/ExtendedTypeSize)+ShortPatternPointer] = tmptype[0];
               }
               SetInSentenceExtendedPattern(LocalExtendedPattern);
               SetInSentencePattern(LocalShortPattern);
               Corrected = true;
               return Corrected;}
      }
    }

    return Corrected;
}
//--------------------------------END GRAMMER PATTERN CHECK-------------------------------------

//---------------------------EXTRAPOLATE NOUN FORMS---------------------------------------
void ExtrapolateNounForms(){
    string  WorkingWord    =  "";
    string  tmpWord        =  "";

    for(int x = 0; x< GetFromSentenceWordCount(); x++){
        if(GetswWordType(x) == typeNoun){
           WorkingWord = GetswWordsLC(x);
           if(WorkingWord[WorkingWord.size()-1] != 's') {
            //make plural
            tmpWord  = WorkingWord + "s";
            SetMemoryCellpCellData(tmpWord);
            SetMemoryCellpSingularForm(tmpWord,WorkingWord);
            SetMemoryCellpExtendedWordType(tmpWord,typeNounBase);
            SetMemoryCellpCellIsSingular(tmpWord,'p');
            SetMemorypWordType(tmpWord,typeNoun);
            //make singular possessive
            tmpWord  = WorkingWord + "'s";
            SetMemoryCellpCellData(tmpWord);
            SetMemoryCellpSingularForm(tmpWord,WorkingWord);
            SetMemoryCellpExtendedWordType(tmpWord,typeNounSingularPossessive);
            SetMemoryCellpCellIsSingular(tmpWord,'p');
            SetMemoryCellpIsPluralPossessive(tmpWord,false);
            SetMemoryCellpIsSingularPossessive(tmpWord,true);
            SetMemorypWordType(tmpWord,typeNoun);

            //make plural possessive
            tmpWord  = WorkingWord + "s'";
            SetMemoryCellpCellData(tmpWord);
            SetMemoryCellpSingularForm(tmpWord,WorkingWord);
            SetMemoryCellpExtendedWordType(tmpWord,typeNounPluralPossessive);
            SetMemoryCellpCellIsSingular(tmpWord,'p');
            SetMemoryCellpIsPluralPossessive(tmpWord,true);
            SetMemoryCellpIsSingularPossessive(tmpWord,false);
            SetMemorypWordType(tmpWord,typeNoun);


           }
        }
    }


}

//------------------------------END EXTRAPOLATE NOUN FORMS--------------------------------


//-----------------------SlowSpeak--------------------------------------------------------
void SlowSpeak(string str_Data, bool Recording = true, int Delay = ThisSpeed, bool CarriageReturn = true ){
    if(StoryMode == false){
             string WorkingWord;
             if(Recording){
                SaveResponsesSent(str_Data);}
             SlowSentence.Parse(str_Data);
             for(int x = 0; x < SlowSentence.GetWordCount(); x++){

                WorkingWord = SlowSentence.GetWords(x);
                for(int y = 0; y < int(WorkingWord.size()); y++){
                    cout << WorkingWord[y];
                    for(int dly = 0; dly < Delay; dly++);
                }
                cout  << " ";

             }
                cout << "\b";
                if(CarriageReturn) cout << SlowSentence.GetPunctuation() << endl;
    }//end Story Mode
}
//--------------------------------End SlowSpeak------------------------------------------

//-------------------------Request User Response-----------------------------------------
int RequestUserResponse(string AltPositiveResponse = "", string AltNegativeResponse = "", string OtherResponse = "")
{
    if(StoryMode == false){
            int Matched = -1;

            string PositiveResponse = " yes Yes OK ok Ok correct Correct right Right Exactly exactly ye ";
            string NegativeResponse = " No no wrong Wrong What what n ";
            string Response         = "";
            if(AltPositiveResponse != "") PositiveResponse = AltPositiveResponse;
            if(AltNegativeResponse != "") NegativeResponse = AltNegativeResponse;

            while (Response == ""){
                cout << ">?";
                getline (cin,Response);}
            tmpSentence.Parse(Response);
            Response = tmpSentence.GetWords(0);
            Matched = PositiveResponse.find(" " + Response + " ");
            if(Matched >= 0)
                return 1;
            Matched = NegativeResponse.find(" " + Response + " ");
            if(Matched >= 0)
                return -1;

            Matched = OtherResponse.find(" " + Response + " ");
            if(Matched >= 0)
                return -2;
    }//end story mode check
    return 1;
}
//-------------------------End Request User Response-----------------------------------------

//---------------------------------FINDSUBJECT()--------------------------------------------------
        int FindSubject()
        {
            //********TODO**********************
            //  Check for and flag/store dual subjects, i.e. Jack and Jill
            //Order Of Preference:
            //  Proper Noun
            //  Pronoun
            //  Noun
            //  Determiner +1
            //  Unknown word

            if(Verbose)cout << "[c_Language.h::FindSubject]" << endl;

            int    DeterminerLocation;       DeterminerLocation   = -1;
            int    UnknownLocation;          UnknownLocation      = -1;
            int    WordCount;                WordCount            =  0;
            int    SubLocation;              SubLocation          = -1;
            int    NounLocation;             NounLocation         = -1;
            int    NounCount;                NounCount            = -1;
            int    SecondNounLocation;       SecondNounLocation   = -1;
            int    ProNounLocation;          ProNounLocation      = -1;
            int    ProperNounLocation;       ProperNounLocation   = -1;
            int    ProNounOtherLocation;     ProNounOtherLocation = -1;
            int    JoinerLocation;           JoinerLocation       = -1;
            int    SecondSubLocation;        SecondSubLocation    = -1;
            string Pattern;                  Pattern              = "";
            string SubString;                SubString            = "";
            bool   PickingSubject;           PickingSubject       = true;

            WordCount = GetFromSentenceWordCount();

            if ((GetswWordsLC(0)== "is") || (GetswWordsLC(0)=="can") || (GetswWordsLC(0)=="will") || (GetswWordsLC(0)=="are") ) SetInSentenceIsQuestion(true);

            for(int x = 0; x < WordCount; x++){
                if(GetswWordType(x)== typeDeterminer) if(DeterminerLocation == -1) DeterminerLocation = x;
                if(GetswWordType(x)== typeUnknownWord) if(UnknownLocation == -1)    UnknownLocation    = x;
                if(GetswWordType(x)== typeNoun){if(NounLocation == -1)    { NounLocation       = x; NounCount ++;} else SecondNounLocation = x; NounCount++;}
                if(GetswWordType(x)== typeReplacementWord) if(SubLocation == -1)        SubLocation        = x;
                if(GetswWordType(x)== typePronoun) if(ProNounLocation == -1)    ProNounLocation    = x;
                if(GetswWordType(x)== typeProperNoun) if(ProperNounLocation == -1) ProperNounLocation = x;
                if(GetswWordType(x)== typeProNounsInward) if(ProNounLocation == -1) ProNounLocation = x;
                if(GetswWordType(x)== typeProNounsOutward) if(ProNounLocation == -1) ProNounLocation = x;
                if(GetswWordType(x)== typeGenderIndicator) if(ProNounOtherLocation == -1) ProNounLocation = x;
                if(GetswWordType(x)== typeJoinerWord) if(JoinerLocation == -1) JoinerLocation = x;
                if(GetswWordType(x)== typeVerb){ SetInSentenceVerbLocation(x);}
                if(GetswWordType(x)== typeAdjective){ SetInSentenceAdjectiveLocation(x);}
                if(GetswWordType(x)== typeAdverb){ SetInSentenceAdverbLocation(x);}
                if(GetswWordType(x)== typePreposition){ SetInSentencePrepositionPosition(x);}
                Pattern += GetswWordType(x);
            }
            //SetInSentencePattern(Pattern);
            if(SecondNounLocation != -1) SetInSentenceIndirectObjectLocation(SecondNounLocation); else SetInSentenceIndirectObjectLocation(-1);
            SetInSentenceNounCount(NounCount);

            if( (ProperNounLocation != -1) && (NounLocation != -1) ){
                SetInSentenceIndirectObjectLocation(NounLocation);       //set indirect object
                SubLocation = ProperNounLocation;
                PickingSubject = false;}
            else
                if ((ProNounLocation != -1) && (NounLocation != -1)){
                    SetInSentenceIndirectObjectLocation(NounLocation);
                    SubLocation = ProNounLocation;
                    PickingSubject = false;}

            while(PickingSubject){
                if((SubLocation == -1) && (ProperNounLocation != -1))
                    SubLocation = ProperNounLocation;
                else
                    if((SubLocation == -1) && (ProNounLocation !=-1))
                        SubLocation = ProNounLocation;
                else
                    if((SubLocation == -1) && (ProNounOtherLocation != -1))
                        SubLocation = ProNounOtherLocation;
                else
                    if((SubLocation == -1) && (NounLocation !=-1))
                        SubLocation = NounLocation;
                else
                    if((SubLocation == -1) && (DeterminerLocation != -1))
                        SubLocation = DeterminerLocation +1;
                else
                    if((SubLocation == -1) && (UnknownLocation != -1))
                        SubLocation = UnknownLocation;

              PickingSubject = false;
            }

                if(JoinerLocation >= 1){                      //check for dual subjects
                    if(JoinerLocation < SubLocation){

                        SetInSentenceHasDualSubjects(true);
                        SetInSentenceSecondSubject(GetswWords(JoinerLocation - 1));
                        SetInSentenceSecondSubjectLocation(JoinerLocation - 1);}
                     else {
                        if((GetswWordType(JoinerLocation+1) == typeNoun) || (GetswWordType(JoinerLocation+1) == typeGenderIndicator) ||
                            (GetswWordType(JoinerLocation+1) == typePronoun) || (GetswWordType(JoinerLocation+1) == typeProperNoun))
                                SecondSubLocation = JoinerLocation + 1;
                        else
                            if((GetswWordType(JoinerLocation+2) == typeNoun) || (GetswWordType(JoinerLocation+2) == typeGenderIndicator) ||
                             (GetswWordType(JoinerLocation+2) == typePronoun) || (GetswWordType(JoinerLocation+2) == typeProperNoun))
                                SecondSubLocation = JoinerLocation + 2;
                        else
                            if((GetswWordType(JoinerLocation+3) == typeNoun) || (GetswWordType(JoinerLocation+3) == typeGenderIndicator) ||
                             (GetswWordType(JoinerLocation+3) == typePronoun) || (GetswWordType(JoinerLocation+3) == typeProperNoun))
                                SecondSubLocation = JoinerLocation + 3;
                        else
                            if((GetswWordType(JoinerLocation+4) == typeNoun) || (GetswWordType(JoinerLocation+4) == typeGenderIndicator) ||
                             (GetswWordType(JoinerLocation+4) == typePronoun) || (GetswWordType(JoinerLocation+4) == typeProperNoun))
                                SecondSubLocation = JoinerLocation + 4;
                            SetInSentenceHasDualSubjects(true);
                            SetInSentenceSecondSubject(GetswWords(SecondSubLocation));
                            SetInSentenceSecondSubjectLocation(SecondSubLocation);
                            }
                }//end dual subjects

            if(Verbose)
                    cout << "Suggested subject location:" << SubLocation << " Pattern:" << GetFromSentencePattern() << " Indirect Object Location:" << GetFromSentenceIndirectObjectLocation()<< endl;
            SetInSentenceSubjectLocation(SubLocation);
            //store the subject string in sPrimeSubject
            if(SubLocation >=0){
                SubString = GetswWordsLC(SubLocation);
                if(GetFromSentenceHasDualSubjects()){
                    SubString += " and " + GetFromSentenceSecondSubject();
                }
                SetInSentencePrimeSubject(SubString);
            }
            FindDirectAndIndirectObject();
            return SubLocation;
        }
//--------------------------------------------------end Find Subject----------------------------------------------------------

       bool FindDirectAndIndirectObject(){
            int    VerbMarker = -1;
            int    LastPos    = -1;
            bool   Marked     = false;
            string WorkingPattern = GetFromSentencePattern();

        //  The direct object must be a noun or pronoun.
        //  A direct object will never be in a prepositional phrase
        //. The direct object will not equal the subject as the predicate nominatives
        //, nor does it have a linking verb as a predicate nominative sentences does.
        // ref. http://www.dailygrammar.com/Lesson-106-Direct-Object.htm

        // An indirect object is really a prepositional phrase
        // in which the preposition to or for is not stated but understood. It tells to whom or for whom something is done.
        // The indirect object always comes between the verb and the direct object.
        // The indirect object always modifies the verb.
        // It may have modifiers and be compound. It is used with verbs such as give, tell, send, get, buy, show, build, do, make, save, and read.
        //ref. http://www.dailygrammar.com/Lesson-191-Indirect-Objects.htm

       //find the noun after the verb and mark it as Direct Object
       //TODO: Could be pronoun instead

            LastPos      = int(WorkingPattern.size());
            VerbMarker   = WorkingPattern.find("v");
            if(VerbMarker == -1) VerbMarker = LastPos;
            for(int x = VerbMarker; x < LastPos; x++){
                if(WorkingPattern[x] == typeNoun){
                    SetInSentenceDirectObjectLocation(x);
                    SetInSentenceDirectObject(GetswWordsLC(x));
                    Marked = true;
                    break;
                }
            }
            return Marked;
       }


//----------------------------Find and Set Gist of Current Sentence-----------------------------------------------------------

        bool FindAndSetGistOfSentence(){
        if(Verbose)cout << "[c_Language::FindAndSetGistOfSentence] :";
            //***TODO*** Find and set subGistOfSentence
            //  also save and read this new data, plus Preposition flag and position in Long Term Memory
            bool   Result          = false;
            bool   Checking        = true;
            int    VerbPointer     = -1;
            int    QuestionPointer = -1;
            int    JoinerPointer   = -1;
            int    StopPoint       = -1;
            int    GistStart       = -1;
            string GistString      = "";
            string subGistString   = "";
            string SupportiveGist  = "";
            string LocalPattern    =GetFromSentencePattern();

            for(int x = 0; x <=int(LocalPattern.size()); x++){
                if(LocalPattern[x] == typeVerb) VerbPointer     = x;
                if(LocalPattern[x] == typeQuestion) QuestionPointer = x;
                if(LocalPattern[x] == typeJoinerWord) JoinerPointer   = x;
            }

            if( (VerbPointer < 0) && (!GetFromSentenceIsQuestion()) ) Checking = false; //no verb, cannot find gist without it(yet)
            while (Checking){
                    if(GetFromSentenceIsQuestion()){
                        //process gist of question
                        GistStart = QuestionPointer+1;
                        for (int x = QuestionPointer+1; x <= GetFromSentenceWordCount(); x++){
                            GistString += " " + GetswWords(x);
                        }
                        Result = true;     //control, Gist was found
                        Checking = false;
                    }
                    else
                    {
                        //process gist of statement
                        //for now, gist is verb to the end of sentence or until preposition is found
                        if(GetFromSentenceHasPreposition()){
                            StopPoint = GetFromSentencePrepositionPosition()-1;
                            if(StopPoint < VerbPointer) StopPoint = GetFromSentenceWordCount();
                        }
                        else{
                            if(JoinerPointer >=0)
                               StopPoint = JoinerPointer-1;
                            else
                               StopPoint = GetFromSentenceWordCount();
                        }
                        GistStart = VerbPointer;
                        for(int x = VerbPointer; x < StopPoint; x++){
                            GistString += " " + GetswWords(x);
                        }
                        Result   = true;  //control, Gist was found
                        Checking = false;
                        //since there is a verb, Get sub-Gist of I type word (preposition)
                        if(GetFromSentenceHasPreposition()){
                            //Get sub-Gist including preposition, to verb pointer or end of sentence
                            if(VerbPointer < GetFromSentencePrepositionPosition()){
                               StopPoint = GetFromSentenceWordCount();
                            }
                            else{
                                StopPoint = VerbPointer-1;
                            }
                            for (int x = GetFromSentencePrepositionPosition(); x < StopPoint; x++){
                                subGistString += " " + GetswWords(x);
                            }
                        }
                        else
                        if(JoinerPointer>=0){
                            for(int x = JoinerPointer+1; x <=GetFromSentenceWordCount(); x++){
                                subGistString += " " + GetswWords(x);
                            }
                        }
                    }

            }//end while checking

            if(Result){ //extract supportive gist to the beginning of the gist
                    for(int x = 0; x<= GistStart-1; x++){
                        SupportiveGist += GetswWords(x) + " ";
                    }

            }

            if(Result){
                //store the Gist and subGist phrase
                //  trim leading space
                string  NewGistString     = "";
                string  NewSubGist        = "";
                string  NewSupportiveGist = "";
                for(int x = 1; x<= int(GistString.size()-1); x++){
                    NewGistString += GistString[x];
                }
                for(int x = 1; x <=int(subGistString.size()-1); x++){
                    NewSubGist += subGistString[x];
                }
                for(int x = 0; x <=int(SupportiveGist.size()-1); x++){
                    NewSupportiveGist += SupportiveGist[x];
                }
                SetInSentenceSupportivePhrase(NewSupportiveGist);
                SetInSentenceGistOfSentence(NewGistString);
                SetInSentenceSubGistOfSentence(NewSubGist);
                if (Verbose){
                    cout << "\n  Gist =" << NewGistString << endl;
                    cout << "  subGist =" << NewSubGist << endl;
                 }
            }
            return Result;

        }
//------------------------END of Bool FINDANDSETGISTOFSENTENCE()----------------------------------------------------------------

//-------------------------Imply Unknowns()-------------------------------------------------------------------------------------

        void ImplyUnknowns(){
        if(Verbose)
           cout << "[c_Language::ImplyUnknowns]\n";
        //look for unknown word types inside certain patterns and assert their type
        // note:This pattern work and assumptions comes from observing patterns stored in PatternData.file for this purpose
        //local vars
        string    LocalPattern      = GetFromSentencePattern();
        bool      SettingPattern    = true;
        int       PatternPointer    = -1;
        if(Verbose)
           cout << "Beginning pattern:" << LocalPattern << endl;

        while(SettingPattern){

            //Check for noun possible in this pattern 'duIduvu'
            // the unknown follows a determiner and then has a preposition, most likely a noun a position 1
            PatternPointer = LocalPattern.find("du>");
            while(PatternPointer >=0){
                LocalPattern[PatternPointer+1] = typeNoun;
                SetswWordType(typeNoun,PatternPointer+1);
                SetInSentencePattern(LocalPattern);
                PatternPointer = LocalPattern.find("du>");   //check again
                SettingPattern = false;
                //break;} // allow next pattern check to proceed
                }

            PatternPointer = LocalPattern.find("duvu");
            if(PatternPointer >= 0){
                LocalPattern[PatternPointer+1] = typeNoun;
                SetswWordType(typeNoun,PatternPointer+1);
                SetInSentencePattern(LocalPattern);
                break;}


            PatternPointer = LocalPattern.find("pu"); //check for implied noun by ownership, i.e. "his bone"
            if(PatternPointer >= 0){
               if((GetswWordsLC(PatternPointer) == "his") || (GetswWordsLC(PatternPointer) == "her")){
                   LocalPattern[PatternPointer+1] = typeNoun;
                   SetswWordType(typeNoun,PatternPointer+1);
                   SetInSentencePattern(LocalPattern);
                   SettingPattern = false;
                   break;}
            }

            //TODO: Some process is over riding this
            PatternPointer = LocalPattern.find(">duu");//check for adject-noun combo
            if(PatternPointer >=0 ){
                if(GetswWordsLC(PatternPointer+2)[GetswWordsLC(PatternPointer+2).size()-1] == 'y'){
                    LocalPattern[PatternPointer+2] = typeAdjective;
                    LocalPattern[PatternPointer+3] = typeNoun;
                    SetInSentencePattern(LocalPattern);
                    SettingPattern = false;
                    break;
                }
            }

         SettingPattern = false;
        }//end while loop


        if(Verbose)
           cout << "Ending pattern:" << LocalPattern << endl;
    }
//-------------------------------END IMPLY UNKNOWNS------------------------------------------------------------------------------
};

#endif // C_LANGUAGE_H
