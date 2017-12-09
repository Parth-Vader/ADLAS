#include <bits/stdc++.h>
#include <windows.h>
#include <map>
using namespace std;                      // No of files -1
int NUM =60;
int SCALE_TIME= 2;
int SLEEP = SCALE_TIME -1;

set <string> file[5000];      // file[i] is a set that consists all app names in file i
set <string>::iterator it;
map <string, pair < vector <int>,vector< int> > >::const_iterator it2;

int main()
{
    string command2="del /q EventFiles\\*";
    system(command2.c_str());
    command2="del /q out.csv";
    system(command2.c_str());

    // Generate NUM number of files and saves them in new folder.

    for(int i=0;i<NUM;i++)
    {
    	Sleep(SLEEP*1000);
        cout<<i<<endl;
        stringstream sss;
        sss << i;
        string str = sss.str();
        string command = "powershell -command \"& {&'Get-Process' | select processname,StartTime,WS | export-csv -Append -NoTypeInformation EventFiles\\";
        command+=str;
        command+=".csv\"};";
        system(command.c_str());
    }

    //PYTHON FILES

    string command = "python FindNum.py";
    system(command.c_str());

    command = "python CleanData.py";
    system(command.c_str());

    // Python FILES


    ifstream nofile;
    nofile.open("NoOfFiles.txt");
    int num=0;
    nofile>>num;
    ifstream infile;
    ofstream outfile;
    outfile.open("out.csv");
    string s;
    map <string, pair < vector <int>,vector< int> > > apps;        // apps is a map (binary tree) that maps name to start/end time
    int fileno=0;
    for(int fileno=0;fileno<num;fileno++)
    {
        string name="EventFiles/";
        ostringstream temp;
        temp<<fileno;
        name+=temp.str();
        name+=".csv";
        infile.open(name.c_str());
        while(getline(infile,s))
        {
            //cout<<s<<endl;
            string k="";
            int j=0;
            while(s[j]!=','&&j<s.length())
                k+=s[j++];
            //cout<<"k: "<<k<<endl;
            //file[fileno].insert(k.substr(1,k.length()-2));
            file[fileno].insert(k);

        }
        infile.close();
    }
/* See apps in file
    for(int i=0;i<6;i++)
    {
        cout<<"File "<<i<<" : ";
        for(it = file[i].begin();it!=file[i].end();it++)
            cout<<*it<<" ";
        cout<<endl;
    }
*/

    for(it =file[0].begin();it!=file[0].end();it++)
            apps[*it].first.push_back(0);

    for(fileno=0;fileno<num-1;fileno++)
    {
       set <string> unionset,endset,begset;      // begset-> files that have just begun; endset-> files that have just ended
       set <string>:: iterator its;

       for(it =file[fileno].begin();it!=file[fileno].end();it++)
            endset.insert(*it);                           // initialize endset with all elements of ith file and then delete elements of i+1the file from this set.

        for(it =file[fileno+1].begin();it!=file[fileno+1].end();it++)
            begset.insert(*it);								// initialize begset with all elements of i+1th file and then delete elements of ithe file from this set.

        for(it =file[fileno+1].begin();it!=file[fileno+1].end();it++)
            if(endset.find(*it)!=endset.end())
                endset.erase(endset.find(*it));
        for(it =file[fileno].begin();it!=file[fileno].end();it++)
            if(begset.find(*it)!=begset.end())
                begset.erase(begset.find(*it));

/*           TO CREATE BEGFILES

        ofstream begfile;
        ostringstream temp;
        string name="";
        temp<<fileno;
        name="BegFiles/beg";
        name+=temp.str();
        name+=".txt";
        begfile.open(name.c_str());
        for(its = endset.begin();its!=endset.end();its++)
        {
            string tmp;
            tmp = *its;
            if(tmp.length()>1)
                tmp=tmp.substr(1,tmp.length()-2);
            begfile<<tmp<<endl;
        }

        begfile.close();


*/

        for(it =endset.begin();it!=endset.end();it++)
                apps[*it].second.push_back(fileno+1);
        for(it =begset.begin();it!=begset.end();it++)
            apps[*it].first.push_back(fileno+1);
    }

    for(it =file[num-1].begin();it!=file[num-1].end();it++)
            apps[*it].second.push_back(num);
/*
    for(it2=apps.begin();it2!=apps.end();it2++)
    {
        cout<<it2->first<<endl;
        cout<<"Start array: \t";
        for(int i=0;i<it2->second.first.size();i++)
            cout<<it2->second.first[i]<<"\t";
        cout<<endl;
        cout<<"End array: \t";
        for(int i=0;i<it2->second.second.size();i++)
            cout<<it2->second.second[i]<<"\t";

        cout<<endl;
    }
*/
    vector < string> name;
    vector < int> stime;
    vector <int > etime;

//    cout<<"\n\n\n";
    for(it2=apps.begin();it2!=apps.end();it2++)
    {
        int sizearr = it2->second.first.size();
        for(int i=0;i<sizearr;i++)
            {
                name.push_back(it2->first);
                stime.push_back(it2->second.first[i]);
                etime.push_back(it2->second.second[i]);
            }
    }

    outfile<<"App Name,Start Time,End Time\n";
    for(int i=0;i<name.size();i++)
        {
            if(stime[i]==0&&etime[i]==NUM)
                continue;

            cout<<name[i]<<"\t"<<stime[i]<<"\t"<<etime[i]<<endl;
            outfile<<name[i]<<","<<stime[i]*SCALE_TIME<<","<<etime[i]*SCALE_TIME<<endl;
        }
}
