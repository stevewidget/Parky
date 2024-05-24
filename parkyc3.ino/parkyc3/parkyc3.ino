//Parky - Parkinson glove software SNC Remap April 2024
// Based on work done here
// github.com/pdbuzzboard/pdbuzzboard 



#include <TLC591x.h>
#include <gButton.h>

unsigned int FINGER_ON_TIME = 167;
unsigned int FINGER_OFF_TIME = 66;
unsigned int FRAME_OFF_TIME = 1000;
#define ONLED_PIN 7
const byte BUTTON = 2;
long debouncing_time = 15; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
unsigned long StartLoopTime= 0;
unsigned int  Minutes = 5;
unsigned long LoopTime = Minutes *60*1000; // in millis
volatile byte Onstate = LOW;
byte ledState = LOW;
unsigned long debounceDuration = 50; // millis
unsigned long lastTimeButtonStateChanged = 0;

// setup array of pin no's for output 
int motorPin[]= {0x11,0x22,0x44,0x88};
// First parameter in constructor is # of TLC591x chips -- this example assumes 2 chips
// Constructor parameters: # of chips, SDI in, CLK pin, LE pin, OE pin (optional parameter)
//TLC591x myLED(2, 7, 8, 9);    // Uncomment if not using OE pin
TLC591x myLED(1, 10, 8, 4, 5);
void randFinger(int *F){ //Generate a 4 finger random sequence
  F[0]=0;F[1]=1; F[2]=2; F[3]=3;
 int i,j,t;
  for(i=0;i<4;i++){
    t = F[i];
  j = random(0,4); // 0-3
    F[i]=F[j];
    F[j]=t;
  }
 
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    Interrupt();
    last_micros = micros();
  }
}

void Interrupt() {
  Serial.print("£");
   if (Onstate){
      Onstate = 0;
      digitalWrite(ONLED_PIN,0);
      Serial.print("Onstate= 0");
    }
  else {
    Onstate = 1;
    digitalWrite(ONLED_PIN,1);
    Serial.print("Onstate=1");
    }
}

void setup() {
  int i=0;
  Serial.begin(115200);
  Serial.println("Motor test!");
  randomSeed(analogRead(A0));  
  myLED.displayEnable();  
  pinMode(15,OUTPUT);
  pinMode(ONLED_PIN, OUTPUT);
  const byte BUTTON = 2;
   attachInterrupt(digitalPinToInterrupt (BUTTON), debounceInterrupt, RISING);
}
void loop() {
  int i;
  char s[9];
  s[0] =32;
  //Serial.println("Start ");
 /* int loopcount = 0;
  while (Onstate){
  //  Serial.print("W ");
    if ( loopcount < 50){
     Serial.print(" L=");
     Serial.print(loopcount);

     */
    int Finger[12]; 

  randFinger(Finger); randFinger(Finger+4); randFinger(Finger+8);   //Set random order for 3 sets of 4 fingers into the Finger array
  //Serial.printf("%d%d%d%d-%d%d%d%d-%d%d%d%d\n",Finger[0]+1,Finger[1]+1,Finger[2]+1,Finger[3]+1,Finger[4]+1,Finger[5]+1,Finger[6]+1,Finger[7]+1,Finger[8]+1,Finger[9]+1,Finger[10]+1,Finger[11]+1);
 //  Serial.print(Finger[0]+1,Finger[1]+1,Finger[2]+1,Finger[3]+1,"_",Finger[4]+1,Finger[5]+1,Finger[6]+1,Finger[7]+1,"_",Finger[8]+1,Finger[9]+1,Finger[10]+1,Finger[11]+1);
 /* int k=0;
  int i=0;
  for(int j=0;j<3;j++){
   for( i=0;i<4;i++){
      Serial.print(Finger[i+k]);
   }
  Serial.print("-");
  k=k+4;
  }
  Serial.println();
*/
// One frame takes 3.67 secs so 1 hour approx 980 loops
  for(int i=0;i<12;i++){
  int opin=Finger[i];
    myLED.print(motorPin[opin]);
    delay(FINGER_ON_TIME);   
	myLED.print(s);
    delay(FINGER_OFF_TIME);
  }
  digitalWrite(17, HIGH);
  delay(FRAME_OFF_TIME);
  digitalWrite(17, LOW);     
 // loopcount++;
/*} //if loopcount
else
{
  Interrupt(); //Period ended so stop
}
}// While Onstate */
}  //Loop