import can
import numpy as np
import time
from can.interfaces import cfuc

bus = can.Bus(
    bustype="cfuc",
    channel="COM11",
    CANBaudRate=100000,
    IsFD=True,
    FDDataBaudRate=1000000,
)

for i in range(120000):
    # rand_dlc = np.random.randint(1,65)
    rand_dlc = 8
    rand_data = np.random.randint(0, 256, rand_dlc)
    # rand_data = [101,102,103,104,105,106,107,108,109]
    rand_id = np.random.randint(0, 0x800)
    print(hex(rand_id), ": ", rand_dlc, " : ", rand_data)
    msg_to_send = can.Message(
        arbitration_id=rand_id, dlc=rand_dlc, data=rand_data[0:rand_dlc], is_fd=True)
    bus.send(msg_to_send)
    # time.sleep(1)
