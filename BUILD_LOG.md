# Build log

## 2026-10-01 — first HID test

**Goal:** Confirm the Micro appears as a game controller and establish the base code for each component one at a time.

**What happened:**

- Installed Arduino IDE, Joystick library
- Tested a code with one ON-OFF switch
- Tested a code with one ON-OFF-ON switch
- Tested a code with two MTS-101 switches and two MTS-203 switches

**Problems:**

- MTS-203 code misbehaved → bracket placement and delay in the wrong spot → fixed both
- OFF position of the MTS-203 didn't register as its own button → the two pins were being read as independent switches → separated the three component types entirely; the THREEWAY block now derives a single position (0/1/2) from both pins instead of reading each one on its own
- `digitalRead(pin == LOW)` compiled clean but read the wrong pin → parenthesis in the wrong place, so it compared the pin number to LOW and read pin 0 → moved the bracket outside the read
- Toggles dead while three-ways worked → `TOTAL_COUNT` was 4 but `PINS[]` had 6 entries, so pins 6 and 8 never got INPUT_PULLUP and read as floating noise → set TOTAL_COUNT to 6
- `millis()` timers never fired → declared inside `loop()`, so they reset every pass → moved them to globals as `unsigned long`
- Encoder printed twice per detent → fired on both CLK edges → added `&& CLK_NOW == LOW` to act on the falling edge only

**Learned:** A variable declared inside `loop()` is destroyed and recreated on every pass, so anything that compares "now" to "last time" has to be global. That one rule explains the timers, LAST_TOGGLE, LAST_THREEWAY and LAST_CLK. Also: C++ will happily compile something that does the wrong thing — a clean build is not a working build.

**Next:** Replace the Serial prints with Joystick.setButton() calls, scale the arrays to 8 toggles and 3 three-ways, then move to the physical panel.

---

## 2026-10-02 — rewrote the sketch from scratch, all inputs working

**Goal:** Write the whole sketch myself, one component type at a time, then scale to the full panel.

**What happened:**

- Rewrote the toggle block from scratch using an array and a for loop
- Wrote the three-way block — derives a single position (0/1/2) from both pins instead of reading them independently
- Wrote my own encoder polling code, got it working, then switched to the Encoder library
- Replaced the Serial prints with `Joystick.setButton()` calls
- Scaled the arrays up to 8 toggles, 3 three-ways, 2 encoders
- Button index layout: toggles 0–15 (two each), three-ways 16–24 (three each), encoders 25–28

**Problems:**

- `millis()` timers never fired → declared inside `loop()`, so they were destroyed and recreated every pass → moved them to globals as `unsigned long`
- Encoder printed twice per detent → fired on both CLK edges → added `&& CLK_NOW == LOW` to act on the falling edge only
- Buttons firing at random → `TOTAL_COUNT` was 2 while `PINS[]` had 14 entries, so 12 pins never got INPUT_PULLUP and read as floating noise → set TOTAL_COUNT to 14
- One switch triggering four different buttons → `LAST_TOGGLE[]` had 2 entries but the loop ran 8 times, writing past the end of the array and corrupting adjacent memory → resized to 8, and `LAST_THREEWAY[]` to 3
- Pin 10 dead, pin 11 firing buttons 9–12 → solder bridge between pins 10 and 11 on the board → not fixed yet, need a proper iron
- Button 17 never fired (three-way 1, up position) → wiring was inverted, the OFF side was connected to the pin → swapped the connections

**Learned:** A variable declared inside `loop()` cannot remember anything — it's destroyed and recreated every pass. Anything comparing "now" to "last time" has to be global.

Array overruns in C++ don't throw an error. They write into whatever memory sits next and the symptoms appear somewhere unrelated. Python would have stopped immediately. Check array length against the loop count every time.

A fault that seems to move when you swap components may still be on the board — swapping changes which pins are under test, not where the fault is.

**Next:** Clear the solder bridge between pins 10 and 11. Buy a proper soldering iron (adjustable temperature, fine tip). Then start on the physical panel.

---

## 2026-10-10 — soldered the wires on every switch

**Goal:** Get the lead wires soldered on all the switches and both encoders.

**What happened:**

- Soldered the lead wires on all 11 switches (8× MTS-101, 3× MTS-203). About 3 hours.
- Wired both KY-040 encoders.
- Pulled on every joint to test it. One broke and I redid it. One other is weaker than the rest.
- Taped every joint — no heat shrink anywhere I trust locally.
- Left the common ground line for later. The panel isn't cut yet so I'd be guessing where the switches end up.

**Decisions:**

- **Lap joints, not hooked ones.** Everyone says to hook the wire through the lug hole. I tried both and the hooked ones came out weaker — the hole is small and the solder doesn't always get in. A lap joint grips more of the wire. Did the rest as lap joints.
- **Spliced wires for the encoders.** No F-to-F wires available. The KY-040 pins are 2.54mm apart, too close to solder without bridging them. Cut two F-to-M jumpers and spliced the female halves together.
- **The Micro stands vertically** on its long edge to take up less floor space in the box. It has no mounting holes so it goes in a printed slot, not on standoffs.

**Learned:** The usual advice isn't always right for the parts I actually have. I tried both ways and the one everyone recommends was worse on these lugs.

**Next:** Model the enclosure. Internal depth comes from the tallest switch plus the wire bend behind it, the USB cutout comes from wherever the board slot puts the port, and the cable needs something to pull against behind the port.

---

## 2026-10-14 — panel arrived, switches mounted

**Goal:** Mount the switches in the cut panel and start the ground bus.

**What happened:**

- Got the cut aluminium panel.
- Mounted all 11 switches. Encoders not in yet.
- Put both nuts on the top face — one to clamp, one as a jam nut against it. The switch body sits directly against the back of the panel.
- Prepared the first of the two ground bus wires.

**Problems:**

- Two joints move more easily than the others → not sure why, they passed the pull test → leaving them, but these are the first ones to check if an input goes weird

**Decisions:**

- **Encoders go in diagonally** inside the box so their wires don't cross the switch wires behind the panel.

**Learned:** The panel isn't really DCS-specific. It shows up as a normal USB game controller, so anything that reads joystick buttons can use it. It's a universal switch panel that I happened to build for DCS.

**Next:**

- Solder the second ground bus wire
- Join both bus lines into one wire going to the Arduino's GND
- Check continuity from the GND end to every switch ground lug before closing the box
- Model the enclosure
