//****************************************************************************//
//  MSP430 state machine
//  fsm_transition.c
//
//  Describtion:
//    A simple state machine for the MSP430
//    You can add your own code in here!!!
//
//  Generated with Excel Table
//  Date:  06/10/2021        Time:  14:34:35
//
//****************************************************************************//
#include <msp430g2553.h>
#include "fsm.h"
//PARA LOS LEDS P1OUT


//****************************************************************************//
// Transition function "SEC_ESPERA"
//****************************************************************************//
void FSM_SEC_ESPERA (void)

{
    volatile unsigned int i;
    P2DIR |= (LED0|LED1|LED2|LED3);
    while((P1IFG & INICIO)!= INICIO)
    {
        for(i=10 ; i>0; i--)
        {
            P2OUT ^= LED0;
            __delay_cycles(50000);

        }
        for(i=10 ; i>0; i--)
        {
            P2OUT ^= LED1;
            __delay_cycles(50000);
        }
        for(i=10 ; i>0; i--)
        {
            P2OUT ^= LED2;
            __delay_cycles(50000);
        }
        for(i=10 ; i>0; i--)
        {
            P2OUT ^= LED3;
            __delay_cycles(50000);
        }
    }

}


//****************************************************************************//
// Transition function "INICIA_JUEGO"
//****************************************************************************//
void FSM_INICIA_JUEGO (void)
{
    volatile unsigned long int LFSR0, RES;
    volatile int f;


    LFSR0 = seed + LFSR0;//En esta instruccion a la semilla le sumamos el LFSR para que en cada inicio de juego nos aparezcan aleatorios distintos

    for (f = 9; f >= 0; f--)//Llevando el conteo de las casillas del arreglo
    {
        generado[f] = 0;
    }

    while (generado[9] == 0)// permite hasta la casilla 9 porque solo queremos 10 elementos
    {
        LFSR0 = RNG_LFSR(LFSR0);//Aqui mandamos a llamar al modulo RNG_LFSR el cual es el que genera los numeros aleatorios
        Asignar(LFSR0, generado);//Mandamos a llamar el modulo asignar
    }
    Decod(generado);

}
//Creando los numeros aleatorias
unsigned int RNG_LFSR(unsigned int LFSR)
{
    volatile char LSB;

     LSB = ((LFSR>>TAP_1)^(LFSR>>TAP_2)^(LFSR>>TAP_3)^(LFSR>>TAP_4))&BIT0;//Aqui usamos cuatro TAPS correspondientes al LFSR[1 2 4 15]

    LFSR = LSB | (LFSR<<1);

    return LFSR;
}
void Asignar(long int LFSR0, int gen[10]) //Los colores generados los guardamos en un arreglo de 10 elementos
{
    volatile static int i = 0, j = 0, k = 0, l = 0, m = 0, h = 0; //inicializamos nuestras variables de los condicionales
    volatile long int RES, no = 0;

    RES = LFSR0; // a res la igualamos con el aleatorio antes generado

    if (0 < RES && RES <= 32768) //Aqui seccionamos a los numeros aleatorios en dos modulos con la ayuda del MOD de un numero y obtenermos los pares e impares
    {
        if((RES % 2) == 0)//Si el LFSR0 es par entra al if
        {
            i = 2;//este 2 es un numero para distinguir que estos numeros seran solamente para el color verde
            j++; //va verificando cuantos colores verdes llevamos y cada vez que pasa un ciclo suma
            if (j > 2)//Este if nos sirve para que el color verde no se repita mas de dos veces
            {
                no = 1;//Si el color se repite mas de dos veces entonces lo apagamos
                //j = 0;
            }
        }

        else//En caso de que no hayan sido numeros pares se vienen a la seccion de impares
        {
            i = 3;//este 3 es un numero para distinguir que estos numeros seran solamente para el color rojo
            k++;//Suma el color rojo
            if (k > 2)//Si el color rojo ya se repitio 2 veces
            {
                no = 1;//Apaga el color rojo
                //k = 0;
            }
        }
    }

    else if (32768 < RES && RES <= 65535)//Aqui separamos el segundo bloque de los numeros aleatorios del numero 32768 a 65535
    {
        if((RES % 2) == 0)//Con este if obtenemos los numeros pares
        {
            i = 5;//esta seccion que obtengamos va pertenercer al color azul
            l++;
            if (l > 2)//Si el color se repite mas de dos veces
            {
                no = 1;//Lo apagamos
                //l = 0;
            }
        }

        else//En este bloque entran los impares
        {
            i = 7;//corresponden a los aleatorios del color amarillo
            m++;
            if (m > 2)//Si se repite mas de dos veces el 7 es decir el color amarillo
            {
                no = 1;//lo apagamos
                //m = 0;
            }
        }
    }

    if (h < 10)//Aqui guarda solo 10 numeros
    {
        if (no == 0)//Si el color no lleva mas de dos entonces los guarda en un arreglo llamado gen
        {
            gen[h] = i;
            h++;
        }
    }
    else
    {
        h = 0;
    }

    if (j > 2 && k > 2 && l > 2 && m > 2) //Esto se hace para que se reinicien los colores
    {
        j = 0;
        k = 0;
        l = 0;
        m = 0;
    }
}
//Modulo decod, muestra el led correcto dependiendo el numero que le este llegando
void Decod(int sec[10])
{
    volatile unsigned int i = 0;
    //volatile int level=3;

    for(i = 0; i < 4; i++)
    {
        if(sec[i] % 2 == 0)
        {
            P2OUT ^= LED0; //llamamos al LED0 el cual corresponde al color verde
            __delay_cycles(INTER);
            P2OUT &= ~LED0;
            __delay_cycles(INTER);
        }

        if(sec[i] % 3 == 0)
        {
            P2OUT ^= LED1; //llamamos al LED1 el cual corresponde al color rojo
            __delay_cycles(INTER);
            P2OUT &= ~LED1;
            __delay_cycles(INTER);
        }

        if(sec[i] % 5 == 0)
        {
            P2OUT ^= LED2;//llamamos al LED2 el cual corresponde al color azul
            __delay_cycles(INTER);
            P2OUT &= ~LED2;
            __delay_cycles(INTER);
        }

        if(sec[i] % 7 == 0)
        {
            P2OUT ^= LED3;//llamamos al LED0 el cual corresponde al color amarillo
            __delay_cycles(INTER);
            P2OUT &= ~LED3;
            __delay_cycles(INTER);
        }
    }
}
//****************************************************************************//
// Transition function "REVISA"
//****************************************************************************//
void FSM_REVISA (void)
{
/*{
__bis_SR_register(CPUOFF + GIE);
}
#pragma vector = PORT1_VECTOR
__interrupt void mi_puerto1(void)
{
    if ((P1IFG & BTN_R)==BTN_R)
    {
        P2OUT ^=LED1;
        P1IFG &=~BTN_R;
        __delay_cycles(20000);
    }
    if ((P1IFG & BTN_V)==BTN_V)
    {
        P2OUT ^=LED0;
        P1IFG &=~BTN_V;
        __delay_cycles(20000);
     }
    if ((P1IFG & BTN_A)==BTN_A)
    {
        P2OUT ^=LED3;
        P1IFG &=~BTN_A;
        __delay_cycles(20000);
     }
    if ((P1IFG & BTN_B)==BTN_B)
    {
        P2OUT ^=LED2;
        P1IFG &=~BTN_B;
        __delay_cycles(20000);
    }
    if ((P1IFG & INICIO)==INICIO)
    {

        FSM_SEC_ESPERA();
        P1IFG &=~INICIO;
        __delay_cycles(20000);
    }
    P1IES &= ~(BTN_R | BTN_V | BTN_A | BTN_B|INICIO);
    P1IFG &= ~(BTN_R | BTN_V | BTN_A | BTN_B|INICIO);

    //Configurar la interrupcion
    WDTCTL = WDT_MDLY_32;
    //Limpiar bandera y habilitar la interrupcion
    IFG1 &= ~WDTIFG;
    IE1 |= WDTIE;
}



#pragma vector = WDT_VECTOR
__interrupt void WDT_debounce(void)
{
    //limpiamos bandera de interrupcion
    IFG1= ~WDTIFG;
    IE1 &= ~WDTIE;
    WDTCTL = WDTPW + WDTHOLD;
    //Volver a habilitar la interrupcion del boton p13
    P1IE |=(BTN_R | BTN_V | BTN_A | BTN_B|INICIO); //El debounce esta listo
}



void Comparador(int leds[10])//Arreglo llamado les de 10 elementos
{
    volatile int *ans, *gud, *lvl;
    volatile static int i = 0;

    ans = &resultado;
    gud = &bien;
    lvl = &nivel;

    if (leds[i] == *ans)//comparamos el resultado con la posicion del led
    {
        *gud = 1;//entonces pasa como correcto
        i++;
    }

    else// en otro caso pasa como incorrecto
    {
        *gud = 0;
        i = 0;
    }

    if (i > 9)// como 9 es el  maximo entonces reiniciamos
    {
        i = 0;//se reinicia
    }

    if (i == *lvl)//Cuando validamos el ultimo valor del nivel entonces i=lvl
    {
        i = 0;//reiniciamos la variable i
    }
}
*/
//****************************************************************************//
// Transition function "DESPLIEGA"
//****************************************************************************//
}
void FSM_DESPLIEGA (void)
{
  // You can add your code here
}


//****************************************************************************//
// Transition function "PERDISTE"
//****************************************************************************//
void FSM_PERDISTE (void)
{
  // You can add your code here
}


//****************************************************************************//
// Transition function "GANASTE"
//****************************************************************************//
void FSM_GANASTE (void)
{
  // You can add your code here
}


//****************************************************************************//
// Transition function "LIMPIA"
//****************************************************************************//
void FSM_LIMPIA (void)
{
  // You can add your code here
}


//****************************************************************************//
