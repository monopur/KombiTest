#include "../settings/model_settings.h"
#include "../hardware/pinmap_dynamic.h"

/*
 * fan_pwm_driver: Fan PWM çıkışı için pin ve parametreleri modele göre dinamik ayarlar.
 */
struct FanPwmConfig {
    int pin;
    int min_pwm;
    int max_pwm;
};

static FanPwmConfig fanConfig;

void fan_pwm_init() {
    fanConfig.pin = modelPinMapping["fan_pwm"];
    fanConfig.min_pwm = modelSettings.getParam("fan_pwm_min").toInt();
    fanConfig.max_pwm = modelSettings.getParam("fan_pwm_max").toInt();
    pinMode(fanConfig.pin, OUTPUT);
    // ledcSetup ve ledcAttachPin burada eklenir.
}

void fan_pwm_set_percent(float percent) {
    int pwm = fanConfig.min_pwm + (fanConfig.max_pwm - fanConfig.min_pwm) * percent;
    ledcWrite(0, pwm); // kanal 0 örnek
}