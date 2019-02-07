#include <iostream>
#include <fstream>
#include <c_Brain.h>
#include <time.h>


using namespace std;

c_Brain Brain;
string Version = "6.1.007.17";
bool Verbose;
int  BaseSpeed = 600000000;
int  SpeedStandard = 1000;
int  RunningStandard = 9000000;  //adjust up or down to change delay for all machines. up=more delay
int  ThisSpeed;
float CalcSpeed;
clock_t Elapsed;
int main()
{

//****Calculate machine speed for a constant delay used in SlowSpeak()
        Elapsed = clock();
         for(int t = 0; t<=BaseSpeed;t++);
        Elapsed = clock() - Elapsed;
        //cout << " Elapsed:" << Elapsed << endl;
        CalcSpeed = float(SpeedStandard)/float(Elapsed);
        ThisSpeed = CalcSpeed * RunningStandard;
        if(ThisSpeed == 0) ThisSpeed = RunningStandard;
//***********END CALCULATE SPEED***************************************


//***SET SOME GLOBAL VARIABLES*****************************************
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
while (Raw_Sentence != "end")
{
    if(Verbose)cout << "[main.cpp]\n";
    if(Raw_Sentence != ""){
       Brain.ProcessUserInput(Raw_Sentence);}

    if(Raw_Sentence != "end"){
        cout << ">>";
        Raw_Sentence = "";
        getline(cin,Raw_Sentence);}
}
    Brain.LTMSaveSentencesInFile();
    Brain.LobesStoreTheLearnedWords();
    return 0;
}
