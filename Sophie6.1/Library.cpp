#include <Library.h>

#include <string>
#include <time.h>

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

using namespace std;
extern string Version;
char typeDeterminer       = 'd';
 string typeDeterminerBase       = "DDDB";
 string typeDefiniteArticle      = "DFAT";
 string typeIndefiniteArticle    = "DIND";
 string typeDeterminerQuantifier = "DQNT";
 string typeDistributive         = "DDIV";

char typeVerb             = 'v';
 string typeVerbBase             = "VVVB";
 string typePastTenseVerb        = "VPST";
 string typeLinkingVerb          = "VLNK";
 string typeActionVerb           = "VACT";

char typeAdverb           = 'A';

char typePronoun          = 'p';
 string typePronounBase          = "PPPB";
 string typePossessivePronoun    = "POSS";
 string typeSubjectPronoun       = "PSUB";
 string typeObjectPronoun        = "POBJ";
 string typeInterrogativePronoun = "PQST";
 string typeIndefinatePronoun    = "PIND";
 string typeDemonstrativePronoun = "PDEM";

char typeProperNoun       = 'P';
char typeNoun             = 'n';
 string typeGenderNounSingular   = "NNGS";
 string typeGenderNounPlural     = "NNGP";
 string typeNounWeekDay          = "NWDY";

char typeAdjective        = 'a';
char typeSentenceBreak    = '_';
char typeContraction      = 'C';
char typeConjunction      = 'c';
 string typeConjunctionBase       = "CB";
 string typeCoordinatingConjunction = "COOR";

char typeProNounsInward   = 'm';
char typeProNounsOutward  = 'y';
char typeQuestion         = 'q';
char typeReplacementWord  = 'r';
char typeDirective        = 'X';
char typeJoinerWord       = '+';
char typeAssociativeWord  = 'g';
char typePluralPronoun    = 'N';
char typeThrowAwayWord    = 't';
char typeGenderIndicator  = 'G';
char typeGreetingsWord    = 'W';
char typeGenderDeterminer = 'B';
char typeFemaleClass      = 'f';
char typeMaleClass        = 'b';
char typePreposition      = 'I';
 string typePrepositionWord         = "PREP";
char typeUnknownWord      = 'u';
 string typeExUnknownWord           = "UUUU";

char typeNumericWord      = '#';
 string typeCardinalNumber          = "CARD";
char typeExclamation      = 'E';



        /// Checks the current file version after the second decimal,
        ///   against the one read.i.e. 6.1.02a.009.28  02a is the file version
        ///   Returns true if same / false if different
        bool VerifyFileVersion(string VersionToCheck){
            int    DecimalPointer1 = -1;
            int    DecimalPointer2 = -1;
            string Extraction1     = "";
            string Extraction2     = "";
            bool   Result = false;


            DecimalPointer1  = Version.find(".");
            DecimalPointer1  = Version.find(".",DecimalPointer1+1);
            Extraction1      = Version.substr(DecimalPointer1+1,3);

            DecimalPointer2  = VersionToCheck.find(".");
            if(DecimalPointer2 >=0){
               DecimalPointer2  = VersionToCheck.find(".",DecimalPointer2+1);}
            if(DecimalPointer2 >=0){
               Extraction2      = VersionToCheck.substr(DecimalPointer2+1,3);}

            if(Extraction1 == Extraction2) Result = true;
            return Result;
        }//end function Verify File Version

        ///Force all char data to lower case
        string MakeStringLowerCase(string strData){
            for(int x =0; x<= int(strData.size()); x++)
                strData[x] = tolower(strData[x]);
            return strData;
        }


        ///DEPRECIATED
        int Tokenize (string str_Data,bool ForceUpperCase = true)
        {
            int z          = str_Data.size();
            int y;
            int PlaceValue = 1;
            int tmpToken   = 0;
            int tmpHolder  = 0;

                if(ForceUpperCase){
                for( y = z; y > 0; y--){
                    tmpHolder  = int(toupper(str_Data[y-1]))-64; //'A' to 'Z'
                    if(tmpHolder <= 0) tmpHolder = str_Data[y-1];
                    tmpToken   = tmpToken + (tmpHolder*PlaceValue);
                    PlaceValue = PlaceValue * 10;}}
                  else {
                    for( y = z; y > 0; y--){
                    tmpHolder  = str_Data[y-1] - 64;
                    if(tmpHolder <= 0) tmpHolder = str_Data[y-1];
                    tmpToken   = tmpToken + (tmpHolder*PlaceValue);
                    PlaceValue = PlaceValue * 10;}
                  }

            return tmpToken;

        }



        /// Returns number of days since beginning of 2019 for a day stamp
        int GetDaysSinceDate(){

            struct  tm StartDate;
            time_t  startTime,Finish;
            time (&Finish);
            time (&startTime);
            StartDate           = *localtime(&startTime);
            StartDate.tm_year   = 2019;
            StartDate.tm_mon    = 0;
            StartDate.tm_mday   = 1;
            StartDate.tm_hour   = 0;
            StartDate.tm_min    = 0;
            StartDate.tm_sec    = 0;
            return StartDate.tm_yday;

        }
