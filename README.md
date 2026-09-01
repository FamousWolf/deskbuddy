# ESPHome Desk Buddy for ESP32 S3 Box 3

An ESPHome desk buddy for an ESP32 S3 Box 3 with a happiness meter that can be set using Home Assistant. The device shows a pair of animated eyes on the built-in LCD and reacts to its environment (loud noises, screen touches) and to the happiness level configured in Home Assistant.

## Features

- Animated eyes rendered on the ESP32 S3 Box 3 LCD, with randomized blinking and horizontal eye movement.
- Seven visual states: Neutral, Happy, Sad, Scared, Loved, Sleepy and Sleeping.
- A `Happiness Level` number entity in Home Assistant (`-100` to `100`) that drives the emotional state.
- Automatic **happiness decay** over time when the meter isn't updated.
- Reactions to real-world events:
  - A loud noise (measured via the built-in microphone) scares the buddy and decreases happiness.
  - Touching the screen makes the buddy feel loved and increases happiness.
- Auto sleep: if idle long enough, the buddy becomes sleepy and may fall asleep.
- Manual state override from Home Assistant via a `State` select entity.

## Project layout

```
desk-buddy-esp-s3-box-3.yaml   ESPHome configuration (board, display, sensors, services)
Components/
  DeskBuddy/                   Custom ESPHome component
    __init__.py                Component registration (schema + code generation)
    DeskBuddy.h / .cpp         Core logic: state selection, animations, happiness
    library.json               PlatformIO library build configuration
    States/                    One file per visual state (BaseState + 7 states)
    Utilities/                 Drawing primitives and animation helpers
```

### States

The active state is picked in priority order. `Scared`, `Loved`, `Sleeping` and `Sleepy` are triggered by events or idle time; `Happy`, `Sad` and `Neutral` depend on the happiness value.

#### Neutral

When no other state is active, the desk buddy will be in a neutral state. It will show two large eyes that blink and move horizontally.

#### Happy

When the happiness meter is above 50, the desk buddy will be happy. It will show two oval half circle eyes that are higher than the neutral state and blink and move horizontally.

#### Sad

When the happiness meter is below -50, the desk buddy will be sad. It will show two drooping eyes that are lower than the neutral state and blink and move horizontally.

#### Scared

When the desk buddy detects a loud noise, it will be scared. It will show two small round eyes that jitter randomly for a few seconds. This will decrease the happiness meter by 10 points.

#### Loved

When the desk buddy's screen is touched, it will feel loved. It will show two red, heart-shaped eyes for a few seconds. This will increase the happiness meter by 10 points.

#### Sleepy

When the desk buddy is idle for at least 5 minutes it can become sleepy. It will show two drooping eyes that will slowly close and then quickly open again.

#### Sleeping

When the desk buddy is sleepy for 30 seconds it can go to sleep. It will show two closed eyes that slowly move up and down.

## Happiness decay

If the happiness meter hasn't changed, every 15 minutes the happiness meter will decay towards neutral by 5 percent. This means that if the happiness meter is above 0, it will decrease by 5 percent every hour until it reaches 0. If the happiness meter is below 0, it will increase by 5 percent every hour until it reaches 0.

## Hardware

- **Board:** ESP32 S3 Box 3 (`esp32s3box`, 16 MB flash, octal PSRAM)
- **Display:** `ili9xxx` model `S3BOX`, driven over SPI
- **Touchscreen:** GT911 on I2C
- **Microphone:** ES7210 ADC over I2S
- **Backlight:** monochromatic LED output on GPIO47

## Prerequisites

- [ESPHome](https://esphome.io/) installed and available on your `PATH`.
- A `secrets.yaml` file with your Wi-Fi credentials, created in the project root. This file is git-ignored and must be provided locally:

```yaml
wifi_ssid: "YourSSID"
wifi_password: "YourPassword"
```

## Installation

1. Compile and flash the firmware to the device:

   ```bash
   esphome run desk-buddy-esp-s3-box-3.yaml --device <PORT>
   ```

   OTA uploads are also enabled, so after the first flash you can use:

   ```bash
   esphome run desk-buddy-esp-s3-box-3.yaml
   ```

## Home Assistant integration

The ESPHome `api:` configuration exposes the following entities:

### Number: `Happiness Level`

- Range `-100` to `100`, default `0`, restored across reboots.
- Drives the Happy / Sad / Neutral states:
  - `> 50` → Happy
  - `< -50` → Sad
  - otherwise → Neutral
- Changes to this entity from Home Assistant are applied to the device.

### Select: `State`

- Options: `Auto`, `Happy`, `Loved`, `Neutral`, `Sad`, `Scared`, `Sleepy`, `Sleeping`.
- `Auto` (default) lets the device decide its state based on happiness and events.
- Any other option forces that state regardless of happiness.

### Service: `add_happiness`

- Variable: `change_by` (float).
- Adjusts the happiness meter by the given amount (e.g. `+10` or `-10`).

### Light: `LCD Backlight`

- Monochromatic light controlling the display backlight brightness.

### Sensors: `Buddy Average Volume` and `Buddy Peak Volume`

- RMS and peak audio level from the built-in microphone (internal). A loud noise (peak above `-16.0 dB`) triggers the Scared state.

## Architecture

The core logic lives in the custom ESPHome component `Components/DeskBuddy`:

- **`DeskBuddy.cpp`** — the main `Component`. In `loop()` it:
  1. Updates blink and horizontal-move animators.
  2. Decides the active state by iterating the priority-ordered `states` vector and picking the first whose `isActive()` returns true.
  3. Renders the active state to the display.
- **`BaseState`** — abstract base class exposing `getName()`, `isActive()` and `render(...)`; each concrete state implements these.
- **`States/`** — one class per visual state. `isActive()` combines event flags (`isScared`, `isLoved`, `isSleepy`, `isSleeping`), the happiness value, and forced-state overrides.
- **`Utilities/`** — `FloatAnimator` (tweened value animation) and `Draw` (rounded rectangles, ovals, donuts, hearts, etc.).
- **`__init__.py`** — registers the `DeskBuddy:` config key and the component class with ESPHome's code generator.

### Idle / sleep logic

When no state is forced and happiness hasn't changed for 5 minutes:

- If already Sleepy for 30 seconds, there is a 50% chance to fall asleep (`isSleeping = true`).
- Otherwise, if no state change for 5 minutes, there is a 10% chance to become Sleepy.

## License

See the [LICENSE](LICENSE) file.
