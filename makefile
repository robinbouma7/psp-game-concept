TARGET = test
OBJS = main.o \
glib2d.o
 
CFLAGS = -G0 -Wall -g -O2
CXXFLAGS = $(CFLAGS) -fno-rtti  -fno-exceptions
ASFLAGS = $(CFLAGS)

LIBS = -lpng -ljpeg -lz -lpspgu -lm -lpspvram -lstdc++

# psp stuff
PSP_FW_VERSION = 500
PSP_LARGE_MEMORY = 1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = the big maze
# PSP_EBOOT_ICON = icon0.png

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
