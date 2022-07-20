OLED_ENABLE = yes
OLED_DRIVER = SSD1306
WPM_ENABLE = yes
VIA_ENABLE = yes

CONWAY_ENABLE ?= yes
EGDE_KILL ?= yes
HELD_SPAWN ?= yes
CONWAY_RENDER = yes

OPT_DEFS += -DCONWAY_ENABLE
OPT_DEFS += -DCONWAY_RENDER

SRC += conway.c

ifeq ($(strip $(EGDE_KILL)), yes)
    OPT_DEFS += -DEGDE_KILL
endif
ifeq ($(strip $(HELD_SPAWN)), yes)
    OPT_DEFS += -DHELD_SPAWN
endif
