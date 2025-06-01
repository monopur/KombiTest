#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>
#include "../settings/hw_version.h"

#define GUNCELLE_API_LIST "https://api.github.com/repos/monopur/KombiTest/contents/guncelle"
#define MODELS_API_LIST "https://api.github.com/repos/monopur/KombiTest/contents/models"

String local_fw_version = "1.0.0"; // Derlemede güncellenir
String local_hw_version = HW_VERSION;

struct FwUpdateInfo {
    String version;
    String notes;
    String download_url;
    bool hw_compatible;
};

FwUpdateInfo latestFwInfo;

FwUpdateInfo fetch_latest_compatible_fw() {
    FwUpdateInfo result;
    HTTPClient http;
    http.begin(GUNCELLE_API_LIST);
    http.addHeader("User-Agent", "ESP32");
    int code = http.GET();
    if (code != 200) { http.end(); return result; }
    String json = http.getString(); http.end();
    DynamicJsonDocument doc(16*1024);
    deserializeJson(doc, json);
    String best_ver = "";
    for (JsonObject file : doc.as<JsonArray>()) {
        String name = file["name"];
        if (name.startsWith("firmware_version_") && name.endsWith(".json")) {
            String url = file["download_url"];
            HTTPClient fh; fh.begin(url); fh.addHeader("User-Agent", "ESP32");
            if (fh.GET() == 200) {
                DynamicJsonDocument fdoc(2048);
                deserializeJson(fdoc, fh.getString());
                String ver = fdoc["version"] | "";
                JsonArray compat = fdoc["hw_compat"];
                bool hw_ok = false;
                for(JsonVariant v : compat) if(v.as<String>() == local_hw_version) hw_ok = true;
                if (hw_ok && ver > best_ver) {
                    best_ver = ver;
                    result.version = ver;
                    result.notes = fdoc["notes"] | "";
                    result.download_url = fdoc["download_url"] | "";
                    result.hw_compatible = true;
                }
            }
            fh.end();
        }
    }
    return result;
}

bool check_firmware_update() {
    latestFwInfo = fetch_latest_compatible_fw();
    return (latestFwInfo.hw_compatible && latestFwInfo.version != "" && latestFwInfo.version != local_fw_version);
}

bool check_and_update_models() {
    HTTPClient http;
    http.begin(MODELS_API_LIST);
    http.addHeader("User-Agent", "ESP32");
    int code = http.GET();
    if (code != 200) { http.end(); return false; }
    String json = http.getString(); http.end();
    DynamicJsonDocument doc(16*1024);
    deserializeJson(doc, json);
    bool any_new = false;
    for (JsonObject file : doc.as<JsonArray>()) {
        String name = file["name"];
        String path = "/models/" + name;
        if (!SPIFFS.exists(path)) {
            String url = file["download_url"];
            HTTPClient fh; fh.begin(url); fh.addHeader("User-Agent", "ESP32");
            if (fh.GET() == 200) {
                File f = SPIFFS.open(path, "w");
                f.print(fh.getString());
                f.close();
                any_new = true;
            }
            fh.end();
        }
    }
    return any_new;
}