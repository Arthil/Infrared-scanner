# Infrared-scanner

The complete project (hardware + software + design) was made with a group of three people but I created the software.
A software created for a infrared scanner using Qt and c++ for the pc part and arduino (basically C) for the microcontroller. 
The program consist of two parts. The computer and a microcontroller (arduino).
The computer sends commands to the microcontroller (arduino) via serialport and listens to the port to fetch any data sent by the arduino device.

The scanner scans roughly a 180 degree area around it.
The infrared camera scans semi-accurately if the scan range is between 1 and 5 meters. Results outside this range the are not reliable.

1. Infrared_scanner_arduino.ino is the arduino microcontroller program
2. Everything else is part of the infrared scanner QtGUI, which is responsible for sending and receiving data from the serialport and drawing the GUI itself.

There is still room for some improvement in the GUI side of the program. Now the data points are being drawn to the GUI almost completely unprocessed. The problem is that some points are more unrealiable than others or may have some stuttering. If developed further, an algorithm should be added to go through the data and cleaning the overall result by removing bad data points.

Some pictures of the working scanner:

A scanner test run (as can be seen from the gif, distances above 5m are very inaccurate):
![alt tag](https://github.com/Arthil/Infrared-scanner/blob/master/Scanner%20pictures/scanner_working.gif?raw=true)

Main menu:
![alt tag](https://github.com/Arthil/Infrared-scanner/blob/master/Scanner%20pictures/Infrared%20scanner%20menu.png?raw=true)

Exposed arduino and the infrared camera
![alt tag](https://github.com/Arthil/Infrared-scanner/blob/master/Scanner%20pictures/infrared%20scanner%20inside.jpg?raw=true)

The complete product:
![alt tag](https://github.com/Arthil/Infrared-scanner/blob/master/Scanner%20pictures/infrared%20scanner.jpg?raw=true)




