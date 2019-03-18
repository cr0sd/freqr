# freqr
CLI utility to generate 1-second square wave at specified frequency directly to stdout

Usage: freqr [frsa]
________________________
-f : frequency in audible range (e.g., 'freqr -f 440')

-r : sample rate (defaults to 44100) in samples/second or Hz

-s : number of samples to generate (defaults to 44100, or 1 second of audio)

-a : positive value of 16 bit signed integer to indicate maximum amplitude



To do
________________________
Implement '-b <16/32...>' switch to change bit-depth (defaults to 16-bit)

Implement triangle wave function, sawtooth, sine wave...

