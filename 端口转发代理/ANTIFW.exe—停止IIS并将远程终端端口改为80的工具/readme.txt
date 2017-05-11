ANTIFW.exe—停止IIS并将远程终端端口改为80的工具

对于一个过防火墙的方法写的程序(AntiFW.exe)

不知道原创是在什么地方看到了，一种比较bt的过防火墙的方式：
停掉IIS，把终端服务端口开到80.
就这个我写了个程序，请看:
F:/C/AntiFW>AntiFW
http://www.bit.edu.cn/ QQ:540085595

Usage:AntiFW [-s | -l]
-s:to stop IIS,and set TS to port 80
-l:to logoff yourself and start IIS in a minute

1)
AntiFW -s
这样IIS就被停掉，同时终端服务的端口被改成80

2)
AntiFW -l
注销自己，并在两分钟之后把终端服务端口改到3389，同时启动IIS.
这样就能让网站还是活过来...

干掉IPSEC后仍然无法连接3389，就可以用到此工具，自动停止IIS将3389转到80上 
工具的命令是在cmd下输入 
antifw -s 运行程序 停止iis将3389改为80 
antifw -l 关闭程序。恢复iis 
web服务器肯定不限制80端口的连接，所以开了防火墙也不会限制80…所以用这个你再开防火墙也没有用，嘎嘎。
