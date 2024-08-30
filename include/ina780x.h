#ifndef INA780X_H
#define INA780X_H

#include <Arduino.h>
#include <Wire.h>

class INA780x {
public:
    INA780x(uint8_t address);
    
    void begin();
    bool isConnected();
    void reset();
    
    // Register read/write functions
    uint16_t readRegister(uint8_t reg);
    uint64_t readRegister(uint8_t reg, uint8_t length);
    void writeRegister(uint8_t reg, uint16_t value);
    
    // Measurement functions
    float getBusVoltage();
    float getCurrent();
    double getPower();
    double getEnergy();
    double getCharge();
    float getTemperature();
    
    // Configuration functions
    void setConfig(uint16_t config);
    void setADCConfig(uint16_t config);

    // Additional functions
    uint16_t getDiagAlert();
    uint16_t getCurrentOverLimit();
    uint16_t getCurrentUnderLimit();
    uint16_t getBusOverVoltageLimit();
    uint16_t getBusUnderVoltageLimit();
    uint16_t getTemperatureLimit();
    uint16_t getPowerLimit();
    uint16_t getManufacturerID();

    void setCurrentOverLimit(uint16_t value);
    void setCurrentUnderLimit(uint16_t value);
    void setBusOverVoltageLimit(uint16_t value);
    void setBusUnderVoltageLimit(uint16_t value);
    void setTemperatureLimit(uint16_t value);
    void setPowerLimit(uint16_t value);

private:
    uint8_t _address;
    
    // Constants for register addresses
    static const uint8_t CONFIG_REG = 0x00;
    static const uint8_t ADC_CONFIG_REG = 0x01;
    static const uint8_t VBUS_REG = 0x05;
    static const uint8_t DIETEMP_REG = 0x06;
    static const uint8_t CURRENT_REG = 0x07;
    static const uint8_t POWER_REG = 0x08;
    static const uint8_t ENERGY_REG = 0x09;
    static const uint8_t CHARGE_REG = 0x0A;
    static const uint8_t DIAG_ALRT_REG = 0x0B;
    static const uint8_t COL_REG = 0x0C;
    static const uint8_t CUL_REG = 0x0D;
    static const uint8_t BOVL_REG = 0x0E;
    static const uint8_t BUVL_REG = 0x0F;
    static const uint8_t TEMP_LIMIT_REG = 0x10;
    static const uint8_t PWR_LIMIT_REG = 0x11;
    static const uint8_t MANUFACTURER_ID_REG = 0x3E;
};

#endif
