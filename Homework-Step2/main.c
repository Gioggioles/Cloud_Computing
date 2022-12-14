#include "main.h"



/**
 * This is the C entry point, upcalled once the hardware has been setup properly
 * in assembly language, see the reset.s file.
 */
int strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 -*(const unsigned char*)s2;
}

void _start() {
  int i = 0;
  struct cb *cb;
  void* cookie;
  /*int orizontal = 0;
  int vertical = 0;
  int r;
  int rows_number = 0;
  int history_number = 0;
  char line[100];
  char command[5] ;
  char rimanente[100];
  char history[20][100];*/
  
  uint8_t c;
  uart_init(UART0);
  vic_setup();
  cb_init(cb);
  vic_enable();
  vic_irq_enable(0,void (*uart_rx_handler)(void*), cookie);
  
  while (1) {
  
    while (!cb_empty(cb)){ //0 == uart_receive(UART0, &c     
    cb_get(cb, &c);
    if(c == 13) {
        uart_send(UART0, '\r');
        uart_send(UART0, '\n');
      } else {
        uart_send(UART0, c);
      }
   }  
   wfi();
 }	
}
  /*while (1) {
    unsigned char c;
    while ( 1 == uart_receive(UART0, &c)){
    if (c == 13)
       {
    
    r=0;
    line[i] = '\0';
        while(line[r] !='\0'){
            while(r<4){
            command[r]=line[r];
            r++;
            }
		r++;
            rimanente[r-5]=line[r];

        }
        rimanente[r]='\0';


     if(strcmp("reset", line) == 0){
         for(r=0; r<=rows_number; r++){
         	kprintf( "\033[2K\r");
         	kprintf("\33[1A");
         }
         
         rows_number = -1;
     }

     else if(strcmp("echo", command) == 0) {
         uart_send_string(UART0, "\n\r");
         uart_send_string(UART0, rimanente);
         rows_number++;

     }
     uart_send_string(UART0, "\n\r");
     //caricamento della linea sul buffer di operazione
     for (r=0; r<=i; r++)
     	history[history_number % 20][r] = line[r];  
     
     i=0;
     vertical = 0;
     orizontal = 0;
     rows_number++;
     history_number++;
     }
    else if (c == 127){
        kprintf( "\033[2K\r");
        
        if(orizontal == i){       
        line[i--] = "";
        orizontal = i; 
        }
        
         else{
         for(r=orizontal-1; r<i; r++)
            line[r] = line[r+1];
         line[i--] = "";
         orizontal--;         
         }
         for(r=0; r<i; r++)
           kprintf( "%c", line[r]);
         for(r=0; r<i-orizontal; r++){
           kprintf("\033[1D");
         }  
        
    }
    else if ( c == 27){
    	uart_receive(UART0, &c);
    	uart_receive(UART0, &c);
    	
    	if(c == 'A'){ //up arrow
    	if (vertical<20 && vertical < history_number)
    	   vertical++;
    	kprintf( "\033[2K\r");      	   
        kprintf( "%s", history[(history_number-vertical)%20]);
        r = 0;
        while(history[(history_number-vertical)%20][r]!='\0'){
              line[r] = history[(history_number-vertical)%20][r];
              r++;
              }
              i = r;
           }
    	  
    	
    	else if (c == 'B'){ //down arrow
    	if(vertical>0)
    	   vertical--;
    	kprintf( "\033[2K\r");
        kprintf( "%s", history[(history_number-vertical)%20]);
        r = 0;
        while(history[(history_number-vertical)%20][r]!='\0'){
              line[r] = history[(history_number-vertical)%20][r];
              r++;
              } 
              i = r;   	
    	}  
    	
    	else if (c == 'C'){ //right arrow
    	if(orizontal<i)
    	   orizontal++;
	   kprintf("\033[1C");
    		}  
    	
    	else if (c == 'D'){ //left arrow
    	  if(orizontal>0){
    	   orizontal--;
	   kprintf("\033[1D");
    	   }
    	}  
 
    	}
    else{
         if(orizontal == i){
           line[orizontal]=c;
           uart_send(UART0, c);
           i++;
           orizontal = i;
           }
         else{
         kprintf( "\033[2K\r");
         for(r=i; r>orizontal; r--)
            line[r] = line[r-1];
         line[orizontal] = c;
         orizontal++;
         i++;
         for(r=0; r<i; r++)
           kprintf( "%c", line[r]);
         for(r=0; r<i-orizontal; r++)
           kprintf("\033[1D");
         
         }
    }

    }
}
}*/




// \r permette di tornare all'inizio della riga
