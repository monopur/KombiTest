#include "../settings/model_settings.h"
#include "../hardware/pinmap_dynamic.h"

/*
 * test_engine: Modeldeki tüm çıkışlar ve girişler için otomatik test adımları uygular.
 */
String run_automatic_test_and_get_log() {
    String log = "";
    for (const auto& o : modelSettings.getOutputs()) {
        int pin = modelPinMapping[o.id];
        if (o.type == "relay") {
            digitalWrite(pin, HIGH); delay(200);
            log += o.label + " ON\n";
            digitalWrite(pin, LOW); delay(200);
            log += o.label + " OFF\n";
        }
        if (o.type == "pwm") {
            for (float p = 0; p <= 1.0; p+=0.5) {
                log += o.label + " PWM %" + String(int(p*100)) + "\n";
                delay(100);
            }
        }
    }
    for (const auto& i : modelSettings.getInputs()) {
        int pin = modelPinMapping[i.id];
        int val = (i.type=="ntc"||i.type=="analog") ? analogRead(pin) : digitalRead(pin);
        log += i.label + ": " + String(val) + "\n";
    }
    return log;
}