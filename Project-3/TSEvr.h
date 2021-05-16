#ifndef __TSEvr__
#define __TSEvr__

#include <stdio.h>


typedef struct data {

/*  members for airport data in array */

    int AirportID;
    char Name[100];
    char City[100];
    char Country[100];
    char IATA [10];
    char ICAO [10];
    
    int AirportIn;				/* Aerodromio afikseon */
    int AirportOut;				/* Aerodromio anaxwrhsewn */

} TStoixeiouEvr;

int TSEvr_setValue (TStoixeiouEvr *target, TStoixeiouEvr source);

int TSEvr_readValue (FILE *from,  TStoixeiouEvr *Elem);

int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem);

#endif
