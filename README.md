# INA780x Arduino Library

## Overview

The INA780x Arduino Library provides an interface to communicate with the Texas Instruments INA780x family of digital power monitors using the I2C interface. The library supports various functionalities such as measuring bus voltage, shunt voltage, current, power, and temperature, as well as configuring the ADC settings and handling diagnostic alerts.

## Features

- Supports all chips in the INA780x family
- Communicates over I2C
- Reads bus voltage, shunt voltage, current, power, and temperature
- Configures ADC settings (conversion time, averaging, etc.)
- Reads and sets diagnostic alert limits
- Checks device connection using the manufacturer ID

## Installation

### Arduino IDE

1. Download the latest release of the library from the [GitHub repository](https://github.com/yourusername/INA780x).
2. Open the Arduino IDE.
3. Go to `Sketch` > `Include Library` > `Add .ZIP Library...`.
4. Select the downloaded `.zip` file to install the library.

### PlatformIO

1. Add the following dependency to your `platformio.ini` file:
   ```ini
   lib_deps = https://github.com/yourusername/INA780x.git
   ```
2. Build your project to automatically download and install the library.

## Usage

### Basic Example

    ```cpp

    #include <Wire.h>
    #include "INA780x.h"

    INA780x powerMonitor(0x40); // Replace 0x40 with the correct I2C address

    void setup() {
    Serial.begin(9600);
    powerMonitor.begin();

        if (powerMonitor.isConnected()) {
            Serial.println("INA780x found and connected!");
        } else {
            Serial.println("INA780x not found!");
            while (1); // Halt the program if the chip is not found
        }

        powerMonitor.reset();

        // Configure ADC (example configuration)
        powerMonitor.setADCConfig(0x4120);

    }

    void loop() {
        float busVoltage = powerMonitor.getBusVoltage();
        float shuntVoltage = powerMonitor.getShuntVoltage();
        float current = powerMonitor.getCurrent();
        float power = powerMonitor.getPower();
        float temperature = powerMonitor.getTemperature();
        uint16_t charge = powerMonitor.getCharge();
        uint16_t diagAlert = powerMonitor.getDiagAlert();

        Serial.print("Bus Voltage: ");
        Serial.println(busVoltage);
        Serial.print("Shunt Voltage: ");
        Serial.println(shuntVoltage);
        Serial.print("Current: ");
        Serial.println(current);
        Serial.print("Power: ");
        Serial.println(power);
        Serial.print("Temperature: ");
        Serial.println(temperature);
        Serial.print("Charge: ");
        Serial.println(charge);
        Serial.print("Diagnostic Alerts: ");
        Serial.println(diagAlert, HEX);

        delay(1000);

    }

    ```

## API Reference

- `INA780x(uint8_t address)`: Constructor, initializes the library with the I2C address of the INA780x device.
- `void begin()`: Initializes the I2C communication.
- `bool isConnected()`: Checks if the INA780x device is connected and working correctly by reading the manufacturer ID.
- `void reset()`: Resets the INA780x device.
- `float getBusVoltage()`: Returns the bus voltage in volts.
- `float getShuntVoltage()`: Returns the shunt voltage in volts.
- `float getCurrent()`: Returns the current in amperes.
- `float getPower()`: Returns the power in watts.
- `float getTemperature()`: Returns the temperature in degrees Celsius.
- `void setADCConfig(uint16_t config)`: Configures the ADC settings (conversion time, - averaging, etc.).
- `void setAlertLimit(uint16_t limit)`: Sets the alert limit.
- `uint16_t getCharge()`: Returns the charge measurement.
- `uint16_t getDiagAlert()`: Returns the diagnostic alert register value.
- `uint16_t getCurrentUnderLimit()`: Returns the current under-limit value.
- `uint16_t getBusOverVoltageLimit()`: Returns the bus over-voltage limit.
- `uint16_t getBusUnderVoltageLimit()`: Returns the bus under-voltage limit.
- `uint16_t getTemperatureLimit()`: Returns the temperature limit.
- `uint16_t getPowerLimit()`: Returns the power limit.
- `uint16_t getManufacturerID()`: Returns the manufacturer ID.

## License

This library is licensed under the MIT License. See the LICENSE file for more details.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

## Support

For issues or questions, please open an issue in the GitHub repository.
