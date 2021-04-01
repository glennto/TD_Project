/*
 Sketch to read temperatures from a series of Maxim DS18B20 temperature
 sensors and display the result on an LCD screen.
 Hardware:
    Arduino Nano or equiv
    Adafruit 24x2 LCD display
    Adafruit i2c/SPI LCD backpack
    http://www.ladyada.net/products/i2cspilcdbackpack/index.html )
        * 5V to Arduino Nano 5V pin
        * GND to Arduino Nano GND pin
        * * CLK to Nano Analog #5
        * DAT to Nano Analog #4
  DS18B20:
    * DQ to Arduino Nano pin D8 (ATMEL PB0)
    * +5V
    * Ground
    * 4.7K pullup R +5V to DQ

 Software:
    OneWire Library
    DallasTemperature Library
    Adafruit LiquidCrystal

    Note: Because we are only displaying temperatures on the bottom line of the LCD display
          this software limits the display to four positive temperature values (even if there are
          more than four (seriously?) sensors)
 
 Written by
      Glenn Tober
      
  Version 0.1
      03/28/2021
  Initial release. Added displayOrder array to make it possible to reorder the temperature
  display list (since in the case of multiple sensors, while the order is always fixed, 
  one does not know which physical sensor is which when displayed (you must test each sensor
  with temperature change and observe results to determine which is which. Use displayOrder{}
  to rearrange temperatures in the order you like.
*/

// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_LiquidCrystal.h>

// Debug printing flag
//#define DEBUG

// digital input pin that will determine units display (open -  deg F) or (ground - deg C)
#define degSet 2

// F is software set for units (digital input pin degSet must be left open for software set)
// if you want digital input pin degSet to determine units instead
// (an external switch could determine the units for example) then leave F = true
// and either leave degSet open (for deg F) or ground it (for deg C)

bool F = true;  // software units set (true for farenheiht or false for celsius)
bool F2 = F;

// DS18B20 DQ wire is plugged into port D8 on the Arduino
// Adjust accordingly
#define ONE_WIRE_BUS 8

// Setup a oneWire instance to communicate with any OneWire devices on ONE_WIRE_BUSS pin
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress sensorAddress;

// Connect to LCD screen via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);

int count = 0;
int nextChar = 0;

// Use dislayOrder list to reorder the display of temperatures in a multi sensor environment
// {0,1,2,3,4} makes no change to order while {4,2,3,0} will display the fourth sensor first
// and the first sensor last. Note, array must always contain all four numbers 0-4
const int displayOrder[] = {0,1,2,3,4}; // default no change order

void setup(void)
{
  Serial.begin(9600);
  // set up the LCD's number of rows and columns:
  lcd.begin(16, 2);
  // Configure digital pin degSet (for F/C display control)
  pinMode(degSet, INPUT_PULLUP);
  
  // locate devices on the bus
  sensors.begin();

    // Set bit resolution for returning temperatures
  sensors.setResolution(sensorAddress, 12);
  
  // How many temperature sensors are there?
  count = sensors.getDeviceCount();

  lcd.setCursor(0,0); // setCursor(col,row)
  lcd.print("TEMPERATURES(");
  
  #ifdef DEBUG  // whole bunch of debug printing next
  Serial.print("Device count = ");
  Serial.println(count, DEC);

  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  if (!sensors.getAddress(sensorAddress, 0))
    Serial.println("Unable to find address for Device 0");
  else
  {
  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(sensorAddress);
  Serial.println();
  }
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(sensorAddress), DEC); 
  Serial.println(); 
  Serial.println(sensors.getTempC(sensorAddress));
  Serial.println(sensors.getTempCByIndex(0));

  #endif
}
//**********************end setup******************************************

void loop(void)
{ 
  sensors.requestTemperatures(); // Send the command to get temperatures

  // Next statement either leaves units as set by F = true/false (above)
  // or overrides it by state of input pin degSet
  // F = true (above) then degSet input open (true) or grounded (false) will set deg F or deg C
  // F = false(above) then will get deg C no matter what degSet input is (open or grounded)
  F2 = F && digitalRead(degSet);
  lcd.setCursor(13,0); // Now that F/C is determined, setCursor(col,13)
  if (F2) lcd.print("F)"); // And print units character
  else lcd.print("C)");

  if(count == 0) 
  {
    lcd.setCursor(0, 1);
    lcd.print("No Temp Sensors");
  }
  
  for(int index = 0;index < count; index++)
  {
    printTemperature(index); // Use a separate function to print out the data
  }
  nextChar = 0;
  delay(5000);
}
//**********************end loop***********************************************

// function to print the temperature for a device
// This function prints 1-4 temperature values on LCD line 2 adjusting precision
// (in order to fit values on the line) from .xx to .x to zero as display count goes from 1 to 4

void printTemperature(int index)
{
  int decimals = 2;
  byte arrayPointer = 0;
  int nbrDigits = 0;
  int decPtFudge = 1;

  int index2 = displayOrder[index]; // this lookup allows the display of temperatures to occur in any assigned order
  
  if(count == 3) decimals = 1;
  if(count > 3) decimals = 0; 
  if(index2 >= 4) index2 = 4; // Allow no more than four sensors to print
   
  float tempF = sensors.getTempFByIndex(index2);  //
  if(!F2) tempF = DallasTemperature::toCelsius(tempF);
  
  lcd.setCursor(nextChar,1);
  lcd.print(tempF, decimals);

  String str = String(tempF, DEC); // Obviously .. get your int or byte into the string
  str = str + '\r' + '\n'; // Add the required carriage return, optional line feed
  
// Next crazy is what you have to do to determine number chars in integer temperature
  byte str_len = str.length();
  while (str_len)
  {
    if(str[arrayPointer] == '.') nbrDigits = arrayPointer;  // counts chars prior to decimal point
    --str_len;
    ++arrayPointer;
  }

  if(decimals == 0) decPtFudge = 0; // Need to add space if no decimal point
  nextChar = nextChar + nbrDigits + decimals + 1 + decPtFudge; // Compute skip distance to next temp print
  
  #ifdef DEBUG
  char suffix = 'F';  //this suffix for serial monitor output only
  if (!F)
  {
    suffix = 'C';
  }
  Serial.print("Temp = ");
  Serial.print(tempF);
  Serial.println(suffix);

  #endif
}
//************************end printTemperature*********************************

#ifdef DEBUG
// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
#endif
