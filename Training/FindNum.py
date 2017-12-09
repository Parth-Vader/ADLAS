import glob
i=0
for file in glob.glob("EventFiles\*.csv"):
	i+=1
f = open('NoOfFiles.txt', 'w')
f.write(str(i))