# RibchoWeb

Compact ESP project using PlatformIO. Provides networking, routing, and trigger/executor components for embedded web-based control.

## Requirements
- [PlatformIO](https://platformio.org)
- Supported ESP toolchain (ESP32c3 as configured in `platformio.ini`)

## Quick build & upload
Build the project:

```bash
platformio run
```

Upload to the device (automatic environment from `platformio.ini`):

```bash
platformio run -t upload
```

Open the serial monitor (default baud rate defined in `platformio.ini`):

```bash
platformio device monitor
```

## Project layout
- `include/` — shared headers (`comms.hh`, `net_cfg.hh`, `utils.hh`)
- `lib/` — local libraries (`Device/`, `Logger/`)
- `src/` — application code split by component
  - `controller/` — controller logic
  - `executor/` — execution engine
  - `router/` — routing logic
  - `trigger/` — trigger sources
- `platformio.ini` — build configuration and board environments

## Where to edit
- Main entry points are in `src/*/main.cpp` files.
- Shared utility headers under `include/`.
- Add device-specific code under `lib/Device`.

## Contact
For questions, contact: ribarskiboris@gmail.com

---
