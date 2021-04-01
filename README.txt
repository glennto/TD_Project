LATHE DISPLAY PROJECT

Arduino based code for an Arduino Nano and a Adafruit 24x2 LCD display/I2C
board combo that implements a multi sensor temperature display application.

	Author: Glenn Tober
	Source: https://github.com/glennto/TD_Project
	Email: glennt@palmnet.net
	Copyright:	Glenn Tober 03/25/2021


INTENDED USE

Arduino family software application whose purpose is to monitor one to four MAXIM DS18B20 digital temperature sensors and display Farenheit/Centigrade values on an LCD screen.

Software licensed under the GNU Public Liscense V3.0 (ref. License)


DOCUMENTATION

All documentation is hosted on the above referenced github site.

	1. This README.TXT file is the project baseline document.
	2. Additional Integration Checkout and Test instructions found in TD_IC&T_Instructions.md
	4. Instructions for software conditional compile directives and other possible
	configuration/tuning changes described in TD_Config_Instructions.md
	5. Project addendum/errata information described in Addendum.md


HARDWARE REQUIREMENTS

Target hardware includes an Arduino Nano processor, a 24x2 LCD display panel
(various choices) and an Adafruit Industries I2C interface board for the display. In addition, project hardware components include a three volt battery pack, a 3-5 volt boost converter board, one to two SPST
toggle switches and connections for the sensors.

A desktop or laptop computer with a USB port and a suitable operating system (Windows, MAC or Linux) is required to compile and download the software to the Nano.

Port pins assigned to this project are defined in the software source code.

A reference mechanical design for the electronics and the enclosure are provided by separate
references [TBD]


SOFTWARE REQUIREMENTS

The application software (TD_Display_VX.X) should be compiled and loaded using the Arduino Integrated Development Environment (IDE) in communication with a connected Nano board. The following Adafruit libraries are required by the software:

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_LiquidCrystal.h	

The code must dedicate the following Arduino Uno pins:

	#define ONE_WIRE_BUS 8	// DS18B20 DQ sense I/O on digital pin 8
	#define degSet 2	// T/C switch input on digital pin 2 
	bool F = true;		// Selects between Fahrenheit (true) and Centigrade (false)
				// If F/C switch is installed, leave 'true'
	CLK wired to Analog A5	// LCD I2C board CLK pin
	DAT wired to Analog A4	// LCD I2C board DAT pin

Future clarifications/errata material will be posted in the file: LH_Project_Addendum.md 


VERSION HISTORY

  Version 0.10 03/24/2021
  
  Initial release

