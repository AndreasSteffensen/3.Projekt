# Kernel Module
KMODULE := spi_drv
DTB_FILE := $(KMODULE)-overlay.dtb
DTBO_FILE := $(KMODULE).dtbo
KERNELDIR = ~/sources/rpi-4.19.89
CCPREFIX = arm-poky-linux-gnueabi-
# To build modules outside of the kernel tree, we run "make"
# in the kernel source tree; the Makefile these then includes this
# Makefile once again.
# This conditional selects whether we are being included from the
# kernel Makefile or not.
ifeq ($(KERNELRELEASE),)
    # The current directory is passed to sub-makes as argument
    PWD := $(shell pwd)
modules:
	$(MAKE) ARCH=arm CROSS_COMPILE=${CCPREFIX} -C ${KERNELDIR} M=$(PWD)
  # Rename .dtb to .dtbo, required by dtoverlay
	mv $(DTB_FILE) $(DTBO_FILE)
modules_install: modules
	scp *.ko *.dtbo root@10.9.8.2:
clean:
	rm -rf *.o *.dtb *.dtbo *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers .*.tmp
.PHONY: default clean
else
    # called from kernel build system: just declare what our modules are
    # Ignore C90 decl after statement warning
    ccflags-y := -DDEBUG -g -std=gnu99 -Wno-declaration-after-statement
    # Device Tree Blobs to build
    always := $(DTB_FILE)
    # Kernel Object target file(s)
    obj-m += $(KMODULE).o
    # If object must be linked from multiple parts
    #xxxxmod-objs := part1.o part2.o
endif