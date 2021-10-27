
#include "BU6740AK.h"
#include <SPI.h>
#include <math.h>

BU6740AK Painel;

unsigned char n = 0 ;
unsigned char m = 0 ;

void Start(){
	SPI.beginTransaction(SPISettings(14000, MSBFIRST, SPI_MODE0));
}

void Stop(){
	SPI.endTransaction();
}

void SelectDevice() {
		 digitalWrite(53, 0);
}

void DeselectDevice() {
		 digitalWrite(53, 1);
}

unsigned int Send16(unsigned int s){
	 unsigned int r;
	 SelectDevice();
	 r = SPI.transfer(s >> 8) << 8;
   	 r = r | SPI.transfer(s & 0xFF);
	 DeselectDevice();
	return r;
}

char * int2char( unsigned char & _n , unsigned char size_buffer ){
	char _buffer[size_buffer];
	for (unsigned char i = (size_buffer -1 ); i >= 0 ; i--)
	{
		_buffer[i] = (_n % 10) - '//' ;
		_n /= 10 ;
	}		
}

// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(115200);

	Serial.println("Test!");

	pinMode(53, OUTPUT); 
	pinMode(MISO, INPUT);
	pinMode(MOSI, OUTPUT);
	pinMode(SCK, OUTPUT);
	digitalWrite(53,HIGH);

	Init(&Painel,Send16,Start,Stop);

	ClearScreen(&Painel);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	ClearScreen(&Painel);
	byte r = 0;

	GetKey(&Painel);
	
	if (Painel.KBState.Back) { r |= 1;  
	PrintIcon(&Painel,0, 0, Painel.KBState.Back * 3);}

	if (Painel.KBState.Down) { r |= 2; 
	PrintIcon(&Painel,1, 0, Painel.KBState.Down * 2);}

	if (Painel.KBState.Up) { r |= 4;  
	PrintIcon(&Painel,2, 0, Painel.KBState.Up * 1);}

	if (Painel.KBState.Help) { r |= 8;  
	PrintIcon(&Painel,3, 0, Painel.KBState.Help * 7);}

	if (Painel.KBState.Menu) { r |= 16; 
	PrintIcon(&Painel,4, 0, Painel.KBState.Menu * 4);}

	if (Painel.KBState.Stop) { r |= 32; 
	PrintIcon(&Painel,5, 0, Painel.KBState.Stop * 5);}

	if (Painel.KBState.Tick) { r |= 64; r |= 128; 
	PrintIcon(&Painel,31-8, 0, Painel.KBState.Tick * 6);
	
	}
	
	SetLeds(&Painel, r ^ 8);
	
  	PrintText(&Painel,n, 8 + 16 - ((cos(n)+1)*13), "Ola Mundo" , 9);
	//PrintText(&Painel,20,1, int2char(n,3) , 10);
	PrintText(&Painel,n + (PI), 8 + 16 - ((cos(n+(PI/2))+1)*13),"Tobias", 9 );
	//digitalWrite(53,LOW);
	Serial.println("N:" + String(n));
	n++;
	if(n > 16)
		n = 0 ;
	delay(200);
}
