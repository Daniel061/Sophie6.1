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
string Version = "6.1.05.EN.009.028";
bool Verbose;
bool StoryMode = false;
int  BaseSpeed = 600000000;
int  SpeedStandard = 1000;
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
//ifstream myfile ("testtext.txt");
//testtext.txt file format is single lines terminated by CR
// -enable StoryMode for no response processing
// -disable StoryMode when finished
//  if (myfile.is_open())
//  {
//    while ( getline (myfile,Raw_Sentence) )
//    {
//      cout << Raw_Sentence << endl;
//      Brain.ProcessUserInput( Raw_Sentence );
//    }
//    myfile.close();
//  }
//
//  else cout << "Unable to open file";

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
                   Brain.ProcessUserInput(Raw_Sentence);} /// First entry point to Brain

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
