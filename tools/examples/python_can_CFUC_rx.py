import can
import numpy as np
import time
from can.interfaces import cfuc

bus = can.Bus(
    bustype="cfuc",
    channel="COM4",
    CANBaudRate=100000,
    IsFD=True,
    FDDataBaudRate=1000000,
)
counter = 0
while(True):
    # bus.send(msg_to_send)
    msgs_recv = bus.recv()

    for msg in msgs_recv:
        if msg != False:
            # if msg.is_fd == True:
            print(msg)
            print("  --------- " + str(counter))
            counter = counter + 1
            # print(len(msg.data), msg.data, msg.dlc)
        # if msg != False:
        # if msg.is_fd == True:
        #   print("FD!")
        # if msg.bitrate_switch == True:
        #   print("BRS!")
