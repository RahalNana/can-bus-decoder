#include "mcp_can.h"
#include <SPI.h>
#include <Arduino_GFX_Library.h>
#include "Adafruit_ILI9341.h"

#define TFT_CLK    14
#define TFT_MOSI   13
#define TFT_MISO   12
#define TFT_CS     26
#define TFT_DC     27
#define TFT_RST  25

#define CAN_ID_ECT 1
#define CAN_ID_IAT 2

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

int IAT = 0, ECT = 0;

MCP_CAN CAN0(5);                               // Set CS to pin 5

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

uint16_t bgcolor=0x0000;

void setup()
{
  Serial.begin(9600);  // Serial0 @ 200000 (200K) Baud  
  Serial.println(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK);

  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(2, INPUT_PULLUP);                            // Setting pin 2 for /INT input
  
  tft.begin();
  tft.setCursor(0, 0);
  tft.setTextSize(3);
  tft.fillScreen(bgcolor);

}

void loop()
{
    if(!digitalRead(2))        // If pin 2 is low, read receive buffer
    {
        CAN0.readMsgBuf(&rxId, &len, rxBuf);              // Read data: len = data length, buf = data byte(s)

        if (rxBuf[0]==CAN_ID_ECT) ECT = rxBuf[3]*256+rxBuf[2]-50;
        if (rxBuf[0]==CAN_ID_IAT) IAT = rxBuf[3]*256+rxBuf[2]-50;
       
        for(int i=0; i<8; i++)
        {
          Serial.print(rxBuf[i]);
          Serial.print(" ");
        }
        Serial.println("");
    } 
//    else
//    {
//      tft.setCursor(20, 20);
//      tft.setTextColor(ILI9341_YELLOW, bgcolor); 
//      tft.print("IAT : ");
//      tft.print(IAT);
//      tft.println("   ");
//  
//      tft.setCursor(20, 80);
//      tft.print("ECT : ");
//      tft.print(ECT);
//      tft.println("   ");
//    }
}

//void canread()
//{
//    CAN0.readMsgBuf(&rxId, &len, rxBuf);              // Read data: len = data length, buf = data byte(s)
//
//    if (rxBuf[0]==CAN_ID_ECT) ECT = rxBuf[2];
//    if (rxBuf[0]==CAN_ID_IAT) IAT = rxBuf[2]; 
//
//    for(int i=0; i<8; i++)
//    {
//      Serial.print(rxBuf[i]);
//      Serial.print(" ");
//    }
//    Serial.println("");
//}
