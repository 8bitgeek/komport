; Komport2 Inno Installer Script
[Setup]
AppName=Komport
AppVersion=0.9.1
DefaultDirName={pf}\Komport
DefaultGroupName=Pike Aero
UninstallDisplayIcon={app}\komport.exe
Compression=lzma2
SolidCompression=yes
OutputDir=userdocs:Pike Aero

[Files]
Source: "..\komport-build-desktop\debug\komport.exe"; DestDir: "{app}"
Source: "c:\cygwin\bin\mingwm10.dll"; DestDir: "{app}"
Source: "c:\Qt\2010.05\mingw\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}"
Source: "c:\Qt\2010.05\qt\bin\QtCored4.dll"; DestDir: "{app}"
Source: "c:\Qt\2010.05\qt\bin\QtGuid4.dll"; DestDir: "{app}"
Source: "Readme.txt"; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\komport"; Filename: "{app}\komport.exe"
