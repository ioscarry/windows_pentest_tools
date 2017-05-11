@shift
@echo off
Title MS08067批量抓鸡器 n1x0r l33专版

color 0a
echo==========================================================================
echo                    MS08067批量抓鸡器 n1x0r l33专版
echo==========================================================================
del host.txt /q 
del Result.txt /q 
echo =========================================================================
echo 1:TCP多线程扫描 XP
echo 2:SYN扫描 2000 2003
echo =========================================================================
:CHO
set choice=
set /p choice=请选择:
if not "%Choice%"=="" set Choice=%Choice:~0,1%
if /i "%choice%"=="1" goto TCP
if /i "%choice%"=="2" goto SYN
echo 错误,请重新输入
goto CHO
:TCP
echo 192.168.1.1 192.168.255.255>ip.txt
start ip.txt
echo========================================================================== 
echo 此IP输入完毕,按任意键开始扫描
echo========================================================================== 
pause>nul
for /f "eol= tokens=1,2 delims= " %%i in (ip.txt) do s tcp %%i %%j 445 800 /save
for /f "skip=2 tokens=1" %%1 in (result.txt) do echo %%1 >>host.txt
del ip.txt /q
del Result.txt /q
exit

 

:SYN
echo 192.168.1.1 192.168.255.255>ip.txt
start ip.txt
echo========================================================================== 
echo 此IP输入完毕,按任意键开始扫描
echo========================================================================== 
pause>nul
for /f "eol= tokens=1,2 delims= " %%i in (ip.txt) do s syn %%i %%j 445 /save
for /f "skip=2 t 700 kens=1" %%1 in (result.txt) do echo %%1 >>host.txt
SET A=1
del ip.txt /q
del Result.txt /q
exit

