#include <Arduino.h>
// Libraries
#include <SPI.h>
#include <MFRC522.h>

// Global variables
#define RFID_SS   5
#define RFID_RST  22

MFRC522 rfid(RFID_SS, RFID_RST);

// Functions

// getUID() turns the card's UID bytes into text, for example "4A 1F 9C 02"
String getUID()
{
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++)
  {
    if (rfid.uid.uidByte[i] < 0x10)
    {
      uid = uid + "0";
    }
    uid = uid + String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1)
    {
      uid = uid + " ";
    }
  }
  uid.toUpperCase();
  return uid;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Program Started");

  // RFID code
  SPI.begin();
  rfid.PCD_Init();
  delay(10);
  rfid.PCD_DumpVersionToSerial();
  Serial.println("Tap a card...");

  // LED and buzzer code
}

void loop()
{
  // Card detection
  if (rfid.PICC_IsNewCardPresent() == true && rfid.PICC_ReadCardSerial() == true)
  {
    String uid = getUID();
      Serial.print("Card UID: ");
      Serial.println(uid);

        rfid.PICC_HaltA();
  }

  // Timer
}
