/**
 * Ana uygulama dosyası.
 * - Donanım ve web sunucusunu başlatır.
 * - Model dosyasını yükler.
 * - Web API uçlarını ve canlı izleme/testi kurar.
 */
#include <Arduino.h>
#include "settings/model_settings.h"
#include "hardware/pinmap_dynamic.h"
#include "app/hardware_manager.cpp"
#include "app/test_engine.cpp"
#include <FS.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    SPIFFS.begin(true);

    // WiFi başlat (örnek AP)
    WiFi.mode(WIFI_AP);
    WiFi.softAP("KombiTest", "12345678");

    // Model dosyasını yükle (ilk dosya)
    modelSettings.loadFromJson("/models/demirdokum_neo_2023.json");

    // Donanımı modele göre başlat
    hardware_init_from_model();

    // Web API uçları
    server.on("/api/model_settings", HTTP_GET, [](AsyncWebServerRequest *request){
        String json = modelSettings.toJson(); // JSON çıktısı
        request->send(200, "application/json", json);
    });
    server.on("/api/model_settings", HTTP_POST, [](AsyncWebServerRequest *request){
        String body = request->getParam("plain", true)->value();
        File f = SPIFFS.open("/models/active_model.json", FILE_WRITE);
        f.print(body);
        f.close();
        modelSettings.loadFromJson("/models/active_model.json");
        request->send(200, "application/json", "{\"ok\":true}");
    });
    server.on("/api/live_values", HTTP_GET, [](AsyncWebServerRequest *request){
        // Test ve izleme için canlı değer API'si
        DynamicJsonDocument doc(2048);
        JsonArray inputs = doc.createNestedArray("inputs");
        for (const auto& io : modelSettings.getInputs()) {
            JsonObject obj = inputs.createNestedObject();
            obj["id"] = io.id;
            obj["label"] = io.label;
            int pin = modelPinMapping[io.id];
            obj["value"] = (io.type == "ntc" || io.type == "analog") ? analogRead(pin) : digitalRead(pin);
        }
        JsonArray outputs = doc.createNestedArray("outputs");
        for (const auto& io : modelSettings.getOutputs()) {
            JsonObject obj = outputs.createNestedObject();
            obj["id"] = io.id;
            obj["label"] = io.label;
            int pin = modelPinMapping[io.id];
            obj["value"] = (io.type == "relay") ? digitalRead(pin) : 0; // PWM için son ayar eklenebilir
        }
        String out;
        serializeJson(doc, out);
        request->send(200, "application/json", out);
    });
    server.on("/api/run_test", HTTP_POST, [](AsyncWebServerRequest *request){
        String testlog = run_automatic_test_and_get_log();
        DynamicJsonDocument doc(1024);
        doc["result"] = "ok";
        doc["log"] = testlog;
        String out;
        serializeJson(doc, out);
        request->send(200, "application/json", out);
    });

    server.serveStatic("/", SPIFFS, "/data/").setDefaultFile("live_monitor.html");
    server.begin();
}

void loop() {
    // Donanım izleme ve diğer işlemler
}