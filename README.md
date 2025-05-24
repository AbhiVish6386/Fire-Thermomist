# 🧯 Fire Thermomist – Smart Fire and Environment Monitoring System

**Author:** Abhishek Kumar Vishwakarma
**Platform:** ESP32 WROOM32 Devkit V1
**Language:** C++
**Framework:** Arduino (via PlatformIO)

---

## 📘 Project Description

Fire Thermomist is an IoT-based safety and environment monitoring system designed to detect fire, monitor humidity and temperature in real-time, and display dynamic animations on an OLED screen. It is ideal for deployment in environments like server rooms where overheating or fire can cause critical damage.

The project uses:

* A DHT22 sensor for temperature & humidity
* A flame sensor for fire detection
* An OLED display for real-time visualization & animated UI
* A buzzer for alarm when fire is detected

Boot time and idle animations provide an enhanced interactive experience. When fire is detected, the system alerts via buzzer and a flame animation on OLED.

---

## ✅ Features

* Animated boot-up screen (3-stage)
* Weather animation (sunrise → rain → sunset)
* Real-time temp & humidity monitoring via DHT22
* Fire detection via IR flame sensor
* Frame-based OLED animation logic
* Buzzer alert system on fire detection

---

## 🧰 Hardware Requirements

* ESP32 WROOM32 Devkit V1
* DHT22/AM2302 Sensor
* Flame Sensor (Infrared)
* 1.3" I2C OLED Display (White)
* Buzzer (5V)
* BC547 Transistor
* 1k & 10k Resistors
* Tactile Push Button
* MB102 Power Supply Module (3.3V/5V)
* Solderless Breadboard
* Jumper Wires
* USB Type-A to Micro USB cable

---

## 💻 Software Requirements

### ⚙️ PlatformIO Setup (Recommended)

> PlatformIO is an extension for VS Code that simplifies embedded development with ESP32.

### 📦 How to Install PlatformIO in VS Code:

1. Install [Visual Studio Code](https://code.visualstudio.com/)
2. Go to Extensions (Ctrl+Shift+X)
3. Search for **PlatformIO IDE**
4. Click **Install**

### 🚀 How to Create a Project in PlatformIO:

1. Open PlatformIO home (alien icon in VS Code sidebar)
2. Click **New Project**
3. Enter name: `FireThermomist`
4. Board: **Espressif ESP32 Dev Module**
5. Framework: **Arduino**
6. Click **Finish** and wait for project to initialize

You can now copy your `.cpp` and `.h` files into `src/` folder.

---

## 🧾 `platformio.ini` Configuration

Here’s an example config (replace or update as per your settings):

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
upload_port = COM3
monitor_port = COM3
lib_deps = 
	adafruit/Adafruit GFX Library @ ^1.12.0
	adafruit/Adafruit SH110X @ ^2.1.12
	adafruit/DHT sensor library @ ^1.4.6
	blynkkk/Blynk @ ^1.3.2
```

🖼️ *(You can add a screenshot of your .ini file here for reference)*

---

## 📂 Folder Structure

```
FireThermomist/
├── include/              # Header files
├── lib/                  # Additional libraries (if any)
├── src/                  # All main .cpp files go here
├── platformio.ini        # PlatformIO configuration
└── README.md
```

---

## 📸 Circuit Diagram


[Schematic_Fire-Thermomist_2025-05-24pdf.pdf](https://github.com/user-attachments/files/20422283/Schematic_Fire-Thermomist_2025-05-24pdf.pdf)

---

## 🧠 Project Use Case

Designed for 24/7 monitoring of high-risk environments like:

* Server rooms
* Data centers
* Chemistry labs
* Storage facilities with sensitive electronics

The system offers passive monitoring and active alerts before damage can occur.

---

## 📜 License

This project is licensed under the MIT License.  
You are free to use, modify, and share this code for educational or personal projects.  
However, **giving proper credit to the original author is mandatory**.

