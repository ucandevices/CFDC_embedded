
# This file was generated by the Tkinter Designer by Parth Jadhav
# https://github.com/ParthJadhav/Tkinter-Designer

import usb.core
import usb.backend.libusb1

backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb-1.0.so")

from glob import glob
from pathlib import Path
from datetime import datetime
from re import X
# import can
import time
# from can.interfaces import cfuc
from tkinter import Tk, Canvas, Toplevel, Entry, Text, Button, PhotoImage, messagebox, Checkbutton, Label, OptionMenu
from tkinter import ttk
import tkinter as tk
import threading
import os
# from serial import SerialException

from gs_usb.gs_usb import GsUsb
from gs_usb.gs_usb_frame import GsUsbFrame
from gs_usb.constants import (
    CAN_EFF_FLAG,
    CAN_ERR_FLAG,
    CAN_RTR_FLAG,
    GS_CAN_MODE_LISTEN_ONLY,
    GS_CAN_MODE_LOOP_BACK,
    GS_CAN_MODE_NORMAL,
    GS_CAN_MODE_HW_TIMESTAMP,
)


can_connected = False
counter = 0
conf_file_name = "can.conf"
thd = None
dev = None
selected_dev = 0


OUTPUT_PATH = Path(__file__).parent
ASSETS_PATH = OUTPUT_PATH / Path("./assets")

timestamps_map = {}
def AddCANFrame(msg_to_send, tree, dir):
    can_flags_str = ""
    # if msg_to_send.is_fd:
        # can_flags_str += "FD "
    # if msg_to_send.bitrate_switch:
    #     can_flags_str += "BRS "
    if msg_to_send.is_error_frame:
        can_flags_str += "ERR "
    if msg_to_send.is_remote_frame:
        can_flags_str += "RMT "
    if msg_to_send.is_extended_id:
        can_flags_str += "EX "

    hex_string = ''.join(format(x, ' 02x')
                         for x in msg_to_send.data[0:msg_to_send.can_dlc])

    global delta_view
    global timestamps_map

    message_time = datetime.now()
    # if (dir == "Rx: "):
    #     datetime.fromtimestamp = msg_to_send.timestamp
    #     message_time.microsecond = msg_to_send.timestamp_us
    if (dir == 'Rx: ') & (msg_to_send.echo_id == 0):
        if (uCAN_ECHO.get() == 1):
            dir = 'EE'
        else:
            return False

    if delta_view == False:
        tree.insert('', 0, text="1", values=(dir+message_time.strftime("%H:%M:%S.%m"),
                hex(msg_to_send.can_id), hex(msg_to_send.can_dlc), str(hex_string), can_flags_str))
    else:
        try:
            delta_t = message_time - timestamps_map[msg_to_send.can_id]            
            timestamps_map[msg_to_send.can_id] = message_time
            tree.item(msg_to_send.can_id, text="1", values=(dir+"{:02d}.{:03d}".format(delta_t.seconds,round(delta_t.microseconds/1000)),
                hex(msg_to_send.can_id), hex(msg_to_send.can_dlc), str(hex_string), can_flags_str))
        except:
            timestamps_map[msg_to_send.can_id] = message_time
            tree.insert('', 0, iid=msg_to_send.can_id, text="1", values=(dir+'0.0',
                hex(msg_to_send.can_id), hex(msg_to_send.can_dlc), str(hex_string), can_flags_str))
        
def CANrx_thread():
    global dev
    global can_connected
    print('can rx thread started')
    while 1:
        if (can_connected == True):
            try:
                msgs_recv = GsUsbFrame()
                if dev.read(msgs_recv, 1):
                    print("RX  {}".format(msgs_recv))
                    AddCANFrame(msgs_recv, tree, "Rx: ")
            except Exception:
                print("rx exception")
                can_connected = False
                break
        else:
            break
        time.sleep(0.001)  # one second
    print('can rx thread exit')


def relative_to_assets(path: str) -> Path:
    try:
        base_path = sys._MEIPASS
    except Exception:
        base_path = os.path.abspath("./assets")

    # return os.path.join(base_path, path)
    return ASSETS_PATH / Path(path)

devs = GsUsb.scan()

def connect_callback():

    global dev
    global devs
    global can_connected
    global thd
    global selected_dev
    

    print("connect click dev " + str(selected_dev))



    if (can_connected == False):
        
        dev = devs[selected_dev]
        br = int(can_baud_rate.get().replace("k","")) * 1000
        
        print("Setting baudrate to ", str(br))
        if not dev.set_bitrate(br):
            print("Can not set bitrate for gs_usb")
            return

        # Start device
        dev_opt = 0
        global mode_select
        if mode_select == "Normal":
            dev_opt = GS_CAN_MODE_NORMAL
        elif mode_select == "LoopBack":
            dev_opt = GS_CAN_MODE_LOOP_BACK
        elif mode_select == "ListenOnly":
            dev_opt = GS_CAN_MODE_LISTEN_ONLY

# GS_CAN_MODE_HW_TIMESTAMP
        dev.start(dev_opt)

        print("can interface created")
        can_connected = True
        button_connect.configure(image=button_connect_img_diss)
        thd = threading.Thread(target=CANrx_thread)
        thd.start()

        gui_select_baud["state"] = "disabled"
        gui_select_dev["state"] = "disabled"
        gui_select_mode["state"] = "disabled"
    else:
        gui_select_baud["state"] = "normal"
        gui_select_dev["state"] = "normal"
        gui_select_mode["state"] = "normal"
        
        button_connect.configure(image=button_connect_img)
        can_connected = False
        thd.join()
        dev.stop()

def CANtx(msg):
    global dev
    global can_connected
    if dev.send(msg):
        print("TX  {}".format(msg))
# -------------------------------------------- GUI -----------------------------------------------


window = Tk()
window.title("uCANViewer2 v2.0")


def on_reflash():
    global bus
    global can_connected
    if messagebox.askokcancel("Enter Boot Mode",
                              "This will enter cfuc embedded device into bootloader mode, on how to flash new software visit  https://ucandevices.github.io/cfuc.html"):
        print("reflash")
        # bus.go_to_bootloader()


def on_closing():
    global can_connected
    # global bus
    global thd

    can_connected = False
    if (thd != None):
        thd.join()
    # if type(bus):
    #     bus.shutdown()
    window.destroy()


window.geometry("680x375")
window.configure(bg="#FFFFFF")


canvas = Canvas(
    window,
    bg="#FFFFFF",
    height=375,
    width=635,
    bd=0,
    highlightthickness=0,
    relief="ridge"
)

canvas.place(x=0, y=0)

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
    x=5.0,
    y=10.0,
    width=85.0,
    height=20.0
)

can_baud_rate = tk.StringVar(window)
can_baud_rate.set("100k") # default value

gui_select_dev_str = Label(text="Select dev -->").place(x=5,y=30,width=85.0)

gui_select_baud = OptionMenu(window, can_baud_rate, "10k","20k","50k","100k","125k","250k","500k", "800k", "1000k")
gui_select_baud.place(    
    x=90.0,
    y=10.0,
    width=80.0,
    height=20.0)

dev_select = tk.StringVar(window)
# devs

def on_dev_select(index):
    global selected_dev
    print("selected " + str(index))
    selected_dev = int(index)

if len(devs) == 0:
    dev_select.set("No Device") # default value
    gui_select_dev = OptionMenu(window, dev_select, "No Device",command=on_dev_select)
else:
    options_list =  []
    for d in range(0,len(devs)):
        options_list.append(str(d))
        selected_dev = d 
    dev_select.set(str(d)) # default value
    gui_select_dev = OptionMenu(window, dev_select,*options_list,command=on_dev_select)
   
gui_select_dev.place(    
    x=90.0,
    y=30.0,
    width=80.0,
    height=20.0)


def on_dev_select(index):
    global selected_dev
    print("selected " + str(index))
    selected_dev = int(index)

def on_mode_select(index):
    global mode_select
    print("selected mode" + index)
    mode_select = index

mode_select = tk.StringVar(window)
gui_select_mode = OptionMenu(window, mode_select, "Normal", "LoopBack", "ListenOnly",command=on_mode_select)
mode_select.set("Normal") # default value
gui_select_mode.place(    
    x=180.0,
    y=30.0,
    width=80.0,
    height=20.0)


# switch view
delta_view = False
def switch_view():
    global delta_view 
    delta_view = not delta_view
    print("delta view is:" + str(delta_view))
    tree.delete(*tree.get_children())

switch_view_img = PhotoImage(
    file=relative_to_assets("switch_view.png"))
switch_view_btn = Button(
    image=switch_view_img,
    borderwidth=0,
    highlightthickness=0,
    command=switch_view,
    relief="flat"
)
switch_view_btn.place(
    x=250.0,
    y=10.0,
    width=100.0,
    height=19.0
)

# clear
button_image_2 = PhotoImage(
    file=relative_to_assets("button_clear.png"))
button_2 = Button(
    image=button_image_2,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: tree.delete(*tree.get_children()),
    relief="flat"
)
button_2.place(
    x=180.0,
    y=10.0,
    width=68.0,
    height=19.0
)

# reflash , enter bootlader
# button_reflash_img = PhotoImage(
#     file=relative_to_assets("reflash.png"))
# button_reflash = Button(
#     image=button_reflash_img,
#     borderwidth=0,
#     highlightthickness=0,
#     command=on_reflash,
#     relief="flat"
# )
# button_reflash.place(
#     x=480.0,
#     y=10.0,
#     width=150.0,
#     height=19.0
# )

# ------------------- can opts ----------
uCAN_EXID = tk.IntVar()
uCAN_BRS = tk.IntVar()
uCAN_FD = tk.IntVar()
uCAN_RTR = tk.IntVar()
uCAN_ECHO = tk.IntVar()

# c_exid c_brs c_err (var1.get())

c_exid = Checkbutton(window, text='ExID',
                     variable=uCAN_EXID, onvalue=1, offvalue=0)
c_exid.place(x=440, y=300)

# c_fd = Checkbutton(window, text='FD', variable=uCAN_FD, onvalue=1, offvalue=0)
# c_fd.place(x=440, y=320)

# c_brs = Checkbutton(window, text='BRS', variable=uCAN_BRS,
#                     onvalue=1, offvalue=0)
# c_brs.place(x=440, y=340)

c_rtr = Checkbutton(window, text='RTR', variable=uCAN_RTR,
                    onvalue=1, offvalue=0)
c_rtr.place(x=500, y=300)

c_echo = Checkbutton(window, text='Echo', variable=uCAN_ECHO,
                    onvalue=1, offvalue=0)
c_echo.place(x=600, y=300)


# ------------------ can send button ----------------------
def send_can_frame():
    if (can_connected == True):
        hexadecimal_data_string = can_frame_text.get("1.0", "end")
        hexadecimal_id_string = can_id.get()
        try:
            can_data_byte_array = bytes(bytearray.fromhex(hexadecimal_data_string))
            data = b"\x12\x34\x56\x78\x9A\xBC\xDE\xF0" 
            can_id_value = int(hexadecimal_id_string, 16)
            
            flags = 0
            if uCAN_EXID.get() == 1:
                flags = flags | CAN_EFF_FLAG
            if uCAN_RTR.get() == 1:
                flags = flags | CAN_RTR_FLAG

            msg_to_send = GsUsbFrame(can_id=can_id_value | flags, data=can_data_byte_array)
            
            AddCANFrame(msg_to_send, tree, "Tx: ")
            CANtx(msg_to_send)
            
        except ValueError:
            len_can_lbl.config(text="data or id is in wrong format")
    else:
        len_can_lbl.config(text="first click connect button")

can_send_button_img = PhotoImage(
    file=relative_to_assets("button_send.png"))
can_send_button = Button(
    image=can_send_button_img,
    borderwidth=0,
    highlightthickness=0,
    command=send_can_frame,
    relief="flat"
)
can_send_button.place(
    x=500.0,
    y=320.0,
    width=68.0,
    height=40.0
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

# can frame send text widget
canvas.create_text(
    85.0,
    280,
    anchor="nw",
    text="CAN DATA",
    fill="#000000",
    font=("Inter", 12 * -1)
)

len_can_lbl = Label(text="len:")
len_can_lbl.place(
    x=185.0,
    y=280
)


def update_can_lenght(event):
    hexadecimal_string = can_frame_text.get("1.0", "end")
    try:
        byte_array = bytearray.fromhex(hexadecimal_string)
        len_can_lbl.config(text="len: " + str(len(byte_array)))
    except ValueError:
        len_can_lbl.config(text="data is in wrong format")


can_frame_text = Text(window, bd=0, bg="#D9D9D9")
can_frame_text.place(
    x=85.0,
    y=300.0,
    width=340,
    height=60
)

can_frame_text.bind('<KeyRelease>', update_can_lenght)

# Add a Treeview widget
style = ttk.Style(window)
style.theme_use("clam")
style.configure('Treeview.Heading', background='#3086AB', foreground='#D9D9D9')
# style.configure('Treeview', background='#D9D9D9', foreground='black')

tree = ttk.Treeview(window, column=("c1", "c2", "c3", "c4", "c5"),
                    show='headings', height=10,)

tree.column("# 1",  anchor="nw", width=85)
tree.heading("# 1", text="Timestamp")
tree.column("# 2",  anchor="nw", width=60)
tree.heading("# 2", text="ID")
tree.column("# 3",  anchor="nw", width=35)
tree.heading("# 3", text="DLC")
tree.column("# 4",  anchor="nw", width=410)
tree.heading("# 4", text="Data")
tree.column("# 5",  anchor="nw", width=60)
tree.heading("# 5", text="Flags")

# Insert the data in Treeview widget


tree.place(x=10.0, y=50)
# tree.pack()

window.resizable(True, True)
window.protocol("WM_DELETE_WINDOW", on_closing)
window.mainloop()
