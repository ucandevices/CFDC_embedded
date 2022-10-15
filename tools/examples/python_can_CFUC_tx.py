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

# send set of predefined messages
bus.send(can.Message(
    arbitration_id=0x1, dlc=1, data=[0x33], is_fd=True, is_extended_id=True))
bus.send(can.Message(
    arbitration_id=0x1, dlc=1, data=[0x33], is_fd=False, is_extended_id=False))
# some random stuff

# for i in range(120000):
#     rand_dlc = np.random.randint(1,65)
#     # rand_dlc = 16
#     rand_data = np.random.bytes(rand_dlc)
#     # rand_data = [101,102,103,104,105,106,107,108,109]
#     rand_id = np.random.randint(0, 0x800)
#     print(hex(rand_id), ": ", rand_dlc, " : ", rand_data.hex())
#     msg_to_send = can.Message(
#         arbitration_id=rand_id, dlc=rand_dlc, data=rand_data[0:rand_dlc], is_fd=True)
#     bus.send(msg_to_send)
#     time.sleep(2)
