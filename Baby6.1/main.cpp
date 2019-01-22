#include <iostream>
#include <c_Brain.h>
#include <time.h>


using namespace std;

c_Brain Brain;
string Version = "6.1.004.14";
bool Verbose;
int  BaseSpeed = 600000000;
int  SpeedStandard = 1000;
int  RunningStandard = 9000000;  //adjust up or down to change delay for all machines. up=more delay
int  ThisSpeed;
float CalcSpeed;
clock_t Elapsed;
int main()
{

Elapsed = clock();
 for(int t = 0; t<=BaseSpeed;t++);
Elapsed = clock() - Elapsed;
//cout << " Elapsed:" << Elapsed << endl;
CalcSpeed = float(SpeedStandard)/float(Elapsed);
ThisSpeed = CalcSpeed * RunningStandard;
if(ThisSpeed == 0) ThisSpeed = RunningStandard;


//cout << Elapsed << " This delay count " << ThisSpeed << " Calc Speed " << CalcSpeed << endl;
Brain.SetMyGender('f');
Brain.SetMyName("Sophie");
Brain.FirstRunWelcomeMessage();
string Raw_Sentence;
Verbose = false;




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
    return 0;
}
