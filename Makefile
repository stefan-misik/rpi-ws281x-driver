obj-m := ws281x.o
dtbo-y := ws281x.dtbo

dtbo-install = /boot/overlays

KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build

TESTS = pwm_blaster


TEST_BINS = $(addprefix test/,$(TESTS))

all: $(dtbo-y)
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean: clean-test
	make -C $(KERNEL_DIR) M=$(PWD) clean
	$(RM) *.dtbo
	$(RM) $(addprefix test/,$(TESTS))

install:
	cp $(dtbo-y) $(dtbo-install)

uninstall:
	$(RM) $(addprefix $(dtbo-install)/,$(dtbo-y))

clean-test:
	$(RM) $(TEST_BINS)

test: $(TEST_BINS)

%.dtbo: %-overlay.dts
	dtc -@ -Hepapr -I dts -O dtb -o $@ $<

test/%: test/%.c
	$(CC) $< -o $@
	./$@

.PHONY: all clean install uninstall test clean-test

