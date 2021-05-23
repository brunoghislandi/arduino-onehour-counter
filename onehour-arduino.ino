/* Project compiled with Arduino IDE, 
 *  using pins 0,1,4,5,6,7,12 and 13
 *  to write on the display and 8 to
 *  11 to activate the display. Now
 *  we have external interrupts acting  
 *  as start/pause and reset buttons.
 *  Have a nice Coding. */

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

#define  A  0
#define  B  1
#define  C  4
#define  D  5
#define  E  6
#define  F  7
#define  G 12
#define DP 13

byte thousand = 0;
byte hundred  = 0;
byte tens     = 0;
byte unit     = 0;

byte seconds  = 0;
byte minutes  = 0;
byte count_ms = 0;

bool blinkDP  = 0;
bool start    = 0;

byte startDisplay[4] = 
{
  PB0,PB1,PB2,PB3
};

byte segments[] = 
{
  A,B,C,D,E,F,G,DP
};

byte numbers[][8] =
{
 {1,1,1,1,1,1,0,0}, //0
 {0,1,1,0,0,0,0,0}, //1
 {1,1,0,1,1,0,1,0}, //2
 {1,1,1,1,0,0,1,0}, //3
 {0,1,1,0,0,1,1,0}, //4
 {1,0,1,1,0,1,1,0}, //5
 {1,0,1,1,1,1,1,0}, //6
 {1,1,1,0,0,0,0,0}, //7
 {1,1,1,1,1,1,1,0}, //8
 {1,1,1,0,0,1,1,0}, //9
};

void pinWrite(int pin, int state)
{
  if(pin>=0 && pin<=7)
  {
    if(state==0)
    {
      PORTD &= ~(1<<pin);
    }
    else if(state==1)
    {
      PORTD |= (1<<pin);     
    }
  }
  else if(pin>=8 && pin<=13)
  {
    if(state==0)
    {
      PORTB &= ~(1<<pin-8);
    }
    else if(state==1)
    {
      PORTB |= (1<<pin-8);      
    }
  }
}

void setNumber(int form)
{
  for(int i = 0; i < 8; i++){
    pinWrite(segments[i],numbers[form][i]);
  }
}

void magic()
{
  if(start==1)
  {
    refreshDisplay();
    counter();
  }
  else if(start==0)
  {
    refreshDisplay();
  }
}

void counter(){
  
/* startDisplay takes 10ms to complete
 *  your cycle, so 10x100ms = 1seg, the
 *  time I set to update the Displays.
 *  
 *  WARNING: This time is not 100%
 *  accurate as it doens't take the
 *  reading time of the command lines.*/

  if(++count_ms>=100)
  {
    count_ms = 0;
    seconds++;
    blinkDP ^= 1;
  }
  if(seconds>59)
  {
    seconds = 0;
    minutes++;
  }
  if(minutes>59)
  {
    minutes = 0;
  }
}

void getData()
{
  thousand = minutes / 10;
  hundred  = minutes % 10;
  tens     = seconds / 10;
  unit     = seconds % 10;
}

void refreshDisplay()
{
  getData();
  
  clr_bit(PORTB,startDisplay[3]);
  clr_bit(PORTB,startDisplay[2]);
  clr_bit(PORTB,startDisplay[1]);
  clr_bit(PORTB,startDisplay[0]);
  delay(2);
  
  setNumber(unit);
  set_bit(PORTB,startDisplay[3]);
  delay(2);
  clr_bit(PORTB,startDisplay[3]);

  setNumber(tens);
  set_bit(PORTB,startDisplay[2]);
  delay(2);
  clr_bit(PORTB,startDisplay[2]);
  
  setNumber(hundred);
  if(blinkDP==1){
    set_bit(PORTB,segments[7]-8);
  }
  set_bit(PORTB,startDisplay[1]);
  delay(2);
  clr_bit(PORTB,startDisplay[1]);
  
  setNumber(thousand);
  set_bit(PORTB,startDisplay[0]);
  delay(2);
}

void resetDisplay()
{
  setNumber(0);
  set_bit(PORTB,startDisplay[3]);
  set_bit(PORTB,startDisplay[2]);
  set_bit(PORTB,startDisplay[1]);
  set_bit(PORTB,startDisplay[0]);
}

ISR(INT0_vect) // external interrupt INT0 (PD2)
{
  start ^= 1;
}

ISR(INT1_vect) // external interrupt INT1 (PD3)
{ 
  seconds = 0;
  minutes = 0;
  start =   0;
}

void setup() 
{
  cli();
  DDRD  = 0xF3;
  DDRB  = 0xFF;
  EICRA = 0xFF; // set INT1 and INT0 with falling (press the button).
  EIMSK = 0x03; // ebable interrupts with INT0 and INT1.
  sei();
}

void loop() 
{
  magic();
}