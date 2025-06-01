// ... Diğer kodlar aynı kalır ...

#define ERROR_TABLES_API_LIST "https://api.github.com/repos/monopur/KombiTest/contents/guncelle/error_tables"

// Hata tablosu güncelleme (tüm markalar için)
bool check_and_update_error_tables() {
    HTTPClient http;
    http.begin(ERROR_TABLES_API_LIST);
    http.addHeader("User-Agent", "ESP32");
    int code = http.GET();
    if (code != 200) { http.end(); return false; }
    String json = http.getString(); http.end();
    DynamicJsonDocument doc(16*1024);
    deserializeJson(doc, json);
    bool any_new = false;
    for (JsonObject file : doc.as<JsonArray>()) {
        String name = file["name"];
        String path = "/error_tables/" + name;
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
    // Yeniden yükle
    vaillantTable.load();
    demirdokumTable.load();
    ecaTable.load();
    boschTable.load();
    return any_new;
}