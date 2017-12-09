#include <bits/stdc++.h>
using namespace std;                      // No of files -1
#define NUM 300

int main()
{

    // Generate NUM number of files and saves them in new folder.

    for(int i=0;i<NUM;i++)
    {

       cout<<i<<endl;
        stringstream sss;
        sss << i;
        string str = sss.str();
        string command = "powershell -command \"& {&'Get-Process' | select processname,StartTime,WS | export-csv -Append -NoTypeInformation EventFiles\\";
        command+=str;
        command+=".csv\"};";
        system(command.c_str());
    }
}
