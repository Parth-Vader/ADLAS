import pandas as pd
import glob,os

process = [ "chrome",
			"sublime_text",
			"AcroRd32",
			"DCPlusPlus",
			"cmd",
			"devcpp",
			"OneDrive",
			"powershell",
			"explorer",
			"firefox",
			"vlc",
			"notepad",
			"WINWORD",
			"MicrosoftEdge",
			"StikyNot",
			"MusicBee",
			"EXCEL",
			"IDMan",
			"mspaint",
			"POWERPNT",
			"SkyDrive",
			"WinRAR",
			"TeamViewer_Service",
			"wordpad",
			"wmplayer",
			"vmware",
			"steam",
			"Photoshop"]
pro = pd.DataFrame(process)

pro.columns = ['ProcessName'] #This should be same as the column name which lists the process name

for file in glob.glob("EventFiles\*.csv"):
	Output = pd.read_csv(file, sep = ',')

	common = Output.merge(pro, on=['ProcessName'])
	#path_d = 'Eventfiles/'
	common.to_csv(file, index = False)
