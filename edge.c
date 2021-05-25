#include <stdio.h>
#include <stdlib.h>
#include "import.h"
#include <math.h>

int saveImage(FILE *,IMAGE *) ;

void edge(){
    FILE *fpIn,*fpOut ;
    IMAGE *imgIn=(IMAGE *)malloc(sizeof(IMAGE)) ;
    IMAGE *imgOut=(IMAGE *)malloc(sizeof(IMAGE)) ;
    int k,x,y,label,ret ;
    int R,R1,R2,R3 ;
    int G,G1,G2,G3 ;
    int B,B1,B2,B3 ;
    fpIn=fopen("Lancaster.bmp","r") ;
    if(fpIn==NULL){
        printf("エラー発生\n") ;
    }
    k=readImage(fpIn,imgIn) ;
    imgOut->width=imgIn->width ;
    imgOut->height=imgIn->height ;
    imgOut->depth=imgIn->depth ;
    imgOut->pixels=(PIXEL *)malloc(imgOut->height*imgOut->width*sizeof(PIXEL)) ;
    for(y=imgIn->height; y>=0; y--){
		for(x=0; x<=imgIn->width; x++){
            label=getLabel(x+1,y,imgIn->width) ;
            R=imgIn->pixels[label].r ;
            G=imgIn->pixels[label].g ;
            B=imgIn->pixels[label].b ;
            label=getLabel(x-1,y,imgIn->width) ;
            R1=imgIn->pixels[label].r ;
            G1=imgIn->pixels[label].g ;
            B1=imgIn->pixels[label].b ;
            label=getLabel(x,y+1,imgIn->width) ;
            R2=imgIn->pixels[label].r ;
            G2=imgIn->pixels[label].g ;
            B2=imgIn->pixels[label].b ;
            label=getLabel(x,y-1,imgIn->width) ;
            R3=imgIn->pixels[label].r ;
            G3=imgIn->pixels[label].g ;
            B3=imgIn->pixels[label].b ;
            R=sqrt(((R-R1)/2)*((R-R1)/2)+(((R2-R3)/2)*((R2-R3)/2))) ;
            G=sqrt(((G-G1)/2)*((G-G1)/2)+(((G2-G3)/2)*((G2-G3)/2))) ;
            B=sqrt(((B-B1)/2)*((B-B1)/2)+(((B2-B3)/2)*((B2-B3)/2))) ;
            if(x==0 || y==0){
                R=0 ;
                G=0 ;
                B=0 ;
            }
            if(x==(imgIn->width) || y==(imgIn->height)){
                R=0 ;
                G=0 ;
                B=0 ;
            }
			label=getLabel(x,y,imgIn->width) ;
			imgOut->pixels[label].r=255-R ;
			imgOut->pixels[label].g=255-G ;
			imgOut->pixels[label].b=255-B ;
		}
	}
    printf("Save data as a file, spiral2.bmp.\n");
	fpOut=fopen("Lancaster-edge.bmp","w") ;
    if(fpOut==NULL){
        printf("エラー発生\n") ;
    }
	printf("Save!\n");
	ret=saveImage(fpOut,imgOut);
	if(!ret){
		printf("ERROR -- could not write the image.") ;
	}
	printf("done.");
	fclose(fpIn);
    fclose(fpOut) ;
}
