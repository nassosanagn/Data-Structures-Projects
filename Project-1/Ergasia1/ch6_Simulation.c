/*************************************************
Arxeio ylopoihshs	: ch6_Simulation.c
Syggrafeas			: Y. Cotronis 07/03/2016
Skopos				: Ylopoihsh ouras prosomoiwshs
Revision 			:  <Athanasios Anagnostopoulos - 21/3/19>
AM          :   sdi1800006
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ch6_QArray.h"
#include "TStoixeiouOuras.h"
#include "Controller.h"

#define SIZE 5

struct{

	TOuras Oura;							/*oura pelatwn-aytokinhtvn */
	TController Controller;		/* ATD gia ton elength diodion */

}Pinakas[SIZE];

int main(void){

	float			pithanotita_afiksis; 		/*pi8anothta afikshs*/
	unsigned int	xronos_eksipiretisis;		/*xronos e3yphrethshs enos pelath*/
	unsigned int min_xronos;
	unsigned int max_xronos;
	unsigned int	xronos_prosomoiosis; 	/*synolikos xronos prosomoiwshs*/
	unsigned int	xronos;				 	/*roloi prosomoiwshs*/
	unsigned int	xronos_anamonis;	 /*synolikos xronos anamonhs*/
	TSOuras		Pelatis;		 				/* o pelaths sthn oyra*/
	float			mesos_xronos;		 	/*mesos xronos anamonhs tvn pelatvn*/
	float			randomAfixi;
	time_t			t;
	int sum = 0;			/* Synolo aytokinitwn poy eksipyreth8hkan */
	int i,tmp;
	int thesi;		/* H thesi ths ouras poy kathe fora exei ta ligotera aytokinhta */
	int min;		/* O elaxistos arithmos aytokinhtwn sthn oyra */

	printf("Dwste units of time prosomoiwshs (0 <=), pi8anothta afikshs in unit of time (0,1) kai ta oria tou xronou e3yphrethshs (>=1) in unit of times )\n");
	scanf("%u %f %u %u",&xronos_prosomoiosis,&pithanotita_afiksis,&min_xronos,&max_xronos);
	getchar();
	printf("\nH prosomoiwsh 8a diarkesei %4u units of time.\n",xronos_prosomoiosis);
	printf("H pi8anothta afikshs pelath se ena unit of time einai: %4.2f.\n",pithanotita_afiksis);
	printf("H diarkeia e3yphrethshs enos pelath den einai sta9erh kai einai metaksy [%u,%u] units of time.\n",min_xronos,max_xronos);

	for(i = 0 ; i < SIZE ; i++){			/* Arxikopoihsh ouras kai elegkth diodion */

		OuraDimiourgia(&(Pinakas[i].Oura));
		ControllerDimiourgia(&(Pinakas[i].Controller));
	}

	xronos = 0;
	xronos_anamonis = 0;
	srand(time(&t));

	while( xronos < xronos_prosomoiosis ){

		/* Pelatis- Aytokinhto  */

		randomAfixi = (float)rand()/(float)RAND_MAX;

		xronos_eksipiretisis = min_xronos + rand() % (max_xronos + 1 - min_xronos);		/* Prosdiorizei ton tyxaio xrono eksypiretisis mesa sta oria poy do8hkan */
		PelatisSetXronoEksipiretisis(&Pelatis,xronos_eksipiretisis);

		if ( randomAfixi < pithanotita_afiksis ){

			min = OuraGetSize(Pinakas[0].Oura);				/* Anazhthsh oyras me ta ligotera aytokinhta */
			thesi = 0;

			for(i = 1 ; i < SIZE ; i++){

				tmp = OuraGetSize(Pinakas[i].Oura);
				if(tmp < min){
						min = tmp;
						thesi = i;
				}
			}

			PelatisSetXronoEisodou(&Pelatis, xronos);
			if (!OuraProsthesi(&(Pinakas[thesi].Oura), Pelatis)){
                  printf("H oyra einai mikrh! H prosomoivsh stamataei \n");
                  getchar();
                  return 0;
        	};
    	};

    	/* Tamias-Elegxos */

		if ( ControllerFree(Pinakas[thesi].Controller))	/*eley8eros tamias*/

			if (!OuraKeni(Pinakas[thesi].Oura)){			/*yparxei pelaths*/

				OuraApomakrynsh(&(Pinakas[thesi].Oura),&Pelatis);		/*phgainei sto tamio*/
				xronos_anamonis += xronos - PelatisGetXronoEisodou(Pelatis);	/*ypologismos xronoy paramonhs sthn oura*/

				/* printf("Time is %d Time out %d\n", xronos, PelatisGetXronoEisodou(Pelatis)); */

				ControllerNewCustomer(&(Pinakas[thesi].Controller));
				ControllerSetXrono(&(Pinakas[thesi].Controller),PelatisGetXronoEksipiretisis(Pelatis) -1); /* kallyptei to trexon unit time */

			}else ControllerNoWork(&(Pinakas[thesi].Controller));

		else ControllerBusy(&(Pinakas[thesi].Controller));		/*o tamias apasxolhmenos me pelath */


		xronos++; /*o xronos prosomoivshs ay3anetai kata 1 unit of time*/
	} /*while( xronos < xronos_prosomoiosis )*/

	for(i = 0 ; i < SIZE ; i++)				/* 	To synolo ton pelatwn poy eksyphrethse kathe elegxths prostithetai gia na brethei to synoliko plhthos pelatwn poy eksyphretithikan*/
		sum += ControllerGetArithmosPelatwn(Pinakas[i].Controller);

	if (sum == 0)
		mesos_xronos = 0.0;
	else
		mesos_xronos = ((float)xronos_anamonis)/((float)sum);

		printf("\nSynolo eksyphreth8hkan %d pelates\n",sum);
		printf("O mesos xronos anamonhs htan %4.2f units of time.\n\n",mesos_xronos);


		for(i = 0 ; i < SIZE ; i++){			/*	 Emfanish Apotelesmatwn	 */

			printf("O %dos tamias eksyphretise %d pelates.\n",i+1, ControllerGetArithmosPelatwn(Pinakas[i].Controller));
			printf("O %dos tamias htan apasxolhmenos gia %d units of time.\n",i+1, ControllerGetBusyXronos(Pinakas[i].Controller));
			printf("O %dos tamias htan adranhs gia %d units of time.\n",i+1, ControllerGetInactiveXronos(Pinakas[i].Controller));
			printf("Stin %dh oura exoyn meinei %d autokinhta.\n",i+1,OuraGetSize(Pinakas[i].Oura));

			printf("O ari8mos ton autokinitwn pou mphkan stin %dh oura einai: %d.\n",i+1,GetCountIn(Pinakas[i].Oura));
			printf("O ari8mos ton autokinitwn pou bghkan apo tin %dh oura einai: %d.\n",i+1,GetCountOut(Pinakas[i].Oura));
			printf("Stin %dh oura den eksyphreth8hkan %d pelates.\n\n",i+1,GetCountIn(Pinakas[i].Oura) - GetCountOut(Pinakas[i].Oura));
		}

getchar();
return 0;
}
