/*************************************************
Header File Name 		: Controller.h
Revision 			:  <Athanasios Anagnostopoulos - 21/3/19>
AM        :      sdi1800006
**************************************************/



#ifndef __Controller__
#define __Controller__

typedef struct {
  unsigned int TimeBusy;
  unsigned int TimeInactive;
  unsigned int ArithmoPelaton;      // == arithmos pelaton
  unsigned int enapomenonXronos;      // == enapomenon_xronos
} TController;

void ControllerDimiourgia(TController *Controller);
void ControllerNewCustomer(TController *Controller);
void ControllerSetXrono(TController *Controller, int xronosEksipiretisis);
void ControllerNoWork(TController *Controller);
void ControllerBusy(TController *Controller);

int ControllerFree(TController Controller);
int ControllerGetArithmosPelatwn(TController Controller);
int ControllerGetEnapomenonXronos(TController Controller);
int ControllerGetInactiveXronos(TController Controller);
int ControllerGetBusyXronos(TController Controller);

#endif
