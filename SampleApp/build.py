#!/bin/env python3
# coding=utf-8
# =============================================================================
#	Simple build script for Brain
# -----------------------------------------------------------------------------
#	2023/Aug/5th  HRA!
# =============================================================================

import sys
import re
import os
import subprocess

cc = "arm-mingw32ce-g++"
cc_opt = [ 
	"-Wall", 
	"-Wextra", 
	"-O3", 
	"-std=gnu++2a", 
	"-march=armv5tej", 
	"-mcpu=arm926ej-s", 
	"-static", 
	"-s", 
	"-lcommctrl", 
	"-lcommdlg",
	"-lmmtimer",
	"-lm",
	"-c" 
]
 
cc_res = "arm-mingw32ce-windres"
cc_res_opt = []

ld = cc
ld_opt = [
]

# --------------------------------------------------------------------
def get_ext( s_file_name ):
	s_ext = re.sub( r'.*\.', '', s_file_name )
	return s_ext.upper()

# --------------------------------------------------------------------
def main():
	try:
		with open( "source.txt", "r" ) as f:
			source_list = f.readlines()
	except:
		print( "Cannot open 'source.txt'." )
		exit(1)

	object_list = []
	for s_file in source_list:
		s_file = re.sub( r'^\s*', '', s_file )
		s_file = re.sub( r'\n', "", s_file )
		if( len( s_file ) == 0 or s_file[0] == '#' ):
			continue
		arg = []
		if get_ext( s_file ) == "RC":
			print( "RES: %s" % s_file )
			arg.append( cc_res )
			arg.extend( cc_res_opt )
			arg.append( s_file )
			arg.append( "-o" )
			arg.append( s_file + ".o" )
			object_list.append( s_file + ".o" )
		else:
			print( "SRC: %s" % s_file )
			arg.append( cc )
			arg.extend( cc_opt )
			arg.append( s_file )
			arg.append( "-o" )
			arg.append( s_file + ".o" )
			object_list.append( s_file + ".o" )
		subprocess.run( arg )
	print( "LNK: AppMain.exe" )
	arg = []
	arg.append( ld )
	arg.extend( ld_opt )
	arg.extend( object_list )
	arg.append( "-o" )
	arg.append( "AppMain.exe" )
	subprocess.run( arg )

	with open( "AppMain.cfg", "wb" ) as f:
		print( "  Write AppMain.cfg" )

	with open( "index.din", "wb" ) as f:
		print( "  Write index.din" )

	print( "Finish!" )

if __name__ == "__main__":
	main()
