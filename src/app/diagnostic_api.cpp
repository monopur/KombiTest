#include <ESPAsyncWebServer.h>
#include "../hardware/diagnostic_driver.cpp"

void setup_diag_api(AsyncWebServer& server) {
    diag_init();

    server.on("/api/diag", HTTP_GET, [](AsyncWebServerRequest *request){
        String brand = request->getParam("brand")->value();
        DiagBrand b = BRAND_VAILLANT;
        if (brand == "demirdokum") b = BRAND_DEMIRDOKUM;
        else if (brand == "eca") b = BRAND_ECA;
        String result = diag_read_errors_json(b);
        request->send(200, "application/json", result);
    });

    server.on("/api/diag_reset", HTTP_POST, [](AsyncWebServerRequest *request){
        String brand = request->getParam("brand")->value();
        DiagBrand b = BRAND_VAILLANT;
        if (brand == "demirdokum") b = BRAND_DEMIRDOKUM;
        else if (brand == "eca") b = BRAND_ECA;
        diag_reset_error(b);
        request->send(200, "application/json", "{\"reset\":\"ok\"}");
    });
}