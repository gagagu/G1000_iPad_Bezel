#include "BleKeyboard.h"
#include <Wire.h>

// Address and communication for Mobiflight
#define I2C_MOBIFLIGHT_ADDR 0x27
#define I2C_MOBIFLIGHT_SDA 21
#define I2C_MOBIFLIGHT_SCL 22
#define MAX_LENGTH_MESSAGE          96 

#define END_OF_I2C_MESSAGE              0x00
#define END_OF_I2C_COMMAND              0x0D      // carriage return in ASCII
#define END_OF_I2C_PARTIAL_MESSAGE      0x0A      // line feed in ASCII

#define WAIT_KEY_PRESS 15 
#define WAIT_KEY_RELEASE 15 

//#define DEBUG
#define NODEBUG  


enum {
    NOT_SYNCHRONIZED = 0,
    RECEIVE_COMMAND,
    RECEIVE_DATA
};

int16_t _messageID = 0;
char _message[MAX_LENGTH_MESSAGE];

BleKeyboard bleKeyboard("G1000 PFD", "Gagagu" , 100);

void setup() {

#if defined(DEBUG)  
  Serial.begin(115200);
  Serial.setDebugOutput(false);
#endif

  // setup i2c receive callback
  Wire.onReceive(onReceive);

  // init i2c busses
  Wire.begin((uint8_t)I2C_MOBIFLIGHT_ADDR,I2C_MOBIFLIGHT_SDA,I2C_MOBIFLIGHT_SCL,400000);
  
  bleKeyboard.setDelay(5);
  bleKeyboard.begin();
  Serial.println("start");
}

void loop() {
  delay(30);
}

void onReceive(int received_bytes) {
//Serial.println("receive");
  static uint8_t byte_counter = 0;
  static uint8_t state = RECEIVE_COMMAND;
  char buffer[7] = {0};                                    // range is -32768 ... 32767 -> max. 6 character plus terminating NULL

  for (uint8_t i = 0; i < received_bytes; i++) {
    switch (state) {
      case NOT_SYNCHRONIZED:
        if (Wire.read() == END_OF_I2C_MESSAGE) {              // wait for end of message to get synchronized
          state = RECEIVE_COMMAND;
          byte_counter = 0;
        }
        break;

      case RECEIVE_COMMAND:
        buffer[i] = Wire.read();
       // Serial.print(buffer[i], HEX);
        if (buffer[i] == END_OF_I2C_COMMAND) {
          buffer[i] = 0x00;                                   // terminate string
          _messageID = atoi(buffer);
          state = RECEIVE_DATA;                               // next bytes are Data Bytes
        }
        if (i >= 6) {                                         // buffer overflow for messageID
          state = NOT_SYNCHRONIZED;                          // something went wrong, get a new synchronization
          byte_counter = 0;
          return;
        }
        break;

      case RECEIVE_DATA:
      //Serial.println("data");
        _message[byte_counter] = Wire.read();
        if (_message[byte_counter] == END_OF_I2C_MESSAGE) {    // end of message detected, prepare for receiving next messageID
          byte_counter = 0;
          state = RECEIVE_COMMAND;

          if(_messageID==0){ // we only await one command with value
            if(bleKeyboard.isConnected()) {
              handleCommand();
            }
          }
          return;
        } else if(_message[byte_counter] == END_OF_I2C_PARTIAL_MESSAGE) {   // end of partial message detected, next transmission will be rest of message  
          return;                                             // keep receiving data
        } else {
          byte_counter++;                                     // get the next byte
        }
        break;

      default:
        break;
    }
  }
  state = NOT_SYNCHRONIZED;                                 // We shouldn't come here, something went wrong
}


void handleCommand(){

  int command= atoi(_message);
#if defined(DEBUG)   
   Serial.print("command:");
   Serial.println(command);
#endif

  switch(command){
    case 0: // Soft Key 1
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('1');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();        
      break;
    case 1: // Soft Key 2
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('2');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 2: // Soft Key 3
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('3');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 3: // Soft Key 4
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('4');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 4: // Soft Key 5
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('5');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 5: // Soft Key 6
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('6');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 6: // Soft Key 7
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('7');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 7: // Soft Key 8
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('8');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 8: // Soft Key 9
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('9');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 9: // Soft Key 10
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('0');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 10: // Soft Key 11
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press(KEY_NUM_MINUS);
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 11: // Soft Key 12
      bleKeyboard.press(KEY_LEFT_SHIFT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('=');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 12: // FPL
      bleKeyboard.press('f');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 13: //DIR-TO
      bleKeyboard.press('d');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 14: // CLR
      bleKeyboard.press('`');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();       
      break;
    case 15: // PROC
      bleKeyboard.press('p');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 16: // MENU
      bleKeyboard.press('m');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;
    case 17: // ENT
      bleKeyboard.write(KEY_RETURN);
      break;
    case 18: // Big FMS Knob+
      bleKeyboard.write(KEY_DOWN_ARROW);
      break;
    case 19: // Big FMS Knob-
      bleKeyboard.write(KEY_UP_ARROW);
      break;
    case 20: // Small FMS Knob+
      bleKeyboard.write(KEY_RIGHT_ARROW);
      break;
    case 21: // Small FMS Knob-
      bleKeyboard.write(KEY_LEFT_ARROW);
      break;
    case 22: // FMS Knob push
      bleKeyboard.write(' ');
      break;
    case 23: // AP
      bleKeyboard.press('a');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;    
    case 24: // FD
      bleKeyboard.press('e');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;      
    case 25: // HDG
      bleKeyboard.press('h');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;      
    case 26: // ALT
      bleKeyboard.press('l');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;      
    case 27: // NAV
      bleKeyboard.press('n');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;      
    case 28: // VNV
      bleKeyboard.press('v');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;      
    case 29: // APR
      bleKeyboard.press('r');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;      
    case 30: // BC
      bleKeyboard.press('b');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;      
    case 31: // VS
      bleKeyboard.press('s');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;      
    case 32: // FLC
      bleKeyboard.press('c');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;      
    case 33: // NOSE UP
      bleKeyboard.press(KEY_LEFT_SHIFT);
      bleKeyboard.write(KEY_UP_ARROW);
      bleKeyboard.release(KEY_LEFT_SHIFT);
      break;      
    case 34: // NOSE DN
      bleKeyboard.press(KEY_LEFT_SHIFT);
      bleKeyboard.write(KEY_DOWN_ARROW);
      bleKeyboard.release(KEY_LEFT_SHIFT);
      break;      
    case 35: // RANGE-
      bleKeyboard.press('-');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;           
    case 36: // RANGE+
      bleKeyboard.press('=');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll(); 
      break;           
    case 37: // MAP CURSOR
      bleKeyboard.press('\\');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();       
      break;           
    case 38: // MAP CURSOR UP
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.write('i');
      bleKeyboard.release(KEY_LEFT_GUI);
      break;           
    case 39: // MAP CURSOR DOWN
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.write('k');
      bleKeyboard.release(KEY_LEFT_GUI);
      break;         
    case 40: // MAP CURSOR LEFT
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.write('j');
      bleKeyboard.release(KEY_LEFT_GUI);
      break;   
    case 41: // MAP CURSOR RIGHT
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.write('l');
      bleKeyboard.release(KEY_LEFT_GUI);
      break;     
    case 42: // NAV Vol+
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('3');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();    
      break;     
    case 43: // NAV Vol-
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('1');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();  
      break;     
    case 44: // NAV Vol Push
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('2');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();     
      break;     
    case 45: // NAV Switch
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('4');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();      
      break;     
    case 46: // Big NAV Knob +
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('t');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();  
      break;     
    case 47: // Big Nav Knob -
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('q');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();     
      break;     
    case 48: // Small Nav Knob +
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('r');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();    
      break;     
    case 49: // Small Nav Knob -
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('w');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();    
      break;     
    case 50: // NAV Knob Push
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('e');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();     
      break;     
    case 51: // HDG Knob +
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('f');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();  
      break;     
    case 52: // HDG Knob -
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('s');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();    
      break;     
    case 53: // HDG Knob Push
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('d');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();     
      break;     
    case 54: // Big ALT Knob +
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('b');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();
      break;     
    case 55: // Big ALT Knob -
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('z');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();          
      break;     
    case 56: // Small ALT Knob +
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('v');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();        
      break;     
    case 57: // Small ALT Knob -
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('x');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();         
      break;     
    case 58: // ALT Knob Push
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('c');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();     
      break;     
    case 59: // COM Vol +
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('3');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();        
      break;     
    case 60: // COM Vol -
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('1');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();         
      break;     
    case 61: // COM Vol Push
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('2');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();        
      break;     
    case 62: // COM Switch
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('4');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();        
      break;     
    case 63: // Big COM Knob +
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('t');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();        
      break;     
    case 64: // Big COM Knob -
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('q');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();      
      break;     
    case 65: // Small COM Knob +
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('r');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();      
      break;     
    case 66: // Small COM Knob -
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('w');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();        
      break;     
    case 67: // COM Knob Push
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('e');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();        
      break;     
    case 68: // Baro Knob +
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('g');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();     
      break;     
    case 69: // Baro Knob -
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('a');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();      
      break;     
    case 70: // CRS Knob +
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('f');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();           
      break;     
    case 71: // CRS Knob -
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('s');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();           
     
      break;     
    case 72: // CRS Knob Push
      bleKeyboard.press(KEY_RIGHT_ALT);
      delay(WAIT_KEY_PRESS);
      bleKeyboard.press('d');
      delay(WAIT_KEY_RELEASE);
      bleKeyboard.releaseAll();       
      break;     
    case 73: // GA Button
      bleKeyboard.press('KEY_LEFT_SHIFT');
      bleKeyboard.write('G');
      bleKeyboard.release(KEY_LEFT_SHIFT);      
      break;     

  }
}