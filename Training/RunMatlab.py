import win32com.client
import os
h = win32com.client.Dispatch('matlab.application')
cwd = os.getcwd()
h.Execute ("cd '"+cwd+"'")
h.Execute ("cluster=get_cluster('out.csv')")
