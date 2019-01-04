#!/bin/bash

ver=v1.3
echo "$ver" > package/base-files/files/etc/sysconfig
cp ~/pupa/src/uart package/base-files/files/sbin/ -v
cp ~/pupa/src/protocol.cgp package/base-files/files/pupa-www/protocol.cgp -v

sleep 1
make V=s

cp bin/ramips/openwrt-ramips-mt7628-mt7628-squashfs-sysupgrade.bin /mnt/hgfs/share/openwrt-ramips-mt7628-mt7628-squashfs-sysupgrade-${ver}.bin -v
