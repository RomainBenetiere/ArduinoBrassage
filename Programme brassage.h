// Declaration libraries utilisées

#include <Indio.h>
#include <Wire.h>

#include <UC1701.h>
static UC1701 lcd;

/* les points ci dessous decrivent ce que font les appuis sur les boutons
#####################################################################################
*/

#include <Indio.h>
#include <Wire.h>

#include <UC1701.h>
static UC1701 lcd;

volatile int counter = 0;
volatile int valid = 0;


void setup() {

  SerialUSB.begin(9600);
  lcd.begin();

  attachInterrupt(24, enter, FALLING);      // D24 is the Enter button (pull-up)
  attachInterrupt(25, up, FALLING);      // D25 is the Up button (pull-up)
  attachInterrupt(23, down, FALLING);      // D23 is the Down button (pull-up)

}


/* valider mode (1: "empattage", 2: "pallier enzymatique 1", 3: "pallier enzymatique 2", 4: "inactivation enzyme", 5: "test 100C") */
void enter() {
  SerialUSB.println("enter");
  valid = counter;
}

/* si up alors passer au mode suivant (1: "empattage", 2: "pallier enzymatique 1", 3: "pallier enzymatique 2", 4: "inactivation enzyme", 5: "test 100C") */
void up() {
  if (counter < 5) {
    counter=counter+1;
  }
  else {
    counter = 1;
  }
  SerialUSB.print(counter);
  SerialUSB.println("up");
}
/* si up alors passer au mode precedent (1: "empattage", 2: "pallier enzymatique 1", 3: "pallier enzymatique 2", 4: "inactivation enzyme", 5: "test 100C") */
void down() {
    if (counter > 1) {
    counter=counter-1;
  }
  else {
    counter = 5;
  }
  SerialUSB.print(counter);
  SerialUSB.println("down");
}

void loop() {
}

/*####################################################################################################*/

float sensorVal1, sensorVal2, sensorVal3, sensorVal4; //variables to hold your sensor data

void setup()
{
  
  SerialUSB.begin(9600); 
   while (!SerialUSB)
  Indio.setADCResolution(18); // Set the ADC resolution. Choices are 12bit@240SPS, 14bit@60SPS, 16bit@15SPS and 18bit@3.75SPS.

  Indio.analogReadMode(1, mA_p); // Set Analog-In CH1 to 10V mode (0-10V).
  Indio.analogReadMode(2, mA_p); // Set Analog-In CH2 to % 10V mode (0-10V -> 0-100%).
  Indio.analogReadMode(3, mA_p); // Set Analog-In CH3 to mA mode (0-20mA).
  Indio.analogReadMode(4, mA_p); // Set Analog-In CH4 to % mA mode (4-20mA -> 0-100%)
//  Indio.analogReadMode(4, V5); // Set Analog-In CH4 to 5V mode (2x gain enabled on ADC).
//  Indio.analogReadMode(4, V5_p); // Set Analog-In CH4 to 5V mode (0-5V -> 0-100%).
//  Indio.analogReadMode(4, V10_raw); // Set Analog-In CH4 to 10V mode and read raw ADC value (0-10V -> 0-4096).
//  Indio.analogReadMode(4, mA_raw); // Set Analog-In CH4 to mA mode and read raw ADC value (0-20mA -> 0-4096).
  
 }

void loop()
{

  sensorVal1=Indio.analogRead(1); //Read Analog-In CH1 (output depending on selected mode)
  SerialUSB.print("CH1: "); //Print "CH" for human readability
  SerialUSB.print(sensorVal1*200/100
  , 1); //Print data
  SerialUSB.print("  "); //Add some "  " space
  

  sensorVal2=Indio.analogRead(2); //Read Analog-In CH1 (output depending on selected mode)
  SerialUSB.print("CH2: "); //Print "CH" for human readability
  SerialUSB.print(sensorVal2, 3); //Print data
  SerialUSB.print("  "); //Add some "  " space


  sensorVal3=Indio.analogRead(3); //Read Analog-In CH1 (output depending on selected mode)
  SerialUSB.print("CH3: "); //Print "CH" for human readability
  SerialUSB.print(sensorVal3, 3); //Print data
  SerialUSB.print("  "); //Add some "  " space
 

  sensorVal4=Indio.analogRead(4); //Read Analog-In CH1 (output depending on selected mode)
  SerialUSB.print("CH4: "); //Print "CH" for human readability
  SerialUSB.print(sensorVal4, 3); //Print data
  SerialUSB.print("  "); //Add some "  " space
 
  SerialUSB.print("\r\n"); // Print a new line to SerialUSB.

}
