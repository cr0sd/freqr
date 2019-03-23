# freqr
CLI utility to generate 1-second square wave at specified frequency to file

### Usage: freqr [frsa] [w <sn, sq, tr, sw>]
________________________
-f : frequency in audible range (e.g., 'freqr -f 440')

-r : sample rate (defaults to 44100) in samples/second or Hz

-s : number of samples to generate (defaults to 44100, or 1 second of audio)

-a : value of signed 16 bit integer to indicate maximum amplitude (notice negatives invert the waveform)

-w : use `sn`, `sq`, `sw`, `tr`, or `ns` for sine, square, saw, triangle waves, or noise respectively

### Notes
________________________
Triangle and Saw waves are offset by 1/4 and 1/2 the period respectively, in order to 'normalize' the
initial output of their functions to zero (this affects phase but is in this writer's opinion beneficial)

### To do
________________________
Implement '-b <16/32...>' switch to change bit-depth (defaults to 16-bit)
