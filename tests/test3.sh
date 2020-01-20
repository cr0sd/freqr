#!/bin/bash

_file=$0
_raw2wav=$1
_dir=$2
_name=$3
_freqr=$4

# Clean if necessary
if [ $1 == "clean" ]; then
	set -x
	rm -f $_dir/$_name.dat $_dir/$_name.dat.wav
	exit
fi

# Test waveforms
#printf "file \"$0\":\t"
set -x
$_freqr -o $_dir/$_name.dat -a 5000 -w tr || exit 101
$_raw2wav $_dir/$_name.dat || exit 102
