#!/usr/bin/perl
#-------------------------------------------------------------------------------------------------------------------------------
#                                                                                                       
#                            _/      _/  _/                        _/    _/          _/_/_/_/_/         
#                           _/_/  _/_/      _/_/_/                _/    _/              _/      _/_/    
#                          _/  _/  _/  _/  _/    _/  _/_/_/_/_/  _/    _/  _/_/_/_/_/  _/    _/_/_/_/   
#                         _/      _/  _/  _/    _/              _/    _/              _/    _/          
#                        _/      _/  _/  _/    _/                _/_/                _/      _/_/_/     
#                                                                                                       
#                                                                                                       
#                                                    Minimal Unit Test support
#
# File:   minute_cCodeGenerator.pl
#
# Author: Silvano Catinella <catinella@yahoo.com>
#
# Description:
#	This script generates the code you have to include in your C program's main() function.
#	The generated procedure will manage the program file arguments and run the tests in the proper way considering the
#	specified arguments.
#	
#	To use this script respect the following syntax:
#		minute_cCodeGenerator.pl       \
#			--srcFilename=<filename> \
#			--tgtFilename=<filename> \
#			--template=<filename>    \
#			[--verbose] [--help]
#
#-------------------------------------------------------------------------------------------------------------------------------

use warnings;
use strict;

my $err = 0;
my @testsList;

my $TEMPLATE_DIR = "templates";

my %templDB = (
	"C"   => "cMain.tmpl",
	"CPP" => "cppMain.tmpl"
);

sub helpMsg {
	print("Use: minute_cCodeGenerator.pl --srcFilename=<filename> --tgtFilename=<filename> [--verbose] [--help]\n");
}

sub get_template {
	#
	# Description:
	#	It accept a filename as input argument and returns the template file name used for that type of file
	#
	my $ext = shift;
	my $templ = "";
	$ext =~ s/^.*\.//;
	$ext = uc($ext);
	foreach (keys(%templDB)) {
		if ($_ eq $ext) {
			$templ = $templDB{$_};
			last;
		}
	}
	return($templ);
}
#-------------------------------------------------------------------------------------------------------------------------------
#                                                        M A I N
#-------------------------------------------------------------------------------------------------------------------------------
my $srcfile = "";
my $tgtfile = "";
my $myVerbose = 0;

if (scalar(@ARGV) < 2) {
	# ERROR!
	helpMsg;
	$err = 131;

} else {
	my $myPath = $0;
	$myPath =~ s/\/[^\/]*//;

	{
		my $key;
		my $value;
		foreach (@ARGV) {
			if (/^--[^=]+=/) {
				$key = $_;
				$value = $_;
				$key =~ s/=.*$//;
				$value =~ s/^[^=]+=//;
				if ($key eq "--srcFilename") {
					$srcfile = $value;
				} elsif ($key eq "--tgtFilename") {
					$tgtfile = $value;
				} else {
					# ERROR!
					print(STDERR "ERROR! \"$_\" is unknown file's argument\n");
					helpMsg;
					$err = 133;
				}
			} elsif (/^--[^=]+$/) {
				$key = $_;
				$value = "";
				if ($key eq "--verbose") {
					$myVerbose = 1;
					
				} elsif ($key eq "--help") {
					helpMsg;
					
				} else {
					# ERROR!
					print(STDERR "ERROR! \"$_\" is unknown file's argument\n");
					helpMsg;
					$err = 133;
				}
			}
		}
	}

	if (-f "$srcfile") {
		my $fh;
		my $counter = 0;
		if ($myVerbose) {
			print("Parsing of \"$srcfile\" file...\n");
			print("Recognized tests list:\n");
		}
		
		if (open($fh, "<$srcfile")) {
			while (<$fh>) {
				my %row = ();
				if (/^[ \t]*TEST/) {
					chomp;
					s/[ \t]//g;
					s/^TEST\(([^,]+),([^,]+)\).*/$1__$2/;
					$row{"cbut"}     = $1; # Code Block Under Test
					$row{"ttype"}    = $2; # Test Type
					$row{"testproc"} = $_;
					if ($_) {push(@testsList, \%row)};
					if ($myVerbose) {
						printf("\t%d) %s::%s\n", $counter, $row{"cbut"}, $row{"ttype"});
					}
					$counter++;
				}
			}
			close($fh);
			
			if ($counter == 0) {
				# WARNING!
				print("WARNING! No test found in the \"$srcfile\" file\n");
				$err = 16;
			} else {
				my $template = &get_template($srcfile);

				if ($template eq "") {
					print("ERROR! I cannot find the proper template for the \"$srcfile\" file\n");
					$err = 135;

				} else {
					my $tgtFH;
					my $tmplFH;
					
					if ($myVerbose) {
						print("\nI will use the \"$template\" template file\n");
					}
					
					if (not open($tgtFH, "> $tgtfile")) {
						# ERROR!
						print(STDERR "ERROR! I cannot write the \"$tgtfile\" file\n$!\n");
						$err = 131;

					} elsif (not open($tmplFH, "< $myPath/$TEMPLATE_DIR/$template")) {
						# ERROR!
						print(STDERR "ERROR! I cannot read the \"$template\" file\n$!\n");
						$err = 131;
						close($tgtFH);

					} else {
						my $tNamesList = "";
						my $tFuncsList = "";
						if ($myVerbose) {print("Template \"$template\" compiling:")};
						foreach (@testsList) {
							$tNamesList = $tNamesList . "\"" . $_->{"cbut"} . "::" . $_->{"ttype"} . "\", ";
							$tFuncsList = $tFuncsList . $_->{"testproc"} . ", ";
						}
						$tNamesList =~ s/, *$//;
						$tFuncsList =~ s/, *$//;
						
						print($tgtFH "// This file has been aumatically created by $0 script\n\n");
						while (<$tmplFH>) {
							chomp;
							if (/##[^ \t;]+##/) {
								if ($myVerbose) {print("#")};
								if (/##TESTSNUM##/) {
									s/##TESTSNUM##/$counter/;
								}
								if (/##TESTSLIST##/) {
									s/##TESTSLIST##/$tNamesList/;
								}
								if (/##FUNCSLIST##/) {
									s/##FUNCSLIST##/$tFuncsList/;
								}
							} else {
								if ($myVerbose) {print(".")};
							}
							print($tgtFH "$_\n");
						}
						if ($myVerbose) {print("\n")};
						close($tgtFH);
						close(tmplFH);
					}
				}
			}
		} else {
			# ERROR!
			print(STDERR "ERROR! I cannot read the \"$srcfile\" file\n");
			$err = 131;
		}
	} else {
		# ERROR!
		print(STDERR "ERROR! \"$srcfile\" file not found\n");
		$err = 129;
	}	
}

exit($err);

