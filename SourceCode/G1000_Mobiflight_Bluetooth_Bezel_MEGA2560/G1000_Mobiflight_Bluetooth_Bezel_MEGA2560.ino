/*

  G1000 Bezel for Simionic iOS App by A.Eckers aka Gagagu
  See more info on www.gagagu.de

*/

/******************** Created by A. Eckers ************************/
#include <Wire.h>
#include <Encoder.h>
#include <light_CD74HC4067.h>

//#define DEBUG
#define NODEBUG  

/************************** PINS *********************************/
#define ENCODER_HDG_A 3
#define ENCODER_HDG_B 2

#define ENCODER_RANGE_A 4
#define ENCODER_RANGE_B 5

#define ENCODER_VOL_COM_A 6
#define ENCODER_VOL_COM_B 7

#define ENCODER_COM_FRONT_A 9
#define ENCODER_COM_FRONT_B 8
#define ENCODER_COM_BACK_A 10
#define ENCODER_COM_BACK_B 11

#define ENCODER_CRS_FRONT_A 13
#define ENCODER_CRS_FRONT_B 12
#define ENCODER_CRS_BACK_A 14
#define ENCODER_CRS_BACK_B 15

#define ENCODER_FMS_FRONT_A 17
#define ENCODER_FMS_FRONT_B 16
#define ENCODER_FMS_BACK_A 18
#define ENCODER_FMS_BACK_B 19

#define ENCODER_NAV_FRONT_A 23
#define ENCODER_NAV_FRONT_B 22
#define ENCODER_NAV_BACK_A 24
#define ENCODER_NAV_BACK_B 25

#define ENCODER_ALT_FRONT_A 27
#define ENCODER_ALT_FRONT_B 26
#define ENCODER_ALT_BACK_A 28
#define ENCODER_ALT_BACK_B 29

#define ENCODER_VOL_NAV_A 30
#define ENCODER_VOL_NAV_B 31

#define MUX_S0 41
#define MUX_S1 42
#define MUX_S2 43
#define MUX_S3 44

#define MUX1_INPUT 47
#define MUX2_INPUT 46
#define MUX3_INPUT 45

// I2C Values for ESP control
#define ENCODER_ALT_FRONT_UP "56"
#define ENCODER_ALT_FRONT_DN "57"
#define ENCODER_ALT_BACK_UP "54"
#define ENCODER_ALT_BACK_DN "55"
#define ENCODER_HDG_UP "51"
#define ENCODER_HDG_DN "52"

#define ENCODER_NAV_FRONT_UP "48"
#define ENCODER_NAV_FRONT_DN "49"
#define ENCODER_NAV_BACK_UP "46"
#define ENCODER_NAV_BACK_DN "47"
#define ENCODER_VOL_NAV_UP "42"
#define ENCODER_VOL_NAV_DN "43"
#define ENCODER_RANGE_UP "35"
#define ENCODER_RANGE_DN "36"
#define ENCODER_FMS_FRONT_UP "20"
#define ENCODER_FMS_FRONT_DN "21"
#define ENCODER_FMS_BACK_UP "18"
#define ENCODER_FMS_BACK_DN "19"
#define ENCODER_CRS_FRONT_UP "70"
#define ENCODER_CRS_FRONT_DN "71"
#define ENCODER_CRS_BACK_UP "68"
#define ENCODER_CRS_BACK_DN "69"
#define ENCODER_COM_FRONT_UP "65"
#define ENCODER_COM_FRONT_DN "66"
#define ENCODER_COM_BACK_UP "63"
#define ENCODER_COM_BACK_DN "64"
#define ENCODER_VOL_COM_UP "59"
#define ENCODER_VOL_COM_DN "60"

/**************************** Mux 1 Pins send values **********************************/
#define MUX_1_0 "13" // direct to
#define MUX_1_1 "6" // Soft Key 7
#define MUX_1_2 "7" // Soft Key 8
#define MUX_1_3 "8" // Soft Key 9
#define MUX_1_4 "9" // Soft Key 10
#define MUX_1_5 "10" // Soft Key 11
#define MUX_1_6 "11" // Soft Key 12
#define MUX_1_7 "0" // Soft Key 1
#define MUX_1_8 "1" // Soft Key 2
#define MUX_1_9 "2" // Soft Key 3
#define MUX_1_10 "3" // Soft Key 4
#define MUX_1_11 "4" // Soft Key 5
#define MUX_1_12 "5" // Soft Key 6
#define MUX_1_13 "" // n.c.
#define MUX_1_14 "" // n.c.
#define MUX_1_15 "" // n.c.

/**************************** Mux 2 Pins send values **********************************/
#define MUX_2_0 "27" // Nav Button
#define MUX_2_1 "26" // Alt Button
#define MUX_2_2 "25" // HDG Button
#define MUX_2_3 "24" // FD
#define MUX_2_4 "23" // AP
#define MUX_2_5 "34" // DN
#define MUX_2_6 "32" // FLC
#define MUX_2_7 "33" // UP
#define MUX_2_8 "31" // VS
#define MUX_2_9 "30" // BC
#define MUX_2_10 "29" // APR
#define MUX_2_11 "17" // ENT Button
#define MUX_2_12 "14" // CLR
#define MUX_2_13 "15" // PROC
#define MUX_2_14 "12" // FPL
#define MUX_2_15 "16" // MENU

/**************************** Mux 3 Pins send values **********************************/
#define MUX_3_0 "58" // Alt Push
#define MUX_3_1 "50" // NAV Push
#define MUX_3_2 "22" // FMS Push
#define MUX_3_3 "72" // CRS Baro Push
#define MUX_3_4 "67" // COM Push
#define MUX_3_5 "61" // VOL COM Push
#define MUX_3_6 "37" // Range Push
#define MUX_3_7 "53" // HDG Push
#define MUX_3_8 "44" // VOL NAV Push
#define MUX_3_9 "40" // Range Left	
#define MUX_3_10 "39" // Range Down
#define MUX_3_11 "41" // Range Right
#define MUX_3_12 "38" // Range Up
#define MUX_3_13 "62" // Coggle COM
#define MUX_3_14 "45" // Nav Switch
#define MUX_3_15 "28" // VNV

/****************************** ENCODERS *****************************************/

Encoder encoder_hdg(ENCODER_HDG_A,ENCODER_HDG_B);
Encoder encoder_range(ENCODER_RANGE_A,ENCODER_RANGE_B);
Encoder encoder_vol_com(ENCODER_VOL_COM_A,ENCODER_VOL_COM_A);

Encoder encoder_com_front(ENCODER_COM_FRONT_A, ENCODER_COM_FRONT_B);
Encoder encoder_com_back(ENCODER_COM_BACK_A, ENCODER_COM_BACK_B);

Encoder encoder_crs_front(ENCODER_CRS_FRONT_A, ENCODER_CRS_FRONT_B);
Encoder encoder_crs_back(ENCODER_CRS_BACK_A, ENCODER_CRS_BACK_B);

Encoder encoder_fms_front(ENCODER_FMS_FRONT_A, ENCODER_FMS_FRONT_B);
Encoder encoder_fms_back(ENCODER_FMS_BACK_A, ENCODER_FMS_BACK_B);

Encoder encoder_nav_front(ENCODER_NAV_FRONT_A, ENCODER_NAV_FRONT_B);
Encoder encoder_nav_back(ENCODER_NAV_BACK_A, ENCODER_NAV_BACK_B);

Encoder encoder_alt_front(ENCODER_ALT_FRONT_A, ENCODER_ALT_FRONT_B);
Encoder encoder_alt_back(ENCODER_ALT_BACK_A, ENCODER_ALT_BACK_B);

Encoder encoder_vol_nav(ENCODER_VOL_NAV_A,ENCODER_VOL_NAV_B);

/***********************************************************************/

#define MUX_BUTTONS_UPDATE_INTERVAL 50 // in milliseconds

/****************************** Variables *****************************************/
int32_t positionLeft  = -999;
int32_t positionRight = -999;

CD74HC4067 mux(MUX_S0, MUX_S1, MUX_S2, MUX_S3);

unsigned long nextKeysMillis=0;   // count millis for next Button updates
unsigned long currentMillis;    

void setup()
{
  // config mux
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(MUX_S3, OUTPUT);
  pinMode(MUX1_INPUT, INPUT);
  pinMode(MUX2_INPUT, INPUT);
  pinMode(MUX3_INPUT, INPUT);


#if defined(DEBUG)
  Serial.begin(115200);
  Serial.println("Start Encoders:");
#endif

  // start I2c bus
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.setClock(400000); // choose 400 kHz I2C rate

  // set all encodder to zero
  encoder_hdg.write(0);
  encoder_range.write(0);
  encoder_vol_com.write(0);
  encoder_com_front.write(0);
  encoder_com_back.write(0);
  encoder_crs_front.write(0);
  encoder_crs_back.write(0);
  encoder_fms_front.write(0);
  encoder_fms_back.write(0);
  encoder_nav_front.write(0);
  encoder_nav_back.write(0);
  encoder_alt_front.write(0);
  encoder_alt_back.write(0);
  encoder_vol_nav.write(0);

}

void loop()
{
  currentMillis = millis();  
  // read encoders and send data
  ReadEncoderAndSend(encoder_alt_front, ENCODER_ALT_FRONT_UP, ENCODER_ALT_FRONT_DN);
  ReadEncoderAndSend(encoder_alt_back, ENCODER_ALT_BACK_UP, ENCODER_ALT_BACK_DN);
  ReadEncoderAndSend(encoder_hdg, ENCODER_HDG_UP, ENCODER_HDG_DN);
  ReadEncoderAndSend(encoder_nav_front, ENCODER_NAV_FRONT_UP, ENCODER_NAV_FRONT_DN);
  ReadEncoderAndSend(encoder_nav_back, ENCODER_NAV_BACK_UP, ENCODER_NAV_BACK_DN);
  ReadEncoderAndSend(encoder_vol_nav,ENCODER_VOL_NAV_UP, ENCODER_VOL_NAV_DN);
  ReadEncoderAndSend(encoder_range, ENCODER_RANGE_UP, ENCODER_RANGE_DN);
  ReadEncoderAndSend(encoder_fms_front, ENCODER_FMS_FRONT_UP, ENCODER_FMS_FRONT_DN);
  ReadEncoderAndSend(encoder_fms_back, ENCODER_FMS_BACK_UP, ENCODER_FMS_BACK_DN);
  ReadEncoderAndSend(encoder_crs_front, ENCODER_CRS_FRONT_UP, ENCODER_CRS_FRONT_DN);
  ReadEncoderAndSend(encoder_crs_back, ENCODER_CRS_BACK_UP, ENCODER_CRS_BACK_UP);
  ReadEncoderAndSend(encoder_com_front, ENCODER_COM_FRONT_UP, ENCODER_COM_FRONT_DN);
  ReadEncoderAndSend(encoder_com_back, ENCODER_COM_BACK_UP, ENCODER_COM_BACK_DN);
  ReadEncoderAndSend(encoder_vol_com, ENCODER_VOL_COM_UP, ENCODER_VOL_COM_DN);


  if (currentMillis >= nextKeysMillis) {   
    for(uint8_t i=0,n=16;i<n;i++){
        // set channel
        mux.channel(i);
        // wait for channel switching (datasheet)
        delay(1);
        // read mux pins
        int mux1Pin=digitalRead(MUX1_INPUT);
        int mux2Pin=digitalRead(MUX2_INPUT);
        int mux3Pin=digitalRead(MUX3_INPUT);

        // mux 1
        if(mux1Pin==0) //is the button pressed?
        {
          ProcessMux1(i); // process values
          while(digitalRead(MUX1_INPUT)!=1) // wait until not pressed anymore
          {
            delay(1);
          }
        }

        // mux 2
        if(mux2Pin==0) //is the button pressed?
        {
          ProcessMux2(i); // process values
          while(digitalRead(MUX2_INPUT)!=1) // wait until not pressed anymore
          {
            delay(1);
          }          
        }

        // Mux 3
        if(mux3Pin==0) //is the button pressed?
        {
          ProcessMux3(i);// process values
          // better PAN movement
          if(i<=8 || i>=13){ // wait until not pressed anymore except pan buttons, we need repead there
            while(digitalRead(MUX3_INPUT)!=1) 
            {
              delay(1);
            }        
          }  
        } // if Mux3pin

        #if defined(DEBUG)
         Serial.print(mux1Pin);
         Serial.print(",");
         Serial.print(mux2Pin);
         Serial.print(",");
         Serial.print(mux3Pin);
         Serial.print(",");  
        #endif      
      } //for
      nextKeysMillis = currentMillis + MUX_BUTTONS_UPDATE_INTERVAL;  

      #if defined(DEBUG)
        Serial.println(""); 
      #endif
  }// millis
  #if defined(DEBUG)
   Serial.println("");
  #endif
} // Loop


/***************************************************************************
* Read the Encode rvalue and send the corresponding message to the ESP32
* depenting which direction is used.
****************************************************************************/
void ReadEncoderAndSend(Encoder &myEncoder, String msg_up, String msg_dn){
  int32_t iEncAltBack = myEncoder.read();
          
  if(iEncAltBack >2 || iEncAltBack <-2)
  {
    myEncoder.write(0);  
    if(iEncAltBack >0)
    {
      #if defined(DEBUG)
        Serial.println("encoder up");
      #endif
      I2CSend(msg_up);
    }else
    {
      #if defined(DEBUG)
        Serial.println("encoder down");
      #endif
      I2CSend(msg_dn);
    }

  }
} //ReadEncoderAndSend

/***************************************************************************
* Send data to ESP32
* It contains of key and value because the ESP32 can also use by Mobilfight
* In my case the Key is always '0'
****************************************************************************/
void I2CSend(String msg){
  Wire.beginTransmission(0x27); // transmit to device #4
  Wire.write('0'); // sends
  Wire.write(0x0D);
  Wire.write(msg.c_str());
  Wire.write(0x00);
  Wire.endTransmission(); // stop transmitting
} //I2CSend

/***************************************************************************
* Process mux 1 and send the corresponding value
****************************************************************************/
void ProcessMux1(int val)
{
  switch (val){
    case 0: 
      I2CSend(MUX_1_0);
      break;
    case 1: 
      I2CSend(MUX_1_1);
      break;
    case 2: 
      I2CSend(MUX_1_2);
      break;
    case 3:
      I2CSend(MUX_1_3);
      break;
    case 4:
      I2CSend(MUX_1_4);
      break;
    case 5:
      I2CSend(MUX_1_5);
      break;
    case 6: 
      I2CSend(MUX_1_6);
      break;
    case 7:
      I2CSend(MUX_1_7);
      break;
    case 8:
      I2CSend(MUX_1_8);
      break;
    case 9:
      I2CSend(MUX_1_9);
      break;
    case 10:
      I2CSend(MUX_1_10);
      break;
    case 11:
      I2CSend(MUX_1_11);
      break;
    case 12:
      I2CSend(MUX_1_12);
      break;
    case 13:
      break;
    case 14:
      break;
    case 15:
      break;                                                                                                                                                                                                    
  }
} //ProcessMux1

/***************************************************************************
* Process mux 2 and send the corresponding value
****************************************************************************/
void ProcessMux2(int val)
{
  switch (val){
    case 0: 
      I2CSend(MUX_2_0);
      break;
    case 1: 
      I2CSend(MUX_2_1);
      break;
    case 2: 
      I2CSend(MUX_2_2);
      break;
    case 3: 
      I2CSend(MUX_2_3);
      break;
    case 4: 
      I2CSend(MUX_2_4);
      break;
    case 5: 
      I2CSend(MUX_2_5);
      break;
    case 6: 
      I2CSend(MUX_2_6);
      break;
    case 7: 
      I2CSend(MUX_2_7);
      break;
    case 8: 
      I2CSend(MUX_2_8);
      break;
    case 9: 
      I2CSend(MUX_2_9);
      break;
    case 10: 
      I2CSend(MUX_2_10);
      break;
    case 11: 
      I2CSend(MUX_2_11);
      break;
    case 12: 
      I2CSend(MUX_2_12);
      break;
    case 13: 
      I2CSend(MUX_2_13);
      break;
    case 14: 
      I2CSend(MUX_2_14);
      break;
    case 15: 
      I2CSend(MUX_2_15);
      break;                                                                                                                                                                                                    
  }
} //ProcessMux2

/***************************************************************************
* Process mux 3 and send the corresponding value
****************************************************************************/
void ProcessMux3(int val)
{
  switch (val){
    case 0: 
      I2CSend(MUX_3_0);
      break;
    case 1: 
      I2CSend(MUX_3_1);
      break;
    case 2: 
      I2CSend(MUX_3_2);
      break;
    case 3: 
      I2CSend(MUX_3_3);
      break;
    case 4: 
      I2CSend(MUX_3_4);
      break;
    case 5: 
      I2CSend(MUX_3_5);
      break;
    case 6: 
      I2CSend(MUX_3_6);
      break;
    case 7: 
      I2CSend(MUX_3_7);
      break;
    case 8: 
      I2CSend(MUX_3_8);
      break;
    case 9: 
      I2CSend(MUX_3_9);
      break;
    case 10: 
      I2CSend(MUX_3_10);
      break;
    case 11:
      I2CSend(MUX_3_11);
      break;
    case 12:
      I2CSend(MUX_3_12);
      break;
    case 13: 
      I2CSend(MUX_3_13);
      break;
    case 14: 
      I2CSend(MUX_3_14);
      break;
    case 15: //VNV
      I2CSend(MUX_3_15);
      break;                                                                                                                                                                                                    
  }
} //ProcessMux3