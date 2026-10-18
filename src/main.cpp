#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN  10

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin(); // Automatically uses GPIO 12 (SCK), 13 (MISO), 11 (MOSI), 10 (SS)
  rfid.PCD_Init();
  
  Serial.println("RFID Reader Ready. Tap a card...");
}

void loop() {
  // Wait for a new card to be placed on the reader
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Print the card UID in HEX
  Serial.print("UID:");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.printf(" %02X", rfid.uid.uidByte[i]);
  }
  Serial.println();

  // Halt the card so it only reads once per tap
  rfid.PICC_HaltA();
}