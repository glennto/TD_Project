**Notice**

    Configuration Instructions for the Temperature Display software.
    
    Copyright (C)  2021 Glenn Tober (glennt@palmnet.net)
    Source: https://github/glennto/LH_Display
    
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

**Configuring the Software**

You may wish to modify some of the configuration and/or performance features of the software. The following configuration items can be adjusted in the software



- Change DS18B20 DQ input from digital pin 8 to a different digital pin (assumes the wire was moved)

  Locate code line '*#define ONE_WIRE_BUS 8*' and change '8' to the new pin number

- Change F/C switch input from digital pin 2 to a different digital pin (assumes the wire was moved)

  Locate code line '*#define degSet 2*' and change '2' to the new pin number.

- Change power-on F/C setting from Fahrenheit to Centigrade (assumes you have not wired in the F/C switch   wire)

  Locate code line '*bool F = true;*' and change 'true' to 'false'

- Reorder the displayed temperature values (multiple sensor case)

  Locate the code line '*const int displayOrder[] = {0,1,2,3,4};*' and reorder the digits representing individual sensors into the sequence you want displayed. For example {1,0,2,3,4} displays sensor '1' first followed by sensor '0' and leaves the order the same for '2-4'. Note must always have digits 1,2,3 and 4 somewhere in the list and never list fewer digits.

- Turn IDE serial monitor printing on (for more information when Nano is connected to the computer/IDE)

  Locate the '*//#define DEBUG*' code line and remove the '//' prefix (i.e., uncomment the line)



In the future program changes may be made by the author at any time including those that correct errors or those that enhance performance. Updates will be posted on the Github web site labeled with a revision number higher than the previous version number. The *README.txt* file on the download site will describe the latest changes and provide current version numbers.

For instructions on how to load, compile and install the software please see (TD_IC&T_Instructions.md)
