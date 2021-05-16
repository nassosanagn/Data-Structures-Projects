/*************************************************************************
Header File Name : Session.h
Ful Name  :  Athanasios Anagnostopoulos
AM     : sdi1800006
**************************************************************************/

#ifndef __SESSION__
#define __SESSION__

typedef struct InfoSession *InfoSessionPtr;

InfoSessionPtr SessionNew(char *);
void SessionNewTab(InfoSessionPtr Session);

void SessionTabShow(InfoSessionPtr Session);
void SessionTabNext(InfoSessionPtr Session);
void SessionTabPrev(InfoSessionPtr Session);
int SessionTabMoveLeft(InfoSessionPtr Session);
int SessionTabMoveRight(InfoSessionPtr Session);

void SessionNewOpeningAddress(InfoSessionPtr Session,char *strNewAddress);
void SessionShowOpeningAddress(InfoSessionPtr Session);

int SessionSiteNext(InfoSessionPtr Session);
int SessionSitePrev(InfoSessionPtr Session);
void SessionSiteShow(InfoSessionPtr Session);

int SessionTabClose(InfoSessionPtr Session);
int SessionClose(InfoSessionPtr Session);

int SessionNewAddress(InfoSessionPtr Session,char *straddress);


#endif
