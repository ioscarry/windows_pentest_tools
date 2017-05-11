
                SecureCRT(R) (Official) -- May 2, 2013

            Copyright (C) 1995-2013 VanDyke Software, Inc.
                        All rights reserved.


Product Overview
----------------

SecureCRT protects your passwords, user accounts, and data, combining
rock-solid terminal emulation with the strong encryption, broad
authentication options, and data integrity of the Secure Shell (SSH)
protocol.

SecureCRT provides versatile solutions for business, network manage-
ment, information security, and development tasks, from accessing 
host-based applications and administering servers to securely 
accessing behind-the-firewall network resources like e-mail, files,
and printers.

SecureCRT supports SSH1, SSH2, Telnet, Telnet/SSL, RLogin, Serial,
and TAPI protocols and authentication via password, public key, X.509
certificate, and Kerberos v5 via GSSAPI.  Ciphers include AES, 
AES-CTR, Twofish, Blowfish, 3DES, and RC4.

Choose from a wide range of emulations including VT100, VT102, VT220,
ANSI, SCO ANSI, Wyse 50/60, Xterm, and Linux console -– all with ANSI
color.  Unicode support includes the ability to display character sets
from multiple languages, support for languages with right-to-left
reading order, and a character encoding list that includes
commonly-used encodings as well as all encodings supported by the
local system.

SecureCRT features a multi-session tabbed or tiled interface with 
extensive session management and customization features.  Customi-
zation options include toolbars, menus, keymaps, button bar, and 
login scripts, as well as fonts, cursors, and color schemes. 

Named sessions and firewalls let you create individual configurations
that can be used on a session-specific basis.  Other features include
auto logon, printing, Emacs mode, and SOCKS firewall support.

Powerful scripting capabilities including ActiveX scripting support
for VBScript and other scripting languages on Windows, embedded
Python support, and the script recorder save you valuable time by 
automating routine configuration tasks.  Secure file transfers can be
performed using Zmodem, Xmodem, Ymodem, or Kermit from an SSH1 or SSH2
session.  Upload files easily by dragging and dropping them onto an 
SFTP tab or session window.

Save steps with the close integration of SecureCRT and the SecureFX(R)
file transfer client, which share sessions and settings that let you
run SFTP, FTP, SCP, and FTP/SSL file transfer sessions without
reentering passwords.

SecureCRT includes a 30-day try-before-you-buy evaluation license for
the fully functional application and access to VanDyke Software(R)
technical support.


Contents
--------

   1. New for SecureCRT 7.1
   2. Enhancement Requests, Updates, and Questions
   3. Encryption Export
   4. Upgrades
   5. Product History
   6. SecureCRT Features
   7. Reporting Bugs
   8. Contact Information


1. New For SecureCRT 7.1
------------------------

SecureCRT 7.1 brings tiled sessions to Mac and Linux versions, adds 
an option to set up dependent sessions for connecting with jump hosts,
and extends file transfer options with Kermit support.  Productivity 
improvements include the ability to send a button bar command to all 
sessions and to optimize data transfer speed with a new send delay 
option.

Here are some of the new features in SecureCRT 7.1:

Tiling for Mac and Linux

  Session tiling is now available on Windows, Mac, and Linux.  Sessions 
  can be tiled cascaded to compare the contents of two or more sessions;
  use the chat window to send commands to all sessions and see the
  resulting output.

Dependent session option

  Link a session to an SSH2 session that it depends on, which allows
  connection to a jump host before connecting to other sessions.

Kermit support

  Support for the Kermit protocol provides an additional way to 
  transfer files.

Button bar enhancements

  Press SHIFT+<click> on a button to send a button bar command to all
  connected tabbed or tiled sessions.

New character send delay option

  A character send delay option to wait for a text prompt allows data 
  to be sent as fast as the system can handle, rather than using a 
  fixed time delay.

Support for SHA1 in RSA signatures

  Support for SHA1 in RSA signatures in addition to MD5 allows X.509
  certificates to be used in FIPS mode. (Windows only)

Integration with SecureFX for Mac and Linux

  With the availability of SecureFX for Mac and Linux, integration 
  between SecureCRT and SecureFX on Mac and Linux is now possible.

Please see History.txt in the SecureCRT program group for additional 
information on other changes and bug fixes.


2. Enhancement Requests, Updates, and Questions
-----------------------------------------------

We want to hear from you.  Let us know what features you would like to
see in future releases of SecureCRT by visiting our website at:

  http://www.vandyke.com/feedback.php

Every VanDyke Software license includes a full year of upgrades and
technical support.  To receive e-mail notification when new releases
of SecureCRT are available, sign up for our SecureCRT mailing list at:

  https://secure.vandyke.com/cgi-bin/subscribe.php?RMF=3

For tips, ideas, and product news, subscribe to VanDyke Software's
"What's New" at:

  https://whatsnewvandyke.com

You can also exchange useful tips and ideas with your peers and
VanDyke developers by joining the online forums:

  http://forums.vandyke.com/index.php?RMF=3

If you have any questions, please visit our website at:

  http://www.vandyke.com/feedback.php

SecureCRT for Windows supports Windows Server 2008 R2, Windows7,
Windows Server 2008, Windows Vista, 2003, Windows Server 2003 R2,
Windows Server 2003, and Windows XP for x86 and x64.


3. Encryption Export
--------------------

This Software is subject to export control.  The Software may be
transmitted, exported, or re-exported only under applicable export
laws and restrictions and regulations of the United States Bureau of
Industry and Security or foreign agencies or authorities.  By
downloading or using the Software, you are agreeing to comply with
export controls.  For more information see:

  http://www.vandyke.com/download/export.html


4. Upgrades
-----------

Users who purchased SecureCRT on or after February 1, 2012 are
eligible for a free upgrade to SecureCRT 7.1.  All users can evaluate
SecureCRT 7.1 for 30 days free of charge.  For more information on
upgrade eligibility and purchasing upgrades, please visit:

  http://www.vandyke.com/pricing/corporate/upgrades


5. Product History
------------------

The list of changes made for this release of SecureCRT can be found
in the SecureCRT_History.txt file installed with the program.


6. SecureCRT Features 
---------------------

Support for SSH1 and SSH2 Secure Shell protocols.
  - SSH2 Protocol support:
    - AES-128, AES-192, AES-256, AES-128-CTR,  AES-192-CTR, 
      AES-256-CTR, Twofish, Blowfish, 3DES, and RC4 ciphers.
    - RSA and DSA host key support.
    - Multiple ordered authentication methods, ciphers and MACs.
    - Public Key Assistant makes it easier to upload public keys.
    - Local port forwarding, X11 forwarding, remote forwarding, and
      dynamic forwarding.
    - OpenSSH Agent forwarding.
    - MD5, MD5-96, SHA1, and SHA1-96 MACs.
    - RSA, DSA, public-key, X.509 certificate, PKCS #11, PKCS #12,
      Kerberos v5 via GSSAPI, and password authentication methods.
    - SFTP tab creates an SFTP session to an existing SSH session.
    - Passphrase and password caching options.
  - SSH1 Protocol support:
    - Blowfish, DES, 3DES, and RC4 ciphers.
    - RSA, TIS, and password authentication.
    - Local port forwarding, X11 forwarding.

Session Management.
  - Named sessions store different preferences for different hosts.
  - Tabbed sessions allow multiple sessions in the same window.
  - Tabbed sessions can be moved in and out of windows.
  - Launch multiple selected sessions in tabs with a single click.
  - Tiling allows multiple sessions to be viewed at once.
  - A session can be logged to a file, including options for logging
    custom data and a option for creating a new log file at midnight.
  - Built-in SSH agent allows keys to be explicitly added or removed.

Configuration & Customization.
  - Easy configuration of basic SSH, port forwarding, remote
    forwarding and other settings in Session Options dialog.
  - Named firewalls.
  - Dependent session option (jump host).
  - Customizable toolbar and menus (Windows only).
  - User-defined number of savelines (scrollback) up to 128,000.
  - User-configurable number of rows and columns.
  - User-defined foreground, background, and bold colors.
  - User-defined keymaps.
  - User-defined button bar.
  - User-defined word delimiter characters for double-click.
  - Emacs mode maps ALT+<key> to send ESC+<key>.
  - Real-time keyword highlighting.

Advanced Terminal Emulation.
  - Quality VT100, VT102, VT220, Linux console, SCO ANSI, Wyse 50/60
    and ANSI emulation:
    - VT line drawing.
    - Support for bold, underline, and reverse attributes.
    - Double-width and double-height fonts.
    - 80/132 column switching.
    - VT100 and VT220 keyboard emulation.
    - Optional ANSI color.
    - 256-color Xterm.
    - Xterm extensions for mouse support and changing title bar.
    - Multi-byte character set support for Japanese, Korean, and
      Chinese.
    - Unicode support includes the ability to display character sets
      from multiple languages, support for multi-byte character sets,
      right-to-left reading order languages, and an extensive
      character encoding list.
 
Other Features.
  - FIPS 140-2 validated cryptographic library support (Windows 
    only).
  - Variable compression increases performance on slow connections.
  - Simple interface for automating logins.
  - Support for Telnet, Telnet/SSL, and RLogin protocols:
    - Telnet supports Negotiate About Window Size (NAWS).
    - Telnet supports Local Flow Control (LFLOW).
  - Serial (COM) device support.
  - Integration with SecureFX 3.x or higher.
  - Scripting language support for VBScript, JScript, and Perlscript.
  - Embedded support for Python scripting.
  - Script recorder.
  - Zmodem, Xmodem, Ymodem, and Kermit file transfer (upload and 
    download).
  - Built-in TFTP server.
  - Drag and drop file transfer (upload).
  - Printing: auto print, selection, screen, and pass-through 
    printing.
  - Modem dialer support: configure and save modem, country code,
    phone, and redial settings for TAPI sessions.
  - SOCKS firewall support with password authentication.
  - Unauthenticated and basic HTTP proxy support.
  - Generic proxy firewall support.
  - Copy and paste, including an "auto copy" option and a "paste on
    middle or right mouse click" option.
  - Chat window option provides an editable type-ahead buffer with
    history support and the ability to send chat text to all tabs or 
    to all tiled sessions.
  - Support for use from the command line or web browsers.
  - Support for standard insertion caret so that it can be tracked
    by screen access technology for the blind.


7. Reporting Bugs
-----------------

If you experience something you believe is a bug, please fill out
our online form at:

  http://www.vandyke.com/feedback.php

Please do not assume someone else will report it.  We will try to
resolve reported bugs as quickly as possible.  However, we can't
resolve bugs that are not reported.

Please describe the problem in as much detail as possible. Please
include the following information:

  - Version of SecureCRT (as shown in the About dialog)
  - Operating system and version


8. Contact Information
-----------------------

For information on ordering licenses, please visit the VanDyke
Software website:

  http://www.vandyke.com


All other inquiries should be directed to:

  VanDyke Software, Inc.
  4848 Tramway Ridge Dr. NE
  Suite 101
  Albuquerque, NM 87111
  USA

  Inquiry form: http://www.vandyke.com/feedback.php


VanDyke Software, SecureCRT, and SecureFX are trademarks or registered
trademarks of VanDyke Software, Inc. in the United States and/or other
countries.

All other products and services mentioned are trademarks or registered
trademarks of their respective companies.