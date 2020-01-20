#!/usr/bin/env bash

_this=raw2wav.sh

# Get input file
if [ $# = 0 ]; then
	echo "$_this: Usage: $_this [inputfile [outputfile]]"
	_inputfile="raw.dat"
else
	_inputfile=$1
	if [ -f $_inputfile ]; then
		:
	else
		echo "$_this: Error: Could not find input file \"$_inputfile\". Exiting"
		exit
	fi
fi

# Get output file
if [ $# -lt 2 ]; then
	_outputfile="raw.wav"
else
	_outputfile=$2
	if [ -f $_outputfile ]; then
		echo "$_this: Warning: \"$_outputfile\" exists. Overwriting."
	fi
fi

# Create 'raw.wav' from 'raw.dat'
sox -b 16 -c 1 -r 44100 -e signed-integer -t raw $_inputfile $_outputfile
