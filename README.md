# 4x4 Calculator Using Keypad and LCD

Welcome to the **4x4 Calculator** project! This simple calculator, built with the ESP32 microcontroller, allows you to perform basic arithmetic operations using a 4x4 keypad and displays the results on an LCD screen. The project features a custom keypad handler and LCD handler libraries that simplify input handling and screen management.

## Table of Contents:
1. [Project Overview](#project-overview)
2. [Components Used](#components-used)
3. [Hardware Connections](#hardware-connections)
4. [Libraries Used](#libraries-used)
5. [Installation Instructions](#installation-instructions)
6. [How to Use](#how-to-use)
7. [License](#license)
8. [Acknowledgements](#acknowledgements)

---

## Project Overview
This project is designed to offer an easy-to-use calculator interface for basic mathematical operations. By pressing keys on the keypad, the user can input numbers and choose operations like addition, subtraction, multiplication, and division. The results are displayed on an LCD screen, and the calculation can be reset at any time.

---

## Components Used:
- **ESP32 Microcontroller**
- **4x4 Keypad**
- **16x2 LCD Display** (or compatible)
- **Custom Libraries**:
  - **KeypadHandler**: A custom library that abstracts keypad input and manages debouncing and key processing.
  - **LCDHandler**: A custom library that controls the LCD screen, updating the display based on user inputs and results.

---

## Hardware Connections:

### Keypad (4x4):
- **Rows** connected to pins: `8, 3, 46, 9`
- **Columns** connected to pins: `10, 11, 12, 13`

### LCD Display:
- **Data Pins (D4-D7)** connected to pins: `47, 48, 45, 35`
- **Enable Pin (E)** connected to pin: `21`
- **Register Select Pin (RS)** connected to pin: `20`

---

## Libraries Used:

### **KeypadHandler**
The **KeypadHandler** library simplifies handling the 4x4 keypad. It takes care of:
- **Debouncing**: The library ensures that only one input is registered per keypress, avoiding multiple triggers.
- **Key Mapping**: It maps the rows and columns of the keypad to their respective actions (numbers or operations).
- **Key Input Management**: It continuously checks for keypresses and returns the corresponding character.

### **LCDHandler**
The **LCDHandler** library manages the LCD display's interactions. It handles:
- **Screen Initialization**: Automatically initializes the LCD with the necessary configuration.
- **Dynamic Updates**: Updates the screen as the user enters numbers or operations.
- **Clear Function**: Provides functionality to clear the screen and reset the calculation.

These libraries are designed to be easily reusable for other projects involving keypads and LCDs.

---

## Installation Instructions:

1. **Clone the repository** to your local machine:
   ```bash
   git clone https://github.com/mobinAlijani/Calculator_Lcd.git
