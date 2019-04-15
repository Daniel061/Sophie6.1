#include <iostream>
#include <fstream>
#include <c_Brain.h>
#include <time.h>
#include <list>


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




//LOCALS
using namespace std;
c_Brain Brain;
list <string> TrainingFileSet;
list <string>::iterator TrainingIT;
float OldLevel   = 1.0;
float NewLevel   = 2.1;
int   Iterations = 0;
int   vc,nc,adc,ac,pc,pn,ukn,kn;

// GLOBALS
string Version       = "6.1d.08x.EN.012.007";
string ReleaseMode   = "debug";

bool Verbose         = false;
bool StoryMode       = false;
bool EchoTraining    = false;
bool TrainingMode    = false;
bool DoIterating     = false;
int  BlockID         = -1;
// End GLOBALS

int  BaseSpeed       = 600000000;
int  SpeedStandard   = 1000;
int  RunningStandard = 9000000;  //adjust up or down to change delay for all machines. up=more delay
int  ThisSpeed;
float CalcSpeed;
clock_t Elapsed;
int main()
{

///****Calculate machine speed for a constant delay used in SlowSpeak()
        Elapsed = clock();
         for(int t = 0; t<=BaseSpeed;t++);
        Elapsed = clock() - Elapsed;
        //cout << " Elapsed:" << Elapsed << endl;
        CalcSpeed = float(SpeedStandard)/float(Elapsed);
        ThisSpeed = CalcSpeed * RunningStandard;
        if(ThisSpeed == 0) ThisSpeed = RunningStandard;
//***********END CALCULATE SPEED***************************************


///***SET SOME GLOBAL VARIABLES*****************************************
        Brain.SetMyGender(typeFemaleClass);
        Brain.SetMyName("Sophie");
        Brain.SlowSpeak("Remembering...",false,0,false);
        Brain.LTMReadSentencesInFile();
        Brain.LobesReadTheLearnedWords();
        string Raw_Sentence;
        Verbose = false;
//***********END SETTING GLOBALS****************************************

//****************FOR INPUT TEXT TESTING********************************
//*****uncomment the following******************************************
ifstream myfile ("trainingdata.dat");
//testtext.txt file format is single lines terminated by CR
// -enable StoryMode for no response processing
// -disable StoryMode when finished
   StoryMode         = true;
   TrainingMode      = true;
   Verbose           = false;
   DoIterating       = true;
   Elapsed           = clock();
   string CommentTag = "";
//FIXME: Float Comparison does not work in release mode

  if (myfile.is_open())
  {
    while ( getline (myfile,Raw_Sentence) )
    {
      CommentTag =  Raw_Sentence[0];
      CommentTag += Raw_Sentence[1];
      if(!( CommentTag == "//") ){  //training file comment
        TrainingIT = TrainingFileSet.end();
        TrainingFileSet.insert(TrainingIT,Raw_Sentence);}
    }
    myfile.close();
    if(DoIterating){
        while (NewLevel != OldLevel){
            cout << OldLevel << " " << NewLevel << endl;
            Brain.GetRightLobeCellMapSummary(vc,nc,adc,ac,pc,pn,ukn,kn,OldLevel);
            for(TrainingIT = TrainingFileSet.begin(); TrainingIT != TrainingFileSet.end(); TrainingIT++){
                Raw_Sentence = *TrainingIT;
                Brain.ControlProcessingUserInput(Raw_Sentence,false);
            }
        Brain.GetRightLobeCellMapSummary(vc,nc,adc,ac,pc,pn,ukn,kn,NewLevel);
        Iterations++;}
    }
    else
    {
            cout << OldLevel << " " << NewLevel << endl;
            Brain.GetRightLobeCellMapSummary(vc,nc,adc,ac,pc,pn,ukn,kn,OldLevel);
            for(TrainingIT = TrainingFileSet.begin(); TrainingIT != TrainingFileSet.end(); TrainingIT++){
                Raw_Sentence = *TrainingIT;
                Brain.ControlProcessingUserInput(Raw_Sentence,false);
            }
        Brain.GetRightLobeCellMapSummary(vc,nc,adc,ac,pc,pn,ukn,kn,NewLevel);
        Iterations++;
    }

    Elapsed = clock() - Elapsed;
    if(EchoTraining){
        for(TrainingIT = TrainingFileSet.begin(); TrainingIT != TrainingFileSet.end(); TrainingIT++){
            Raw_Sentence = *TrainingIT;
            CommentTag =  Raw_Sentence[0];
            CommentTag += Raw_Sentence[1];
            if(!( CommentTag == "//") ){
                    cout << *TrainingIT << endl;}
        }
    }
    cout << "Training file processed in " << Elapsed << " milliseconds with " << Iterations << " iterations for " << TrainingFileSet.size() << " lines.\n";
    TrainingFileSet.clear(); // free up memory
    cout << OldLevel << " " << NewLevel << endl;
    Raw_Sentence = "map summary";
    Brain.ControlProcessingUserInput(Raw_Sentence, true);
  }

  else cout << "No training file found.\n";
StoryMode = false;
Verbose   = false;
//*******************END TRAINING FILE READ****************************

if(!TrainingMode)
    Brain.FirstRunWelcomeMessage();
else
    TrainingMode = false;

cout << ">>";
getline (cin,Raw_Sentence);

///  Begin user input loop
///   Terminates when string raw_Sentence = "end"
///   input string raw_string can be modified by
///     internal processes to end the program.
            while (Raw_Sentence != "end")
            {
                if(Verbose)cout << "[main.cpp]\n";
                if(Raw_Sentence != ""){
                   Brain.ControlProcessingUserInput(Raw_Sentence,true);} /// First entry point to Brain

                if(Raw_Sentence != "end"){
                    cout << ">>";
                    Raw_Sentence = "";
                    getline(cin,Raw_Sentence);}
            }
  /// Save all data learned in files
    Brain.LTMSaveSentencesInFile();
    Brain.LobesStoreTheLearnedWords();
    Brain.FilePTLmmData();
    return 0;
}
