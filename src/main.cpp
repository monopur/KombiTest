#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <SPIFFS.h>
#include "settings/update_settings.h"
#include "settings/hw_version.h"
#include "app/update_manager.cpp"
#include "app/diagnostic_api.cpp"

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    SPIFFS.begin(true);
    updateSettings.load();

    // Güncelleme kontrolü
    if (updateSettings.auto_update) {
        bool fw_update = check_firmware_update();
        bool models_update = check_and_update_models();
        bool tables_update = check_and_update_error_tables();

        if (fw_update) {
            updateSettings.last_checked_fw_version = latestFwInfo.version;
            updateSettings.save();
        }
        if (models_update || tables_update) {
            // Dilerseniz kullanıcıya bilgi verin
        }
    }

    // Güncelleme tercihi API
    server.on("/api/update_pref", HTTP_POST, [](AsyncWebServerRequest *request){
        bool enabled = request->getParam("enabled")->value() == "true";
        updateSettings.auto_update = enabled;
        updateSettings.save();
        request->send(200, "application/json", "{\"ok\":true}");
    });

    // Güncelleme durumu API
    server.on("/api/update_status", HTTP_GET, [](AsyncWebServerRequest *request){
        bool update = check_firmware_update();
        String json = "{\"update_available\":";
        json += update ? "true" : "false";
        json += ",\"version\":\"" + latestFwInfo.version + "\",\"notes\":\"" + latestFwInfo.notes + "\",\"download_url\":\"" + latestFwInfo.download_url + "\"}";
        request->send(200, "application/json", json);
    });

    setup_diag_api(server);

    server.begin();
}

void loop() {
    // ...
}