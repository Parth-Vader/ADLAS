#test.py
try:
    import tkinter as tk  # for python 3
except:
    import Tkinter as tk  # for python 2
import pygubu
import os
from subprocess import call


def on_click():
	os.system('g++ main.cpp')
	os.system('a.exe')
	#print(out)
	#print("click")
	#tk.messagebox.showinfo('Message', 'You clicked Button 1')


def stop():
	os.system('\x03')	
class Application:
    def __init__(self, master):

        #1: Create a builder
        self.builder = builder = pygubu.Builder()

        #2: Load an ui file
        builder.add_from_file('gui.ui')

        #3: Create the widget using a master as parent
        
        #photo = tk.PhotoImage(file = 'giphy.gif',format="gif -index 4")
        #canvas = builder.get_object('Canvas_1')
        #canvas.create_image(50,10,image =photo)
        #img_path = os.path.join(os.path.abspath(os.path.dirname(__file__)), '..', 'giphy.gif')
        #img_path = os.path.abspath(img_path)
        #print (img_path)


        path = os.getcwd()
        print (path)
        builder.add_resource_path(path)
        self.mainwindow = builder.get_object('Labelframe_1', master)

        # Configure callbacks
        callbacks = {
            'on_click': on_click,
            'stop' : stop,
        }

        builder.connect_callbacks(callbacks)    
if __name__ == '__main__':
    root = tk.Tk()
    root.wm_title("ADLAS")
    app = Application(root)
    root.mainloop()