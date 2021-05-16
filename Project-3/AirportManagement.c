/************************************************************************
Programma pelaths	: AirportManagement.c
Syggrafeas			:
Skopos				: skeleton main for askhsh 3
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>  

#include "TSEvr.h"
#include "TSDDA.h"
#include "Evretirio.h"

#define Simple 1

#define MAXSIZE 7200

int ReadAll_airports(EvrPtr E,FILE *from);
int Read_routes(EvrPtr E,FILE *out);

int main(int argc, char *argv[]){

	#if (Simple)
		char text1[30] = "OUTPUTRandomBST.txt";
		char text2[30] = "OUTPUTSortedBST.txt";
	#else
		char text1[30] = "OUTPUTRandomAVL.txt";
		char text2[30] = "OUTPUTSortedAVL.txt";
	#endif
	
	int i,counter = 0;
	FILE *from;
	FILE *out;
	EvrPtr E;

	/* Mia epanalhspsh gia airportsRandom kai mia gia airportsSorted */
	
	for(i = 0; i < 2; i++){
		
		/* BHMA 1 */
		
		E = EvrConstruct(MAXSIZE);
		
		/* BHMA 2 */
		
		if (i == 0)		
			from = fopen("airportsWinRandom.txt","r");
		else
			from = fopen("airportsWinSorted.txt","r");
			
		if (!ReadAll_airports(E,from))
			exit(0);
			
		fclose(from);
		
		/* BHMA 3 */
		
		if (i == 0)		
			out = fopen(text1,"w");
		else
			out = fopen(text2,"w");
			
		Read_routes(E,out); 
		
		/* BHMA 4 */
	
		Evr_PrintAll(E,out,&counter); 
		fclose(out);
		
		/* BHMA 5 */
		EvrDestruct(&E);	
	}
				
	getchar();
	return 0;
}

int ReadAll_airports(EvrPtr E,FILE *from){
	
	TStoixeiouEvr Elem;
	int i,x, N = 9;
	int error = 0;
	
	clock_t c1, c2;
    double ratio = 1./CLOCKS_PER_SEC;

	LARGE_INTEGER frequency;
    LARGE_INTEGER t1, t2,t3;
    double elapsedTime;
    
    c1 = clock();
    QueryPerformanceFrequency(&frequency);
   	QueryPerformanceCounter(&t1);
   	
	x = pow(2,N) - 1;
	
	for(i = 0; i < MAXSIZE ; i++){
		
			
		/* Epistrefei 1 an petyxe, alliws epistrefei 0 an eftase sto telos toy file */
		
		if(!TSEvr_readValue(from,&Elem))
			break;
		
		error = EvrInsert(E,Elem);
				
		if (error){
			fprintf(stderr,"Error while reading airports data. \n");	
			return 0;	
		} 
		
		if (x == GetStoixeia(E)){
			
			QueryPerformanceCounter(&t2);
			elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
			
			printf("Xronos eisagwghs meta apo 2^%2d-1 stoixeia: %g msec\n", N,elapsedTime);
						
			N++;
			x = pow(2,N) - 1;
		}
	}
	
	c2 = clock();
	
	printf("\nOlikos arithmos stoixeiwn : %d \n",GetStoixeia(E));
	printf("Synolikos xronos eisagwghs: %g seconds\n\n",ratio*(long)c2 - ratio*(long)c1);
	
	return 1;
}

int Read_routes(EvrPtr E,FILE *out){

	FILE *file;
	keyType key;
	int i,j,k,InOut,found = 0;
	int telos = 0, syndeseis = 0;
	int airfound = 0, airnotfound = 0;
	char ch, buffer[80];
	double mo_anazitisis;
	
	LARGE_INTEGER frequency;        /* ticks per second */
    LARGE_INTEGER t1, t2;           /* ticks */
    double elapsedTime;
    
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&t1);
		
	file = fopen("routesWin.txt", "r");
	
	for (k = 0 ; k < 68000 ; k++){
		
		if (telos)
			break;
		
		syndeseis++;
		
		for(j = 0; j < 9 ;j++){
			
			ch = fgetc(file);
	    	if(telos)
				break;

			if(j == 8){
		
				for(i = 0 ; ch != '\n' ; i++){
					
					buffer[i] = ch;
					ch = fgetc(file);
		
					if (feof(file)){
						telos = 1;
						break;
					}			
				}
				buffer[i] = '\0';
				break;	
			}		
			
			for (i = 0 ; ch != ';' ; i++){
				buffer[i] = ch;
				ch = fgetc(file);
			}
			
			buffer[i] = '\0';
			
			/* Dhladh einai sto Source airport,kai ara aykshse tis anaxwrhseis */
			
			 if(j == 3){
			 	
				InOut = 0;
				key = atoi(buffer);
				EvrSearch(E,key,InOut,&found);
				
				if (found)
					airfound++;
				else
					airnotfound++;	
			 }
				
			/* Dhladh einai sto Destination airport,kai ara aykshse tis afikseis */
			
			 if(j == 5){
			 	
				InOut = 1;
				key = atoi(buffer);
				EvrSearch(E,key,InOut,&found);
				
				if (found)
					airfound++;
				else
					airnotfound++;	
			}	
		}
	}
	
	fclose(file);

	QueryPerformanceCounter(&t2);
	
    elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	mo_anazitisis = elapsedTime / ((double)(airfound + airnotfound));
	
	fprintf(out,"Syndeseis:   %d \n", syndeseis);
	fprintf(out,"Brethhkan:     %d \n", airfound);
	fprintf(out,"Den brethhkan: %d \n", airnotfound);
	fprintf(out,"Mo anazhthshs: %f msec \n", mo_anazitisis);
	fprintf(out,"Synolikos xronos gia thn enhmerwsh: %g msec \n\n",elapsedTime);
	
	return 1;
}
