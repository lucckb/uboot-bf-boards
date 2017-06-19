#!/bin/sh
if [ -e u-boot.bin ]; then
	cp u-boot.bin "/tmp/u-boot.$$"
	stat --printf "U-boot size %sb\n" u-boot.bin
	lzf -cv "/tmp/u-boot.$$"
	stat --printf "U-boot compr size %sb\n" "/tmp/u-boot.$$.lzf"
fi
stty -F /dev/ttyUSB1 pass8 raw speed 115200
sz -X "/tmp/u-boot.$$.lzf" > /dev/ttyUSB1 < /dev/ttyUSB1
rm "/tmp/u-boot.$$.lzf"

