#include <iostream>
#include <c_Brain.h>
#include <time.h>

using namespace std;

c_Brain Brain;
bool Verbose;

int main()
{
int StartCount = clock();
 for(int t = 0; t<=30000000;t++);
int EndCount = clock();
cout << EndCount - StartCount << endl;
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
