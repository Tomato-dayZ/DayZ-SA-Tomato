@echo off
SetLocal EnableDelayedExpansion
TITLE DayZ SA Server - Status
COLOR 0A
:: Variables

set Y=!date:~-4!
set M=!date:~-7,2!
set D=!date:~-10,2!
set hr=!time:~0,2!
if "!hr:~0,1!" == " " SET hr=0!hr:~1,1!
set min=!time:~3,2!
set sek=!time:~6,2!

set Date=[!D!-!M!-!Y!_!hr!-!min!-!sek!]
::DayZServer_64.exe path
set DAYZ-SA_SERVER_LOCATION="D:\Steam\steamapps\common\DayZServer"
::Bec.exe path
set BEC_LOCATION="D:\Steam\steamapps\common\DayZServer\battleye\bec"
::PboManagerConsole.exe path
SET PBOManager="D:\Steam\steamapps\common\DayZServer\e\pbo\PBOConsole.exe"
::Folder to bec packet into pbo file
SET ScriptFolder="D:\Steam\steamapps\common\DayZServer\DayZ-SA-Tomato\addons\DayZ-SA-Tomato"
::Destination for packed PBo File
SET PBOFile="D:\Steam\steamapps\common\DayZServer\DayZ-SA-Tomato\addons\DayZ-SA-Tomato.pbo"
::Script.log File
SET scriptl="D:\Steam\steamapps\common\DayZServer\Log\script.log"
::crash.log File
SET crashl="D:\Steam\steamapps\common\DayZServer\Log\crash.log"
::Destionation Script.log File
SET scriptln="D:\Steam\steamapps\common\DayZServer\Log\Old\[Script]-!Date!.log"
::Destionation crash.log File
SET crashln="D:\Steam\steamapps\common\DayZServer\Log\Old\[Crash]-!Date!.log""
::::::::::::::
echo !Date! - Welcome
goto checksv
pause

:clearlogs
echo !Date! - Copy old Logs ..
IF EXIST %scriptl% copy %scriptl% %scriptln%
IF EXIST %crashl% copy %crashl% %crashln%
IF EXIST %scriptl% del %scriptl%
IF EXIST %crashl% del %crashl%
goto startsv

:checksv
tasklist /FI "IMAGENAME eq DayZServer_x64.exe" 2>NUL | find /I /N "DayZServer_x64.exe">NUL
if "%ERRORLEVEL%"=="0" goto checkbec

echo !Date! - Server is not running, taking care of it..
goto killsv
goto startsv

:checkbec
tasklist /FI "IMAGENAME eq Bec.exe" 2>NUL | find /I /N "Bec.exe">NUL
if "%ERRORLEVEL%"=="0" goto loopsv
echo !Date! - Bec is not running, taking care of it..
goto startbec

:Restart
cls
echo !Date! - Restarting...
echo !Date! - killing Bec.exe
taskkill /f /im Bec.exe
echo !Date! - Killing DayZServer_x64.exe
taskkill /f /im DayZServer_x64.exe
goto clearlogs
goto startsv

:loopsv
ECHO !Date! - Press any key to Repack and restart
   PAUSE >NUL
goto Restart

:killsv
taskkill /f /im Bec.exe
taskkill /f /im DayZServer_x64.exe
goto clearlogs


:startsv
echo !Date! - Start Packing Process
IF EXIST %PBOFile% echo !Date! - PBO Found Deleting...
IF EXIST %PBOFile% DEL /F %PBOFile%
echo !Date! - Packing 
%PBOManager% -pack %ScriptFolder% %PBOFile%
echo !Date! - packing Done
echo !Date! - Starting DayZ SA Server.
timeout 1 >nul
echo !Date! - Starting DayZ SA Server..
timeout 1 >nul
echo !Date! - Starting DayZ SA Server...
cd "%DAYZ-SA_SERVER_LOCATION%"
start /high DayZServer_x64.exe "-config=serverDZmoddet.cfg" -scrAllowFileWrite -mod=DayZ-SA-Tomato -dologs -adminlog -profiles=D:\Steam\steamapps\common\DayZServer\Log -netlog -freezecheck -noFilePatching -cpuCount=12 -BEpath=D:\DayZServer\battleye
FOR /L %%s IN (1,-1,0) DO (
	echo !Date! - Initializing server, wait %%s seconds to initialize Bec.. 
	timeout 1 >nul
)
goto startbec







:startbec
echo Starting Bec.
timeout 1 >nul
echo Starting Bec..
timeout 1 >nul
echo Starting Bec...
timeout 1 >nul
cd "%BEC_LOCATION%"
start /min Bec.exe -f Config.cfg --dsc
goto checksv

