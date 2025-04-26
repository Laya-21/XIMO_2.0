
# XIMO (Xenodochial Intelligent Manipulative Operator)

Welcome to the Ximo Robotic Arm project repository!
This robotic arm is developed by the Robot Study Circle, COEP. Ximo is a 5-DOF robotic arm designed for precise multi-axis motion, controlled wirelessly via an ESP32-based web server. The project combines SolidWorks mechanical design, custom PCB electronics, and web-based embedded control.


## Roadmap

- CAD Design

- PCB Development

- Web-based Control System

- Assembly & Testing



## Hardware Components

- Microcontroller: ESP32

- Actuators: 5x Servo Motors

- Power Supply: AC Adapter with voltage regulation

- Custom PCB: Designed for ESP32 integration and servo connections

- 3D Printed / CNC Machined Parts: Based on SolidWorks CAD model


## CAD Design

The mechanical structure of Ximo was designed in SolidWorks, focusing on joint stability, movement range, and aesthetic form.

## Model Preview

| ![Main PCB](https://raw.githubusercontent.com/Laya-21/XIMO_2.0/refs/heads/main/Media/img11.jpg) | ![Main PCB 3D](https://raw.githubusercontent.com/Laya-21/XIMO_2.0/refs/heads/main/Media/gif1.gif) |
|:--:|:--:|
| Ximo CAD Model | Full 3D Assembly |

## Control System
Ximo is controlled via a wireless ESP32 Web Server, enabling real-time joint control through your smartphone or any web browser.

**FEATURES**:
- Individual sliders to control each joint angle
- Live, wireless control over Wi-Fi / ESP32 Access Point
- Compact and user-friendly interface

## PCB Design
A custom-designed PCB was developed using Altium Designer, integrating the ESP32, power regulation, and servo motor headers for a clean and efficient layout.

**TOOLS USED**:
- Software: Altium Designer

- Board Material: FR4

- Layers: Single-sided

**DESIGN HIGHLIGHTS:**

- Stable 5V/3.3V power distribution for ESP32 and servo motors

- Organized header pins for plug-and-play servo connections

- Compact board layout optimized for the arm’s compact chassis

## CODE Overview
The firmware for Ximo is developed using Arduino Framework for the ESP32.

**ESP32 Web Server**:
- Hosts a custom webpage for real-time control

- Sliders for each servo motor (Base, Shoulder, Elbow, Wrist, Gripper)

**Servo Control Logic**
- PWM signals generated using ESP32 hardware timers

- Smooth, precise control of each joint

## MEDIA

| ![Main PCB](https://raw.githubusercontent.com/Laya-21/XIMO_2.0/refs/heads/main/Media/gif2.gif) | ![Main PCB 3D](https://raw.githubusercontent.com/Laya-21/XIMO_2.0/refs/heads/main/Media/img2.jpg) |
|:--:|:--:|
| Test | Full BOT |
