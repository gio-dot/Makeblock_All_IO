# Makeblock_All_IO
Arduino Standard Programming for Makeblock mBot (mCore Board)

 [Makeblock mBot](https://www.makeblock.com/pages/mbot-robot-kit) is a very good educational project, especially suited for younger students thanks to its use of the Scratch programming language and the dedicated Makeblock platform, which provides a comprehensive Arduino library.

However, in my opinion, the use of this library is **not ideal for students in the final years of technical high school**, for the following reasons:

- The mCore board is based on an **ATmega328** microcontroller (like the Arduino Uno), but the Makeblock library **hardcodes I/O assignments** that do not match the standard Arduino pin names.
- Motor control is abstracted by the library and does **not use standard Arduino PWM functions**, hiding important details.
- Most other sensors are accessed through **custom Makeblock commands**, which differ from the standard Arduino APIs and generic libraries.

For these reasons, I decided to [**analyze the mCore schematic**](https://github.com/gio-dot/Makeblock_All_IO/blob/main/docs/mCore.pdf) to map all its I/O connections to the onboard ATmega328 chip.  
By understanding the relationship between mCore ports and the ATmega328 pins, it is now possible to **use pure Arduino code and generic libraries to program the mBot**.

This allows the robot to become a more useful tool for students in technical high schools, who can now learn **standard Arduino programming** without relying on simplified or proprietary libraries.

---

##  Project Features

- Use of **Arduino standard code** (no Makeblock library)
- Compatibility with **standard Arduino IDE**
- Use of **generic Arduino libraries** for sensors and actuators
- Educational examples suitable for **technical high school students**

---

##  Provided example

- Provided example test all onboard OUTPUTS by pressing onboard button
- Ultrasonic and Light sensors provide readings on serial monitor
- Line Follower sensors activate respectively left and right onboard red leds 

---

