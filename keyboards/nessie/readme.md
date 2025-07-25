# Nessie v1.1 [DEV]

![nessie](https://i.imgur.com/4jbQzpj.png)

- 58-key semi split, 5 key thumb row
- 2.2" ILI9341 display
- Cirque Trackpad OR EC11 encoder

<hr/>

- Keyboard Maintainer: [Neil Finlay / thslkeys](https://github.com/finlaybob)
- Hardware Supported: *Nessie PCB / plates, rpi pico or compatible clone (e.g. waveshare rp2040 plus usb-c)*
- Hardware Availability: *tbc*

Make example for this keyboard (after setting up your build environment):

    - make nessie:default
    - qmk compile -kb nessie -km default

Flashing example for this keyboard:

    Reboot into bootloader, copy .uf2 firmware file to storage device

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press the reset button twice in quick succession on the front of the PCB to the right of the screen mounting area
* **Keycode in layout**: Press the key mapped to `QK_BOOT`. By default, hold both raise and lower layers to get to ADJUST, press the '-' key
