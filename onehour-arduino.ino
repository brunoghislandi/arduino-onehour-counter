/* Project compiled with Arduino IDE, 
 *  using pins 0 to 7 to write on the 
 *  display and 8 to 11 to activate 
 *  the display. Have a nice Coding. */

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

char thousand = 0;
char hundred  = 0;
char tens     = 0;
char unit     = 0;

char seconds  = 0;
char minutes  = 0;
char count_ms = 0;

bool blinkDP  = 0;

int startDisplay[4] = 
{
  PB0,PB1,PB2,PB3
};

const char numbers[] = 
{
  0b00111111, //0
  0b00000110, //1
  0b01011011, //2
  0b01001111, //3
  0b01100110, //4
  0b01101101, //5
  0b01111101, //6
  0b00000111, //7
  0b01111111, //8
  0b01101111, //9
  0b00000000 //10
};

void refreshDisplay()
{
  PORTD = numbers[10];
  clr_bit(PORTB,startDisplay[3]);
  clr_bit(PORTB,startDisplay[2]);
  clr_bit(PORTB,startDisplay[1]);
  clr_bit(PORTB,startDisplay[0]);
  delay(2);
  PORTD = numbers[unit];
  set_bit(PORTB,startDisplay[3]);
  delay(2);
  clr_bit(PORTB,startDisplay[3]);
  PORTD = numbers[tens];
  set_bit(PORTB,startDisplay[2]);
  delay(2);
  clr_bit(PORTB,startDisplay[2]);
  PORTD  = numbers[hundred];
  if(blinkDP==1){
    PORTD |= 0x80;
  }
  set_bit(PORTB,startDisplay[1]);
  delay(2);
  clr_bit(PORTB,startDisplay[1]);
  PORTD = numbers[thousand];
  set_bit(PORTB,startDisplay[0]);
  delay(2);
}

void setup() 
{
  DDRD = 0xFF;
  DDRB = 0x0F;
}

void loop() 
{
  thousand = minutes / 10;
  hundred  = minutes % 10;
  tens     = seconds / 10;
  unit     = seconds % 10;
  
  refreshDisplay();

/* startDisplay takes 10ms to complete
 *  your cycle, so 10x100ms = 1seg, the
 *  time I set to update the Displays.
 *  
 *  WARNING: This time is not 100%
 *  accurate as it doens't take the
 *  reading time of the command lines.*/

  if(++count_ms>=100){
    count_ms = 0;
    seconds++;
    blinkDP ^= 1;
  }
  if(seconds>59){
    seconds = 0;
    minutes++;
  }
  if(minutes>59){
    minutes = 0;
  }
}
