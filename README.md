# Arduino Fan Control System

A sophisticated fan control system built with Arduino that provides precise temperature control through either PID control or custom fan curves. This project is perfect for cooling applications where maintaining a specific temperature is crucial.

## Features

- Temperature monitoring using a temperature sensor
- Control of 4-pin PWM PC fan
- Two control modes:
  - PID (Proportional-Integral-Derivative) control for precise temperature regulation
  - Custom fan curve control for predefined temperature-to-speed mapping
- Real-time temperature monitoring
- PWM-based fan speed control

## Hardware Requirements

- Arduino board (compatible with your specific model)
- Temperature sensor
- 4-pin PWM PC fan
- Power supply (appropriate for your fan's requirements)
- Optional: Display for monitoring (if implemented)

## Pin Connections

The project uses the following pin connections:
- Temperature sensor: Connected to an analog input pin
- Fan PWM control: Connected to a PWM-capable digital pin
- Fan tachometer: Connected to a digital input pin (if using 4-pin fan)

## Control Modes

### PID Control
The PID control mode provides precise temperature regulation by:
- Continuously monitoring the temperature
- Calculating the required fan speed based on the PID algorithm
- Adjusting the fan speed to maintain the target temperature

### Fan Curve Control
The fan curve mode allows you to:
- Define custom temperature-to-speed mappings
- Set different fan speeds for different temperature ranges
- Create a more natural cooling response

## Project Structure

```
fan_control/
├── src/                    # Source code files
├── docs/                   # Documentation and design files
│   ├── design.fzz         # Fritzing design file
│   ├── design_bb.png      # Breadboard layout
│   └── design_pcb.png     # PCB layout
└── README.md              # This file
```

## Design Files

The project includes design files in the `docs/` directory:
- `design.fzz`: Fritzing design file for the circuit
- `design_bb.png`: Breadboard layout diagram
- `design_pcb.png`: PCB layout diagram

## Installation

1. Clone or download this repository
2. Open the Arduino project in the Arduino IDE
3. Install any required libraries
4. Upload the code to your Arduino board
5. Connect the hardware according to the wiring diagram in `docs/design_bb.png`

## Usage

1. Power on the system
2. Select your preferred control mode (PID or Fan Curve)
3. Set your target temperature or configure the fan curve
4. The system will automatically maintain the desired temperature

## Contributing

Feel free to submit issues and enhancement requests!

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

## Author

bugparty