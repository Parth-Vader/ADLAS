# ADLAS

## Following is the workflow for the program :

* `BegSetCreate.cpp` gets input from `prev.csv` and `now.csv`.
* It finds the apps that were opened just now. It saves these apps in `BegSetNow.txt`
* Then `check.cpp` gets the file-list and checks them against `clusters.txt` to get the applications that are to be opened. It saves these apps in `filestorun.csv`.
* `RunApps.cpp` takes `filestorun.csv`, converts it word by word (app by app) to `word.txt` and using `RunApp.py` runs the apps.
