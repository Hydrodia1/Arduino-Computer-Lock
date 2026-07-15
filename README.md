# 🔒 Arduino Computer Lock

A hardware-based computer security lock built as a senior capstone project. The system requires a user to enter the correct passcode on a keypad before the Arduino can activate the PC's power switch, preventing unauthorized use of the computer.

---

## ✨ Features

* 🔐 Password-protected computer power button
* 💡 LED status indicators
* 🔄 Communication between the Arduino Uno R4 and Arduino Nano Every using I²C
* 🔑 Randomly generated passcode that updates every hour
* 📱 Passcode synchronization through Arduino Cloud

---

## 🛠️ Hardware

| Component                | Description                   |
| ------------------------ | ----------------------------- |
| Arduino Uno R4           | Cloud-connected controller    |
| Arduino Nano Every       | Main controller               |
| 3×4 Matrix Keypad        | DIYables                      |
| 16×2 LCD                 | I2C Interface                 |
| NOT Gate Schmitt Trigger | 74HC14                        |
| Logic Level Shifter      | TCA9517D                      |
| PNP Transistor           | Controls the PC power switch  |
| LEDs                     | Red & Green status indicators |
| Resistors                | 1×100Ω, 2×180Ω, 2×1kΩ, 2×4kΩ  |
| Miscellaneous            | Breadboard & Jumper Wires     |

---

# 🚀 Installation

## 1. Download the Project

Clone this repository or download it as a ZIP file.

---

## 2. Install Arduino Cloud

1. Create an **Arduino Cloud** account if you do not already have one.
2. Download the **Arduino Cloud** mobile app (Android or iOS).
3. Sign in using the same Arduino account that will be used for this project.

> **Note:** The Arduino Cloud mobile app is required because it displays the randomly generated passcode used to unlock the computer.

---

## 3. Configure Arduino Cloud

1. Connect the **Arduino Uno R4** to your computer.
2. Open **Arduino Cloud**.
3. Create a new **Device** using the Arduino Uno R4.
4. Create a new **Thing**.
5. Add a **Character String** variable named:

```text
random_passcode
```

Configure the variable with the following settings:

| Setting    | Value            |
| ---------- | ---------------- |
| Type       | Character String |
| Permission | Read Only        |
| Update     | On Change        |

Once configured, the generated passcode will automatically synchronize with the Arduino Cloud mobile app.

---

## 4. Upload the Code

Upload each sketch to its corresponding Arduino.

| Sketch        | Board              |
| ------------- | ------------------ |
| `UNO-R4-Slave` | Arduino Uno R4     |
| `NANO-Master` | Arduino Nano Every |

---

## 5. Assemble the Hardware

Build the circuit using the included:

📄 **WiringDiagram.pdf**

---

# ▶️ Operation

1. Power the circuit.
2. Open the **Arduino Cloud** mobile app.
3. View the current **`random_passcode`**.
4. Enter the passcode using the keypad.
5. If the passcode is correct, the Arduino will momentarily activate the computer's power switch, allowing the computer to power on.
