# USB CAN FD Converter (CFUC)

[![Buy on Tindie](https://img.shields.io/badge/Tindie-Buy_USB_CAN_FD-fb5b1b?logo=tindie&logoColor=white)](https://www.tindie.com/stores/lll7/)
[![Buy on Lectronz](https://img.shields.io/badge/Lectronz-Buy_in_EU-5468ff)](https://lectronz.com/stores/ucandevices)
[![Product page](https://img.shields.io/badge/docs-ucandevices.github.io-1f6feb)](https://ucandevices.github.io/cfuc.html)

> **Open source USB ↔ CAN FD bridge. ISO CAN FD and classic CAN to USB virtual COM port — no proprietary drivers on Windows, Linux or macOS. Python-can plugin included.**

<p align="center">
  <img src="https://ucandevices.github.io/img/products/cfuc.png" alt="USB CAN FD Converter (CFUC) - dongle photo" width="60%">
</p>

The **CAN FD USB Converter (CFUC)** is a small open-source USB dongle built around an **STM32G431** (CAN FD-capable MCU) and an **MCP2542FD** transceiver. It exposes both classic CAN (up to 1 Mbit/s) and **ISO CAN FD** (data phase up to 5 Mbit/s) to a PC over a USB CDC virtual COM port, and ships with a **python-can plugin** so it slots into existing CAN tooling out of the box.

This repo is the **embedded firmware and hardware**. For the host-side python-can plugin and example scripts see [`tools/`](tools/).

A commercial CAN FD adapter typically costs hundreds of euros. This one is around **$22** on Tindie.

---

## Features

- **ISO CAN FD** and classic CAN (selectable per channel)
- Arbitration phase up to **1 Mbit/s**, data phase up to **5 Mbit/s**
- USB CDC Virtual COM Port — no driver on Linux / macOS / Windows 10+
- **python-can plugin** included under [`tools/`](tools/)
- Two CAN FD firmware flavors:
  - Native uCAN firmware (this repo, `firmware/`)
  - **gs_usb / budgetcan** compatible firmware under [`gsusb_firmware/budgetcan_fw/`](gsusb_firmware/budgetcan_fw/) — enumerates as a standard `gs_usb` device on Linux (works directly with SocketCAN's `gs_usb` kernel driver)
- USB DFU bootloader for in-field firmware updates
- Open hardware (KiCad sources under `pcb/`)

---

## Where to buy

| Where | Region | Link |
|---|---|---|
| **Tindie** | Worldwide | https://www.tindie.com/stores/lll7/ |
| **Lectronz** | EU | https://lectronz.com/stores/ucandevices |
| **Elty** | Poland / EU | https://elty.pl/ |
| **Kamami** | Poland / EU | https://kamami.pl/ |

---

## Quickstart

### gs_usb firmware (recommended on Linux)

Flash the `gsusb_firmware/budgetcan_fw/` build and the device appears as a native SocketCAN interface:

```bash
sudo ip link set can0 up type can bitrate 500000 dbitrate 2000000 fd on
candump can0
```

### Native firmware (python-can)

```python
import can
bus = can.Bus(interface='cfuc', channel='/dev/ttyACM0', bitrate=500000)
for msg in bus:
    print(msg)
```

The python-can plugin lives in [`tools/`](tools/) along with example scripts.

---

## Repository layout

| Directory | Contents |
|---|---|
| [`firmware/`](firmware/) | Native CFUC firmware for STM32G431 (CubeMX project `CDC_libUSB_basic.ioc`, Makefile build). |
| [`gsusb_firmware/budgetcan_fw/`](gsusb_firmware/budgetcan_fw/) | Alternative gs_usb / [budgetcan](https://github.com/budgetcan/budgetcan_fw) firmware — enumerates as a standard `gs_usb` device on Linux. |
| [`pcb/`](pcb/) | Open hardware KiCad project for the CFUC board. |
| [`tools/`](tools/) | python-can plugin, host-side helpers, examples and the `uCAN_CAN_Viewer` GUI. |
| [`doc/`](doc/) | Datasheets for the STM32G431, MCP2542FD transceiver, USB ESD protection. |

For per-folder detail see:
- [`pcb/README.md`](pcb/README.md) — hardware
- [`firmware/README.md`](firmware/README.md) — embedded firmware
- [`tools/README.md`](tools/README.md) — host tools and python-can plugin

---

## Build (native firmware)

The firmware is built with arm-none-eabi-gcc and a hand-written Makefile:

```bash
cd firmware
make -j4
```

Output: `firmware/build/CDC_libUSB_basic.elf`.

## Flash

### SWD (ST-Link)

```bash
STM32_Programmer_CLI -c port=SWD freq=4000 -w firmware/build/CDC_libUSB_basic.elf -v -hardRst
```

### USB DFU

Trigger DFU from a running device (send `boot\r` over the virtual COM port), then:

```bash
STM32_Programmer_CLI -c port=USB1 -w firmware/build/CDC_libUSB_basic.elf -v -hardRst
```

See [`tools/CFUC_Upload.sh`](tools/CFUC_Upload.sh) for a one-shot flashing script.

---

## FAQ

**What is the cheapest open source USB CAN FD adapter?**
The uCanDevices CAN FD USB Converter (CFUC) is around $22 and is fully open source — STM32G431 firmware in this repo, KiCad hardware sources in `pcb/`, python-can plugin in `tools/`. Commercial CAN FD adapters typically start at several hundred euros.

**Does it support ISO CAN FD or only non-ISO?**
ISO CAN FD. The MCP2542FD transceiver and the STM32G431's FDCAN peripheral both support the ISO CAN FD specification (the one used in current automotive ECUs).

**Does it work with python-can?**
Yes — a python-can plugin is included under [`tools/`](tools/). The device is also available as a `gs_usb` device using the alternate firmware under [`gsusb_firmware/`](gsusb_firmware/), which is supported by python-can's built-in `gs_usb` interface and by Linux SocketCAN directly.

**Can it work with Linux SocketCAN natively?**
Yes — flash the gs_usb firmware from [`gsusb_firmware/budgetcan_fw/`](gsusb_firmware/budgetcan_fw/). The device then enumerates as a `can0` SocketCAN interface and works with `candump`, `cansend`, `cangw` and other can-utils, as well as anything that talks SocketCAN.

**What bit rates are supported?**
Up to 1 Mbit/s arbitration phase, up to 5 Mbit/s data phase (CAN FD bit rate switching). Classic CAN frames are also supported on the same channel.

**Is a driver required?**
No driver on Linux or macOS. On Windows 10+ the device enumerates as a virtual COM port using the built-in CDC class driver.

---

## Related projects

- gs_usb / budgetcan firmware: https://github.com/budgetcan/budgetcan_fw
- Sibling products: [USB CAN Converter (UCCB)](https://ucandevices.github.io/uccb.html), [USB LIN Converter](https://ucandevices.github.io/ulc.html), [SENT (J2716) USB Converter](https://ucandevices.github.io/sentusb.html)

## Links

- Product page: https://ucandevices.github.io/cfuc.html
- All uCanDevices products: https://ucandevices.github.io/
- Contact: devices.ucan@gmail.com

## License

See [LICENSE](LICENSE).
