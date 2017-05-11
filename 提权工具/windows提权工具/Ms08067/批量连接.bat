@shift
for /f "eol= tokens=1,2 delims= " %%i in (host.txt) do nc %%i 4444
 pause
