# Pin map

Arduino Micro (ATmega32U4). Button index 0 appears as JOY_BTN1.

## Two-position toggles

| #   | Pin | Index (on/off) | Buttons       |
| --- | --- | -------------- | ------------- |
| 1   | 6   | 0 / 1          | BTN1 / BTN2   |
| 2   | 8   | 2 / 3          | BTN3 / BTN4   |
| 3   | 9   | 4 / 5          | BTN5 / BTN6   |
| 4   | 10  | 6 / 7          | BTN7 / BTN8   |
| 5   | 11  | 8 / 9          | BTN9 / BTN10  |
| 6   | 12  | 10 / 11        | BTN11 / BTN12 |
| 7   | A0  | 12 / 13        | BTN13 / BTN14 |
| 8   | A1  | 14 / 15        | BTN15 / BTN16 |

## Three-position switches

| #   | Up pin | Down pin | Index (up/centre/down) | Buttons  |
| --- | ------ | -------- | ---------------------- | -------- |
| 1   | A2     | A3       | 16 / 17 / 18           | BTN17–19 |
| 2   | A4     | A5       | 19 / 20 / 21           | BTN20–22 |
| 3   | 7      | MISO     | 22 / 23 / 24           | BTN23–25 |

Only one pole of each DPDT is used. Common pin → GND.

## Rotary encoders

| #   | CLK | DT  | Index (CW/CCW) | Buttons       |
| --- | --- | --- | -------------- | ------------- |
| A   | 2   | 4   | 25 / 26        | BTN26 / BTN27 |
| B   | 3   | 5   | 27 / 28        | BTN28 / BTN29 |

Push buttons (SW) not wired.

## Pins avoided

| Pin  | Why                                                      |
| ---- | -------------------------------------------------------- |
| 13   | Onboard LED pulls it down — unreliable with INPUT_PULLUP |
| 0, 1 | RX/TX, can misbehave during upload                       |

## Notes

- Interrupt-capable: 0, 1, 2, 3, 7. Encoder CLK must use these.
- Both encoders' + → 5V. All grounds daisy-chained to one GND pin.
- 29 of 32 available button indices used.
