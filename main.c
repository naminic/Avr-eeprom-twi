/*****************************************************
Chip type               : ATmega32
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega32.h>
#include <twi.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>

#define AT24_ADDRESS 0xA0 >> 1 

void main(void)
{
unsigned char AD_EE[5],result[10];

lcd_init(16);   //initiate lcd.
twi_master_init(400);
#asm("sei")
AD_EE[0]=0x01;       //eeprom address.
AD_EE[1]=0x75;       //data that write to address 0x01(above line)
AD_EE[2]=0x57;

while (1)
      {
         lcd_clear();
         lcd_gotoxy(0,0);
         lcd_putsf("Writing two     number in EEPROM");
         delay_ms(3000);
         twi_master_trans(AT24_ADDRESS,&AD_EE[0],3,0,0);
         delay_ms(40);
         
         twi_master_trans(AT24_ADDRESS,&AD_EE[0],1,&AD_EE[3],2);
         lcd_clear();
         lcd_gotoxy(0,0);
         switch(twi_result)
         {
            case TWI_RES_OK:
                lcd_putsf("Data readed is:");
                delay_ms(500);
                lcd_gotoxy(0,1);
                sprintf(result,"%d AND %d",AD_EE[3],AD_EE[4]); 
                lcd_puts(result);
                break;
            case TWI_RES_BUFFER_OVERFLOW:
                lcd_putsf("Buffer is out of Full!"); 
                break;
            case TWI_RES_ARBITRATION_LOST:
                lcd_putsf("This Master losts the bus."); 
                break; 
            case TWI_RES_BUS_ERROR:
                lcd_putsf("BUS ERROR."); 
                break; 
            case TWI_RES_NACK_RECEIVED:
                lcd_putsf("The Device sends NACK signal."); 
                break;
            case TWI_RES_BUS_TIMEOUT:
                lcd_putsf("Device Dosen't reply."); 
                break;
            case TWI_RES_FAIL:
                lcd_putsf("TWI BUS can't initialize."); 
                break;
            case TWI_RES_UNKNOWN:
                lcd_putsf("Unknown ERROR."); 
                break;
            default:
                lcd_putsf("I confused! and don't know about error.");
         }
         

         while(1);      //end of 8 byte read/write test.
      }
}
