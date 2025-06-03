
QUANTUM_PAINTER_DRIVERS += ili9341_spi
QUANTUM_PAINTER_DRIVERS += surface

POINTING_DEVICE_DRIVER = cirque_pinnacle_spi
SPI_DRIVER_REQUIRED = yes

TRI_LAYER_ENABLE = yes
SEND_STRING_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

POINTING_DEVICE_DEBUG = yes

POINTING_DEVICE_ENABLE = yes
CONSOLE_ENABLE = yes



SRC += fonts/agave.qff.c
SRC += display.c
SRC += drawing/nessie.qgf.c
SRC += drawing/logo.qgf.c
SRC += drawing/text.c
SRC += drawing/nessie-text-logo.qgf.c
