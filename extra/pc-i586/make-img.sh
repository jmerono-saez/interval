#!/bin/sh

source "extra/sh-include.sh"

# === environment setup ===

mount_path=$(mktemp -d -t interval.XXXXXX)

disk_image_file="${build_path}/disk.img"
bios_image_file="/usr/lib/grub/i386-pc/boot_hybrid.img"

grub_image_file="${build_path}/grub.img"
grub_setup_file="${extra_path}/grub.cfg"

# === image creation and partitioning ===

dd if=/dev/zero of=${disk_image_file} count=196608

parts=""

parts="${parts}\nstart=0x0200, type=0xEC, size=0x0800"
parts="${parts}\nstart=0x0A00, type=0x07"

echo -e "${parts}" | sfdisk ${disk_image_file}

# === kernel copying ===

dd if=${interval_build_file} of=${disk_image_file} seek=512 conv=notrunc

# === GRUB image creation and copying ===

grub-mkimage -c ${grub_setup_file} -o ${grub_image_file} -O i386-pc -p / multiboot2 biosdisk part_msdos boot blocklist

dd if=${bios_image_file} of=${disk_image_file} bs=1 count=446 conv=notrunc
dd if=${grub_image_file} of=${disk_image_file} seek=1 conv=notrunc

# === cleanup ===

rm -r -f ${mount_path}
