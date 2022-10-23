CC         := sh2be-none-elf-gcc
AR         := sh2be-none-elf-ar
CFLAGS     := -O2 -fno-builtin -Qn -nostdlib -ffreestanding
ARMIPS     := armips

CDFS_DIR     := cdfs
CD_SYSID     := "SEGA SATURN"
CD_VOLID     := "HelloWorld"
CD_PUBLISHER := "SEGA ENTERPRISES, LTD."
CD_PREPARER  := "SEGA ENTERPRISES, LTD."
CD_APPID     := "HelloWorld"
IP_PATH      := build/IP.BIN

# Note:
#	SEGA Saturn will always load the *first* file in the
#	ISO9660 filesystem as an executable.
#	Therefore, the result code binary filename should
#	start with something like a zero, so that mkisofs would place
#	it at the top of the filesystem, as it sorts files alphabetically,
#	it seems
EXE_NAME := 0kernel.bin


BUILD_DIR := ./build
SRC_DIR   := ./src
SRCS      := $(shell find $(SRC_DIR) -name "*.c")
OBJS      := $(SRCS:%=$(BUILD_DIR)/%.o)
EXE_PATH  := $(BUILD_DIR)/$(EXE_NAME)

default: all
all: $(BUILD_DIR)/game.iso

$(BUILD_DIR)/game.iso: $(EXE_PATH)
	mkisofs -sysid $(CD_SYSID) -volid $(CD_VOLID) -publisher $(CD_PUBLISHER) \
		-preparer $(CD_PREPARER) -appid $(CD_APPID) -full-iso9660-filenames \
		-sectype 2352 -generic-boot $(IP_PATH) -o "$(BUILD_DIR)/game.iso" $(CDFS_DIR) $(EXE_PATH)

$(EXE_PATH): $(BUILD_DIR)/combined.a
	$(ARMIPS) -strequ BUILD_DIR $(BUILD_DIR) \
              -strequ EXE_PATH $(EXE_PATH) \
              -strequ LIBGCC_PATH $(shell $(CC) $(CFLAGS) -print-libgcc-file-name)\
              -sym "$(BUILD_DIR)/symbols.sym" \
              armips.s
	
$(BUILD_DIR)/combined.a: $(OBJS)
	mkdir -p $(dir $@)
	$(AR) r $(BUILD_DIR)/combined.a $?
	
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	rm -r $(BUILD_DIR)