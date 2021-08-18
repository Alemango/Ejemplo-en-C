//****************************************************************************//
//  MSP430 state machine
//  fsm.c
//
//  Describtion:
//    A simple state machine for the MSP430
//    Do not change code in here!!!
//
//  Generated with Excel Table
//  Date:  06/10/2021        Time:  14:34:34
//
//****************************************************************************//

#include <stdint.h>
#include <stdio.h>
#include "fsm.h"

//****************************************************************************//
// Global variables
//****************************************************************************//
uint8_t  ActState;

const FSM_STATE_TABLE StateTable [NR_STATES][NR_EVENTS] =
{
  NULL, ESPERA, NULL, ESPERA, NULL, ESPERA, NULL, ESPERA, FSM_SEC_ESPERA, ESPERASEC, NULL, ESPERA, NULL, ESPERA, NULL, ESPERA,
  NULL, ESPERASEC, NULL, ESPERASEC, NULL, ESPERASEC, NULL, ESPERASEC, FSM_INICIA_JUEGO, DIGITA_SEC, NULL, ESPERASEC, NULL, ESPERASEC, NULL, ESPERASEC,
  FSM_REVISA, DIGITA_SEC, FSM_REVISA, DIGITA_SEC, FSM_REVISA, DIGITA_SEC, FSM_REVISA, DIGITA_SEC, NULL, DIGITA_SEC, FSM_DESPLIEGA, DIGITA_SEC, FSM_PERDISTE, GAME_OVER, FSM_GANASTE, GAME_OVER,
  NULL, GAME_OVER, NULL, GAME_OVER, NULL, GAME_OVER, NULL, GAME_OVER, FSM_LIMPIA, ESPERA, NULL, GAME_OVER, NULL, GAME_OVER, NULL, GAME_OVER
};


//****************************************************************************//
// Initialize state machine
//****************************************************************************//
void FSM_Init (void)
{
  ActState = ESPERA;
}


//****************************************************************************//
// Event function "BTNR"
//****************************************************************************//
void FSM_BTNR (void)
{
  if (StateTable[ActState][BTNR].ptrFunct != NULL)
    StateTable[ActState][BTNR].ptrFunct();

  ActState = StateTable[ActState][BTNR].NextState;
}


//****************************************************************************//
// Event function "BTNA"
//****************************************************************************//
void FSM_BTNA (void)
{
  if (StateTable[ActState][BTNA].ptrFunct != NULL)
    StateTable[ActState][BTNA].ptrFunct();

  ActState = StateTable[ActState][BTNA].NextState;
}


//****************************************************************************//
// Event function "BTNV"
//****************************************************************************//
void FSM_BTNV (void)
{
  if (StateTable[ActState][BTNV].ptrFunct != NULL)
    StateTable[ActState][BTNV].ptrFunct();

  ActState = StateTable[ActState][BTNV].NextState;
}


//****************************************************************************//
// Event function "BTNB"
//****************************************************************************//
void FSM_BTNB (void)
{
  if (StateTable[ActState][BTNB].ptrFunct != NULL)
    StateTable[ActState][BTNB].ptrFunct();

  ActState = StateTable[ActState][BTNB].NextState;
}


//****************************************************************************//
// Event function "INICIO_RST"
//****************************************************************************//
void FSM_INICIO_RST (void)
{
  if (StateTable[ActState][INICIO_RST].ptrFunct != NULL)
    StateTable[ActState][INICIO_RST].ptrFunct();

  ActState = StateTable[ActState][INICIO_RST].NextState;
}


//****************************************************************************//
// Event function "SEC_GOOD"
//****************************************************************************//
void FSM_SEC_GOOD (void)
{
  if (StateTable[ActState][SEC_GOOD].ptrFunct != NULL)
    StateTable[ActState][SEC_GOOD].ptrFunct();

  ActState = StateTable[ActState][SEC_GOOD].NextState;
}


//****************************************************************************//
// Event function "SEC_BAD"
//****************************************************************************//
void FSM_SEC_BAD (void)
{
  if (StateTable[ActState][SEC_BAD].ptrFunct != NULL)
    StateTable[ActState][SEC_BAD].ptrFunct();

  ActState = StateTable[ActState][SEC_BAD].NextState;
}


//****************************************************************************//
// Event function "SEC_WIN"
//****************************************************************************//
void FSM_SEC_WIN (void)
{
  if (StateTable[ActState][SEC_WIN].ptrFunct != NULL)
    StateTable[ActState][SEC_WIN].ptrFunct();

  ActState = StateTable[ActState][SEC_WIN].NextState;
}


//****************************************************************************//
