// Radon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math.h"
#include "windows.h"

#define MSIZE 512

int _tmain(int argc, _TCHAR* argv[])
{
	int i,j;
	float k;

	int projsize=(int)(MSIZE*1.415+2);

	double d,count;
	float *data_in=(float*)malloc(sizeof(float)*MSIZE*MSIZE);
	float *x=(float*)malloc(sizeof(float)*MSIZE*MSIZE);
	float *y=(float*)malloc(sizeof(float)*MSIZE*MSIZE);
	float *x_r=(float*)malloc(sizeof(float)*MSIZE*MSIZE);
	float *y_r=(float*)malloc(sizeof(float)*MSIZE*MSIZE);
	float *Iproj=(float*)malloc(sizeof(float)*projsize*2);
	float *Icount=(float*)malloc(sizeof(float)*projsize*2);
	float *p_data_in,*p_x,*p_y,*p_x_r,*p_y_r;

	count=0;
	int t1=GetTickCount();
	p_data_in=data_in;
	p_x=x;
	p_y=y;
	for (i=0;i<MSIZE;i++)
	{
		for (j=0;j<MSIZE;j++)
		{
			*p_data_in=rand();
			*p_x=i;
			*p_y=j;
			p_data_in++;
			p_x++;
			p_y++;
		}
	}
	

	for(k=0;k<180;k+=1)
	{
		float sink,cosk,dist_min;
		int fx_r;
		sink=sin(k*3.1415926/180);
		cosk=cos(k*3.1415926/180);
		p_data_in=data_in;
		p_x=x;
		p_y=y;
		p_x_r=x_r;
		p_y_r=y_r;
		dist_min=1E9;

		for (i=0;i<projsize*2;i++)
		{
			*(Iproj+i)=0;
			*(Icount+i)=0;
		}

		for (i=0;i<MSIZE;i++)
		{
			for (j=0;j<MSIZE;j++)
			{
				*p_x_r=*p_x*cosk+*p_y*sink;
				fx_r=(int)floor(*p_x_r);
				//if(*p_x_r<dist_min)
				//	dist_min=*p_x_r;
				*(Iproj+fx_r+projsize)+=*p_data_in;
				(*(Icount+fx_r+projsize))=(*(Icount+fx_r+projsize))+1;
				p_x_r++;
				p_x++;
				p_data_in++;
			}
		}
	}
	int t2=GetTickCount();
	printf("time difference: %d %f\n",t2-t1,count);
	free(data_in);
	free(x);
	free(y);
	free(x_r);
	free(y_r);
	free(Iproj);
	free(Icount);
	return 0;
}

