# rpi-ws281x-driver
Linux kernel driver (primarily for Raspberry Pi Zero) for controlling WS281x
LEDs

## Build and Installation
To build and install the module just rune the following commands from within the
root of the repository.

```
sudo apt-get install raspberrypi-kernel-headers
make
sudo make install
```

To enable the module modify the `/boot/config.txt` and add following line:

```
dtoverlay=ws281x
```

## Uninstallation
You can uninstall the module by issuing following command:

```
sudo make uninstall
```

Do not forget to remove the aforementioned line from `/boot/config.txt` file.
