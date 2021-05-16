#include "Evretirio.h"
#include <string.h>
#include <windows.h>

#define Simple 1	   /* 0 for AVL - any Evr integer for Simple  */

/* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres - mporeite na xrhsimopoihsete
 thn  domh #if ... #else ...#endif gia na diaforopihsete tis dyo ylopoihseis  */

#if (Simple)
#include "BST/ch8_BSTpointer.h"         /* gia Simple Ylopoihsh */
#else
#include "AVL/ch8_AVLpointer.h"     /* gia AVL Ylopoihsh */
#endif

/* H synarthsh GetStoixeia epistrefei to E->Index gia na gnwrizei h main posa stoixeia exoyn eisaxthei */

int GetStoixeia(EvrPtr E);
void Endodiataksi(EvrPtr E, FILE *out, typos_deikti riza, int *counter);

struct EvrNode{
	
    TStoixeiouEvr *DataArray;    /* array of size MaxSize */
    int Index;                  /* index of first available element in array */
    typos_deikti TreeRoot;     /* Root of DDA */
    
} EvrNode;

EvrPtr EvrConstruct(int MaxSize){

  /* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres -
  mporeite na xrhsimopoihsete thn  domh #if ... #else ...#endif */

   EvrPtr E;
   typos_deikti TreeRoot;

   E = malloc(sizeof(struct EvrNode));

  #if (Simple)
    printf("use simple BST\n");
    Tree_dimiourgia(&TreeRoot);
  #else
    printf("use AVL BST\n");
	AVLTree_dimiourgia(&TreeRoot);
  #endif

  E->DataArray = malloc(MaxSize * sizeof(TStoixeiouEvr));
  E->TreeRoot = TreeRoot;
  E->Index = 0;
  
  return E;
}

int EvrInsert(EvrPtr E, TStoixeiouEvr Data){

  int error = 0;
  int ypsilotero;
  TStoixeiouDDA temp;
  
  /* Antigrafh stoixeiwn aerodromioy ston pinaka */
  
  TSEvr_setValue(&(E->DataArray[E->Index]),Data);
  
  /* Enhmerwsh kai eisagwgh key kai theshs toy pinaka sto dyadiko dentro */
    
  temp.key = E->DataArray[E->Index].AirportID;
  temp.arrayIndex = E->Index;

  #if (Simple)
	Tree_eisagogi(&(E->TreeRoot),temp,&error);
  #else
	AVLTree_eisagogi(&(E->TreeRoot),temp,&ypsilotero,&error);
  #endif
  
  E->Index++;

  return error;
}

int EvrSearch(EvrPtr E, keyType key, int InOut, int * found){

	TStoixeiouDDA stoixeio;
	typos_deikti deiktis;
	
	stoixeio.key = key;
	
	#if (Simple)	
		Tree_anazitisi(E->TreeRoot,stoixeio,&deiktis,found);
		Tree_periexomeno(deiktis,&stoixeio);
	#else
		AVLTree_anazitisi(E->TreeRoot,stoixeio,&deiktis,found);
		AVLTree_periexomeno(deiktis,&stoixeio);
	#endif
	
	if (*found)
		if (InOut)
			E->DataArray[stoixeio.arrayIndex].AirportIn++; 		
		else
			E->DataArray[stoixeio.arrayIndex].AirportOut++;
		
	return 1;
}


int Evr_PrintAll(EvrPtr E, FILE *out, int * counter){
	
	typos_deikti a = E->TreeRoot;
	TStoixeiouDDA stoixeio;
	
	LARGE_INTEGER frequency;        /* ticks per second */
    LARGE_INTEGER t1, t2;           /* ticks */
    double elapsedTime;	

    QueryPerformanceFrequency(&frequency);	 /* get ticks per second */
    QueryPerformanceCounter(&t1);			/* start timer */
    
    *counter = 0;
	
	/* endo-diadromh - use recursion with apaidi-depaidi */

	Endodiataksi(E,out,a,counter);
	
    QueryPerformanceCounter(&t2);		/* stop timer */
    
    /* compute and print the elapsed time in millisec */
    
    elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    
    fprintf(out,"\nSynolikos xronos gia thn ektypwsh: %g msec \n", elapsedTime);
    fprintf(out,"Arithmos stoixeiwn poy ektypwthikan: %d \n\n",*counter);
}

int EvrDestruct(EvrPtr *E){

  #if (Simple)
	Tree_katastrofi(&((*E)->TreeRoot));
  #else
	AVLTree_katastrofi(&((*E)->TreeRoot));
  #endif
  
  free((*E)->DataArray);
  free(*E);
  
  E = NULL;
  return 1;
}

void Endodiataksi(EvrPtr E, FILE *out, typos_deikti riza, int *counter){
	
	TStoixeiouDDA stoixeio;
	
	#if (Simple)
		
		if (!Tree_keno(riza)){
			
		Endodiataksi(E,out,Tree_apaidi(riza),counter);
		
		Tree_periexomeno(riza,&stoixeio);

		fprintf(out,"Key: %5d  ",E->DataArray[stoixeio.arrayIndex].AirportID);
		fprintf(out,"Afikseis: %4d  ",E->DataArray[stoixeio.arrayIndex].AirportIn);
		fprintf(out,"Anaxwrhseis: %4d \n",E->DataArray[stoixeio.arrayIndex].AirportOut);
		
		*counter = *counter + 3;		/* Giati kathe fora ektypwnei 3 stoixeia */
				
		Endodiataksi(E,out,Tree_dpaidi(riza),counter); 	
		}		
	#else
	
		if (!AVLTree_keno(riza)){
			
		Endodiataksi(E,out, AVLTree_apaidi(riza),counter);
		
		AVLTree_periexomeno(riza,&stoixeio);
		TSEvr_writeValue(out , E->DataArray[stoixeio.arrayIndex]);
		
		*counter = *counter + 3;
		
		Endodiataksi(E,out, AVLTree_dpaidi(riza),counter);
		}
	#endif			
}

int GetStoixeia(EvrPtr E){
	
	return E->Index;
}
