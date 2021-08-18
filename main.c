#include <msp430g2553.h>
#include "fsm.h"


volatile unsigned int inc = 150;
void main(void)

{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1OUT = 0;
    P2OUT = 0;

    //CONFIGURANDO A 1 MHZ EL CPU CON DCO COMO FUENTE DE OSCILACION
    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL3 |= LFXT1S_2;


    P1REN |= (INICIO);//|BTN_V|BTN_R|BTN_A|BTN_B);
    P1OUT |= (INICIO);//|BTN_V|BTN_R|BTN_A|BTN_B);
    P1DIR &= ~(INICIO);//|BTN_V|BTN_R|BTN_A|BTN_B);
    P1IE |= (INICIO);//|BTN_V|BTN_R|BTN_A|BTN_B);
    P1IES &= ~(INICIO);//|BTN_V|BTN_R|BTN_A|BTN_B);
    P1IFG &= ~(INICIO);//|BTN_V|BTN_R|BTN_A|BTN_B);

    FSM_SEC_ESPERA();
    __bis_SR_register(CPUOFF + GIE);
    //FSM_REVISA();

}



#pragma vector = PORT1_VECTOR
__interrupt void puerto1(void)
{
        //P1DIR &= ~(LED0|LED1|LED2|LED3);
        FSM_INICIA_JUEGO();
        __bic_SR_register_on_exit(CPUOFF + GIE);

}

