// **********************************************************************************************************
// Moteino gateway/base sketch that works with Moteinos equipped with RFM69W/RFM69HW/RFM69CW/RFM69HCW
// This is a basic gateway sketch that receives packets from end node Moteinos, formats them as ASCII strings
//      with the end node [ID] and passes them to Pi/host computer via serial port
//     (ex: "messageFromNode" from node 123 gets passed to serial as "[123] messageFromNode")
// It also listens to serial messages that should be sent to listening end nodes
//     (ex: "123:messageToNode" sends "messageToNode" to node 123)
// Make sure to adjust the settings to match your transceiver settings (frequency, HW etc).
// **********************************************************************************
// Copyright Felix Rusu 2016, http://www.LowPowerLab.com/contact
// **********************************************************************************
// License
// **********************************************************************************
// This program is free software; you can redistribute it
// and/or modify it under the terms of the GNU General
// Public License as published by the Free Software
// Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public
// License for more details.
//
// Licence can be viewed at
// http://www.gnu.org/licenses/gpl-3.0.txt
//
// Please maintain this license information along with authorship
// and copyright notices in any redistribution of this code
// **********************************************************************************
#include <RFM69.h>         //get it here: https://github.com/lowpowerlab/rfm69
#include <RFM69_ATC.h>     //get it here: https://github.com/lowpowerlab/RFM69
#include <RFM69_OTA.h>     //get it here: https://github.com/lowpowerlab/RFM69

//****************************************************************************************************************
//**** IMPORTANT RADIO SETTINGS - YOU MUST CHANGE/CONFIGURE TO MATCH YOUR HARDWARE TRANSCEIVER CONFIGURATION! ****
//****************************************************************************************************************
#define NODEID          1 //the ID of this node
#define NETWORKID     10 //the network ID of all nodes this node listens/talks to
#define FREQUENCY     RF69_433MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define ACK_TIME       30  // # of ms to wait for an ack packet
//*****************************************************************************************************************************
//#define ENABLE_ATC    //comment out this line to disable AUTO TRANSMISSION CONTROL
#define ATC_RSSI      -75  //target RSSI for RFM69_ATC (recommended > -80)
//*****************************************************************************************************************************
// Serial baud rate must match your Pi/host computer serial port baud rate!
#define SERIAL_EN     //comment out if you don't want any serial verbose output
#define SERIAL_BAUD  115200
//*****************************************************************************************************************************

#ifdef __AVR_ATmega1284P__
#define LED           15 // Moteino MEGAs have LEDs on D15
#define FLASH_SS      23 // and FLASH SS on D23
#else
#define LED           9 // Moteinos have LEDs on D9
#define FLASH_SS      8 // and FLASH SS on D8
#endif

#ifdef SERIAL_EN
#define DEBUG(input)   {Serial.print(input); delay(1);}
#define DEBUGln(input) {Serial.println(input); delay(1);}
#else
#define DEBUG(input);
#define DEBUGln(input);
#endif

typedef struct
{
  int           nodeId;
  float         temperature;
  float         humidity;
} Payload;

#ifdef ENABLE_ATC
RFM69_ATC radio;
#else
RFM69 radio;
#endif

Payload theData;

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(10);
  DEBUGln("starting");
  radio.initialize(FREQUENCY, NODEID, NETWORKID);

#ifdef ENABLE_ATC
  radio.enableAutoPower(ATC_RSSI);
#endif

}

void loop() {
  if (radio.receiveDone())
  {
    if (radio.DATALEN > 0)
    {
      theData = *(Payload*) radio.DATA;
      DEBUG("nodeid: ");
      DEBUG(theData.nodeId);
      DEBUG(" temp: ");
      DEBUG(theData.temperature);
      DEBUG(" humidity: ");
      DEBUG(theData.humidity);
    }

    if (radio.ACKRequested())
    {
      byte theNodeID = radio.SENDERID;
      radio.sendACK();
    }
    DEBUGln();
    Blink(LED, 3);
  }
}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN, LOW);
}
