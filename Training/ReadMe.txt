Clear files from EventFiles and delete out.csv

"FindNum.py" finds the number of files in EventFiles
"CleanData.py" cleans all files in EventFiles from redundant apps.
"main.cpp" takes in all the number of files from "NoOfFiles.txt" from "event files" files and gives out the app//starttime//endtime table in "out.txt"
MATLAB will take in "out.txt" and create clusters.
"getcluster.m" is a matlab function.
"RunMatlab.py" runs matlab from python

===SEQUENCE==

main.cpp   (Runs FindNum.py and CleanData.py)
MATLAB