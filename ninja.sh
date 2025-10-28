#!/bin/sh

source "extra/sh-include.sh"

# === environment setup ===

ninja_file="build.ninja"

# === old file removal ===

if test -e ${ninja_file}; then
    rm ${ninja_file}
fi

# === platform-specific tools and constants ===

cc_options=""
as_options=""
ld_options=""

kernel_modules=""
user_modules=""

if test -z $PLATFORM; then
    echo -e "${echo_fail}: no PLATFORM was specified"
    exit 1
elif test $PLATFORM = "pc-i586"; then
    cc="/usr/cross/bin/i586-pc-elf-gcc"
    as="/usr/cross/bin/i586-pc-elf-as"
    ld="/usr/cross/bin/i586-pc-elf-ld"
    
    cc_options="${cc_options} -D PAGE_BYTES=4096"
    ld_options="${ld_options} -L /usr/cross/lib/gcc/i586-pc-elf/14.3.0"
elif test $PLATFORM = "pc-amd64"; then
    echo -e "${echo_fail}: pc-amd64 is not implemented yet"
    exit 1
elif test $PLATFORM = "watch-armv8-m"; then
    cc="/usr/cross/bin/armv8-none-elf-gcc"
    as="/usr/cross/bin/armv8-none-elf-as"
    ld="/usr/cross/bin/armv8-none-elf-ld"
    
    cc_options="${cc_options} -D PAGE_BYTES=1024"
else
    echo -e "${echo_fail}: an unknown PLATFROM was specified"
    exit 1
fi

cc_options="${cc_options} -ffreestanding"
cc_options="${cc_options} -fdiagnostics-color=always"
cc_options="${cc_options} -I ."
cc_options="${cc_options} -std=c23"
cc_options="${cc_options} -Os"

as_options="${as_options} -fdiagnostics-color=always"

ld_options="${ld_options} -T ${extra_path}/linker.l"
ld_options="${ld_options} -l gcc"

kernel_modules="${kernel_modules} interval"
kernel_modules="${kernel_modules} interval/kernel"
kernel_modules="${kernel_modules} interval/$PLATFORM"

user_modules="${user_modules} interval"
user_modules="${user_modules} programs/<NAME>"

# === tool rule generation ===

echo -e "${echo_note}: using cc='${cc}'"
echo -e "${echo_note}: using cc_options='${cc_options}'"

echo -e "rule cc" >> ${ninja_file}
echo -e "    command = ${cc} ${cc_options} -c \$in -o \$out" >> ${ninja_file}

echo -e "${echo_note}: using 'as=${as}'"
echo -e "${echo_note}: using as_options='${as_options}'"

echo -e "rule as" >> ${ninja_file}
echo -e "    command = ${as} ${as_options} -c \$in -o \$out" >> ${ninja_file}

echo -e "${echo_note}: using ld='${ld}'"
echo -e "${echo_note}: using ld_options='${ld_options}'"

echo -e "rule ld" >> ${ninja_file}
echo -e "    command = ${ld} ${ld_options} \$in -o \$out" >> ${ninja_file}

# === build rule generation (for interval) ===

echo -e "${echo_note}: adding kernel build rules"

objects=""

for module in ${kernel_modules}; do
    echo -e "${echo_note}: adding module '${module}' to kernel build"
    
    mkdir -p "${build_path}/${module}"
    
    for file in ${module}/*.c; do
        if test "$(basename ${file})" = "*.c"; then continue; fi
        
        object="${build_path}/${file%.*}.o"
        objects="${objects} ${object}"
        
        echo -e "build ${object}: cc ${file}" >> ${ninja_file}
    done
    
    for file in ${module}/*.s; do
        if test "$(basename ${file})" = "*.s"; then continue; fi
        
        object="${build_path}/${file%.*}.o"
        objects="${objects} ${object}"
        
        echo -e "build ${object}: as ${file}" >> ${ninja_file}
    done
done

echo -e "${echo_note}: adding kernel linker rule"

echo -e "build ${interval_build_file}: ld ${objects}" >> ${ninja_file}

# === build rule generation (for programs) ===

for program in ${programs_path}/*; do
    if test "$(basename ${program})" = "*"; then continue; fi
    
    objects=""
    
    echo -e "${echo_note}: adding build rules for '${program}'"
    
    for module in ${user_modules/<NAME>/${program}}; do
        echo -e "${echo_note}: adding module '${module}' to build"
        
        mkdir -p "${build_path}/${program}/${module}"
        
        for file in ${module}/*.c; do
            if test "$(basename ${file})" = "*.c"; then continue; fi
            
            object="${build_path}/${file%.*}.o"
            objects="${objects} ${object}"
            
            echo -e "build ${object}: cc ${file}" >> ${ninja_file}
        done
    done
    
    echo -e "${echo_note}: adding linker rule for '${program}'"
    
    # TODO: choose where to save programs
done
