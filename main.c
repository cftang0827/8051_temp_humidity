
#include<reg52.h>
#include <stdio.h>


#define display_port P2      //Data pins connected to port 2 on microcontroller
sbit rs = P3^2;  			 //RS pin connected to pin 2 of port 3
sbit rw = P3^3;  			 // RW pin connected to pin 3 of port 3
sbit e =  P3^4;              //E pin connected to pin 4 of port 3


sbit dat = 0x91;



char code err[] = "Error!!\n";
char code err2[] = "Error2\n";
char code erro[] = "ss\n";
char code erro2[] = "ss2\n";
void send_string(char *mes);

int I_RH, D_RH, I_T, D_T, CheckSum;

int humidity, temperature;

void timer_usec(unsigned int usec)
{
    TMOD = 0x01;
    TH0 = (65536 - usec) / 256;
    TL0 = (65536 - usec) % 256;
    TR0 = 1;
    while(TF0 == 0);
    TF0 = 0;
    TR0 = 0;
}


void us_delay(unsigned int time)  // Function for creating delay in usecs.
{
    unsigned int i;
    for(i = 1; i < time; i++);
}

void lcd_cmd(unsigned char command)  //Function to send command instruction to LCD by using 4 bit mode
{
    display_port = (command & 0xF0 );
    rs = 0;
    rw = 0;
    e = 1;
    us_delay(300);
    e = 0;
    us_delay(1000);

    display_port = ( (command << 4 ) & 0xF0 );
    rs= 0;
    rw=0;
    e=1;
    us_delay(300);
    e=0;   
    us_delay(1000); 
}
void lcd_data(unsigned char disp_data)  //Function to send display data to LCD
{
    display_port = (disp_data & 0xF0);
    rs= 1;
    rw=0;
    e=1;
    us_delay(300);
    e=0;

    us_delay(1000);

    display_port = ( (disp_data << 4) & 0xF0);
    rs= 1;
    rw=0;
    e=1;
    us_delay(300);
    e=0;
    us_delay(1000);

}

void lcd_init()     //Function to prepare the LCD  and get it ready
{
    lcd_cmd(0x28);  // 4 bit mode and 2 line display
    lcd_cmd(0x0C);  // display on cursor off
    lcd_cmd(0x06);  // entry mode
    lcd_cmd(0x01);  // clear display
    lcd_cmd(0x02);  // return home
    lcd_cmd(0x80);  // move cursor to the begining
}

void uart_init()
{
	SCON = 0x50;			/* uart in mode 1 (8 bit), REN=1 */
	T2CON &= 0xF0;			/* EXEN2=0; TR2=0; C/T2#=0; CP/RL2#=0; */
	T2CON |= 0x30;			/* RCLK = 1; TCLK=1; */
	TH2 = 0xFF;
	TL2 = 0xDC;
	RCAP2H = 0xFF;
	RCAP2L = 0xDC;			
	TR2 = 1;			    /* Timer 2 run */
	TI = 1;
	RI = 0;
}

    
void write_string(char *s)
{
    unsigned int l = 0;
    unsigned int ii = 0;

    while(s[l] != '\0')
    {
        lcd_data(s[l]);
        l++;
        timer_usec(300);       
    }
}


int strlen(char *s)
{
	unsigned int length = 0;
	while(s[length] != '\0')
	{
		length++;
	}
	return length;
}

int char2int(char i)
{
	return (int)i - 48;
}

int pow_10(int power)
{
    int ans = 1;
    int i = 0;
	for(i = 0; i < power; i++){
		ans = ans * 10;
	}
	return ans;
}

int str2int(char* s)
{
	int ans = 0;
	int length = strlen(s);
	unsigned int i = 0;
	for(i = 0; i < length; i++)
	{
		ans += pow_10( (length-i-1)) * char2int(s[i]);
	}
	return ans;
}

char int2char(int i)
{
	return (char)i + 48;
}

void timer_delay20ms()		/* Timer0 delay function */
{
	TMOD = 0x01;
	TH0 = 0xB8;		        /* Load higher 8-bit in TH0 */
	TL0 = 0x0C;		        /* Load lower 8-bit in TL0 */
	TR0 = 1;		        /* Start timer0 */
	while(TF0 == 0);	    /* Wait until timer0 flag set */
	TR0 = 0;		        /* Stop timer0 */
	TF0 = 0;		        /* Clear timer0 flag */
}

void timer_delay30us()		/* Timer0 delay function */
{
	TMOD = 0x01;		    /* Timer0 mode1 (16-bit timer mode) */
	TH0 = 0xFF;		        /* Load higher 8-bit in TH0 */
	TL0 = 0xF1;		        /* Load lower 8-bit in TL0 */
	TR0 = 1;		        /* Start timer0 */
	while(TF0 == 0);	    /* Wait until timer0 flag set */
	TR0 = 0;		        /* Stop timer0 */
	TF0 = 0;		        /* Clear timer0 flag */
}

char uart_getc()
{
    char tmp;
    while(!RI);
    tmp = SBUF;
    RI = 0;
    return(tmp);
}

void int2str(int ii, char* s)
{
	int length = strlen(s);
	unsigned int i = 0;
	for(i = 0; i < length; i++)
	{
		s[i] = int2char( ii / pow_10( (length-i-1) ) );
		ii = ii % pow_10( (length-i-1) );
	}
}

unsigned char serial_read()
{
    while(!RI);
    RI = 0;
    return SBUF;
}

void serial_send(unsigned char dat)
{
    while(!TI);
    TI = 0;
    SBUF = dat;
}

void new_request()
{
    dat = 0;
    us_delay(1000);
    dat = 1;
}

void new_response()
{

    while(dat==1);  
    while(dat==0);
    while(dat==1); 
}



void at2302_request()
{      
    dat = 0;
    timer_delay20ms();
    dat = 1;
}

void at2302_response()
{  
    while(dat==1);
    while(dat==0);
    while(dat==1); 
}

void send_string(char *mes)
{
    char *buf;
    for(buf = mes; *buf != '\0';)
    {
        SBUF=*buf++;
        while(TI == 0);
        TI = 0;
    }
}

int receive_data()
{
    int ii = 0;
    int i = 0;
    int c = 0;
    int highCount = 0;
    int lowCount = 0;    
    char ss1[5];
   
    
    
    for(ii = 0; ii < 8; ii++)
    {
        highCount = 0;
        lowCount = 0;
        while(dat==0);
        // {
        //     lowCount++;
        // }
      
        while(dat==1)
        {
            highCount++;
        }    
          
        if(highCount > 5)
        {
            c = (c<<1) | (0x01);
        }else{
            c = (c<<1);
        }

    }

    
    return c;
}


char cmd;
void main()
{

    int ii = 1;
    char ss1[18];
    char ss2[18];
    
    lcd_init();
    uart_init();
    dat = 1;
    while(1)
    {
        cmd = uart_getc();
        while(cmd != 'a');        
        while(1)
        {



            new_request();
            new_response();
            I_RH = receive_data();
            D_RH = receive_data();
            I_T = receive_data();
            D_T = receive_data();
            CheckSum = receive_data();
        

            humidity = I_RH * 256 + D_RH;
            temperature = I_T * 256 + D_T;

            // sprintf(ss1,"I_RH=%d\n",I_RH);
            // send_string(ss1);

            // sprintf(ss1,"D_RH=%d\n", D_RH);
            // send_string(ss1);

            // sprintf(ss1,"I_T=%d\n", I_T);
            // send_string(ss1);
            
            // sprintf(ss1,"D_T=%d\n", D_T);
            // send_string(ss1);
            
            // sprintf(ss1,"CheckSum=%d\n", CheckSum);
            // send_string(ss1);                


            if((I_RH + D_RH + I_T + D_T) != CheckSum )
            {
                lcd_init();
                write_string(err);
                us_delay(2000000);        
            }else
            {
                sprintf(ss2,"Hum: %d.%d %%",humidity/10,humidity%10);
                sprintf(ss1,"H%d.%d\n",humidity/10,humidity%10);
                send_string(ss1);
                lcd_cmd(0x80);
                write_string(ss2);

                sprintf(ss2,"Temp: %d.%d C", temperature / 10,temperature%10);
                sprintf(ss1,"T%d.%d\n",temperature / 10,temperature%10);
                send_string(ss1);
                lcd_cmd(0xC0);
                write_string(ss2); 
                us_delay(2000000);
            }
        }


    }
}

