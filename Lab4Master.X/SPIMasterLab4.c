/*
 * File:   SPIMasterLab4.c
 * Author: David Vela
 *
 * Created on 11 de febrero de 2020, 12:54 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 4000000

#include <xc.h>
#include "usartlib.h"
#include "SPI.h"


char recived;
char c1 = 0;
char c2 = 0;

void main(void) {
    TRISB = 0;
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD4 = 1;
    TRISDbits.TRISD5 = 1;
    PORTDbits.RD7 = 1;
    PORTB = 255;
    ANSEL = 0;
    ANSELH = 0;
    
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_HIGH, SPI_IDLE_2_ACTIVE);
    //usart_setup();
    while(1){
        
        if ((PORTDbits.RD4 == 1)&&(spiDataReady())){
            PORTB--;
            RD7 = 0;
            __delay_ms(1);
            spiWrite(0);
            PORTB = spiRead();
            __delay_ms(1);
            RD7 = 1;
            __delay_ms(100);   
        }
        
        
        /*
        UART_Write(ADCval1);
        //UART_Write(ADCval2);
        if (UART_Data_Ready()){
            recived = UART_Read(); 
            RCSTAbits.CREN = 1; 
        }
        else{
            asm("nop");
        }
        PORTB = recived;
        c1++;
        if (c1 == 255){
            ADCval1++;
            ADCval2--;
            c1 = 0;
            
        }
        else{
            asm("nop");
        }*/
    }
    return;
}
