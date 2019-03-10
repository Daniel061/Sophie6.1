#include <iostream>
#include <fstream>
#include <c_Brain.h>
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
c_Brain Brain;
string Version       = "6.1d.02d.EN.010.001";
string ReleaseMode   = "debug";
bool Verbose         = false;
bool StoryMode       = false;
bool EchoTraining    = true;
int  BlockID         = -1;

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
        Brain.SetMyGender('f');
        Brain.SetMyName("Sophie");
        Brain.SlowSpeak("Remembering...",false,0,false);
        Brain.LTMReadSentencesInFile();
        Brain.LobesReadTheLearnedWords();
        Brain.FirstRunWelcomeMessage();
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
   Verbose           = false;
   Elapsed           = clock();
   string CommentTag = "";
  if (myfile.is_open())
  {
    while ( getline (myfile,Raw_Sentence) )
    {
      CommentTag =  Raw_Sentence[0];
      CommentTag += Raw_Sentence[1];
      if(!( CommentTag == "//") ){  //training file comment
          if(EchoTraining){
            cout << Raw_Sentence << endl;}
            Brain.ControlProcessingUserInput( Raw_Sentence );}
      CommentTag = "";
    }
    Elapsed = clock() - Elapsed;
    myfile.close();
    if(EchoTraining)
        cout << "Training file processed in " << Elapsed << " milliseconds.\n";
  }

  else cout << "No training file found.\n";
StoryMode = false;
Verbose   = false;
//*******************END TRAINING FILE READ****************************


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
                   Brain.ControlProcessingUserInput(Raw_Sentence);} /// First entry point to Brain

                if(Raw_Sentence != "end"){
                    cout << ">>";
                    Raw_Sentence = "";
                    getline(cin,Raw_Sentence);}
            }
  /// Save all data learned in files
    Brain.LTMSaveSentencesInFile();
    Brain.LobesStoreTheLearnedWords();
    return 0;
}
