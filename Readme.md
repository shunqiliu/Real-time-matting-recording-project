# Real Time Matting Recording Project
Matting program for pure color background. With functions: Editing screen logo, subtitle, host Icon, and recording. Also with generating serial number according to network card information to encrypt program permission.
## Downloads
.exe for Windows 10 x64 in release file.
### Installation
Download an Configure ffmpeg to PC from internet.

Put "vasource" and "testresult" to D:\.

Run vc_redist.x64.exe.

Click start.exe to startup program
### Operation guide
Users need send the serial number in first interface to author to get access by email: 644602967@qq.com.
#### Main Menue
#### Prepare Recording Interface
#### Recording Interface
## For developers
The platform of this project is Visual Studio 2019 and Qt 5. Coded by C++, with OpenCV. All open source files are in code file.
### Interface file
MainWindow.ui: Main Menue.
ssy.ui: Prepare Recording Interface.
### Code file
main.cpp: Qt main file.
MainWindow.cpp/h:  Encrypt; Main menue interface; Preview HDMI frame; View recorded files; Shut down/Restart.
ssy.cpp/h: Recording; Matting; Frame operations.

Recording used dxgi, developers can include this from internet.
