#!/usr/bin/python3
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
# File:   minute_cCodeGenerator.py
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
#-------------------------------------------------------------------------------------------------------------------------------+
import sys
import argparse
import re
from pathlib import Path

TEMPLATE_DIR = "templates";
TESTSNUM_PATTERN = r"##TESTSNUM##"
TESTSLIST_PATTERN = r"##TESTSLIST##"
FUNCSLIST_PATTERN = r"##FUNCSLIST##"

templDB = {
	"c"   : "cMain.tmpl",
	"cpp" : "cppMain.tmpl"
}

def testsFileParser (filename: str, verbose: bool) -> list[str] :
	#
	# Description:
	#	It parses the src-file that contain TEST macros ansd returns a list of the defined tests names
	#
	fh = open(filename, "r");
	pattern = r"TEST[\t]*(.+,.t)"
	tlist = []
	if (verbose) :
		print("\nDetected test procedures:")
	while (row := fh.readline()) :
		row = row.rstrip("\n")
		if (re.match(pattern, row)):
			row = re.sub(r"[ \t]", r"", row);
			item = re.sub(r"TEST\(([^,]+),([^,]+)\).*", r"\1::\2", row);
			if (verbose) :
				print(f"\t{item}");
			tlist.append(item);
	fh.close()
	return(tlist)

def get_template (filename: str) -> str :
	#
	# Description:
	#	It accept a filename as input argument and returns the template file name used for that type of file
	#
	templFile = ""
	ext = re.sub(r"^.*\.", r"", filename);
	for key in templDB.keys() :
		if (key.upper() == ext.upper()) :
			templFile = templDB[key]

	return(templFile)

#-------------------------------------------------------------------------------------------------------------------------------
#                                                        M A I N
#-------------------------------------------------------------------------------------------------------------------------------
parser = argparse.ArgumentParser()

parser.add_argument(
	"--srcFilename",
	required = True,
	action   = "store",
	help     = "The source file that contains the tests"
)
parser.add_argument(
	"--tgtFilename",
	required = True,
	action   = "store",
	help     = "The name of the file that contains the main() function definition"
)
parser.add_argument(
	"--verbose",
	action = "store_true",
	help   = "It increcmets the process' output verbosity level"
)

args = parser.parse_args()

#
# Checking for the file's arguments
#
if (Path(args.srcFilename).is_file()) == False :
	print(f"ERROR! \"{args.srcFilename}\" file not found")
	exit(129)

else :
	tNFList  = ""
	tFFList  = ""
	myPath   = re.sub(r"[^\/]*$", "", sys.argv[0])
	testList = testsFileParser(args.srcFilename, args.verbose)
	tmplFile = get_template(args.srcFilename)
	
	for rec in testList :
		tNFList = tNFList + f'"{rec}"' + ", "
		rec = re.sub(r"::", r"__", rec)
		tFFList = tFFList + rec + ", ";
		
	tNFList = re.sub(r", $", "", tNFList)
	tFFList = re.sub(r", $", "", tFFList)
						
	if args.verbose :
		print(f"Selected template: {tmplFile}");
	
	try :
		tmplFh = open(f"{myPath}/{TEMPLATE_DIR}/{tmplFile}", "r")
		sgcFh  = open(args.tgtFilename, "w")

	except OSError as err:
		print(err)
		exit(131)
	
	while (row := tmplFh.readline()) :
		#row = row.rstrip("\n")
		if (re.match(r".*##[^#]+##", row)) :
			row = re.sub(TESTSNUM_PATTERN,  str(len(testList)), row)
			row = re.sub(TESTSLIST_PATTERN, tNFList, row)
			row = re.sub(FUNCSLIST_PATTERN, tFFList, row)
		
		sgcFh.write(row)
	
	tmplFh.close();
	sgcFh.close();

