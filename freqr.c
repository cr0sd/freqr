#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<inttypes.h>
#include<string.h>

#if defined(COMPILE_FOR_WINDOWS) || defined(_WIN32)
#	ifndef COMPILE_FOR_WINDOWS
#		define COMPILE_FOR_WINDOWS
#	endif
#	include<io.h>
#	include<fcntl.h>
#endif

#define SEMITC pow(2,1/12.0)

#define raisesemi(f,n) (f*pow(SEMITC,(n)))
// #define sq(f,o,s,a) (o%(s/f)<(s/f)/2?a:-a)
#define pi 3.14159265

enum {SN,SQ,SW,TR,NS};
char szFn[5][3]={"sn","sq","sw","tr","ns"};
//FILE *fer;

/********
 * sn(f,o,r,a)
 * Generate sine wave
 * sn(x,f) = sin( (2*pi)/period * x ) * amplitude
 * 
 ********/
int32_t sn(double f,double o,double r,double a)
{
	return sin(((2.0L*pi)/(r/f))*o)*(a/2.0L);
}
/********
 * sq(f,o,r,a)
 * Generate single 50% duty cycle square wave 
 * at frequency f, offset o, samplerate r, and
 * (positive) amplitude a
 * 
 ********/
int32_t sq(double f,int32_t o,int32_t r,int32_t a)
{
	return o%(int32_t)(r/f)<(int32_t)(r/f)/2?(a/2.0L):-(a/2.0L);
}

int32_t tr(double f,int32_t o,int32_t r,int32_t a)
{
	// return 2*a/3.1415926f*asin(sin(2*3.1415926f/((r/f)*o)));
	// return ((a*((r/f)-(int32_t)fabs(o%(int32_t)(2*(r/f))-(r/f)) ))/(r/f))-(a/2);
	return ((a*((r/f/2.0L)-(int32_t)fabs((o+(int32_t)(r/f/4.0L))%(int32_t)(2*(r/f/2.0L))-(r/f/2.0L)) ))/(r/f/2.0L))-(a/2.0L);
}

int32_t sw(double f,int32_t o,int32_t r,int32_t a)
{
	return fmod((double)(o+(int32_t)(r/f/2.0L)),((double)r/f))/((double)r/f)*(double)a-(a/2.0L);
}

int32_t ns(double f,int32_t o,int32_t r,int32_t a)
{
	return (double)a/2.0L-fmod(rand(),a);
}

int main(int argc,char **argv)
{
	//16 bit integer 44.1kHz
	//16 bit signed int range = ( -32,768 to 32,767 )

	//dynamic buffering vs static (per sec)
	//16 bit / 2 bytes per sample @ 44.1k samples per sec = 705.6kB

	#ifdef COMPILE_FOR_WINDOWS
 	setmode(fileno(stdout),O_BINARY); //only on Windows
	#endif

	//FILE *output_file=fopen("raw.dat","wb");
	FILE*output_file=stdout;

	uint32_t samplerate=44100;
	uint32_t samples=samplerate;
	//uint8_t bitdepth=16;
	double f=440;
	int32_t a=900;
	uint8_t fn=0;

	//fer=fopen("log.txt","w");
	//if(!fer) return 3;

	if(argc>1)
	{
		for(int i=0;i<argc;i++)
		{
			if(argc>i)
			{
				if(strcmp(argv[i],"-f")==0)f=atof(argv[i+1]);
				//else if(strcmp(argv[i],"-b")==0)bitdepth=atoi(argv[i+1]);
				else if(strcmp(argv[i],"-r")==0)samplerate=atoi(argv[i+1]);
				else if(strcmp(argv[i],"-s")==0)samples=atoi(argv[i+1]);
				else if(strcmp(argv[i],"-a")==0)a=atoi(argv[i+1]);
				else if(strcmp(argv[i],"-w")==0)
				{
					for(int j=0;j<5;j++)
						if(strcmp(argv[i+1],szFn[j])==0)
							fn=j;
				}
				else if(strcmp(argv[i],"-o")==0)
				{
					if(output_file!=stdout)
						printf("%s: warning: output file already specified",*argv);
					else
						output_file=fopen(argv[i+1],"wb");
				}
			}

		}
	}
	else
	{
		printf("Usage: %s [-f] [-r] [-s] [-a] [-o] [-w {sn|sq|tr|sw|ns}]\n",*argv);
		puts("\t-f FREQ\t\tFrequency");
		puts("\t-r SAMPLERATE\tSample rate(e.g., -s 44100)");
		puts("\t-s NUM_SAMPLES\tNumber of samples");
		puts("\t-a AMPLITUDE\tAmplitude (16-bit int)");
		puts("\t-w WAVEFORM\tOne of: sn,sq,tr,sw,ns");
		puts("\t-o OUTPUTFILE\tSpecify file to output to");
		return 1;
	}


	//fprintf(fer,"fn:%s\n",szFn[fn]);

	int16_t *b=malloc(sizeof(int16_t)*samples);
	if(!b)printf("fail\n");

	for(int i=0;i<samples;i++)
	{
		switch(fn)
		{
		case SN:
		default:
			b[i]=sn(f,i,samplerate,a);
			break;
		case SQ:
			b[i]=sq(f,i,samplerate,a);
			break;
		case SW:
			b[i]=sw(f,i,samplerate,a);
			break;
		case NS:
			b[i]=ns(f,i,samplerate,a);
			break;
		case TR:
			b[i]=tr(f,i,samplerate,a);
		}
		//fprintf(fer,"b:%i\n",b[i]);

		// b[i]+=sq(raisesemi(f,7),i,samplerate,700.0);
		// b[i]/=2;
	}


	#ifdef COMPILE_FOR_WINDOWS
 	fwrite(b,sizeof(int16_t),samples,stdout); //sizeof(uint16_t)==2 (bytes)!
	#else
	fwrite(b,sizeof(int16_t),samples,output_file);
	#endif

	free(b);
	//fclose(fer);
	fclose(output_file);
	return 0;
}
