#!/bin/bash

# 2019,2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

OPT_COMPILATION="-Wall -fdiagnostics-color=always"
OPT_ASSEMBLAGE=""

clear
if [[ $# -ge 1 ]]; then
	case $1 in
		"clean" )
			echo "clean"
			rm -rf _obj
			exit 0 ;;
		"rebuild" )
			rm -rf _obj ;;
		"build" ) ;;
		*)
			echo "Commande inconnue $1" >&2
			exit 1 ;;
	esac
fi

mkdir -p _obj/

fail=false
for progPath in `find . -name \*.c`
do
	progObjet=`sed 's#.*/\(.*\)\.c#_obj/\1.o#' <<< $progPath`
	progLib=`sed 's#\.c$#.h#' <<< $progPath`

	echo -ne "\e[01;34m=== Compilation [$progPath]"
	if [[
		!( -e $progObjet )
		|| $progObjet -ot $progPath
		|| $progObjet -ot $progLib
	]]
	then
		which clang-format &>/dev/null && clang-format \
			-assume-filename=~/.clang-format -i $progPath
		gcc $OPT_COMPILATION -c $progPath -o $progObjet &>.log
		if [[ $? == 0 ]]; then
			echo -e "\e[32m OK\033[0m"
		else
			echo -e "\e[31m FAIL\033[0m"
			cat .log
			fail=true
		fi
	else
		echo -e "\e[35m CACHE\033[0m"
	fi
done
rm -f .log
$fail && exit 1

echo -e "\e[01;34m=== Assemblage\033[0m"
bin=`pwd | sed 's#.*/##'`
gcc _obj/*.o -o $bin $OPT_ASSEMBLAGE || exit $?

which getDoc >/dev/null && echo -e "\e[01;34m=== Documentation\033[0m" && getDoc

echo -e "\e[01;34m=== Lancement\033[0m"
./$bin
