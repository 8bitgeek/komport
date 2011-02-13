; Komport2 Inno Installer Script
[Setup]
AppName=Komport2
AppVersion=0.8
DefaultDirName={pf}\Komport2
DefaultGroupName=Komport2
UninstallDisplayIcon={app}\Komport2.exe
Compression=lzma2
SolidCompression=yes
OutputDir=userdocs:Pike Aero

[Files]
Source: "Komport2.exe"; DestDir: "{app}"
Source: "Readme.txt"; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\Komport2"; Filename: "{app}\Komport2.exe"
