# 🌡️ STM32-Based Temperature & Humidity Monitor (DHT11 + I2C LCD)

## 🚀 Project Overview

This project builds a compact environmental monitoring system using an **STM32F4 microcontroller**, where temperature and humidity values are captured using a **DHT11 sensor** and displayed on a **16x2 LCD via I2C communication**.

Instead of relying on libraries for everything, this implementation focuses on **low-level timing control and protocol understanding**, making it a great hands-on embedded systems project.

---

## 🎯 What Makes This Project Interesting?

* Uses **precise microsecond timing** to communicate with DHT11
* Demonstrates **single-wire protocol decoding**
* Minimizes wiring using **I2C LCD interface**
* Built completely using **STM32 HAL drivers**
* Real-time data visualization on hardware

---

## 🧩 Hardware Used

* STM32F401 Microcontroller
* DHT11 Temperature & Humidity Sensor
* 16x2 LCD with I2C module
* Breadboard & jumper wires

---

## 🔌 Pin Configuration

### 📍 Sensor (DHT11)

* DATA → PA1
* VCC → 3.3V
* GND → GND

### 📍 LCD (I2C)

* SDA → PB9
* SCL → PB8
* VCC → 5V
* GND → GND

---

## ⚙️ Core Idea Behind Implementation

The DHT11 doesn’t use standard protocols like I2C or SPI. Instead, it communicates using **timing-based digital signals**.

### 🧠 How data is captured:

1. STM32 sends a **start pulse** to wake the sensor
2. DHT11 acknowledges with a response signal
3. Sensor transmits **40 bits of data**
4. Each bit is interpreted based on how long the signal stays HIGH
5. Extracted values are converted into readable temperature & humidity

---

## ⏱️ Timing is Everything

A hardware timer (TIM2) is used to generate **microsecond-level delays**, which is critical because:

* DHT11 differentiates between 0 and 1 using timing
* Even small delay errors can corrupt data

---

## 📟 Display Logic

Once data is decoded:

* First row → Temperature
* Second row → Humidity
* LCD is controlled via I2C → reduces GPIO usage

Example output:

```
Temp: 27C
Hum: 60%
```

---

## 🔄 Execution Flow

* Initialize peripherals (GPIO, I2C, Timer)
* Trigger DHT11 communication
* Read and decode sensor data
* Send formatted values to LCD
* Repeat continuously with delay

---

## 💡 Key Learning Takeaways

This project helped in understanding:

* Embedded timing constraints
* GPIO mode switching (input/output dynamically)
* Sensor communication without standard protocols
* Interfacing multiple peripherals simultaneously
* Writing modular embedded C code

---

## 🚀 Possible Enhancements

* Upgrade to **DHT22** for better accuracy
* Add **UART logging** for debugging
* Integrate **WiFi module (ESP8266)** for IoT dashboard
* Store data using **SD card module**

---

## 📁 Project Structure

```
Core/
 ├── Inc/
 ├── Src/
STM32_DHT11.ioc
README.md
```

---

