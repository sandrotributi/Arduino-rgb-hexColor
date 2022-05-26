 /**
 * Turns on an RGB led in accordance with a hexadecimal string
 * read from the serial port.
 * The colors may be define using the hexadecimal representation 
 * preceded by a # sign.
 * The hexadecimal string format is #rrggbb where rr is the RED value, 
 * gg is the GREEN value and bb is the BLUE value.
 * 
 * This code is in the public domain. 
 * 
 * by Sandro Tributi <sandro.tributi@gmail.com>
 *
 * https://github.com/sandrotributi/Arduino-rgb-hexColor/edit/main/rgb_hexColor.ino
 */

// led RGB pins
#define pinRed 11
#define pinGreen 10
#define pinBlue 9

// Variables
String hexStr; 
byte r, g, b;  

void setup() {
  // serial port initialization
  Serial.begin(9600);
  // pin initialization where the RGB led is connected
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);  
}

void loop() {
  // if there are bytes to read on the serial ...
  if (Serial.available() > 0) {
    // lettura della stringa
    hexStr = Serial.readStringUntil('\n');
    hexStr.trim();        // delete any spaces
    hexStr.toUpperCase(); // converts to uppercase
    // if the first character of the string is '#'...
    if (hexStr.charAt(0) == '#') {
      // conversion from hex to decimal
      r = hex2dec(hexStr.substring(1,3));
      g = hex2dec(hexStr.substring(3,5));
      b = hex2dec(hexStr.substring(5,7));
      // turns on the RGB led
      setColor(pinRed, pinGreen, pinBlue, r, g, b);
      // print decimal values on the serial monitor
      Serial.print(r);
      Serial.print(",");
      Serial.print(g);
      Serial.print(",");
      Serial.println(b);
    }  
  }
}

byte hex2dec(String hexDigit) {
  char hc;
  byte dd[2];

  for (int i = 0; i < hexDigit.length(); i++) {    
    hc = hexDigit.charAt(i);
    if (hc >= '0' && hc <= '9') {
      dd[i] = hexDigit.charAt(i) - 48;
    } else {
      dd[i] = hexDigit.charAt(i) - 55;
    }
  } 
  return dd[0] * 16 + dd[1];
}

void setColor(byte pinR, byte pinG, byte pinB, byte red, byte green, byte blue) {
  analogWrite(pinR, red);
  analogWrite(pinG, green);
  analogWrite(pinB, blue);
}
