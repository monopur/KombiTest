#include "../settings/model_settings.h"
#include "../hardware/pinmap_dynamic.h"

/*
 * hardware_manager: Model dosyasındaki giriş/çıkışlara göre donanım pinlerini ve sürücüleri başlatır.
 */
void hardware_init_from_model() {
    for (const auto& io : modelSettings.getInputs()) {
        int pin = modelPinMapping[io.id];
        if (io.type == "ntc" || io.type == "analog") {
            pinMode(pin, INPUT);
        } else if (io.type == "digital") {
            pinMode(pin, INPUT_PULLUP);
        } else if (io.type == "pulse") {
            pinMode(pin, INPUT);
        }
    }
    for (const auto& io : modelSettings.getOutputs()) {
        int pin = modelPinMapping[io.id];
        if (io.type == "relay") {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);
        } else if (io.type == "pwm") {
            pinMode(pin, OUTPUT);
        }
    }
}