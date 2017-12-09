# -*- coding: utf-8 -*-
"""
Created on Thu Apr 06 22:00:06 2017

@author: Rahul Das
"""

import os
import pandas as pd 



file = open("word.txt",'r')
app = file.read()


if app == "devcpp":
	os.startfile("C:\Dev-Cpp\\devcpp.exe")
elif app == "DCPlusPlus":
	os.startfile("C:\Program Files\DC++\\DCPlusPlus.exe")
elif app == "vlc":
	os.startfile("C:\Program Files (x86)\VideoLAN\VLC\\vlc.exe")
elif app == "sublime_text":
	os.startfile("C:\Program Files\Sublime Text 3\\sublime_text.exe")
elif app == "codeblocks":
	os.startfile("C:\Program Files (x86)\CodeBlocks\\codeblocks.exe")
else : 
    if len(app)>2 :
    	os.system('start ' + app)
    	
#os.startfile("C:\Users\Rahul Das\Desktop\Acrobat Reader DC\Reader\\AcroRd32.exe")
