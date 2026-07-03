#!/bin/bash
#-------------------------------------------------------------------------------------------------------------------------------
#
#                                            __  __ _             _   _     _____    
#                                           |  \/  (_)_ __       | | | |   |_   _|__ 
#                                           | |\/| | | '_ \ _____| | | |_____| |/ _ \
#                                           | |  | | | | | |_____| |_| |_____| |  __/
#                                           |_|  |_|_|_| |_|      \___/      |_|\___|
#                                                    Minimal Unit Test support
#
# File:      INSTALL.sh
#
# Author:    Silvano Catinella
#
# Description:
#	This script allows you to install/remove the minute software-project.
#
#	use the following syntax: ./INSTALL [--cmd={install|uninstall}] [--prefix=<dir>]
#
#-------------------------------------------------------------------------------------------------------------------------------

CMD="install"
PREFIX="/usr/local"
PRJCT_DIR="share/minute"
TEMP_DIR="templates"

libFilesList="./src_C/libMinuteC.a ./src_CPP/libMinuteCPP.a"
incFilesList="./src_C/minute.h ./src_CPP/minute.hpp"
tmplFilesList="./templates/cMain.tmpl ./templates/cppMain.tmpl"
scriptsList="./minute_cCodeGenerator.py"

cd ${0%/*}

for arg in $*
do
	key=""
	value=""
	expr "$arg" : '--[^=]\+=[^=]\+$' >/dev/null && {
		key="${arg%%=*}"
		key="${key#--}"
		value="${arg#*=}"
		echo "[$key] [$value]"
	}
	
	if [ "$key" = "cmd" ]; then
		CMD="$value"

	elif [ "$key" = "prefix" ]; then
		PREFIX="$prefix"
	fi
done

if [ "$CMD" = "install" ]; then
	make -C "./src_C"
	make -C "./src_CPP"

	[ -d "$PREFIX/$PRJCT_DIR/$TEMP_DIR" ] || mkdir -p "$PREFIX/$PRJCT_DIR/$TEMP_DIR"

	for file in $libFilesList; do
		install --verbose --mode=644 --owner=root "$file" "$PREFIX/lib/${file##*/}"
	done

	for file in $incFilesList; do
		install --verbose --mode=644 --owner=root "$file" "$PREFIX/include/${file##*/}"
	done

	for file in $scriptsList; do
		install --verbose --mode=755 --owner=root "$file" "$PREFIX/$PRJCT_DIR/${file##*/}"
	done

	for file in $tmplFilesList; do
		install --verbose --mode=644 --owner=root "$file" "$PREFIX/$PRJCT_DIR/$TEMP_DIR/${file##*/}"
	done

	echo "PREFIX=\"$PREFIX\""       >  minute.log
	echo "PRJCT_DIR=\"$PRJCT_DIR\"" >> minute.log
	echo "TEMP_DIR=\"$TEMP_DIR\""   >> minute.log

elif [ "$CMD" = "uninstall" ]; then
	source minute.log
	for file in $libFilesList; do
		rm -fv "$PREFIX/lib/${file##*/}"
	done
	for file in $incFilesList; do
		rm -fv "$PREFIX/include/${file##*/}"
	done

	for file in $scriptsList; do
		rm -fv "$PREFIX/$PRJCT_DIR/${file##*/}"
	done

	for file in $tmplFilesList; do
		rm -fv "$PREFIX/$PRJCT_DIR/$TEMP_DIR/${file##*/}"
	done
		

	rmdir --ignore-fail-on-non-empty "$PREFIX/$PRJCT_DIR/$TEMP_DIR"
	rmdir --ignore-fail-on-non-empty "$PREFIX/$PRJCT_DIR"

else
	echo "ERROR! Please, use the following syntax: $0 [--cmd={install|uninstall}] [--prefix=<dir>]"
	exit 131
fi
