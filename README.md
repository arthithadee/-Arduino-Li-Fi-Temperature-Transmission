# -Arduino-Li-Fi-Temperature-Transmission

Connected DHT11 to measure temperature
  Used LED as transmitter: it blinks to send binary data
  Used LDR as receiver: it detects brightness changes
	Built a bit-by-bit communication protocol (with delays and averaging)
	Created code to send temp as binary and reconstruct it from LDR readings
	Successfully transmitted temperatures like 32, 34, etc.
	Analyzed LDR values and fine-tuned threshold and timing


 # Arduino Li-Fi Temperature Transmission (Single Board)

This project demonstrates how to transmit temperature data using visible light, through a simple setup involving one Arduino UNO board. The system uses a DHT11 temperature sensor, an LED as a transmitter, and an LDR (Light Dependent Resistor) as a receiver.

---

## Project Summary

- **Objective**: Send temperature data as light signals (1s and 0s) using an LED and detect them with an LDR, all using a single Arduino.
- **Approach**: Convert temperature readings into binary and transmit each bit by blinking an LED. The LDR detects light intensity changes and reconstructs the binary data.

---

## Hardware Requirements

- Arduino UNO
- DHT11 Temperature Sensor
- 1 x LED (transmitting light)
- 1 x LDR (light detection)
- 10kΩ resistor (for voltage divider with LDR)
- Jumper wires and breadboard
- USB cable and Arduino IDE

---

## How It Works

1. The Arduino reads the temperature using the DHT11 sensor.
2. It converts the temperature (e.g., 34°C) to ASCII characters (e.g., '3' and '4').
3. Each character is converted to 8-bit binary.
4. For each bit:
   - If bit is 1 → LED is turned ON
   - If bit is 0 → LED is turned OFF
5. While the LED transmits, the LDR reads brightness values multiple times.
6. The program compares LDR average against a threshold to decide if a 1 or 0 was received.
7. Bits are reconstructed to form the original temperature and printed to the Serial Monitor.

---

## Wiring Connections

### Power
- 5V → Breadboard + rail
- GND → Breadboard – rail

### DHT11 Sensor
- VCC → 5V
- GND → GND
- DATA → D2

### LED (Transmitter)
- Anode → D5 (through 220Ω resistor)
- Cathode → GND

### LDR (Receiver)
- One leg → 5V
- Other leg → A0 and to GND through a 10kΩ resistor (voltage divider)

---

## Code Features

- Transmits one character at a time using LED
- Reads analog input using LDR and averages multiple samples
- Applies a configurable threshold to decide bit values
- Reconstructs characters and outputs the decoded temperature

---

## Configuration Parameters

| Parameter           | Value         |
|---------------------|---------------|
| Bit delay           | 1000 ms       |
| Samples per bit     | 10            |
| LDR threshold       | ~200 (adjustable) |

---

## Output Example



```
Starting Transmission Cycle
 Sending Temp: 34

Sending char: 3
  Bit 0: Sent = 0 | LDR avg = 180 → 0
  Bit 1: Sent = 0 | LDR avg = 174 → 0
  Bit 2: Sent = 1 | LDR avg = 215 → 1
  Bit 3: Sent = 1 | LDR avg = 223 → 1
  Bit 4: Sent = 0 | LDR avg = 183 → 0
  Bit 5: Sent = 0 | LDR avg = 182 → 0
  Bit 6: Sent = 1 | LDR avg = 227 → 1
  Bit 7: Sent = 1 | LDR avg = 229 → 1

Sending char: 4
  Bit 0: Sent = 0 | LDR avg = 172 → 0
  Bit 1: Sent = 0 | LDR avg = 171 → 0
  Bit 2: Sent = 1 | LDR avg = 223 → 1
  Bit 3: Sent = 1 | LDR avg = 233 → 1
  Bit 4: Sent = 0 | LDR avg = 188 → 0
  Bit 5: Sent = 1 | LDR avg = 224 → 1
  Bit 6: Sent = 0 | LDR avg = 177 → 0
  Bit 7: Sent = 0 | LDR avg = 170 → 0
 Decoded Temp: 34
✅ Transmission complete.
```
.
