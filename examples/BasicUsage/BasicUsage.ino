#include <Wire.h>
#include <INA780x.h>

INA780x powerMonitor(0x44); // Replace 0x44 with the correct I2C address

void setup() {
    Serial.begin(9600);
    powerMonitor.begin();
    
    if (powerMonitor.isConnected()) {
        Serial.println("INA780x found and connected!");
        delay(500);
    } else {
        Serial.println("INA780x not found!");
        while (1); // Halt the program if the chip is not found
    }

    powerMonitor.reset();
    
    // Configure ADC (example configuration)
    //powerMonitor.setADCConfig(0x4120);
}

void loop() {
    float busVoltage = powerMonitor.getBusVoltage();
    float current = powerMonitor.getCurrent();
    double power = powerMonitor.getPower();
    double energy = powerMonitor.getEnergy();
    float temperature = powerMonitor.getTemperature();
    double charge = powerMonitor.getCharge();
    uint16_t diagAlert = powerMonitor.getDiagAlert();

    Serial.print("Bus Voltage: ");
    Serial.print(busVoltage);
    Serial.println(" V");
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println(" A");
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println(" W");
    Serial.print("Energy: ");
    Serial.print(energy);
    Serial.println(" J");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    Serial.print("Charge: ");
    Serial.print(charge);
    Serial.println(" As");
    Serial.print("Diag Alert: ");
    Serial.println(diagAlert, BIN);
    Serial.println("--------------------");

    delay(2000);
}
