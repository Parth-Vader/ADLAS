#include <bits/stdc++.h>
#include <map>
#include <sstream>
//#include <unistd.h>
using namespace std;
#define TIME 20
                    // No of files -1

set <string> prev,now;      // file[i] is a set that consists all app names in file i
set <string>::iterator it;
map <string, pair < vector <int>,vector< int> > >::const_iterator it2;

int main()
{

    // Modify "clusters.txt"

    ifstream FileOpen;
    FileOpen.open("clusters.txt");
    string lineOne;
    FileOpen>>lineOne;
    if(lineOne.length()>=3)
    {
        ifstream infile;
        infile.open("clusters.txt");
        int lines=0;
        vector <string> strings[100];
        string s;
        while(getline(infile,s))
        {

            stringstream stream(s);
            int cnt=0;
            while(stream)
            {
                string tmp;
                stream>>tmp;
                strings[lines].push_back(tmp);
            }
            lines++;
        }
        infile.close();
        remove("clusters.txt");

        ofstream outfile;
        outfile.open("clusters.txt");
        outfile<<lines<<endl;
        for(int i=0;i<lines;i++)
        {
            outfile<<strings[i].size()-1<<" ";
            for(int j=0;j<strings[i].size()-1;j++)
                outfile<<strings[i][j]<<" ";
            outfile<<endl;
        }
        outfile.close();
    }
    FileOpen.close();

        // SORT:
        ifstream clin2;
        clin2.open("clusters.txt");
        vector <string > clustersV;
        string c_str,c_top;
        clin2>>c_top;
        while(getline(clin2,c_str ))
        {
            clustersV.push_back(c_str);
        }
        sort(clustersV.begin(),clustersV.end());
        clin2.close();
        remove("clusters.txt");

        ofstream outClusters;
        outClusters.open("clusters.txt");
        outClusters<<c_top;
        for(int i=0;i<clustersV.size();i++)
        {
            outClusters<<clustersV[i]<<endl;
        }
        outClusters.close();


    int time=TIME;
    while(time--)
    {
        // copying the "now.csv" file to "prev.csv" file
        prev.clear();
        now.clear();
        ifstream nowfilein;
        nowfilein.open("now.csv");
        ofstream prevfileout;
        prevfileout.open("prev.csv");

        string s;

        while(getline(nowfilein,s))
        {
            prevfileout<<s<<endl;
        }
        nowfilein.close();
        prevfileout.close();

        // Powershell script to get the current now file

        remove("now.csv");
        string command = "powershell -command \"& {&'Get-Process' | select processname,StartTime,WS | export-csv -Append -NoTypeInformation now.csv\"};";
        system(command.c_str());

        //******************************* Clean prev.cpp and now.cpp for redundant apps ***********************

        string filename0 = "CleanData.py";
        string command0 = "python ";
        command0 += filename0;
        system(command0.c_str());


        // ******************************* clean ends ************************************

        //************************************************** BegSetCreate.cpp (start) ************


        ifstream infile;
        ofstream outfile;
        outfile.open("BegSetNow.txt");
        map <string, pair < vector <int>,vector< int> > > apps;        // apps is a map (binary tree) that maps name to start/end time

        infile.open("prev.csv");
        while(getline(infile,s))
        {
            //cout<<s<<endl;
            string k="";
            int j=0;
            while(s[j]!=','&&j<s.length())
                k+=s[j++];
            prev.insert(k);
        }
        infile.close();

        infile.open("now.csv");
        while(getline(infile,s))
        {
            //cout<<s<<endl;
            string k="";
            int j=0;
            while(s[j]!=','&&j<s.length())
                k+=s[j++];
            now.insert(k);
        }
        infile.close();


       set <string> begset;      // begset-> files that have just begun; endset-> files that have just ended
       set <string>:: iterator it;

        for(it =now.begin();it!=now.end();it++)
            begset.insert(*it);								// initialize begset with all elements of i+1th file and then delete elements of ithe file from this set.

        for(it =prev.begin();it!=prev.end();it++)
            if(begset.find(*it)!=begset.end())
                begset.erase(begset.find(*it));


        for(it = begset.begin();it!=begset.end();it++)
        {
            cout<<"\nBEGSET : ";
            string tmp;
            tmp = *it;
            /*                              To remove quotes ("") from app_name
            if(tmp.length()>1)
            tmp=tmp.substr(1,tmp.length()-2);
            */
            outfile<<tmp<<endl;
            cout<<tmp;
        }
        cout<<endl;

        outfile.close();

        //************************************** BegSetCreate.cpp (end)**************
        //************************************** Check.cpp(start)********************

        ifstream begfile;
        begfile.open("BegSetNow.txt");

        outfile.open("filestorun.txt");

        set <string> cluster[100];
        set <string> filestorun;



        ifstream clin;
        clin.open("clusters.txt");
        // getting "clusters.txt" in list of clusters[]
        int t;
        clin>>t;
        for(int i=0;i<t;i++)
        {
            int n;
            clin>>n;
            while(n--)
            {
                string tmp;
                clin>>tmp;
                cluster[i].insert(tmp);
            }
        }
        //

        while(getline(begfile,s))
        {
            cout<<"For app "<<s<<":";
            for(int i=0;i<t;i++)
            {
                if(cluster[i].find(s)!=cluster[i].end())
                {
                    cout<<"Cluster found, RUN : ";
                    for(set<string>::iterator it=cluster[i].begin();it!=cluster[i].end();it++)
                        if(*it!=s)
                            {
                                cout<<*it<<" ";
                                filestorun.insert(*it);
                                //outfile<<*it<<endl;
                            }
                    cout<<endl;
                    break;
                }

            }
            cout<<endl;
        }
        begfile.close();
        begfile.open("BegSetNow.txt");
        while(getline(begfile,s))
        {
            if(filestorun.find(s)!=filestorun.end())
                {
                    filestorun.erase(filestorun.find(s));
                    cout<<"erased "<<s<<endl;
                }
        }

        for(it =now.begin();it!=now.end();it++)
        {
            cout<<"Now element: "<<*it;
            if(filestorun.find(*it)!=filestorun.end())
                {
                    filestorun.erase(filestorun.find(*it));
                    cout<<"erased2 "<<*it<<endl;
                }
        }

        cout<<"Finally, the files that will be run are :  ";
        for(set<string>::iterator it=filestorun.begin();it!=filestorun.end();it++)
            {
                cout<<*it<<" ";
                outfile<<*it<<endl;
            }
        cout<<endl;
        begfile.close();
        clin.close();
        outfile.close();

        //****************************************** check.cpp(end) *****************
        //****************************************** RunApps.cpp(start) *************

        infile.open("filestorun.txt");

        while(getline(infile,s))
        {
              outfile.open("word.txt");
             outfile<<s;
             outfile.close();
             string filename = "RunAnApp.py";
            command = "python ";
         command += filename;
         system(command.c_str());
        }

        //usleep(5000000);

    }

    // ************************* RunApps.cpp (end)******************
    return 0;
}
