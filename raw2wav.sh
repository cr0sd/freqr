#!/usr/bin/env bash

# Create 'raw.wav' from 'raw.dat'
sox -b 16 -c 1 -r 44100 -e signed-integer -t raw raw.dat -t wav raw.wav
