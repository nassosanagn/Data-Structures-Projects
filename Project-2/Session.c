/*************************************************************************
Implementation File	: Session.c
Full Name	:  Athanasios Anagnostopoulos
AM    :   sdi1800006
**************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Session.h"

typedef struct TabNode *TabNodePtr;
typedef struct SiteNode *SiteNodePtr;

struct InfoSession {
	TabNodePtr FirstTab;
	TabNodePtr LastTab;
	TabNodePtr CurrTab;
	TabNodePtr AuxTab;
	char* 	  OpeningAddress;
};

struct TabNode {
	TabNodePtr PrevTab, NextTab;
	SiteNodePtr FirstSite;
	SiteNodePtr CurrSite;
};

struct SiteNode{
	SiteNodePtr PrevSite, NextSite;
	TabNodePtr UpTab;
	char *Address;
};


InfoSessionPtr SessionNew(char * OpeningAddress){

	InfoSessionPtr MySession;
	TabNodePtr	tabptr;
	SiteNodePtr	siteptr;

	MySession	= malloc(sizeof(struct InfoSession));
	tabptr 		= malloc(sizeof(struct TabNode));
	siteptr 	= malloc(sizeof(struct SiteNode));

	/* Elegxos gia to ti epestrepsan oi malloc */

	assert(MySession);
	assert(tabptr);
	assert(siteptr);

	MySession->FirstTab = tabptr;
	MySession->LastTab  = tabptr;
	MySession->CurrTab  = tabptr;
	MySession->AuxTab		= NULL;
	MySession->OpeningAddress = malloc(80);
	strcpy(MySession->OpeningAddress,OpeningAddress);

	/* Epeidh einai o prwtos komvos kai einai kyklika syndedemeni lista */
	/* to PrevTab kai to NextTab deixnoyn ston idio komvo arxika */
	
	tabptr->PrevTab 	= tabptr;
	tabptr->NextTab 	= tabptr;
	tabptr->FirstSite = siteptr;
	tabptr->CurrSite 	= siteptr;

	siteptr->PrevSite = NULL;
	siteptr->NextSite = NULL;
	siteptr->UpTab 		= tabptr;
	siteptr->Address 	= malloc(80);
	strcpy(siteptr->Address,MySession->OpeningAddress);

	return MySession;
}

void SessionNewTab(InfoSessionPtr Session){

	TabNodePtr tabptr;
	SiteNodePtr	siteptr;

	assert(Session);

	tabptr  = malloc(sizeof(struct TabNode));
	siteptr = malloc(sizeof(struct SiteNode));

	assert(tabptr);
	assert(siteptr);

	tabptr->PrevTab   = Session->LastTab;
	tabptr->NextTab   = Session->FirstTab;
	tabptr->FirstSite = siteptr;
	tabptr->CurrSite 	= siteptr;

	siteptr->PrevSite =	NULL;
	siteptr->NextSite = NULL;
	siteptr->UpTab 		= tabptr;
	siteptr->Address 	= malloc(80);
	strcpy(siteptr->Address,Session->OpeningAddress);

	/* Meta ton proteleutaio mpainei o tabptr kai pleon einai teleutaios */
	Session->LastTab->NextTab  = tabptr;
	/* Panta o prohgoymenos toy prwtoy einai o telytaios */
	Session->FirstTab->PrevTab = tabptr;

	Session->LastTab = tabptr;
	Session->CurrTab = tabptr;

}

void SessionTabShow(InfoSessionPtr Session){

	/* Idia me thn SessionSiteShow */
	assert(Session);
	printf("\nThe address of the current site is %s ",Session->CurrTab->CurrSite->Address);

}


void SessionTabNext(InfoSessionPtr Session){

	assert(Session);
	Session->CurrTab = Session->CurrTab->NextTab;

}


void SessionTabPrev(InfoSessionPtr Session){

	assert(Session);
	Session->CurrTab = Session->CurrTab->PrevTab;
}

int SessionTabMoveLeft(InfoSessionPtr Session){

	TabNodePtr ProProigTab,ProigTab,EpomTab;

	assert(Session);

	/* An o CurrTab einai o prwtos komvos den ginetai metakinhsh */

	if ((Session->CurrTab) == (Session->FirstTab))
					return 0;

	ProigTab 		=	Session->CurrTab->PrevTab;
	ProProigTab = ProigTab->PrevTab;
	EpomTab 		= Session->CurrTab->NextTab;

	/* Sth periptwsh opoy yparxoyn mono 2 komvoi */

	if (((Session->CurrTab) == (Session->LastTab)) && ((Session->FirstTab) == (ProigTab))){

			Session->CurrTab->NextTab = ProigTab;
			Session->CurrTab->PrevTab = ProigTab;

			ProigTab->PrevTab = Session->CurrTab;
			ProigTab->NextTab = Session->CurrTab;

			Session->FirstTab = Session->CurrTab;
			Session->LastTab  = ProigTab;

			return 1;
	}

	/* Se opoiadhpote allh periptwsh me panw apo 2 komvous */

	ProProigTab->NextTab = Session->CurrTab;
	EpomTab->PrevTab  	 = ProigTab;

	Session->CurrTab->NextTab = ProigTab;
	Session->CurrTab->PrevTab = ProProigTab;

	ProigTab->NextTab = EpomTab;
	ProigTab->PrevTab = Session->CurrTab;

	/* An o komvos poy metakinhthhke htan o teleutaios, tote pleon o proteleutaios tha einai o teleytaios */

	if ((Session->CurrTab) == (Session->LastTab))
			Session->LastTab = ProigTab;

	/* An o komvos poy metakinhthhke htan o deuteros, tote pleon tha einai o prwtos */

	if ((Session->FirstTab) == ProigTab)
			Session->FirstTab = Session->CurrTab;

	return 1;

}

int SessionTabMoveRight(InfoSessionPtr Session){

	TabNodePtr ProigTab,EpomTab,MethEpomTab;

	assert(Session);

	/* An einai o teleutaios komvos den ginetai metakinhsh */

	if ((Session->CurrTab) == (Session->LastTab))
			return 0;

	EpomTab  	  = Session->CurrTab->NextTab;
	ProigTab 	  = Session->CurrTab->PrevTab;
	MethEpomTab = EpomTab->NextTab;

	/* An yparxoyn mono 2 komvoi */

	if (((Session->CurrTab) == (Session->FirstTab)) && ((Session->LastTab) == (EpomTab))){

		Session->CurrTab->NextTab = EpomTab;
		Session->CurrTab->PrevTab = EpomTab;

		EpomTab->NextTab = Session->CurrTab;
		EpomTab->PrevTab = Session->CurrTab;

		Session->FirstTab = EpomTab;
		Session->LastTab  = Session->CurrTab;

		return 1;
	}

	/* Se opoiadhpote allh periptwsh me panw apo 2 komvous */

	Session->CurrTab->NextTab = EpomTab->NextTab;
	Session->CurrTab->PrevTab = EpomTab;

	EpomTab->NextTab = Session->CurrTab;
	EpomTab->PrevTab = ProigTab;

	ProigTab->NextTab 	 = EpomTab;
	MethEpomTab->PrevTab = Session->CurrTab;

	/* An o komvos poy metakinhthhke htan o prwtos, tote pleon o deuteros tha einai o prwtos */

	if ((Session->CurrTab) == (Session->FirstTab))
		Session->FirstTab = EpomTab;

	/* An o komvos poy metakinhthhke htan proteleutaios, tote pleon tha einai o teleutaios */

	if ((Session->LastTab) == EpomTab)
			Session->LastTab = Session->CurrTab;

		return 1;
}

void SessionNewOpeningAddress(InfoSessionPtr Session, char *strNewAddress){

	assert(Session);
	Session->OpeningAddress = malloc(80);
	strcpy(Session->OpeningAddress,strNewAddress);

}

void SessionShowOpeningAddress(InfoSessionPtr Session){

	assert(Session);
	printf("\nThe default opening address is %s ",Session->OpeningAddress);
}


int SessionSiteNext(InfoSessionPtr Session){

	/* H synarthsh epistrefei 1 an metakinithike ston epomeno */
	/* komvo site alliws an einai ston teleytaio epistrefei 0 */

	assert(Session);

	if ((Session->CurrTab->CurrSite->NextSite) != NULL){
			Session->CurrTab->CurrSite = Session->CurrTab->CurrSite->NextSite;
			return 1;
	}else
			return 0;

}


int SessionSitePrev(InfoSessionPtr Session){

	/* H synarthsh epistrefei 1 an metakinithike ston prohgoumeno */
	/* komvo site alliws an einai ston prwto epistrefei 0 */

	assert(Session);

	if ((Session->CurrTab->CurrSite) != (Session->CurrTab->FirstSite)){
			Session->CurrTab->CurrSite = Session->CurrTab->CurrSite->PrevSite;
			return 1;
	}else
			return 0;
}


void SessionSiteShow(InfoSessionPtr Session){

	/* Idia me thn SessionTabShow */
	assert(Session);
	printf("\nThe address of the current site is %s ",Session->CurrTab->CurrSite->Address);
}


int SessionTabClose(InfoSessionPtr Session){

	/* H synarthsh epistrefei 1 an diegrapse ton teleytaio komvo tab kai to */
	/* InfoSession, alliws epistrefei 0 an diegrapse mono ton CurrTab */

	SiteNodePtr CurrentSite,TempSite;
	TabNodePtr TempTab;

	assert(Session);

	CurrentSite = Session->CurrTab->CurrSite;

	/* Diagrafh olwn twn komvwn site */

	while(CurrentSite != NULL){

	TempSite 		= CurrentSite;
	CurrentSite = CurrentSite->NextSite;
	free(TempSite);

	}

	/* TempTab = o kombos poy tha diagrafei */
	TempTab = Session->CurrTab;

	/* O CurrTab pleon einai o epomenos */
	Session->CurrTab = Session->CurrTab->NextTab;

	/* An exei meinei mono enas komvos Tab diagrafetai kai olo to Infosession */

	if ((Session->FirstTab) == (Session->LastTab)){
					free(Session);
					free(TempTab);
					return 1;
	}

	TempTab->PrevTab->NextTab = Session->CurrTab;
	Session->CurrTab->PrevTab = TempTab->PrevTab;

	/* An diagrafei o prwtos, prwtos tha ginei o deuteros */

	if ((Session->FirstTab) == (TempTab))
				Session->FirstTab = Session->CurrTab;

	/* An diagrafei o teleytaios, teleutaios tha ginei o proteleutaios */

	if ((Session->LastTab) == (TempTab))
				Session->LastTab = TempTab->PrevTab;

	free(TempTab);

	return 0;
}


int SessionClose(InfoSessionPtr Session){

	/* H synarthsh epistrefei 1 an petyxe,dhladh an diagrafthke */
	/* to InfoSession, alliws an apetyxe epistrefei 0 */

	int check;

	assert(Session);
	Session->CurrTab = Session->FirstTab;

	/* Diagrafh olwn twn komvwn Tab ektos toy teleutaiou */

	while ((Session->CurrTab) != (Session->LastTab))
		 SessionTabClose(Session);

	/* Diagrafh toy teleytaiou komvoy kai check an diagrafthke to InfoSession*/

	check = SessionTabClose(Session);

	return check;

}


int SessionNewAddress(InfoSessionPtr Session,char *straddress){

	SiteNodePtr TempSite1,TempSite2;

	assert(Session);

	TempSite1 = Session->CurrTab->CurrSite;

	/* Diagrafh olwn twn komvwn site meta to Current Site */

	while((TempSite1->NextSite) != NULL){

		TempSite2 = TempSite1;
		TempSite1 = TempSite1->NextSite;

		free(TempSite2);

	}

	TempSite1 = Session->CurrTab->CurrSite;

	TempSite2 = malloc(sizeof(struct SiteNode));

	TempSite2->NextSite  = NULL;
	TempSite2->PrevSite  = TempSite1;
	TempSite2->UpTab 		 = Session->CurrTab;
	TempSite2->Address   = malloc(80);
	strcpy(TempSite2->Address,straddress);

	TempSite1->NextSite = TempSite2;
	Session->CurrTab->CurrSite = TempSite2;

	return 1;

}
