// C library headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Linux headers
#include <time.h>	// Contains sleep function
#include <fcntl.h>	// Contains file controls like O_RDWR
#include <unistd.h>	// Contains write(), read(), close()

//Hocam normalde yorum satırlarıyla açıklamalarım vardı. Arduino bozulunca back-up olarak aldığım dosyaları tekrardan çalıştırdım süre azaldığı için.
//Videoyu da bu haliyle çektiğim için yorum satırı eklemedim.

int main()
{
	//opens and closes serial port
	char serialPort_tty = open("/dev/ttyUSB0", O_NOCTTY);	
	
	//sends data to arduino and recieves data from arduino
	char serialPort_write = open("/dev/ttyUSB0", O_RDWR);
	
	//an open for reading-only will return without delay
	char serialPort_nonblock = open("/dev/ttyUSB0", O_NONBLOCK);						
	
	char menu[10];	//
	int Operations;
	

	
	printf("## WELCOME TO GTU ARDUINO LAB        ##\n");
	printf("## STUDENT NAME: YUSUF ARSLAN		  ##\n");
	printf("## PLEASE SELECT FROM THE FOLLOWING  ##\n");

	while (1)
	{
		printf("## MENU :                            ##\n");
		printf("(1) TURN ON LED ON ARDUINO\n");
		printf("(2) TURN OFF LED ON ARDUINO\n");
		printf("(3) FLASH ARDUINO LED 3 TIMES\n");
		printf("(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO\n");
		printf("(5) BUTTON PRESS COUNTER\n");
		printf("(0) EXIT\n");
		printf("PLEASE SELECT:	");
		scanf("%s", menu);		
		
		Operations = atoi(menu);
		
		switch (Operations)
		{
		
			case 0:
			{								
				return 0;
				break;												
			}																
			
			//led on																	
			case 1:	
			{
				sleep (0.75);
				write(serialPort_write,"1",2);
				printf ("\n");	
				close(serialPort_tty);
				break;															
			}																				
			
			//led off																					
			case 2:
			{			
				sleep (0.75);
				write(serialPort_write,"2",1);  
				printf ("\n");                                                      
				close(serialPort_tty);
				break;																	
			}																					
			
			//blink 3 time																						
			case 3:
			{															
				sleep (0.75);
				write(serialPort_write,"3",1);
				printf ("\n");														
				close(serialPort_tty);
				break;																		
			}																									
			
			//square of a number																 
			case 4:
			{	
				char number[10];      
				char index[9];						
				int byte;										
				unsigned char read_number;								
				int square;	
												
				sleep (1);
				write(serialPort_write,"4",1);
					
				printf("\nEnter a number :  ");
				scanf("%s",number);								
			
				byte = strlen(number);							
				write(serialPort_write,number,byte);
			
				sleep (4);	
											
				read_number = read(serialPort_write,index,9);		
				printf("\n%s^2 = %d\n\n",number, atoi(index));	
				close(serialPort_tty);	
				break;
			}
			
			//button counter
			case 5: 
			{
				unsigned char read_number;
				unsigned char check_number;
				char index[99] = "";
				int check = 1;
				sleep(1);
				printf ("\nPlease press the buton.\n");
				
				do
				{
					write(serialPort_write, "5", 1);
					sleep (1);
					
					read_number = read(serialPort_write,index,99);
					if (*index == 'Q')
					{
						printf("\n");
						break;
					}
					printf ("%s", index);
					sleep (1);
					
					
				}while (1);	
				close(serialPort_tty);
				break;
				
			}
		}

	}
	
	close(serialPort_tty);
	
	return 0;
}


	
	
