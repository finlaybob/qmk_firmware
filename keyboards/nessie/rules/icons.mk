SRC += icons.c

# Icon source files
ICON_SRC = drawing/icons/caps-off.qgf.c \
           drawing/icons/caps-on.qgf.c \
           drawing/icons/cogs.qgf.c \
           drawing/icons/layer.qgf.c \
           drawing/icons/layout.qgf.c \
           drawing/icons/light.qgf.c \
           drawing/icons/mac.qgf.c \
           drawing/icons/matrix.qgf.c \
           drawing/icons/num-off.qgf.c \
           drawing/icons/num-on.qgf.c \
           drawing/icons/power.qgf.c \
           drawing/icons/scrl-off.qgf.c \
           drawing/icons/scrl-on.qgf.c \
           drawing/icons/win.qgf.c \
           drawing/icons/trackpad.qgf.c \
           drawing/icons/encoder.qgf.c \
           drawing/icons/heart.qgf.c \
           drawing/icons/arrow-left.qgf.c \
           drawing/icons/game.qgf.c \
           drawing/icons/speed.qgf.c \
           drawing/icons/time.qgf.c \
           drawing/icons/screen.qgf.c

# Add icon sources to the main source files
SRC += $(ICON_SRC)
