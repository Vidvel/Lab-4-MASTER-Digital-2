/*
 * File:   SPIMaster.c
 * Author: David Vela
 *
 * Created on 12 de febrero de 2020, 07:06 PM
 */
//CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
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
#include "SPI.h"
#include "usartlib.h"

void main(void){
  TRISB = 0x00; //PORTB as OUt
  PORTB = 0x00; //All LEDs OFF
  //TRISA = 0xFF;
  char mvar1 = 0;
  char mvar2 = 0;
  char select = 0;
  char selectp1 = 0;
  char recived = 0;
  
  usart_setup();
  spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

  while(1){
      if (UART_Data_Ready()){
            recived = UART_Read(); 
            RCSTAbits.CREN = 1; 
        }
        else{
            asm("nop");
        }
        PORTB = recived;
        
        if (recived == 0b10000000){
            selectp1 = 0;
        }
        else if (recived == 0b01111111){
            selectp1 = 1;
        }
        else{
            ;
        }
        switch (selectp1){
            case 0:
                UART_Write(mvar1);
                break;
            case 1:
                UART_Write(mvar2);
                break;
        }
        //UART_Write(mvar2);
        spiWrite(0);
        mvar1 = spiRead();
        __delay_ms(10);
    
        spiWrite(1);
        mvar2 = spiRead();
        __delay_ms(10);
    /*
    select = PORTA;
    switch (select){
        case 0:
            PORTB = mvar2;
            break;
        case 1:
            PORTB = mvar1;
            break;
    }*/
  }
}
