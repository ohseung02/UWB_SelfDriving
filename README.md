# Autonomous Delivery System using UWB Precision Positioning (Capstone Design)

This project was developed as part of the Capstone Design (Engineering Design) course during the 3rd year, 6th semester of the 2025 academic year. It features an autonomous delivery vehicle based on Ultra-Wideband (UWB) technology.

---

## Project Introduction
The goal of this project was to implement an autonomous delivery system that collects real-time location data using UWB technology to ensure safe navigation to a destination. The system was designed based on the premise that UWB provides more precise positioning than conventional GPS in both indoor and outdoor environments.

### Key Features
* Real-time Location Tracking: Calculates vehicle position by measuring the distance between UWB Tags and Anchors.
* Wireless Control and Autonomous Navigation: Controls motors based on data sent from the Sender to the Receiver.
* Precision Distance Measurement: Utilizes the DW1000 module, which offers lower error margins than traditional sensors.

---

## Hardware Configuration
* Controller: Arduino Nano / ESP8266
* Sensor: DW1000 UWB Module
* Motor: DC Motor & Motor Driver (e.g., L298N)
* Communication: Data processing via SPI communication

---

## Repository Structure
* /src: Arduino source code (Sender/Receiver)
* /docs: Presentation materials, final poster (PDF)
* /media: Demonstration video (operation check)
* /libs: Dedicated libraries used in the project

---

## Getting Started
1. Download or clone this repository.
2. Add the libraries in the /libs folder to your Arduino libraries directory.
3. Upload the code from /src/sender and /src/receiver to their respective boards.
4. Refer to the presentation materials in the /docs folder for hardware wiring diagrams.

---

## Project Information
* Development Period: March 2025 - June 2025
* Reference Materials: Detailed design processes are documented in the /docs folder.
