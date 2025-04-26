#!/bin/bash

set -xue

clang \
    -std=c11 \
    -O2 \
    -g3 \
    -Wall \
    -Wextra \
    --target=riscv32-unknown-elf \
    -fno-stack-protector \
    -ffreestanding \
    -nostdlib \
    -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    kernel.c common.c

qemu-system-riscv32 \
    -machine virt \
    -bios default \
    -nographic \
    -serial mon:stdio \
    --no-reboot \
    -kernel kernel.elf
