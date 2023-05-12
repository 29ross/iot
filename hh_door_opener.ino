#include <Servo.h>
#include "LowPower.h"


const int wakeUpPin = 2;
const int buttonPin = 3;
const int buzzerPin = 4;
const int ledPin = 5;
const int servoPin = 12;
int keypadPin = A0;
int analogVals[3][2] = { {985, 1015}, {960, 984}, {915, 945}};
int passcode[6] ={1,2,2,1,3,2};


// Use pin 2 as wake up pin

int getKey() {
  int gotVal = 0;
  int buttonVal = 0; 
  
  while (!gotVal) {
  
    int val = analogRead(keypadPin);
    for (int i=0; i<3; i++) {
        //if (val>15) Serial.println(val);

        if (val>analogVals[i][0] && val <=analogVals[i][1])  {
          gotVal=1;
          buttonVal=i;
        }

	    Serial.print("Got buttonpress ");
	    Serial.println(key+1);

       if (gotVal==1) {
          delay(350);  // debounce the button press
          return(buttonVal);
       }
    }
  }
}


int checkPasscode() {
	//todo give up after an amount of millis
	int entered[6]={0,0,0,0,0,0};
	
	for (int i=0;i<6;i++) 
		entered[i] = getKey(); 
	
	for (int j=0;j<6;j++)
		if (entered[j]!= passcode[j])
			return 0;
		
	return 1;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  
  pinMode(servoPin, OUTPUT);
  pinMode(buttonPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPIN, OUTPUT);
  pinMode(wakeUpPin, INPUT);
  
  for (int i=0;i<3;i++) {
    Serial.print(analogVals[i][0]); 
    Serial.print(",");
    Serial.println(analogVals[i][1]);
  }
}


void loop() {
  
   
   attachInterrupt(0, wakeUp, LOW);

   // Enter power down state with ADC and BOD module disabled.
   // Wake up when wake up pin is low.
   LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

   // Disable external pin interrupt on wake up pin.
   detachInterrupt(0);
   
  
  // put your main code here, to run repeatedly:
  Serial.println("starting");
  // Flash LED
  
  // add trigger for wakeup
  int loginOK = checkPassocode();
  if (loginOK) {
	Serial.println("login OK");
	// Flash LED fast
	// operate servo 
  } else {
	Serial.println("login Failed");
	// Flash LED slow
  }
  

  
}
