//Daxton Johnson, Kirk Johnson

volatile unsigned char* port_k = (unsigned char*) 0x108; 
volatile unsigned char* ddr_k  = (unsigned char*) 0x107; 
volatile unsigned char* pin_k  = (unsigned char*) 0x106; 
volatile unsigned char* port_d = (unsigned char*) 0x2B; 
volatile unsigned char* ddr_d  = (unsigned char*) 0x2A; 
volatile unsigned char* pin_d  = (unsigned char*) 0x29; 
volatile unsigned char* port_e = (unsigned char*) 0x2E; 
volatile unsigned char* ddr_e  = (unsigned char*) 0x2D; 
volatile unsigned char* pin_e  = (unsigned char*) 0x2C; 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  *ddr_k &= 0xFB;
  *ddr_d |= 0x01;
  *ddr_e |= 0x08;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(*pin_k & 0x04){
    *port_d |= 0x01;
    *port_e &= 0xF7; 
  } else {
    *port_d &= 0xFE;
    *port_e |= 0x08;
  }
  delay(100);
}
