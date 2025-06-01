#pragma once
#include <Arduino.h>
#include <vector>

struct ErrorEntry { uint16_t code; String description; };

class ErrorTable {
public:
    std::vector<ErrorEntry> entries;
    String file_path;
    ErrorTable(String path) : file_path(path) {}

    void load() {
        entries.clear();
        File f = SPIFFS.open(file_path, "r");
        if (!f) return;
        String s = f.readString();
        DynamicJsonDocument doc(4096);
        deserializeJson(doc, s);
        for (JsonObject err : doc["errors"].as<JsonArray>()) {
            entries.push_back({ (uint16_t)err["code"], (const char*)err["description"] });
        }
        f.close();
    }
    String description(uint16_t code) {
        for (auto& e : entries) if (e.code == code) return e.description;
        return "Bilinmeyen arıza kodu";
    }
};

extern ErrorTable vaillantTable, demirdokumTable, ecaTable, boschTable;
