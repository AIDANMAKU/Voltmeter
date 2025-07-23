//Electric Charge detector by Aidan Makumbe R.T

#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LiquidCrystal I2C By Frank de Brabander

LiquidCrystal_I2C lcd(0x3F, 16, 2); // Setting up the LCD Address, size

const int probePin = A0; // Pin connected to the probe I'll use to test for charge
const int potPin = A1; // Pin connected to the potentiometer
const int ledPin = 6; // Use Pin 6 for utilization of Pulse-Width-Modulation (PWM)
const int buzzerPin = 4; // Pin connected to Buzzer

void setup() {
  //Declaring the LED and Buzzer as Outputs
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  //Initialising the lcd
  lcd.init();
  lcd.backlight();

  //Begining Serial lines for Debugging purposes
  Serial.begin(9600);
}

void loop() {

  float chargeReading = analogRead(probePin); // Collecting the input from the analog pin
  float voltage = (chargeReading / 1024.0)* 5.0; // Calculate the voltage
  float threshhold = analogRead(potPin)/204.6;  //map(analogRead(potPin), 0, 1023, 0, 1000); // Mapping the Threshold put forth by the potentiometer to 1000 scale  
  float led_brightness = map(voltage, 0.0, 5, 0, 255); // Mapping the brightness of the LED from the charge to the maximum value off 255
  //float buzzer_frequency = map(voltage, 0.0, 5, 0,255); // Mapping the reading from the probe pin to that of the buzzer i.e buzzer max frequency 1Khz

  analogWrite(ledPin, led_brightness);// Set the brightness of the 12C_LCD

  //Adding Text to The LCD
  lcd.setCursor(0, 0); // Setting cursor to top left corner
  lcd.print("Voltage:");
  lcd.print(voltage, 2); //Display voltage with 2 decimal places
  lcd.print("V");
  lcd.setCursor(0, 1); // Setting cursor to top left corner
  lcd.print("Threshold:");
  lcd.print(threshhold); //Display threshhold in percentage
  lcd.setCursor(15,1);
  lcd.print("V");


  if (voltage >= threshhold){
    lcd.setCursor(14, 0);
    lcd.print("HI");
    tone(buzzerPin, 1000, 600);
       //Logging the Output to the Computer Via Serial at 9600 bauds
    Serial.print("Voltage : ");
    Serial.print(voltage,2);
    Serial.print(" HI ");
    Serial.print(" Threshhold : ");
    Serial.print(threshhold);
    Serial.println("V");
  }
  else{
    //tone(buzzerPin);
    lcd.setCursor(14,0);
    lcd.print("LO");
       //Logging the Output to the Computer Via Serial at 9600 bauds
    Serial.print("Voltage : ");
    Serial.print(voltage,2);
    Serial.print(" LO ");
    Serial.print(" Threshhold : ");
    Serial.print(threshhold);
    Serial.println("V");
    
  }
  delay(500);

}
