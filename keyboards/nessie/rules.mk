QUANTUM_PAINTER_DRIVERS += ili9341_spi
QUANTUM_PAINTER_DRIVERS += surface

SPI_DRIVER_REQUIRED = yes

TRI_LAYER_ENABLE = yes
SEND_STRING_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

POINTING_DEVICE_DRIVER = cirque_pinnacle_spi

SRC += fonts/default.qff.c
SRC += display.c
SRC += drawing/nessie.qgf.c
SRC += drawing/logo.qgf.c
SRC += drawing/splash_text.qgf.c
SRC += drawing/splash_logo.qgf.c
SRC += drawing/widget.c

include keyboards/nessie/rules/icons.mk

POINTING_DEVICE_DEBUG = yes
CONSOLE_ENABLE = yes
