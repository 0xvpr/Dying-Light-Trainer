#!/bin/bash

# Creator: VPR
# Created: December 13th, 2021
# Updated: December 13th, 2021

# Gets the required MinGW compiler

set -o pipefail
set -o errexit
set -o nounset

if [[ ! -f .installed ]];
then
    apt update && apt upgrade -y
    apt install -y --no-install-recommends mingw-w64 \
                                           mingw-w64-common \
                                           mingw-w64-i686-dev \
                                           mingw-w64-x86-64-dev \
                                           nasm

else
    printf "install-toolchain.sh has already been ran."
    exit 1
fi

touch .installed
