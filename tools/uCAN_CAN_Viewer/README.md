# uCAN_CAN_Viewer 

Python application with basic CAN viewing and sending functionality 

## Making exe for windows 
python3 -m pip install pyinstaller
python3 -m PyInstaller --add-data="C:\Users\lukasz.juranek\Desktop\ucan\CFDC_embedded\tools\uCAN_CAN_Viewer\ucan_can_viewer\build\assets;."  -p C:\Users\lukasz.juranek\Desktop\ucan\python-can .\gui.py
