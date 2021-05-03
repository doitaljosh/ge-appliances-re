### About the SBC2 board:

*What is the SBC2 board?*

The SBC2 board is a BeagleBone Black clone developed by GE Appliances that 
drives the smart Linux-based user interface on smart Profile/Cafe/Advantium
wall-ovens and built in convection microwaves. It can boot BBB images,
with a bit of modification.

## Software hierarchy:
* Kernel: Linux 4.14.40-jumpnow
	* Rootfs: Yocto/Buildroot
		* GUI front-end: 
			* Crank StoryBoard/Lua
		* Gea2 back-end: 
			* fifo-based JavaScript JSON API
		* Connected application: 
			* JavaScript/Lua/NodeJS
			* XMPP cloud API to communicate ERD data

Everything is identical to the BBB hardware-wise, except for a few add-ons 
that GE added, in addition to a lack of GPIO headers/HDMI controller.

## Hardware:
* Display
	* SN75LVDS83B TTL to LVDS serializer (7" WSVGA IPS LCD)
	* LED backlight driver
* Audio
	* TAS5713 I2S stereo DAC (only L channel is populated)
* Networking
	* WM-BN-BM-26_A WiFi/Bluetooth SiP based on BCM43438 connected via SDIO/HCI
* Storage
	* 512MB DDR2 RAM
	* 4GB ISSI IS21ES04G eMMC
* Security
	* NXP A71CL secure element
* Connectivity
	* 3x 5V Full-duplex UART and 1x 1.8V debug UART
		* ttyO0 - debug
		* ttyO1 - Left wing GEA2 bus
		* ttyO2 - Right wing GEA2 bus
		* ttyO4 - MC GEA2 bus
	* USB host
	* USB debug
	* Micro SD card slot
	* Mono speaker out
	* I2C touch screen connector
	* LVDS out for LCD panel

### Booting from micro SD card:

## Software modifications:
1. Flash a BeagleBone Black image to an SD card.
2. Using gparted, create a FAT16 partition at the start of the SD card, before the rootfs, and mark it as bootable.
3. Copy the above MLO, and u-boot.img from /opt/backup/uboot in the rootfs to the FAT partition.
4. Copy the above am335x-dorado.dtb to /boot/dtbs/$(uname -r) of the rootfs.
5. Copy the above uEnv.txt to / of the rootfs.
6. Unmount and insert the SD card into the SBC2 board.

## Hardware modifications:
1. Solder a jumper from the middle of R249/R248 footprints near the LCD connector to ground. This is equivalent to pressing the user button on a BBB.

## You should immediately see console messages scrolling across your oven's display upon powering on.
