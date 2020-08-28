#include <Wire.h>
#include <Adafruit_ADS1015.h>

 Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */

//int CalibrationPin = D6;
int WirePin = D7;
int sensorPin = D8;

float temp; //Global definition for usinf in different voids!
char temp_char[8]; // Buffer big enough for 7-character float

const char DEGREE_SYMBOL[] = { 0xB0, '\0' };
char* dimension1 = " C";

#include "Display.h"


void setup() 
{

  setup_display();
  display_logo();
  display_project();
  
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  //pinMode(CalibrationPin, OUTPUT);
  pinMode(sensorPin, OUTPUT);
  pinMode(WirePin, OUTPUT);

  //digitalWrite(CalibrationPin, HIGH);
  digitalWrite(sensorPin, LOW);
  digitalWrite(WirePin, LOW);
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
     ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();
}

void loop() 
{

  

  float R1 = 100; // R1 hat 100 Ohm
  //float U0 = 3.3; // Ausgangsspannung 3,3 Volt
  
  int16_t adc0, adc1, adc2, adc3;
  int ptCount=0, WireCount=0;
  float R2=0, R2_Mean=0, R2_Sum=0;
  float U0=0, U0_Mean=0, U0_Sum=0;
  float U1=0;
  float U2=0, U2_Mean=0, U2_Sum=0;
  
  Serial.println("PT-Widerstand: ");
  //digitalWrite(sensorPin, HIGH);
  //digitalWrite(WirePin, LOW);
  //delay(500);

  while(ptCount < 10){
    digitalWrite(sensorPin, HIGH);
    delay(50);
    adc0 = ads.readADC_SingleEnded(0);
    U0 = adc0 * 0.125 * 0.001;
    //Serial.print("U0: "); Serial.println(U0,5);
    U0_Sum = U0_Sum + U0;

    adc1 = ads.readADC_SingleEnded(1);
    U2 = adc1 * 0.125 * 0.001;
    //Serial.print("U2: "); Serial.println(U2,5);
    U2_Sum = U2_Sum + U2;

    R2 = (U2*R1)/(U0-U2);
    //Serial.print("R2: "); Serial.println(R2,5);
    R2_Sum = R2_Sum + R2;

    digitalWrite(sensorPin, LOW);
    ptCount++;
    //delay(10);
  }

  U0_Mean = U0_Sum / ptCount;
  Serial.print("U0 Mean: "); Serial.println(U0_Mean,5);

  U2_Mean = U2_Sum / ptCount;
  Serial.print("U2 Mean: "); Serial.println(U2_Mean,5);

  R2_Mean = R2_Sum / ptCount;
  Serial.print("R2 Mean: "); Serial.println(R2_Mean,5);

 // Leitungswiderstand ermitteln ##################################################

  Serial.println("Leitungswiderstand: ");
  //digitalWrite(sensorPin, LOW);
  //digitalWrite(WirePin, HIGH);
  //delay(500);

  float R3 = 1; // R1 hat 100 Ohm
  float R4=0, R4_Mean=0, R4_Sum=0; 
  float U3=0; 
  float U4=0, U4_Mean=0, U4_Sum=0; 
  float U5=0, U5_Mean=0, U5_Sum=0;

  while(WireCount < 10){
    digitalWrite(WirePin, HIGH);
    delay(50);
    adc2 = ads.readADC_SingleEnded(2);
    U5 = adc2 * 0.125 * 0.001;
    //Serial.print("U5: "); Serial.println(U5,8);
    U5_Sum = U5_Sum + U5;

    adc3 = ads.readADC_SingleEnded(3);
    U4 = adc3 * 0.125 * 0.001;
    //Serial.print("U4: "); Serial.println(U4,8);
    U4_Sum = U4_Sum + U4;

    //U3 = U5-U4;
    //Serial.print("U3: "); Serial.println(U3,5);

    R4 = (U4*R3)/(U5-U4);
    //Serial.print("R4: "); Serial.println(R4,5);
    R4_Sum = R4_Sum + R4;
    digitalWrite(WirePin, LOW);
    //delay(10);
    WireCount++;
    
  }

  U5_Mean = U5_Sum / WireCount;
  Serial.print("U5 Mean: "); Serial.println(U5_Mean,5);

  U4_Mean = U4_Sum / WireCount;
  Serial.print("U4 Mean: "); Serial.println(U4_Mean,5);

  R4_Mean = R4_Sum / WireCount;
  Serial.print("R4 Mean: "); Serial.println(R4_Mean,5);


  float R_PT100 = R2_Mean - R4_Mean;
  Serial.print("PT100: "); Serial.print(R_PT100,5); Serial.println(" Ohm");

  // Temnperatur basierend auf Widerstand berechnen

  //float A = pow( 3.9083 * pow(10,-3) , -1);
  float A = 3.9083 * pow(10,-3);
  Serial.print("A: "); Serial.println(A,5);
  //float B = pow (-5.775 * pow(10,-7) , -2);
  float B = -5.775 * pow(10,-7);
  Serial.print("B: "); Serial.println(B,10);
  float R0 = 100;

  temp =  ( (-(A*R0)) +    sqrt ( pow((A*R0),2) - (4*B*R0 * (R0-R_PT100)) ) ) / (2 * B * R0)  ;
  Serial.print("Temperatur: "); Serial.print(temp,2); Serial.println(" °C");
  
  Serial.println();


  dtostrf(temp, 5, 2, temp_char); // Leave room for too large numbers!

  strcat(temp_char, " "); //Leerzeichen vor der Einheit

  
  strcat(temp_char, DEGREE_SYMBOL);
  
  strcat(temp_char, "C");
  
  //Serial.println(temp_char);
  
  display_temperature();
  
  delay(2000); //NUr um am seriellen Monitor was erkennezu können aktivieren // Abkülung der Widerstände und Leitungen
}
