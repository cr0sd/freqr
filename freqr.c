#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<inttypes.h>
#include<string.h>

#define SEMITC pow(2,1/12.0)

#define raisesemi(f,n) (f*pow(SEMITC,(n)))
// #define sq(f,o,s,a) (o%(s/f)<(s/f)/2?a:-a)

FILE *fer;

/********
 * sq(f,o,r,a)
 * Generate single 50% duty cycle square wave 
 * at frequency f, offset o, samplerate r, and
 * (positive) amplitude a
 * 
 ********/
int32_t sq(double f,int32_t o,int32_t r,int32_t a)
{
	// if(f<=0) return 0;
	return o%(int32_t)(r/f)<(int32_t)(r/f)/2?a:-a;
}

int32_t tr(double f,int32_t o,int32_t r,int32_t a)
{
	// if(f<=0) return 0;
	// return 2*a/3.1415926f*asin(sin(2*3.1415926f/((r/f)*o)));
	// return ((a*((r/f)-(int32_t)fabs(o%(int32_t)(2*(r/f))-(r/f)) ))/(r/f))-(a/2);
	return pow(-1,o%2+1)*(o%(int32_t)(r/f))*a;
}

int32_t sw(double f,int32_t o,int32_t r,int32_t a)
{
	// if(f<=0) return 0;
	
	// double rv;
	// rv=fmod(o,r/f);
	// rv*=pow(10,-2);
	// fprintf(fer,"sw rv:%i\n",(int32_t)(rv*a));
	// return (int32_t)rv*a;
	double rv=fmod((double)o,((double)r/f))/((double)r/f)*(double)a;
	return (int32_t)rv;
}

int main(int argc,char **argv)
{
	//16 bit integer 44.1kHz
	//16 bit signed int range = ( -32,768 to 32,767 )
	
	//dynamic buffering vs static (per sec)
	//16 bit / 2 bytes per sample @ 44.1k samples per sec = 705.6kB
	
	uint32_t samplerate=44100;
	uint32_t samples=samplerate;
	uint8_t bitdepth=16;
	double f=440;
	uint32_t a=900;
	
	fer=fopen("log.txt","w");
	if(!fer) return 3;
	
	if(argc>1)
	{
		for(int i=0;i<argc;i++)
		{
			if(argc>i)
			{
			     if(strcmp(argv[i],"-f")==0)f=atof(argv[i+1]);
			else if(strcmp(argv[i],"-b")==0)bitdepth=atoi(argv[i+1]);
			else if(strcmp(argv[i],"-r")==0)samplerate=atoi(argv[i+1]);
			else if(strcmp(argv[i],"-s")==0)samples=atoi(argv[i+1]);
			else if(strcmp(argv[i],"-a")==0)a=atoi(argv[i+1]);
			}
			
		}
	}
	else
	{
		printf("%s [fbrsa]\n",*argv);
		return 1;
	}
	
	int16_t *b=malloc(sizeof(int16_t)*samples);
	if(!b)printf("fail\n");
	
	for(int i=0;i<samples;i++)
	{
		b[i]=sw(f,i,samplerate,a);
		fprintf(fer,"b:%i\n",b[i]);
		// b[i]+=sq(raisesemi(f,7),i,samplerate,700.0);
		// b[i]/=2;
	}
	
	fwrite(b,sizeof(int16_t),samples,stdout); //sizeof(uint16_t)==2 (bytes)!
	
	free(b);
	fclose(fer);
	return 0;
}
