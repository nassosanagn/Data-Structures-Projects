#include "TSEvr.h"
#include <string.h>

int TSEvr_setValue (TStoixeiouEvr *target, TStoixeiouEvr source){

	/* Enhmerwsh twn stoixeiwn twn aerodromiwn ston pinaka */

	(*target).AirportID = source.AirportID;
	strcpy((*target).Name, source.Name);
	strcpy((*target).City, source.City);
	strcpy((*target).Country, source.Country);
	strcpy((*target).IATA, source.IATA);
	strcpy((*target).ICAO, source.ICAO);

	/* Arxikopoihsh metrhtwn anaxwrhsewn kai afiksewn */
  
	(*target).AirportIn  = 0;
	(*target).AirportOut = 0;
	
	return 1;
}

int TSEvr_readValue (FILE *from,  TStoixeiouEvr *Elem){
	
	/* H synarthsh diabazei ta stoixeia apo to AirportsRandom kai AirportsSorted 
	kai epistrefei 1 an petyxe h 0 an eftase sto telos toy file */
	
	int i;
	char ch;
	char buffer[80];
	
	/* Antigrafh toy AirportID */

	ch = fgetc(from);
    if (feof(from))
    	return 0;

	for (i = 0; ch != ';' ; i++){
		buffer[i] = ch;
		ch = fgetc(from);
	}

	buffer[i] = '\0';
	(*Elem).AirportID = atoi(buffer);

	/* Antigrafh toy onomatos aerodromioy */

	for (i = 0; ((ch = fgetc(from)) != ';'); i++)
		(*Elem).Name[i] = ch;
			
	(*Elem).Name[i] = '\0';
	
	/* Antigrafh polhs */
	
	for(i = 0; ((ch = fgetc(from)) != ';'); i++)
		(*Elem).City[i] = ch;
			
	(*Elem).City[i] = '\0';
	
	/* Antigrafh xwras */
		
	for(i = 0; ((ch = fgetc(from)) != ';'); i++)
		(*Elem).Country[i] = ch;

	(*Elem).Country[i] = '\0';
	
	/* Antigrafh kwdikoy IATA */
		
	for(i = 0;((ch = fgetc(from)) != ';'); i++)
		(*Elem).IATA[i] = ch;
	
	(*Elem).IATA[i] = '\0';
	
	/* Antigrafh kwdikoy ICAO */
		
	for(i = 0; ((ch = fgetc(from)) != '\n'); i++)
		(*Elem).ICAO[i] = ch;
			
	(*Elem).ICAO[i] = '\0';
	
	return 1;
}

int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem){

	fprintf(to,"Key: %5d  ",Elem.AirportID);
	fprintf(to,"Afikseis: %4d  ",Elem.AirportIn);
	fprintf(to,"Anaxwrhseis: %4d \n",Elem.AirportOut);
	
	return 1;

}

