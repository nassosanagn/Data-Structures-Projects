/*************************************************
Implementation File	: Controller.c
Revision 			:  <Athanasios Anagnostopoulos - 21/3/19>
AM          :   sdi1800006
**************************************************/
#include <stdio.h>
#include "Controller.h"


void ControllerDimiourgia(TController *Controller){

Controller->TimeBusy = 0;         /* Xronos apasxolhshs toy elegχth */
Controller->TimeInactive = 0;     /* Xronos poy o elegxths den doyleue */
Controller->ArithmoPelaton = 0;     /*plh8os e3yphreth8entwn pelatwn*/
Controller->enapomenonXronos = 0;   /*Xronos gia to telos e3yphrethshs enos pelath*/

}

void ControllerNewCustomer(TController *Controller){

  Controller->ArithmoPelaton++;
  Controller->TimeBusy++;
}


void ControllerSetXrono(TController *Controller, int xronosEksipiretisis){

  Controller->enapomenonXronos = xronosEksipiretisis;
}

void ControllerNoWork(TController *Controller){

  Controller->TimeInactive++;

}

void ControllerBusy(TController *Controller){

  Controller->TimeBusy++;
  Controller->enapomenonXronos--;
}

int ControllerFree(TController Controller){

  return(Controller.enapomenonXronos == 0);

}


int ControllerGetArithmosPelatwn(TController Controller){

  return Controller.ArithmoPelaton;

}

int ControllerGetEnapomenonXronos(TController Controller){

  return Controller.enapomenonXronos;
}

int ControllerGetInactiveXronos(TController Controller){

  return Controller.TimeInactive;
}

int ControllerGetBusyXronos(TController Controller){

  return Controller.TimeBusy;
}
