#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<inttypes.h>

#define SAMPLESPERSEC 44100
#define BITSPERSAMPLE 16
#define BITRATE (BITSPERSAMPLE/SAMPLESPERSEC)
#define FREQ 440
#define ONEOSC (SAMPLESPERSEC/FREQ)
#define MAG 1000

#define sq(f,o) (o%(SAMPLESPERSEC/f)<(SAMPLESPERSEC/f)/2?MAG:-MAG)
// #define tr(f,o) (o%(SAMPLESPERSEC/f)<(SAMPLESPERSEC/f)/2 ? MAG*(o/(SAMPLESPERSEC/f)) : 1/(o/(SAMPLESPERSEC/f))*-MAG)
int main(int argc,char **argv)
{
	//16 bit integer 44.1kHz
	//16 bit signed int range = ( -32,768 to 32,767 )
	
	//dynamic buffering vs static (per sec)
	//16 bit / 2 bytes per sample @ 44.1k samples per sec = 705.6kB
	
	if(argc<2)
	{
		printf("sy [freq]\n");
		return 1;
	}
	
	int i=0;
	int16_t *b=malloc(sizeof(uint16_t)*SAMPLESPERSEC);
	if(!b)printf("fail\n");
	
	for(i=0;i<SAMPLESPERSEC;i++)
		b[i]=sq(atoi(argv[1]),i);
		// b[i]=i%ONEOSC<ONEOSC/2?MAG:-MAG;
	
	fwrite(b,sizeof(uint16_t),SAMPLESPERSEC,stdout); //sizeof(uint16_t)==2 (bytes)!
	
	
	// printf("\nfinished\n");
	free(b);
	return 0;
}