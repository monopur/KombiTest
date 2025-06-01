#pragma once
#include <Arduino.h>
#include <map>

/*
 * modelPinMapping: Model dosyasındaki giriş/çıkış ID'lerini ESP32 pin numaralarına eşler.
 */
static std::map<String, int> modelPinMapping = {
    {"ntc1", 34}, {"ntc2", 35}, {"ntc3", 36},
    {"relay_fan", 26}, {"relay_valve", 27}, {"relay_pump", 14},
    {"fan_pwm", 4}, {"gas_pwm", 12},
    {"turbine", 13}, {"pressure", 39}, {"pressure_sw", 39},
    {"ion", 32}, {"condensate", 33}, {"fan_rpm", 25},
    {"modbus", 22}
};