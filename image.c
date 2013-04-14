#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define BI_RGB 0

#pragma pack(push,1)
typedef struct bitmapFileHeader{
   unsigned short int bfType;				
   unsigned int bfSize;					   
   unsigned short int bfReserved1, bfReserved2;
   unsigned int bfOffBits;					
} BITMAPFILEHEADER;

typedef struct bitmapInfoHeader{
   unsigned int biSize;			   
   int biWidth, biHeight;				
   unsigned short int biPlanes;	   
   unsigned short int biBitCount;		 
   unsigned int biCompression;		
   unsigned int biSizeImage;		 
   int biXPelsPerMeter, biYPelsPerMeter;	 
   unsigned int biClrUsed;		   
   unsigned int biClrImportant;   
} BITMAPINFOHEADER;

typedef struct colourIndex{
   unsigned char r,g,b,junk;
} COLOURINDEX;

#pragma pack(pop)

void convert(uint8_t image[144][196], char* outfile){
	int x=144;
	int y=196;
	int rowsize = (24*x+31)/32 * 4;
	int i,j;
//	printf("%d\n", rowsize);

	BITMAPFILEHEADER hdr; 
	hdr.bfType = 0x4d42;
	hdr.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + rowsize*y;
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	BITMAPINFOHEADER info;
	info.biSize=sizeof(BITMAPINFOHEADER);
	info.biWidth = x;
	info.biHeight = y;
	info.biPlanes = 1;
	info.biBitCount = 24;
	info.biCompression = BI_RGB;
	info.biSizeImage = rowsize * y;
	info.biXPelsPerMeter = 7200;
	info.biYPelsPerMeter = 7200;
	info.biClrUsed = 0;
	info.biClrImportant;

	unsigned char *data = malloc(rowsize*y);
	FILE* wf = fopen(outfile,"w");

	for(i=0; i < y; i++){
		for(j=0; j < x; j++){
			int v = image[j][i]=='1'?255:0;
			data[i*rowsize + j*3] = v;
			data[i*rowsize + j*3+1] = v;
			data[i*rowsize + j*3+2] = v;
		}
	}

	fwrite(&hdr,sizeof(hdr),1,wf);
	fwrite(&info,sizeof(info),1,wf);
	fwrite(data,rowsize*y,1,wf);	

	fclose(wf);
	free(data);
}

