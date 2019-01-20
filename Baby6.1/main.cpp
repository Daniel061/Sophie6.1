#include <iostream>
#include <c_Brain.h>
#include <time.h>

using namespace std;

c_Brain Brain;
bool Verbose;
int  BaseSpeed = 15000000;
int  SpeedStandard = 50;
int  ThisSpeed;
float CalcSpeed;
int main()
{
int StartCount = clock();
 for(int t = 0; t<=BaseSpeed;t++);
int EndCount = clock();
CalcSpeed = float((EndCount - StartCount)/SpeedStandard);
ThisSpeed = BaseSpeed * CalcSpeed;
if(ThisSpeed == 0) ThisSpeed = BaseSpeed;


cout << EndCount - StartCount << " This delay count " << ThisSpeed << endl;
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
