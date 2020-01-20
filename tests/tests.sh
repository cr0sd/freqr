#!/bin/bash

# Relative directory from freqr/
_dir=tests
_freqr=./freqr
_raw2wav=./raw2wav.sh
_clean=0

# clean command was passed
if [ $# = 1 ]; then
	if [ $1 == "clean" ]; then
		_clean=1
	fi
fi

# Run tests (or clean)
for i in {0..10}
do
	_name="test$i"
	if [ -f $_dir/$_name.sh ]; then
		if [ $_clean = 1 ]; then
			$_dir/$_name.sh clean $_dir $_name $_freqr
		else
			$_dir/$_name.sh $_raw2wav $_dir $_name $_freqr || exit 1
		fi
	else
		echo "$0: Error: Could not find \"$_dir/$_name.sh\""
		exit 2
	fi
done
