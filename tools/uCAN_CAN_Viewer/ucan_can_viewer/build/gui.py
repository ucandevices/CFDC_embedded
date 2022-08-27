
# This file was generated by the Tkinter Designer by Parth Jadhav
# https://github.com/ParthJadhav/Tkinter-Designer


from pathlib import Path
from datetime import datetime
from re import X
import can
import time
from can.interfaces import cfuc
from tkinter import Tk, Canvas, Entry, Text, Button, PhotoImage, messagebox, Text, Checkbutton
from tkinter import ttk
import tkinter as tk
import threading
import numpy as np
import queue
from serial import SerialException


can_connceted = False
counter = 0
bus = 0
conf_file_name = "can.conf"

OUTPUT_PATH = Path(__file__).parent
ASSETS_PATH = OUTPUT_PATH / Path("./assets")

def CANrx_thread():
    if (can_connceted):
        print('rx CAN Thread start')
        # msgs_recv = bus.recv()
        # for msg in msgs_recv:
        #     if msg != False:
        #         # if msg.is_fd == True:
        #         print(msg)
        #         tree.insert('', 0 , text="1", values=(datetime.now().strftime("%H:%M:%S.%m"), str(msg_to_send.arbitration_id), msg_to_send.data.hex() ))
        

        for x in range(10):
            rand_dlc = 8
            rand_data = np.random.randint(0, 256, rand_dlc)
            rand_id = np.random.randint(0, 0x800)
            msg_to_send = can.Message(
            arbitration_id=rand_id, dlc=rand_dlc, data=rand_data[0:rand_dlc], is_fd=True)
            tree.insert('', 0 , text="1", values=(datetime.now().strftime("%H:%M:%S.%m"), str(msg_to_send.arbitration_id), msg_to_send.data.hex() ))
            time.sleep(0.001)  # one second

def relative_to_assets(path: str) -> Path:
    return ASSETS_PATH / Path(path)

def connect_callback():
    print("connect click")
    global can_connceted
    if (can_connceted == False):   
        conf_file_name = entry_1.get()
        print(conf_file_name)
        can_conf = can.util.load_file_config(path=relative_to_assets(conf_file_name))  
        print (can.util.load_file_config(path=relative_to_assets(conf_file_name)) )  
        if len(can_conf) == 0 :
                messagebox.showerror(title="Device not found", message="Configuration file not found")
                return
        try:
            bus = can.Bus(
                bustype=can_conf['interface'],
                channel=can_conf['channel'],
                CANBaudRate=int(can_conf['CANBaudRate']),
                IsFD=can_conf['IsFD'] == 'True',
                FDDataBaudRate=int(can_conf['FDDataBaudRate']),
            )
        except (AttributeError, SerialException) as error:
            messagebox.showerror(title="Device not found", message=repr(error)+": Device not found check " + conf_file_name + " file. Current config: " 
                + can_conf['interface'] + ", "
                + can_conf['channel'] + ", "
                + can_conf['CANBaudRate'] + ", "
                + can_conf['IsFD'] + ", "
                + can_conf['FDDataBaudRate'] + ", ",)
            return
        can_connceted = True
        button_connect.configure(image=button_connect_img_diss)
        thd = threading.Thread(target=CANrx_thread)   # timer thread
        thd.start()
    else:
        button_connect.configure(image=button_connect_img)
        can_connceted = False

# -------------------------------------------- GUI -----------------------------------------------

window = Tk()

window.geometry("635x375")
window.configure(bg = "#FFFFFF")


canvas = Canvas(
    window,
    bg = "#FFFFFF",
    height = 375,
    width = 635,
    bd = 0,
    highlightthickness = 0,
    relief = "ridge"
)

canvas.place(x = 0, y = 0)

button_connect_img = PhotoImage(
    file=relative_to_assets("button_connect.png"))
button_connect_img_diss = PhotoImage(
    file=relative_to_assets("button_connect_diss.png"))
button_connect = Button(
    image=button_connect_img,
    borderwidth=0,
    highlightthickness=0,
    command=connect_callback,
    relief="flat"
)
button_connect.place(
    x=7.0,
    y=10.0,
    width=87.0,
    height=24.0
)

canvas.create_rectangle(
    84.0,
    45.0,
    85.0,
    330.0,
    fill="#FFFFFF",
    outline="")


canvas.create_text(
    108.0,
    3.0,
    anchor="nw",
    text="config file",
    fill="#000000",
    font=("Inter", 12 * -1)
)

button_image_2 = PhotoImage(
    file=relative_to_assets("button_2.png"))
button_2 = Button(
    image=button_image_2,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: print("button_2 clicked"),
    relief="flat"
)
button_2.place(
    x=180.0,
    y=10.0,
    width=68.0,
    height=19.0
)
#------------------- can opts ----------
uCAN_EXID = tk.IntVar()
uCAN_BRS = tk.IntVar()
uCAN_ERR = tk.IntVar()

#  (var1.get())  
    
c1 = Checkbutton(window, text='ExID',variable=uCAN_EXID, onvalue=1, offvalue=0)
c1.place(x = 440, y=300)

c1 = Checkbutton(window, text='BRS',variable=uCAN_BRS, onvalue=1, offvalue=0)
c1.place(x = 440, y=320)

c1 = Checkbutton(window, text='ERR',variable=uCAN_ERR, onvalue=1, offvalue=0)
c1.place(x = 440, y=340)


#------------------ can send button ----------------------
can_send_button_img = PhotoImage(
    file=relative_to_assets("button_send.png"))
can_send_button = Button(
    image=can_send_button_img,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: print("can_send_button clicked"),
    relief="flat"
)
can_send_button.place(
    x=495.0,
    y=300.0,
    width=68.0,
    height=60.0
)

canvas.create_text(
    15.0,
    280,
    anchor="nw",
    text="CAN ID",
    fill="#000000",
    font=("Inter", 12 * -1)
)

can_id_img = PhotoImage(
    file=relative_to_assets("can_id.png"))
can_id = Entry(
    bd=0,
    bg="#D9D9D9",
    highlightthickness=0,
)
can_id.place(
    x=15.0,
    y=300.0,
    width=67.0,
    height=17.0
)
can_id.insert(0, "0x00")

#can frame send text widget
canvas.create_text(
    85.0,
    280,
    anchor="nw",
    text="CAN DATA",
    fill="#000000",
    font=("Inter", 12 * -1)
)

can_frame_text = Text(window,bd=0,bg="#D9D9D9")
can_frame_text.place(
    x=85.0,
    y=300.0,
    width=340,
    height=60
)



# ------------------------ conf entry + tree 

entry_image_1 = PhotoImage(
    file=relative_to_assets("entry_1.png"))
entry_bg_1 = canvas.create_image(
    141.5,
    27.5,
    image=entry_image_1
)
entry_1 = Entry(
    bd=0,
    bg="#D9D9D9",
    highlightthickness=0,
)
entry_1.place(
    x=108.0,
    y=18.0,
    width=67.0,
    height=17.0
)
entry_1.insert(0, conf_file_name)

# Add a Treeview widget
style = ttk.Style(window)
style.theme_use("clam")
style.configure('Treeview.Heading', background='#3086AB', foreground='#D9D9D9')
# style.configure('Treeview', background='#D9D9D9', foreground='black')

tree = ttk.Treeview(window, column=("c1", "c2", "c3"), show='headings', height=10,)

tree.column("# 1",  anchor="nw",)
tree.heading("# 1", text="Timestamp")
tree.column("# 2",  anchor="nw",)
tree.heading("# 2", text="ID")
tree.column("# 3",  anchor="nw",)
tree.heading("# 3", text="Data")

# Insert the data in Treeview widget


tree.place(x=10.0,y=50)
# tree.pack()

window.resizable(False, False)
window.mainloop()
