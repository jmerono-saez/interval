# this file is to be included by ninja.sh and all extra scripts, and
# provides common utilities.

# === environment setup ===

interval_path="interval"
programs_path="programs"

build_path="build/$PLATFORM"
extra_path="extra/$PLATFORM"

interval_build_file="${build_path}/interval.elf"

# === script log setup ===

set -e

echo_note="\e[34mNOTE\e[39m"
echo_fail="\e[41mFAIL\e[49m"

# === folder setup ===

mkdir -p ${build_path}
