#include "INA780x.h"

INA780x::INA780x(uint8_t address) {
    _address = address;
}

void INA780x::begin() {
    Wire.begin(8, 9); // SDA on pin 8, SCL on pin 9
}

bool INA780x::isConnected() {
    uint16_t manufacturerID = getManufacturerID();
    return (manufacturerID == 0x5449); // Check against expected manufacturer ID (0x5449 for TI)
}

void INA780x::reset() {
    writeRegister(CONFIG_REG, 0x8000); // Set the reset bit
}

int16_t INA780x::readRegisterSigned(uint8_t reg) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission();
    
    Wire.requestFrom(_address, (uint8_t)2);
    int16_t value = (Wire.read() << 8) | Wire.read();

    return value;
}

uint16_t INA780x::readRegister(uint8_t reg) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission();
    
    Wire.requestFrom(_address, (uint8_t)2);
    uint16_t value = (Wire.read() << 8) | Wire.read();

    return value;
}

uint64_t INA780x::readRegister(uint8_t reg, uint8_t length) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission();
    
    Wire.requestFrom(_address, length);
    uint64_t value = 0;
    for (uint8_t i = 0; i < length; i++) {
        value = (value << 8) | Wire.read();
    }

    return value;
}

void INA780x::writeRegister(uint8_t reg, uint16_t value) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(value >> 8);
    Wire.write(value & 0xFF);
    Wire.endTransmission();
}

float INA780x::getBusVoltage() {
    uint16_t rawValue = readRegister(VBUS_REG);
    return rawValue * 0.003125; // Conversion factor for bus voltage
}

float INA780x::getCurrent() {
    int16_t rawValue = readRegisterSigned(CURRENT_REG);
    return rawValue * 0.0024; // Conversion factor for current
}

double INA780x::getPower() {
    uint64_t rawValue = readRegister(POWER_REG, 3);
    return rawValue * 0.00048; // Conversion factor for power
}

double INA780x::getEnergy() {
    uint64_t rawValue = readRegister(ENERGY_REG, 5);
    return rawValue * 0.00768; // Conversion factor for energy
}

double INA780x::getCharge() {
    uint64_t rawValue = readRegister(CHARGE_REG, 5);
    return rawValue * 0.000150; // Conversion factor for charge
}

float INA780x::getTemperature() {
    uint16_t rawValue = readRegister(DIETEMP_REG);
    rawValue = rawValue >> 4; // Temperature is stored in the upper 12 bits
    return rawValue * 0.125; // Conversion factor for temperature
}

void INA780x::setConfig(uint16_t config) {
    writeRegister(CONFIG_REG, config);
}

void INA780x::setADCConfig(uint16_t config) {
    writeRegister(ADC_CONFIG_REG, config);
}

// Returns the diagnostic alert register value see datasheet for more information
uint16_t INA780x::getDiagAlert() {
    return readRegister(DIAG_ALRT_REG);
}

// Returns the current over limit in A
uint16_t INA780x::getCurrentOverLimit() {
    uint16_t value = readRegister(COL_REG);
    return value * 0.0024; // Conversion factor for current limit
}

// Returns the current under limit in A
uint16_t INA780x::getCurrentUnderLimit() {
    uint16_t value = readRegister(CUL_REG);
    return value * 0.0024; // Conversion factor for current limit
}

// Returns the bus over voltage limit in V
uint16_t INA780x::getBusOverVoltageLimit() {
    uint16_t value = readRegister(BOVL_REG);
    return value * 0.003125; // Conversion factor for bus voltage limit
}

// Returns the bus under voltage limit in V
uint16_t INA780x::getBusUnderVoltageLimit() {
    uint16_t value = readRegister(BUVL_REG);
    return value * 0.003125; // Conversion factor for bus voltage limit
}

// Returns the temperature limit in degrees Celsius
uint16_t INA780x::getTemperatureLimit() {
    uint16_t value = readRegister(TEMP_LIMIT_REG);
    value = value >> 4; // Temperature limit is stored in the upper 12 bits
    return value * 0.125; // Conversion factor for temperature limit
}

// Returns the power limit in W
uint16_t INA780x::getPowerLimit() {
    uint16_t value = readRegister(PWR_LIMIT_REG);
    return value * 0.12288; // Conversion factor for power limit to W
}

// Returns 0x5449 which is TI in ASCII
uint16_t INA780x::getManufacturerID() {
    return readRegister(MANUFACTURER_ID_REG);
}

// Sets the current over limit in A
void INA780x::setCurrentOverLimit(uint16_t value) {
    writeRegister(COL_REG, value / 0.0024); // Conversion factor for current limit
}

// Sets the current under limit in A
void INA780x::setCurrentUnderLimit(uint16_t value) {
    writeRegister(CUL_REG, value / 0.0024); // Conversion factor for current limit
}

// Sets the bus over voltage limit in V
void INA780x::setBusOverVoltageLimit(uint16_t value) {
    writeRegister(BOVL_REG, value / 0.003125); // Conversion factor for bus voltage limit
}

// Sets the bus under voltage limit in V
void INA780x::setBusUnderVoltageLimit(uint16_t value) {
    writeRegister(BUVL_REG, value / 0.003125); // Conversion factor for bus voltage limit
}

// Sets the temperature limit in degrees Celsius
void INA780x::setTemperatureLimit(uint16_t value) {
    value = value/0.125; // Conversion factor for temperature limit
    value = value << 4; // Temperature limit is stored in the upper 12 bits
    writeRegister(TEMP_LIMIT_REG, value);
}

// Sets the power limit in W
void INA780x::setPowerLimit(uint16_t value) {
    writeRegister(PWR_LIMIT_REG, value / 0.12288); // Conversion factor for power limit to W
}
