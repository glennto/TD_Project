**Notice**

    Temperature Display Software Integration Checkout and Test Instructions
    
    Copyright (C)  2021 Tober (glennt@palmnet.net)
    Source: https://github/glennto/TD_Project
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.Configuring the Software

**Installation Checkout  and Test**

The following paragraphs provide essential information about installing/setting up, testing and configuring the Temperature Display software. Complete information is beyond the scope of this article (refer to vendor documentation for this).

You must download and install a version of the Arduino Integrated Development Environment (IDE) suitable for your computer (IDE is an industry name for a computer program that aids software development and software installation).  Arduino IDE versions are available for Windows, Mac and Linux operating systems.  The IDE is required for installation of the Temperature Display software.

Once the IDE is installed use the USB cable and connect the Arduino Nano board (by itself) to your computer.  The board will power up on its own.  Now look under the IDE ‘Tools’ menu and see that the ‘Port’ button is active.  Selecting the ‘Port’ button should that either one port is already selected or reveal that one or more port options must be selected. The proper computer USB port option must be selected before going further. You may have to trial and error them to see which one works.  The USB port is properly configured when you can go under the IDE ‘Tools  - Get Board Info’ and see the Nano board listed.  On my Linux machine the proper USB port is labeled ‘/dev/ttyACMO(Arduino Nano)’.  On a windows computer the port name will contains a similar ‘tty..’ identifier.  Next go to IDE ‘Tools’ and see that ‘Board Arduino Nano’ is displayed.

With the IDE properly configured select one of the example programs under the IDE ‘File - Examples – Basic’ menu (‘Blink’ is a good choice).  In the new IDE window click on the left most upper check mark and the file should compile successfully.  Next click on the upload button to the right of the compile button and the ‘Blink’ program will be uploaded to the Nano. The Nano board will then execute the test program and you can verify that, for example, the Nano LED is indeed blinking.  Your Arduino IDE and Nano interface are now working.

When the IDE was installed a number of  ‘library packages’ were installed with it. A few additional libraries are required to support the Adafruit LCD resistive touch screen used by Lathe Helper. Adding these libraries is straightforward.  Select “Tools Manage Libraries’.  One at a time enter each of the following library names into the filter window and select ‘Install’ for any one which is not already installed:

1. OneWire
2. DallasTemperature
3. Adafruit_LiquidCrystal

**Testing the Hardware**

Mate the TFT Display board to the Nano board and reconnect the Nano board to the computer. Go to ‘Files Examples’ and successively open, compile and load/run HelloWorldI2C from the AdaFruit LiquidCrystal folder. If you see the text you are good to go. 

The last step is to locate and open the downloaded Temp_Display_I2C_VXX.ino file.  Check the compile box followed by the load check box.  After the credits screen goes away and you see the Temperature Display screen on the LCD display, the software is installed.  You will not need the IDE again unless you change the software or for any reason the installation becomes corrupted.  Note that power on/off cycles of the instrument does not effect the installed software.

For instructions on how to make certain modifications to the software please see (TD_Config_Instructions)
