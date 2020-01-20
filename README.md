[![Build Status](https://travis-ci.com/cr0sd/freqr.svg?branch=master)](https://travis-ci.com/cr0sd/freqr)

# freqr
CLI utility to generate 1-second square wave at specified frequency to file

#### Introduction

  Try this:

  `pacman -S sox` or `apt install sox`

  `make`

  `./freqr -f 440 -o myaudio.dat`

  `./raw2wav.sh myaudio.dat`

  `play myaudio.dat.wav`


#### Usage: ./freqr [-f] [-r] [-s] [-a] [-o] [-w {sn|sq|tr|sw|ns}]

	-f FREQ		Frequency			frequency in audible range (e.g., 'freqr -f 440')

	-r SAMPLERATE	Sample rate(e.g., -s 44100)	sample rate (defaults to 44100) in samples/second or Hz

	-s NUM_SAMPLES	Number of samples		number of samples to generate (defaults to 44100, or 1 second of audio)

	-a AMPLITUDE	Amplitude (16-bit int)		value of signed 16 bit integer to indicate maximum amplitude (notice negatives invert the waveform)

	-w WAVEFORM	One of: sn,sq,tr,sw,ns		sine, square, triangle, saw, noise

	-o OUTPUTFILE	Specify file to output to

#### Notes

  Triangle and Saw waves are offset by 1/4 and 1/2 the period respectively, in order to 'normalize' the
  initial output of their functions to zero (this affects phase but is worth the quality improvement IMHO)

#### To do

  Implement '-b <16/32...>' switch to change bit-depth (defaults to 16-bit)
