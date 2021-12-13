MCU = STM32G474

BOOTMAGIC_ENABLE = yes		  # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = yes         # Commands for debug and configuration
SLEEP_LED_ENABLE = yes       # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes            # USB Nkey Rollover
UNICODE_ENABLE = yes         # Unicode
WPM_ENABLE = yes

SPLIT_KEYBOARD = yes

ENCODER_ENABLE = yes

USBPD_ENABLE = yes

BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = pwm

WS2812_DRIVER = pwm
CIE1931_CURVE = yes

RGBLIGHT_ENABLE = no
RGBLIGHT_DRIVER = WS2812

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812

EEPROM_DRIVER = spi

AUDIO_ENABLE = yes
AUDIO_DRIVER = pwm_software
AUDIO_PIN = A5
AUDIO_PIN_ALT = A4

QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS = ili9341

LTO_ENABLE = yes
OPT = 2

#LTO_ENABLE = no
#OPT = 0
#OPT_DEFS += -g

DEFAULT_FOLDER = tzarc/djinn/rev2
