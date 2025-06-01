#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>

// Kullanıcı güncelleme tercihleri (auto_update: açık/kapalı)
struct UpdateSettings {
    bool auto_update = true;
    String last_checked_fw_version;
    void load() {
        File f = SPIFFS.open("/update_settings.json", "r");
        if (!f) return;
        String s = f.readString(); f.close();
        int idx = s.indexOf("auto_update");
        if (idx >= 0) auto_update = s.indexOf("true") > idx;
    }
    void save() {
        File f = SPIFFS.open("/update_settings.json", "w");
        f.print("{\"auto_update\":");
        f.print(auto_update ? "true" : "false");
        f.print(",\"last_checked_fw_version\":\"");
        f.print(last_checked_fw_version);
        f.print("\"}");
        f.close();
    }
};
extern UpdateSettings updateSettings;