QUANTUM_PAINTER_DRIVERS += ili9341_spi
QUANTUM_PAINTER_DRIVERS += surface

# ENCODER_ENABLE = yes
# ENCODER_MAP_ENABLE = yes
TRI_LAYER_ENABLE = yes
SEND_STRING_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

# BACKLIGHT_ENABLE = yes
# too slow BACKLIGHT_DRIVER = software # TODO - RP2040 pwm?

# TODO -  Trackpad with multiple SPI devices requires a custom driver.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER += cirque_pinnacle_spi

# Debugging
CONSOLE_ENABLE = yes


SRC += fonts/agave.qff.c
SRC += display.c
SRC += drawing/nessie.qgf.c
SRC += drawing/logo.qgf.c
SRC += drawing/text.c

