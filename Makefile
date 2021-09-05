obj-m := ws281x.o
dtbo-y := ws281x.dtbo

dtbo-install = /boot/overlays

KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build

all: $(dtbo-y)
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
	$(RM) *.dtbo

install:
	cp $(dtbo-y) $(dtbo-install)

uninstall:
	$(RM) $(addprefix $(dtbo-install)/,$(dtbo-y))

%.dtbo: %-overlay.dts
	dtc -@ -Hepapr -I dts -O dtb -o $@ $<


.PHONY: all clean install uninstall

