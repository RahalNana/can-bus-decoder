#include "mcp_can.h"
#include <SPI.h>
//#include <genieArduino.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

MCP_CAN CAN0(5);                               // Set CS to pin 5

int MVAL_EGT = 0;
int PVAL_EGT = 0;
int VAL_EGT = 0;
float MVAL_OILPRS = 0;
float PVAL_OILPRS = 0;
float VAL_OILPRS = 0;
float MVAL_AFR = 0;
float PVAL_AFR = 0;
float VAL_AFR = 0;
int MVAL_OILTMP = 0;
int PVAL_OILTMP = 0;
int VAL_OILTMP = 0;
int MVAL_WATER = 0;
int PVAL_WATER = 0;
int VAL_WATER = 0;
int MVAL_INTAKE = 0;
int PVAL_INTAKE = 0;
int VAL_INTAKE = 0;
int MVAL_KNOCK = 0;
int PVAL_KNOCK = 0;
int VAL_KNOCK = 0;
int KNOCK_FLAG = 0;

int a,b,c,d,VFrame;

//Genie genie;
#define RESETLINE 4  // Change this if you are not using an Arduino Adaptor Shield Version 2 (see code below)


void setup()
{
  Serial.begin(9600);  // Serial0 @ 200000 (200K) Baud
//  genie.Begin(Serial);   // Use Serial0 for talking to the Genie Library, and to the 4D Systems display

  //Reset the Display (change D4 to D2 if you have original 4D Arduino Adaptor)
  pinMode(RESETLINE, OUTPUT);  // Set D4 on Arduino to Output (4D Arduino Adaptor V2 - Display Reset)
  digitalWrite(RESETLINE, 1);  // Reset the Display via D4
  delay(100);
  digitalWrite(RESETLINE, 0);  // unReset the Display via D4
  
  delay (10000); //let the display start up
  
  //Write a string to the Display
//  genie.WriteObject(GENIE_OBJ_FORM, 0x00,0);
//  delay(3000);
//  genie.DoEvents();
  
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
//  if(CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_16MHZ) == CAN_OK)   genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x00, 200);
//  else   genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x00, 666);
  
  Serial.println(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK);

//  genie.DoEvents();
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(2, INPUT);                            // Setting pin 2 for /INT input
//  genie.DoEvents();
//  
//  genie.DoEvents();
//
//  genie.WriteObject(GENIE_OBJ_USER_LED, 0x00, 0);
//  genie.DoEvents(); 
//  genie.WriteObject(GENIE_OBJ_USER_LED, 0x01, 0);
//  genie.DoEvents(); 

}

void loop()
{
//    genie.DoEvents(); 
    if(!digitalRead(2))                         // If pin 2 is low, read receive buffer
    {
        CAN0.readMsgBuf(&rxId, &len, rxBuf);              // Read data: len = data length, buf = data byte(s)

        VFrame = (rxBuf[1]*256 + rxBuf[0]);
        b = (rxBuf[3]*256 + rxBuf[2]);
        c = (rxBuf[5]*256 + rxBuf[4]);
        d = (rxBuf[7]*256 + rxBuf[6]);

        for(int i=0; i<8; i++)
        {
          Serial.print(rxBuf[i]);
          Serial.print(" ");
        }
        Serial.println("");
        
//        switch(VFrame) {
//      
//          case 0:
//          // b Water Temp
//          VAL_WATER = b - 50;
//          if(VAL_WATER != PVAL_WATER) {
//            PVAL_WATER = VAL_WATER;
//            genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x04, VAL_WATER);
//            genie.DoEvents();    
//          }
//       
//          // c Air Temp
//          VAL_INTAKE = c - 50;
//          if(VAL_INTAKE != PVAL_INTAKE) {
//            PVAL_INTAKE = VAL_INTAKE;
//            genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x01, VAL_INTAKE);
//            genie.DoEvents();
//          }
//       
//          // d Wideband
//          VAL_AFR = (d * 0.01) * 10;
//          if(VAL_AFR != PVAL_AFR) {
//            PVAL_AFR = VAL_AFR; 
//            genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x02, VAL_AFR);
//            genie.DoEvents();
//          }
//          break;
//          case 1:
//             
//          // b Oil Temp
//          VAL_OILTMP = b - 50;
//          if(VAL_OILTMP != PVAL_OILTMP)  {
//            PVAL_OILTMP = VAL_OILTMP;
//            genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x03, VAL_OILTMP);
//            genie.DoEvents();  
//          }
//
//          // c Exhaust Temp
//          VAL_EGT = c - 50;
//          if(VAL_EGT != PVAL_EGT) {
//            PVAL_EGT = VAL_EGT;
//            genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x00, VAL_EGT);
//            genie.DoEvents();  
//          }    
//      
//          // d wideband CL
//          if(d == 4 || d == 5 || d == 6 || d == 16)  {
//            genie.WriteObject(GENIE_OBJ_USER_LED, 0x00, 1);
//            genie.DoEvents(); 
//          }
//          else  {
//            genie.WriteObject(GENIE_OBJ_USER_LED, 0x00, 0); 
//            genie.DoEvents();
//          }    
//          break;
//          case 2:
//          // over 1 turn on led
//          // leddigits 10 for max
//          
//          VAL_OILPRS = (c * 0.0101972)*10;
//
//         if(VAL_OILPRS != PVAL_OILPRS)  {
//            PVAL_OILPRS = VAL_OILPRS;
//            genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x0B, VAL_OILPRS);
//            genie.DoEvents();  
//          }
//          
//          // b knock global
//          if((b*5) > 1) {
//
//          VAL_KNOCK = VAL_KNOCK + 1;
//            
//          if(VAL_KNOCK != PVAL_KNOCK) {
//            PVAL_KNOCK = VAL_KNOCK;
//            genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x0D, VAL_KNOCK);
//            genie.DoEvents();    
//          }
//          }
//          break;
//        }
//    genie.DoEvents();
//
//    if(MVAL_KNOCK < VAL_KNOCK) { 
//        MVAL_KNOCK = VAL_KNOCK;
//        genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x0A, VAL_KNOCK); 
//        genie.DoEvents();    
//    }
//    
//    if(MVAL_EGT < VAL_EGT) { 
//        MVAL_EGT = VAL_EGT;
//        genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x08, VAL_EGT); 
//        genie.DoEvents();    
//    }
//   
//    if(MVAL_INTAKE < VAL_INTAKE) { 
//        MVAL_INTAKE = VAL_INTAKE;
//        genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x09, VAL_INTAKE); 
//        genie.DoEvents();    
//    }
//
//    if(MVAL_AFR < VAL_AFR) { 
//        MVAL_AFR = VAL_AFR;
//        genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x05, VAL_AFR); 
//        genie.DoEvents();
//    }
//    if(MVAL_WATER < VAL_WATER) { 
//        MVAL_WATER = VAL_WATER;
//        genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x07, VAL_WATER); 
//        genie.DoEvents();
//    }
//    if(MVAL_OILTMP < VAL_OILTMP) { 
//        MVAL_OILTMP = VAL_OILTMP;
//        genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x06, VAL_OILTMP); 
//        genie.DoEvents();
//    }
//    if(MVAL_OILPRS < VAL_OILPRS) { 
//        MVAL_OILPRS = VAL_OILPRS;
//        genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x0C, VAL_OILPRS); 
//        genie.DoEvents();
//    }
//        
//   }
//   genie.DoEvents();   
    } 
}




/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
