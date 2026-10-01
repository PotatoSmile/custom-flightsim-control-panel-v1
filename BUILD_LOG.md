# Build log

## 2026-10-01 — first HID test

**Goal:** Confirm the Micro appears as a game controller and establish the base code for each component one at a time.

**What happened:**

- Installed Arduino IDE, Joystick library
- Tested a code with one ON-OFF switch
- Tested a code with one ON-OFF-ON switch
- Tested a code with two MTS-101 switches and two MTS-203 switches

**Problems:**

- For the code on the MTS-203 switch, I had a problem with the bracket placement and the placement of the delay.
- Had trouble making the OFF position of the MTS-203 switch count as a button of its own. I decided to seperate the codes for the three components entirely. The THREEWAY Switch Block uses now position values instead of
- `digitalRead(pin == LOW)` compiles clean and reads the wrong pin
- `TOTAL_COUNT` not matching the array length → silent floating pins
- Variables inside `loop()` can't remember anything
- Encoder fires on both edges unless you filter to one

**Learned:**

**Next:** One MTS-101 on pin 6.

---

## 2026-10-02 — all 13 inputs on the breadboard

**Goal:** XXX

**What happened:**

- XXX
- XXX

**Problems:**

- XXX
- XXX
- XXX

**Learned:** XXX

**Next:** XXX
