#include <HardwareSerial.h>
#include <ArduinoJson.h>
#include "pinmap_dynamic.h"
#include "error_tables.h"

HardwareSerial DiagSerial(1);
#define DIAG_BAUD 9600

enum DiagBrand { BRAND_VAILLANT, BRAND_DEMIRDOKUM, BRAND_ECA };

void diag_init() {
    DiagSerial.begin(DIAG_BAUD, SERIAL_8N1, modelPinMapping["diag_rx"], modelPinMapping["diag_tx"]);
}

String diag_read_errors_json(DiagBrand brand) {
    DynamicJsonDocument doc(512);
    JsonArray arr = doc.createNestedArray("errors");
    while (DiagSerial.available()) {
        uint8_t buf[8];
        if (DiagSerial.readBytes(buf, 8) == 8) {
            uint16_t code = (buf[5] << 8) | buf[6];
            JsonObject err = arr.createNestedObject();
            err["code"] = String(code, HEX);
            switch (brand) {
                case BRAND_VAILLANT:   err["desc"] = error_description(vaillant_error_table, code); break;
                case BRAND_DEMIRDOKUM: err["desc"] = error_description(demirdokum_error_table, code); break;
                case BRAND_ECA:        err["desc"] = error_description(eca_error_table, code); break;
            }
        }
    }
    String out; serializeJson(doc, out);
    return out;
}

// Reset komutu (örnek frame, protokole göre güncellenebilir)
void diag_reset_error(DiagBrand) {
    uint8_t reset_cmd[] = {0xAA, 0x00, 0x10, 0x05, 0x01, 0x00, 0x01, 0x0D};
    DiagSerial.write(reset_cmd, sizeof(reset_cmd));
}