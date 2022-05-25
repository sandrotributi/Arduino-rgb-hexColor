 /**
 * Accende un led RGB in accordo con una stringa esadecimale
 * letta dalla porta seriale.
 * Formato della stringa esadecimale: #RRGGBB 
 * 
 * @author     Sandro Tributi <tributi.sandro@curiepergine.it>
 */

// Pin led RGB
#define pinRed 11
#define pinGreen 10
#define pinBlue 9

// Variabili
String hexStr; // stringa letta dalla porta seriale
byte r, g, b;  // valori decimali RGB (0-255)

void setup() {
  // inizializzazione porta seriale
  Serial.begin(9600);
  // inizializzazione pin dove è collegato il led RGB
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);  
}

void loop() {
  // se ci sono byte da leggere sulla seriale...
  if (Serial.available() > 0) {
    // lettura della stringa
    hexStr = Serial.readStringUntil('\n');
    hexStr.trim();        // elimina spazi
    hexStr.toUpperCase(); // converte in maiuscolo
    // se il primo carattere della stringa è '#'...
    if (hexStr.charAt(0) == '#') {
      // conversione hex --> dec
      r = hex2dec(hexStr.substring(1,3));
      g = hex2dec(hexStr.substring(3,5));
      b = hex2dec(hexStr.substring(5,7));
      // accende il led RGB
      setColor(pinRed, pinGreen, pinBlue, r, g, b);
      // stampa valori sul monitor seriale
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
