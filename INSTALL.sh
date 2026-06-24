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
TEMP_DIR="template"

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
	[ -d "$PREFIX/$PRJCT_DIR/$TEMP_DIR" ] || mkdir -p "$PREFIX/$PRJCT_DIR/$TEMP_DIR"

	install --verbose --mode=644 --owner=root "./src_C/libMinuteC.a"       "$PREFIX/lib/libMinuteC.a"
	install --verbose --mode=644 --owner=root "./src_C/minute.h"           "$PREFIX/include/minute.h"
	install --verbose --mode=755 --owner=root "./minute_cCodeGenerator.pl" "$PREFIX/$PRJCT_DIR/minute_cCodeGenerator.pl"
	install --verbose --mode=644 --owner=root "./templates/cMain.tmpl"     "$PREFIX/$PRJCT_DIR/$TEMP_DIR/cMain.tmpl"

	echo "PREFIX=\"$PREFIX\""       >  minute.log
	echo "PRJCT_DIR=\"$PRJCT_DIR\"" >> minute.log
	echo "TEMP_DIR=\"$TEMP_DIR\""   >> minute.log

elif [ "$CMD" = "uninstall" ]; then
	source minute.log
	rm -fv                                              \
		"$PREFIX/lib/libMinuteC.a"                    \
		"$PREFIX/include/minute.h"                    \
		"$PREFIX/$PRJCT_DIR/minute_cCodeGenerator.pl" \
		"$PREFIX/$PRJCT_DIR/$TEMP_DIR/cMain.tmpl"     \
	&& {
		rmdir --ignore-fail-on-non-empty "$PREFIX/$PRJCT_DIR/$TEMP_DIR"
		rmdir --ignore-fail-on-non-empty "$PREFIX/$PRJCT_DIR"          
	}
fi
