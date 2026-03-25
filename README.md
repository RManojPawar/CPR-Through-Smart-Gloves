#  CPR Smart Glove for Cardio

###  IoT-Based Wearable System for Real-Time CPR Monitoring & Emergency Response

---

##  Overview

The CPR Smart Glove is an advanced IoT-enabled wearable healthcare system designed to improve the effectiveness of Cardiopulmonary Resuscitation (CPR) during cardiac emergencies.

It provides real-time feedback on compression quality, monitors critical vital signs, and automatically sends emergency alerts, enabling faster and more accurate life-saving intervention.

---

##  Problem Statement

Performing effective CPR is challenging due to:

*  Inconsistent compression depth and rhythm
*  Lack of real-time feedback
*  No continuous monitoring of vital signs
*  Delayed emergency communication

---

##  Key Features

* Real-Time CPR Monitoring (Depth & Rate Detection)
* Vital Sign Tracking (Heart Rate, SpO₂, ECG, Temperature)
* Instant Feedback System (Buzzer Alerts)
* Live Data Display (LCD Output)
* IoT Emergency Alerts (Telegram API Integration)
* Automated CPR Support (Air Pump Activation)
* Wearable & Portable Design

---

##  System Architecture

The system integrates multiple hardware and software components:

* **ESP32 Microcontroller** → Core processing & IoT communication
* **Biomedical Sensors** → Capture real-time patient data
* **Compression Sensor** → Detect CPR depth & frequency
* **Output Modules** → LCD + Buzzer for feedback
* **Relay System** → Controls automated air pump
* **IoT Layer** → Sends alerts via Telegram

---

##  Working Mechanism

1. Device initializes and checks all sensors
2. Vital signs are continuously monitored
3. CPR compressions are detected and analyzed
4. Feedback is provided in real-time
5. Alerts are triggered if abnormal conditions occur
6. Emergency notification is sent via IoT
7. Automated compression activates if needed

---

##  Tech Stack

###  Software

* Arduino IDE
* Embedded C / C++
* IoT Integration (WiFi, Telegram API)

###  Hardware

* ESP32 Microcontroller
* ECG Sensor
* SpO₂ Sensor
* Heartbeat Sensor
* Temperature Sensor (DS18B20)
* LCD Display
* Buzzer
* Relay Module
* Air Pump

---

##  Results & Impact

*  Improved CPR accuracy and consistency
*  Reduced human error during emergencies
*  Real-time patient monitoring
*  Faster emergency response through automation
*  Affordable and portable healthcare solution

---

##  Project Demonstration

* Smart Glove Setup
* Sensor Integration
* LCD Output Display
* Telegram Alert System

---

##  Research & Achievements

*  Research work based on this project has been presented/published
*  Demonstrated at technical National conference
*  Detailed documentation available upon request

> *Note: Full documents are not publicly shared due to privacy and institutional policies.*

---

##  Future Enhancements

*  Mobile App Integration
*  AI-based CPR Quality Analysis
*  Cloud Monitoring Dashboard
*  Integration with Hospital Emergency Systems

---

##  Project Structure

```
CPR-Smart-Glove/
│── code/
│── hardware/
│── images/
│── results/
│── README.md
```

---

##  Why This Project Stands Out

* Combines **Healthcare + IoT + Embedded Systems**
* Solves a **real-world life-saving problem**
* Includes **automation + real-time feedback**
* Demonstrates **end-to-end system design**


