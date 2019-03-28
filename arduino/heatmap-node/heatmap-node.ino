#include <RFM69.h>
#include <SPI.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

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
boolean requestACK = false;
long lastPeriod = -1;

void setup()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  Serial.begin(SERIAL_BAUD);
  while (!Serial);


  Serial.print("Initializing radio... ");
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.setPowerLevel(25);
  Serial.println("OK");

  //radio.encrypt(KEY);
  Serial.print("Transmitting...");

  Serial.print("Requesting DHT22 reading... ");
  dht.begin();
  digitalWrite(LED, LOW);
}

void loop()
{
  //check for any received packets
  if (radio.receiveDone())
  {
    Serial.print('[');
    Serial.print(radio.SENDERID, DEC);
    Serial.print("] ");
    for (byte i = 0; i < radio.DATALEN; i++) {
      Serial.print((char)radio.DATA[i], DEC);
      if (i < radio.DATALEN - 1) Serial.write(',');
    }
    Serial.print("   [RX_RSSI:");
    Serial.print(radio.readRSSI());
    Serial.print("]");

    if (radio.ACKRequested())
    {
      radio.sendACK();
      Serial.print(" - ACK sent");
      delay(10);
    }
    Serial.println();

    if ((char)(radio.DATA[0]) == 1 && (char)radio.DATA[1] > 0) {
      TRANSMITPERIOD = (char)radio.DATA[1];
      Serial.print("Setting timeout to ");
      Serial.print((char)radio.DATA[1], DEC);
      Serial.println("s");
    }
  }

  int currPeriod = millis() / (TRANSMITPERIOD * 1000);
  if (currPeriod != lastPeriod)
  {
    lastPeriod = currPeriod;

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
  }
}
