//****************************************************************************//
//  MSP430 state machine
//  fsm.h
//
//  Describtion:
//    A simple state machine for the MSP430
//
//  Generated with Excel Table
//  Date:  06/10/2021        Time:  14:34:35
//
//****************************************************************************//

#ifndef FSM_H
#define FSM_H

#include <stdint.h>
#include <stdio.h>

//****************************************************************************//
// State table typedef
//****************************************************************************//
typedef struct
{
  void (*ptrFunct) (void);
  uint8_t NextState;
} FSM_STATE_TABLE;
//BOTONES EN EL PUERTO 1
#define BTN_R BIT0
#define BTN_V BIT4
#define BTN_A BIT5
#define BTN_B BIT6
#define INICIO BIT3
extern uint8_t ActState;
//LEDS EN P2
#define LED1  BIT2//ROJO
#define LED0  BIT5//VERDE
#define LED3  BIT4//AMARILLO
#define LED2  BIT0//AZUL
//BOTON DE INICIO Y REINICIO EN P2

#define TAP_1 1
#define TAP_2 2
#define TAP_3 4
#define TAP_4 15
#define INTER  500000
//Semilla
#define seed 0xF9CD

#define NR_EVENTS 8
#define BTNR  0
#define BTNA  1
#define BTNV  2
#define BTNB  3
#define INICIO_RST  4
#define SEC_GOOD  5
#define SEC_BAD  6
#define SEC_WIN  7

#define NR_STATES 4
#define ESPERA  0
#define ESPERASEC  1
#define DIGITA_SEC  2
#define GAME_OVER  3


//****************************************************************************//
unsigned int RNG_LFSR(unsigned int LFSR);
void Asignar(long int LFSR0, int gen[10]);
void Decod(int sec[10]);
int generado[10];
//****************************************************************************//
// Initialize state machine
void FSM_Init (void);

// Event function "BTNR"
void FSM_BTNR (void);

// Event function "BTNA"
void FSM_BTNA (void);

// Event function "BTNV"
void FSM_BTNV (void);

// Event function "BTNB"
void FSM_BTNB (void);

// Event function "INICIO_RST"
void FSM_INICIO_RST (void);

// Event function "SEC_GOOD"
void FSM_SEC_GOOD (void);

// Event function "SEC_BAD"
void FSM_SEC_BAD (void);

// Event function "SEC_WIN"
void FSM_SEC_WIN (void);

// Transition function "SEC_ESPERA"
void FSM_SEC_ESPERA (void);

// Transition function "INICIA_JUEGO"
void FSM_INICIA_JUEGO (void);

// Transition function "REVISA"
void FSM_REVISA (void);

// Transition function "DESPLIEGA"
void FSM_DESPLIEGA (void);

// Transition function "PERDISTE"
void FSM_PERDISTE (void);

// Transition function "GANASTE"
void FSM_GANASTE (void);

// Transition function "LIMPIA"
void FSM_LIMPIA (void);


//****************************************************************************//

#endif /* FSM_H */

//****************************************************************************//
