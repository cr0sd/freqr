# freqr
CLI utility to generate 1-second square wave at specified frequency directly to stdout (Windows only)

### Usage: freqr [frsa]
________________________
-f : frequency in audible range (e.g., 'freqr -f 440')

-r : sample rate (defaults to 44100) in samples/second or Hz

-s : number of samples to generate (defaults to 44100, or 1 second of audio)

-a : positive value of 16 bit signed integer to indicate maximum amplitude

-w : use `sn`, `sq`, `sw`, or `tr` for sine, square, saw, or triangle waves respectively



### To do
________________________
Implement '-b <16/32...>' switch to change bit-depth (defaults to 16-bit)

Implement triangle wave function, sawtooth, sine wave...

