#include <ESPAsyncWebServer.h>
#include "../hardware/diagnostic_driver.cpp"

void setup_diag_api(AsyncWebServer& server) {
    diag_init();
    vaillantTable.load();
    demirdokumTable.load();
    ecaTable.load();
    boschTable.load();

    server.on("/api/diag", HTTP_GET, [](AsyncWebServerRequest *request){
        String brand = request->getParam("brand")->value();
        DiagBrand b = BRAND_VAILLANT;
        if (brand == "demirdokum") b = BRAND_DEMIRDOKUM;
        else if (brand == "eca") b = BRAND_ECA;
        else if (brand == "bosch") b = BRAND_BOSCH;
        String result = diag_read_errors_json(b);
        request->send(200, "application/json", result);
    });

    server.on("/api/diag_reset", HTTP_POST, [](AsyncWebServerRequest *request){
        String brand = request->getParam("brand")->value();
        DiagBrand b = BRAND_VAILLANT;
        if (brand == "demirdokum") b = BRAND_DEMIRDOKUM;
        else if (brand == "eca") b = BRAND_ECA;
        else if (brand == "bosch") b = BRAND_BOSCH;
        diag_reset_error(b);
        request->send(200, "application/json", "{\"reset\":\"ok\"}");
    });
}