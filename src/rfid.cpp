#include "settings.h"

#include <SPI.h>
#include <MFRC522.h>

MFRC522 rfid(SS_PIN, RST_PIN);

void init_reader() {
    SPI.begin();
    rfid.PCD_Init();
}


String read_uid() {
    if (!rfid.PICC_IsNewCardPresent()) {
        return "";
    }
    if (!rfid.PICC_ReadCardSerial()) {
        return "";
    }

    String uidString = "";

    for (byte i = 0; i < rfid.uid.size; i++) {
        if (rfid.uid.uidByte[i] < 0x10) {
            uidString += " 0";
        } else {
            uidString += " ";
        }
        uidString += String(rfid.uid.uidByte[i], HEX);
    }

    return uidString;
}

void halt_card() {
    rfid.PICC_HaltA();
}
