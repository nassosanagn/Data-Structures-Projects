/*************************************************************************
Arxeio ylopoihshs	: main.c
Full Name	:  Athanasios Anagnostopoulos
AM    :   sdi1800006
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Session.h"
#define MAX_OPTIONS 16

void print_options();
int get_option();

int main(int argc, char *argv[]) {

	InfoSessionPtr 	MySession1 = NULL;
	InfoSessionPtr 	MySession2 = NULL;
	InfoSessionPtr CurrSession = NULL;

	/* The default session is 1 */
	int Session = 1;
	int option,check;
	char address[100];

	do{

	option = get_option();

	switch (option){

	case 1:

		printf("\nGive the address of the first site: ");
		fgets(address,sizeof(address),stdin);

		CurrSession = SessionNew(address);
		printf("\nSession created.\n");
		break;

	case 2:

		SessionNewTab(CurrSession);
		printf("\nNew tab created.\n");
		break;

	case 3:

		SessionTabShow(CurrSession);
		break;

	case 4:

		SessionTabNext(CurrSession);
		printf("\nCurrTab moved successfully to the next tab.\n");
		break;

	case 5:

		SessionTabPrev(CurrSession);
		printf("\nCurrTab moved successfully to the previous tab.\n");
		break;

	case 6:

		check = SessionTabMoveLeft(CurrSession);

		if(check)
			printf("\nCurrent tab moved left.\n");
		else
			printf("\nCurrent Tab is already the first tab.\n");
		break;

	case 7:

		check = SessionTabMoveRight(CurrSession);

		if(check)
			printf("\nCurrent tab moved right.\n");
		else
			printf("\nCurrent Tab is already at the end.\n");
		break;

	case 8:

		printf("\nGive a new opening address: ");
		fgets(address,sizeof(address),stdin);

		SessionNewOpeningAddress(CurrSession,address);
		break;

	case 9:

		SessionShowOpeningAddress(CurrSession);
		break;

	case 10:

		check = SessionSiteNext(CurrSession);

		if(check)
			printf("\nCurrSite moved successfully to the next site.\n");
		else
			printf("\nIt's the last site node.\n");
		break;

	case 11:

		check = SessionSitePrev(CurrSession);

		if (check)
			printf("\nCurrSite moved successfully to the previous site.\n");
		else
			printf("\nIt's the first site node.\n");
		break;

	case 12:

		SessionSiteShow(CurrSession);
		break;

	case 13:

		check = SessionTabClose(CurrSession);

		if (!check)
			printf("\nTabNode deleted.\n");
		else{
				printf("\nThe last TabNode and the InfoSession got deleted.\n");
				CurrSession =	NULL;
			}
		break;

	case 14:

		check = SessionClose(CurrSession);
		CurrSession = NULL;

		if (check)
			printf("\nSession Deleted.\n");
		else
			fprintf(stderr,"\nAn error has occured while deleting the Session.\n");

		break;

	case 15:

		printf("\nGive the new address of the site: ");
		fgets(address,sizeof(address),stdin);

		check = SessionNewAddress(CurrSession,address);

		if(check)
			printf("\nAdded a new site address.\n");
		break;

	case 16:

		/* Enallagh metaksy twn Sessions */

		if (Session == 1){
				MySession1  = CurrSession;
				CurrSession = MySession2;
				Session = 2;
				printf("\nSwitched successfully to Session2.\n");
		}else{
				MySession2  = CurrSession;
				CurrSession = MySession1;
				Session = 1;
				printf("\nSwitched successfully to Session1.\n");
			}

		break;

	}

	}while (option);

	return 0;
}


void print_options(){

	printf("\n");
	printf("0. Exit\n");
	printf("1. Create a new session\n");
	printf("2. Create a new tab\n");
	printf("3. Show the current site\n");
	printf("4. Go to the next tab node\n");
	printf("5. Go to the previous tab node\n");
	printf("6. Move the currrent tab to the left\n");
	printf("7. Move the currrent tab to the right\n");
	printf("8. Change the opening site\n");
	printf("9. Show the opening site\n");
	printf("10. Go to the next site node\n");
	printf("11. Go to the previous site node\n");
	printf("12. Show the current site\n");
	printf("13. Close the current tab\n");
	printf("14. Close the session\n");
	printf("15. Give a new site address\n");
	printf("16. Switch between sessions\n\n");
	printf("Enter your input [0-%d]: ", MAX_OPTIONS);
}

int get_option(){

	int option = -1;
	char buffer[80];

	while (option < 0 || option > MAX_OPTIONS){

		print_options();
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d" ,&option);
	}

	return option;
}
