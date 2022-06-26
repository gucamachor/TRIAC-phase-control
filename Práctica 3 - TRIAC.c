///////////////////////////////////////////////////////////////////////////////
//             Pr�ctica 3. Control de fase con TRIAC                         //
// PROYECTO: Control del �ngulo con triac para voltaje aplicado a            //
//          carga de 500  ohsm                                               //
//                                                                           //   
// Fecha:    10/03/22                                                        //
// AUTOR: Camacho Rodr�guez, Gerardo U                                       //
// COMPILADOR:  CCS C COMPILER                                               //
// MICROCONTROLADOR: PIC16F877                                               //
// OSCILADOR: 4 MHz                                                          //
////////////////////////////////  DIRECTIVAS  /////////////////////////////////

//Generales.
#include <16f877.h>              // Incluye fichero del MCU PIC16F877 
#fuses XT,NOWDT,NOPROTECT,PUT    // Define las palabras de configuraci�n del PIC
#use delay(clock = 4 Mhz)        // Define la Frec. del oscilador de PIC(4 MHz)

// Librer�as
#include <lcd.c>                // Librer�a de LCD
#include <math.h>               // Librer�a de matem�ticas para pi

// Registros
#byte PortA = 0x05              // Puerto A

// Variables tipo bit en registros.
#bit ZCD = portA.1             // Registro de bit para Zero Cross Detector (ZCD)
#bit AT = portA.2              // Registro salida de pulsos del MCU

// Variables globales.
float A_AT;
float RADS, GRADS;                    // Variable para radianes
int16 ANGLE;                   // Variable para �ngulo

/////////////////////  PROTOTIPOS DE FUNCIONES Y TAREAS ///////////////////////

void iniciar(void){           // Inicializa la funci�n iniciar
   
   lcd_init();                // Inicia la liber�a LCD 16x2
   set_tris_a(0b00000011);    // Configura los Puertos del PIC
}                             // fin de iniciar

/////////////////////////////  FUNCI�N PRINCIPAL   ////////////////////////////

void main(void){              // Inicia el programa principal
   
   iniciar();                 // Llamada a la funci�n iniciar.
   A_AT = 180;                // Define �ngulo asignado para el trigger o disparo, se ajusta
   ANGLE = (A_AT * 8332)/180; // C�lculo del �ngulo a partir del periodo (ms) y su conv. a grados
   RADS = (A_AT * pi)/180; // Degrees to rads conversion
   //GRADS = RADS * (180/pi);
   //float Vcd = ((1)/(2 * pi))*(100) * (cos(RADS) + 1); // Fórmula para VCD
   
   // LCD display para desplegar el �ngulo
   lcd_gotoxy(1,1);           // 1st LCD line
   printf(lcd_putc,"RADS: %01.2f",RADS); 
   lcd_gotoxy(1,2);           // 2nd LCD line
   printf(lcd_putc,"Angulo: %01.2f",A_AT);

   /// Fija ángulo de disparo a partir de condici�n de ZCD
   while(true){               // Initial infinite loop while
      if (ZCD==1){            // Condici�n de la funci�n de ZCD
         delay_us(ANGLE);     // Delay para el �ngulo resultante
         AT = 1;              // Si hay ZDC
         AT = 0;              // Si no hay ZDC
      }
   }
} // Fin del programa
