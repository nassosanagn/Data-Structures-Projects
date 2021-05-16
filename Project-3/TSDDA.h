#ifndef __TSDDA__
#define __TSDDA__
#include <stdio.h>

typedef int keyType; /* integer key for airport */

typedef struct KeyIndex{
        keyType key;
        int arrayIndex;
} TStoixeiouDDA;

int TSDDA_setValue (TStoixeiouDDA *target, TStoixeiouDDA source);

int TSDDA_setKey(keyType * key, keyType Val);

int TSDDA_setIndex(int * Index, int Val);

/* basikes sygkriseis gia xrhsh sthn eisagcgh-diagarfh-anazhthsh se DDA */
int TSDDA_iso(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_mikrotero(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_megalytero(TStoixeiouDDA, TStoixeiouDDA);

/* symplhrvmatikes sygkriseis */
int TSDDA_mikrotero_iso(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_megalytero_iso(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_diaforo(TStoixeiouDDA, TStoixeiouDDA);
#endif
