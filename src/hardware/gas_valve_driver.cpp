#include "../settings/model_settings.h"
#include "../hardware/pinmap_dynamic.h"

/*
 * gas_valve_driver: Gaz valfi PWM çıkışı için parametreleri dinamik ayarlar.
 */
struct GasPwmConfig {
    int pin;
    int min_pwm;
    int max_pwm;
};

static GasPwmConfig gasConfig;

void gas_valve_init() {
    gasConfig.pin = modelPinMapping["gas_pwm"];
    gasConfig.min_pwm = modelSettings.getParam("gaz_pwm_min").toInt();
    gasConfig.max_pwm = modelSettings.getParam("gaz_pwm_max").toInt();
    pinMode(gasConfig.pin, OUTPUT);
    // ledcSetup ve ledcAttachPin burada eklenir.
}

void gas_valve_set_percent(float percent) {
    int pwm = gasConfig.min_pwm + (gasConfig.max_pwm - gasConfig.min_pwm) * percent;
    ledcWrite(1, pwm); // kanal 1 örnek
}