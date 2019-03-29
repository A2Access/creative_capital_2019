#include <RFM69.h>
#include <SPI.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <Arduino.h>            // assumes Arduino IDE v1.0 or greater
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>

#define NODEID      100 // Current Node

#define NETWORKID   10	// Network
#define GATEWAYID   1	// Node to which messages should be sent
#define FREQUENCY   RF69_433MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_915MHZ)

#define KEY         "thisIsEncryptKey" //has to be same 16 characters/bytes on all nodes, not more not less!
#define LED         9	// Where the LED is connected (by default 9 on Moteino, 13 on normal UNOs)

#define SERIAL_BAUD 115200
#define ACK_TIME    100  // # of ms to wait for an ack

#define DHTPIN 5
#define DHTTYPE    DHT22

int TRANSMITPERIOD = 15; //transmit a packet to gateway so often (in sec)

typedef struct
{
  int           nodeId;		//store this nodeId
  float         temperature;  //temperature
  float         humidity;		//temperature
} Payload;

RFM69 radio;

DHT dht(DHTPIN, DHTTYPE);


Payload theData;
byte sendSize = 0;

//watchdog interrupt
ISR (WDT_vect) {
  wdt_disable();
}

void setup()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  Serial.begin(SERIAL_BAUD);
  while (!Serial);


  Serial.print("Initializing radio... ");
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.setPowerLevel(25);

  radio.sleep();

for (uint8_t i=0; i<=A5; i++)
  {
    if (i == RF69_SPI_CS) continue;

    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  
  power_timer1_disable();
  power_timer2_disable();
  power_twi_disable();
  
  Serial.println("OK");

  //radio.encrypt(KEY);
  Serial.print("Transmitting...");

  Serial.print("Requesting DHT22 reading... ");
  dht.begin();
  digitalWrite(LED, LOW);
}

void loop()
{
// disable ADC
  ADCSRA = 0;  
  // clear various "reset" flags
  MCUSR = 0;
  // allow changes, disable reset
  WDTCSR = bit (WDCE) | bit (WDE);
  //set interrupt mode and an interval
  WDTCSR = bit (WDIE) | bit (WDP3) | bit (WDP0); //set WDIE, and 8 seconds delay
  wdt_reset(); //pat the dog...
  
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  noInterrupts(); // timed sequence follows  
  sleep_enable();

  // turn off brown-out enable in software
  // BODS must be set to one and BODSE must be set to zero within four clock cycles
  MCUCR = bit (BODS) | bit (BODSE);
  // The BODS bit is automatically cleared after three clock cycles
  MCUCR = bit (BODS); 
  interrupts();
  sleep_cpu();

  //cancel sleep as a precaution
  sleep_disable();

  radio.sleep();

  //digitalWrite(LED, HIGH);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Serial.println(t);


  //digitalWrite(LED, LOW);

  //fill in the struct with new values
  theData.nodeId = NODEID;
  theData.temperature = t;
  theData.humidity = h;

  Serial.print("Sending ");
  Serial.print(sizeof(theData));
  Serial.print(" bytes, ");
  Serial.print("temp: ");
  Serial.print(theData.temperature);
  Serial.print(" humidity: ");
  Serial.print(theData.humidity);
  Serial.print("... ");
  if (radio.sendWithRetry(GATEWAYID, (const void*)(&theData), sizeof(theData))) {
    Serial.println(" ok!");
    digitalWrite(LED, HIGH);
    delay(150);
    digitalWrite(LED, LOW);
    delay(350);
    digitalWrite(LED, HIGH);
    delay(150);
    digitalWrite(LED, LOW);

  } else {
    Serial.println(" nothing...");
    digitalWrite(LED, HIGH);
    delay(150);
    digitalWrite(LED, LOW);
    delay(350);
    digitalWrite(LED, HIGH);
    delay(150);
    digitalWrite(LED, LOW);
    delay(350);
    digitalWrite(LED, HIGH);
    delay(150);
    digitalWrite(LED, LOW);
  }
  
  radio.sleep();
  
}
