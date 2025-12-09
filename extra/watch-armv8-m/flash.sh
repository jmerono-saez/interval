#!/bin/sh

source "extra/sh-include.sh"

# === environment setup ===

if test -z $DEBUGGER_PATH; then
    echo -e "${echo_fail}: no DEBUGGER_PATH was specified"
    exit 1
fi

interval_flash_path="${build_path}/interval.hex"

objcopy="/usr/cross/bin/arm-eabi-objcopy"

openocd="$DEBUGGER_PATH/bin/openocd"
openocd_scripts="$DEBUGGER_PATH/share/openocd/scripts"

# === ELF-to-binary conversion ===

${objcopy} ${interval_build_file} -O ihex ${interval_flash_path}

# === board flashing ===

openocd_options="-s \"${openocd_scripts}\""

openocd_options="${openocd_options} -f \"interface/cmsis-dap.cfg\""
openocd_options="${openocd_options} -f \"target/efm32s2_g23.cfg\""

openocd_options="${openocd_options} -c \"init; reset_config srst_nogate; reset halt; program ${interval_flash_path}; reset; exit\""

echo "${openocd} ${openocd_options}"

# TODO: clean this mess!

doas ${openocd} -s ${openocd_scripts} -f interface/cmsis-dap.cfg -f target/efm32s2_g23.cfg -c "init; reset_config srst_nogate; reset halt; program ${interval_flash_path}; reset; exit"
