另外半个WIN OS 提权EXP.

Windows NT/2K/XP/2K3/VISTA/2K8/7 NtVdmControl()->KiTrap0d local ring0 exploit
原作者联系方式:taviso@sdf.lonestar.org


本版本以这位GOOGLE黑客高手Tavis Ormandy的大作为基础改写而成.
修改部分如下:
1:根据作者个人遗憾的几点做了改进,避免了因NT系统的目录差异而失败的情况.
2:造成蓝屏的机率减少,改了一些宏的重复DEFINIE.
3:去除ROOT过程中的提示,保留了最终结果提示.
4:模拟之前的MS08066 利用方法,直接在程序后接收参数,方便上传后在WEBSHELL上使用.
5: ...  ...


使用方法(详见程序内提示):
----------------------------------------
exp.exe net localgroup administrators you /add   or
exp.exe malwear.exe
....
----------------------------------------


DLL名字不可更改,EXE文件名可随意更改.时间仓促之作,如果有问题,欢迎回应.