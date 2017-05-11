First we would like to thank everyone who has made hping because we use it
constantly.  We have found it to be one of the main tools we use when
testing out 'odd' network traffic or that new application that no one can
really explain.

The main reason for this release is the fix the problem that was caused by
Microsoft releasing SP2 for XP and removing the ability for an application
to make use of 'raw sockets'.

Some information on this can be found at:
http://www.microsoft.com/technet/prodtechnol/winxppro/maintain/sp2netwk.mspx#EHAA

This of course broke the ability for hping to send packets.  Since we are sometimes
required to run the tool under Windows this was a problem. ;)

We decided to try and fix this.  (We are James Fields [james.v.fields@gmail.com and
Kevin Johnson [kjohnson@secureideas.net])

We took a look at the code and then looked at what Fyoder and the NMAP team
did to fix the same issue. (NMAP is available at http://www.insecure.org and
we HIGHLY recommend it!)  We saw that by using libdnet and some of the code
Fyoder had written, we could modify hping and enable it to work on Windows
again.

There are a couple notes that we would like to make you aware of:
    
    * Hping now creates the entire Ethernet packet instead of depending on the
        network stack.  This means we will only support Ethernet networks.  We
        are not sure if hping supported other types before, but it definitely
        doesn't now.
    
    * The timing of the packets is incorrect.  By this we mean that when hping
        displays the RTT of a packet it is higher then the actual RTT.  This is
        an error with how hing gets that time.  We are looking at ways to fix
        this and would love ideas or help.(see below)  This bug existed in the
        previous version of hping for Windows.  We do not believe that our changes
        have added any extra time to this display.

    * The random destination scan now works correctly.  This was a bug in the
        original version for Windows.

We hope that you find this release useful.  If you have any comments, questions
or just want to talk to someone, feel free to contact us directly.  You can either
use the email addresses above or send an email to hping@secureideas.net and the
message will get to the two of us.

If we are able to make any other significant updates to this package, we will
upload it to the hping wiki at http://wiki.hping.org

Thanks
James Fields and Kevin Johnson
[james.v.fields@gmail.com] [kjohnson@secureideas.net]
May 24, 2006

###############################################################################
        Original README
###############################################################################

First thing of note.  Thanks to Salvatore Sanfilippo for the hping tool.  It's
helped me to better understand some network concepts.  Much more info. can be
found at the 'mother' site: http://www.hping.org.  

There is also a wiki at http://wiki.hping.org.


Usage for Windows version of hping:

Here's a URL for how to use hping (Unix and Windows version, except revisions with
Windows version listed below):

http://www.hping.org/manpage.html


Some differences in argument parameters and behavior compared to the Unix version
are as follows:

1. When hping is run in listen mode on Unix, memory paging is disabled. I haven't
implemented this in the native Windows version. If I get all fired up at some
point, maybe I'll try to figure it out.

2. There is an option to choose the network interface to use under Unix. I
haven't seen a simple way that Windows defines the network interfaces (i.e. eth0,
ppp0, ...). Thus, I've used the IP address as an I.D. for a specific interface.

3. Under Unix, pressing ctrl-z once will increment a port or ttl value
(depending on context) and pressing it twice will decrement it. I've changed this
to ctrl-z will increment, ctrl-a will decrement.

4. The option for sending packets at a specified interval is done using
microseconds in Unix. For example: hping -i u10000. Under Windows I've
changed this to milliseconds. Thus, the equivalent to the command above would
be: hping -i m100 (10 packets per second).



Compile:

I compiled hping using the free Dev-C++ compiler, and had to link these libraries:

libwinmm.a
libws2_32.a
libwsock32.a
libwpcap.a
libiphlpapi.a


Using Microsoft Visual C++ you'll have to link:

winmm.lib
ws2_32.lib
wsock32.lib
wpcap.lib
iphlpapi.lib


NOTE:  
I have been able to successfully compile with the Borland and Visual C++
compilers.  However, when attempting to send packets I get a 10049 socket error
code on a `sendto'.  I'm guessing it has something to do with how these compilers
deal with structs, but have not looked into it.  Any ideas and/or help would be
much appreciated.


ANOTHER NOTE:
Also, the new SP2 for Windows XP appears to be causing some issues.  Here's a
link explaining some changes to raw sockets.

http://www.microsoft.com/technet/prodtechnol/winxppro/maintain/sp2netwk.mspx#EHAA

Some people have reported some problems with Windows XP SP2.  TCP packets don't
get sent out (10004 error).  UDP and ICMP appear to be fine.  (However, you
cannot spoof an IP with UDP packets).  I'd like to get more feedback from
other people on how it is working on Windows XP SP2 machines.


SCAN MODE:
In regards to hping2-rc3-win32 version.  I have implemented the scan mode
for windows now.  The only switch that won't work is scanning for `known'
ports.  The argument would be something like:

`hping --scan known <hostname>'

I haven't looked too hard into how to implement it, but for now it doesn't work.
I wanted to get something out for the scan mode as it's a very useful function.


Any comments can be sent to rgturpin@epop3.com
