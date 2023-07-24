# uCAN_CAN_Viewer 

Python application with basic CAN viewing and sending functionality 

## Making exe for windows 
python3 -m pip install pyinstaller
python3 -m PyInstaller --add-data="C:\Users\lukasz.juranek\Desktop\ucan\CFDC_embedded\tools\uCAN_CAN_Viewer\ucan_can_viewer\build\assets;."  -p C:\Users\lukasz.juranek\Desktop\ucan\python-can .\gui.py


from:
C:\Users\Lukasz.Juranek\Desktop\ucan\CFDC_embedded\tools\uCAN_CAN_Viewer\ucan_can_viewer\build

python -m PyInstaller --noconfirm --windowed --add-data="C:\Users\Lukasz.Juranek\Desktop\ucan\CFDC_embedded\tools\uCAN_CAN_Viewer\ucan_can_viewer\build\assets;.\assets" --add-binary="C:\Users\Lukasz.Juranek\Desktop\ucan\CFDC_embedded\tools\uCAN_CAN_Viewer\ucan_can_viewer\build\libs\libusb-1.0.dll;." .\gui.py

builds into:

C:\Users\Lukasz.Juranek\Desktop\ucan\CFDC_embedded\tools\uCAN_CAN_Viewer\ucan_can_viewer\build\dist\gui\gui.exe
